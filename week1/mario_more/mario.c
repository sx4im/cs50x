#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    do
    {
        printf("Height: ");
        scanf("%d", &height);
    }
    while (height < 1 || height > 8);

    int i, j, k, l;

    for (i = 0; i < height; i++)
    {
        for (j = height; j > (i + 1); j--)
        {
            printf(" ");
        }
        for (k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("  ");
        for (l = 0; l < i + 1; l++)
        {
            printf("#");
        }
        printf("\n");
    }

    return 0;
}
