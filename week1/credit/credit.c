#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    long card;
    do
    {
        card = get_long("Number: ");
    }
    while (card < 0);

    long temp_card = card;
    int length = 0;
    while (temp_card > 0)
    {
        temp_card /= 10;
        length++;
    }

    int sum1 = 0;
    int sum2 = 0;
    temp_card = card;

    for (int i = 1; temp_card > 0; i++)
    {
        int digit = temp_card % 10;
        if (i % 2 == 0)
        {
            digit *= 2;
            if (digit > 9)
            {
                sum2 += digit % 10 + digit / 10;
            }
            else
            {
                sum2 += digit;
            }
        }
        else
        {
            sum1 += digit;
        }
        temp_card /= 10;
    }

    if ((sum1 + sum2) % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    long first_digit = 0;
    long first_two_digits = 0;

    if (length == 13)
    {
        first_digit = card / 1000000000000;
    }
    else if (length == 15)
    {
        first_two_digits = card / 10000000000000;
    }
    else if (length == 16)
    {
        first_digit = card / 1000000000000000;
        first_two_digits = card / 100000000000000;
    }

    if ((length == 13 || length == 16) && first_digit == 4)
    {
        printf("VISA\n");
    }
    else if (length == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && first_two_digits >= 51 && first_two_digits <= 55)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}
