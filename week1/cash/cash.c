#include <cs50.h>
#include <stdio.h>

int quarter(int c);
int dime(int c);
int nickel(int c);

int main(void)
{
    int change;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 1);

    // Declare variables
    int qCoins = quarter(change);
    change -= 25 * qCoins;

    int dCoins = dime(change);
    change -= 10 * dCoins;

    int nCoins = nickel(change);
    change -= 5 * nCoins;

    int coins = qCoins + dCoins + nCoins + change;

    printf("%i\n", coins);

    return 0;
}

int quarter(int c)
{
    return c / 25;
}

int dime(int c)
{
    return c / 10;
}

int nickel(int c)
{
    return c / 5;
}
