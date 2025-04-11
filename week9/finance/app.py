import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    user_id = session["user_id"]

    # Get all the stocks the user owns
    rows = db.execute("""
        SELECT symbol, SUM(shares) as total_shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING total_shares > 0
    """, user_id)

    holdings = []
    total_value = 0

    for row in rows:
        stock = lookup(row["symbol"])
        total = stock["price"] * row["total_shares"]
        total_value += total
        holdings.append({
            "symbol": row["symbol"],
            "name": stock["name"],
            "shares": row["total_shares"],
            "price": usd(stock["price"]),
            "total": usd(total)
        })

    # Get user's cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    total_value += cash

    return render_template("index.html", holdings=holdings, cash=usd(cash), total=usd(total_value))



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol", 400)

        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)

        # Validate shares is a positive integer
        try:
            shares = int(shares)
            if shares <= 0:
                return apology("shares must be positive", 400)
        except:
            return apology("invalid shares", 400)

        # Check user’s cash
        user_id = session["user_id"]
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        total_price = stock["price"] * shares

        if user_cash < total_price:
            return apology("can't afford", 400)

        # Subtract from user's cash
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_price, user_id)

        # Log the transaction
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            user_id, symbol, shares, stock["price"]
        )

        return redirect("/")

    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    user_id = session["user_id"]

    transactions = db.execute("""
        SELECT symbol, shares, price, transacted
        FROM transactions
        WHERE user_id = ?
        ORDER BY transacted DESC
    """, user_id)

    return render_template("history.html", transactions=transactions)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)

        stock = lookup(symbol.upper())
        if not stock:
            return apology("invalid symbol", 400)

        return render_template("quoted.html", name=stock["name"], symbol=stock["symbol"], price=stock["price"])

    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 400)
        if not password:
            return apology("must provide password", 400)
        if password != confirmation:
            return apology("passwords do not match", 400)

        hash_pw = generate_password_hash(password)

        try:
            new_user_id = db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)",
                username, hash_pw
            )
        except:
            return apology("username already exists", 400)

        session["user_id"] = new_user_id
        return redirect("/")

    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user_id = session["user_id"]

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("must select a stock to sell", 400)

        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("invalid number of shares", 400)

        shares = int(shares)

        # Get current number of shares owned
        result = db.execute("""
            SELECT SUM(shares) as total_shares FROM transactions
            WHERE user_id = ? AND symbol = ?
            GROUP BY symbol
        """, user_id, symbol)

        if not result or result[0]["total_shares"] < shares:
            return apology("too many shares", 400)

        stock = lookup(symbol)
        total_price = shares * stock["price"]

        # Add cash to user
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_price, user_id)

        # Record transaction as a negative "sell"
        db.execute("""
            INSERT INTO transactions (user_id, symbol, shares, price)
            VALUES (?, ?, ?, ?)
        """, user_id, symbol, -shares, stock["price"])

        return redirect("/")

    else:
        # Get list of stocks user owns
        rows = db.execute("""
            SELECT symbol FROM transactions
            WHERE user_id = ?
            GROUP BY symbol
            HAVING SUM(shares) > 0
        """, user_id)

        symbols = [row["symbol"] for row in rows]
        return render_template("sell.html", symbols=symbols)

