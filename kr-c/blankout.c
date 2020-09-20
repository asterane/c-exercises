#include <stdio.h>

// copy input to output; remove extra blanks
int main(void)
{
    int c, last;
  
    while ((c = getchar()) != EOF) {
        if (c == ' ' && last == ' ')
            continue;

        last = c;
        putchar(c);
    }
}
