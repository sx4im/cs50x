from cs50 import get_float

change = 0
coins = 0

while change <= 0:
    change = get_float("Change: ")

def reducer(valueToReduce):
    global change
    global coins
    while (change >= valueToReduce):
        change = round(change - valueToReduce, 10)
        coins += 1

reducer(0.25)
reducer(0.10)
reducer(0.05)
reducer(0.01)

print(coins)
