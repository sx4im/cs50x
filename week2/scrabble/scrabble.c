#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Take input from two users
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    // Declare variables to store the points for both users
    int score1 = 0;
    int score2 = 0;

    // Array containing points for each alphabet
    int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    // Calculate points for Player 1
    int n = strlen(player1);
    for (int i = 0; i < n; i++)
    {
        if (isalpha(player1[i]))
        {
            char c = toupper(player1[i]);
            score1 += points[c - 65];
        }
    }

    // Calculate points for Player 2
    n = strlen(player2);
    for (int i = 0; i < n; i++)
    {
        if (isalpha(player2[i]))
        {
            char c = toupper(player2[i]);
            score2 += points[c - 65];
        }
    }

    // Determine the winner or tie
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}