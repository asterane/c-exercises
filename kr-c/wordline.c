#include <stdio.h>

// copy input to output, one word per line
int main(void)
{
  int c;
  
  while ((c = getchar()) != EOF) {
    if (c == ' ')
      putchar('\n');
    else
      putchar(c);
  }
}
