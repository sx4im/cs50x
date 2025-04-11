#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check if the key is a number
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert key to integer
    int key = atoi(argv[1]);

    // Get plaintext from user
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    // Encrypt plaintext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                printf("%c", (plaintext[i] - 'A' + key) % 26 + 'A');
            }
            else
            {
                printf("%c", (plaintext[i] - 'a' + key) % 26 + 'a');
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}
