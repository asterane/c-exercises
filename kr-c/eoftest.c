#include <stdio.h>

int main(void)
{
  printf("%d\n", (int) EOF);
  printf("%d\n", getchar() != EOF);
}
