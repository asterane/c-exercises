#include <stdio.h>

// count blanks, tabs, lines in input
int main(void)
{
    int c, nb, nt, nl;

    nb = 0;
    nt = 0;
    nl = 0;
  
    while ((c = getchar()) != EOF) {
        if (c == ' ')
            ++nb;
        if (c == '\t')
            ++nt;
        if (c == '\n')
            ++nl;
    }
  
    printf("Blanks: %d\n", nb);
    printf("Tabs: %d\n", nt);
    printf("Lines: %d\n", nl);
}
