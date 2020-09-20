#include <stdio.h>
#include <cs50.h>

void make_pyramid(int n);

// get valid height from user and call pyramid generator
int main(void)
{
    int height;

    // keeps user from being difficult
    do
    {
        height = get_int("Enter pyramid height (1-8, inclusive): ");
    }
    while (height < 1 || height > 8);

    make_pyramid(height);
}

// generate pyramid of given height to specification
void make_pyramid(int n)
{
    for (int i = 0; i < n; i++)
    {
        // centering
        for (int j = 0; j < n - (i + 1); j++)
        {
            printf(" ");
        }

        // left side
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // middle
        printf("  ");

        // right side
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // end layer
        printf("\n");
    }
}