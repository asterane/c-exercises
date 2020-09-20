#include <stdio.h>

/* print Celsius to Fahrenheit table from
   cels = 0, 20, ..., 300 (with floats) */
int main(void)
{
  float cels, fahr;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  printf(" C  |  F\n");
  printf("-----------\n");

  cels = lower;
  while (cels <= upper) {
    fahr = 32.0 + (9.0 / 5.0) * cels;
    printf("%3.0f |%6.1f\n", cels, fahr);
    cels = cels + step;
  }
}
