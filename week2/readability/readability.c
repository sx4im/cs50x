#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{

    string text = get_string("Text: ");

    // Initialize variables for letters, sentences, and words
    int letters = 0;
    int sentences = 0;
    int words = 1;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Count words by spaces
        if (isspace(text[i]))
        {
            words++;
        }
        // Count sentences by periods, question marks, or exclamation points
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
        // Count letters (only alphabetic characters)
        else if (isalpha(text[i]))
        {
            letters++;
        }
    }

    // Calculate the Coleman-Liau index
    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Output the grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
