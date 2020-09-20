#include <stdio.h>

/* print Fahrenheit to Celsius table from
   fahr = 0, 20, ..., 300 (now with floats) */
int main(void)
{
  float fahr, cels;
  int lower, upper, step;

  lower = 0;     // lower temp table limit
  upper = 300;   // upper temp table limit
  step = 20;     // step size

  printf(" F  |   C\n");
  printf("-----------\n");

  fahr = upper;
  while (fahr >= lower) {
    cels = (5.0 / 9.0) * (fahr - 32.0);
    printf("%3.0f |%6.1f\n", fahr, cels);
    fahr = fahr - step;
  }
}
