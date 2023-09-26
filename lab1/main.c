#include <math.h>
#include <stdio.h>
float F(float a, float b, float c, float x) {
  float res;

  if ((b - a) < 0 && c == 0) {
    res = (1 + x) / (x - cos(c)) - b / a;
  } else if ((b - a) > 0 && c != 0) {
    res = (a - b * x) / log(x);
  } else {
    res = (10 * x + 2) / (c * c - 6 - b);
  }

  return res;
}

void while_loop(float a, float b, float c, float x1, float x2, float px) {
  int n = 0;
  float x = x1;
  while (x < x2) {
    n++;
    float res = F(a, b, c, x);
    printf("%i: x = %.3f\tF = %.3f\n", n, x, res);
    x += px;
  }
}

void do_while(float a, float b, float c, float x1, float x2, float px) {
  int n = 0;
  float x = x1;
  do {
    n++;
    float res = F(a, b, c, x);
    printf("%i: x = %.3f\tF = %.3f\n", n, x, res);
    x += px;
  } while (x < x2);
}

void go_to(float a, float b, float c, float x1, float x2, float px) {
  int n = 0;
  float x = x1;
loop:
  n++;
  float res = F(a, b, c, x);
  printf("%i: x = %.3f\tF = %.3f\n", n, x, res);
  x += px;
  if (x < x2)
    goto loop;
}

void for_loop(float a, float b, float c, float x1, float x2, float px) {
  float x = x1;
  for (int i = 1; x < x2; i++) {
    float res = F(a, b, c, x);
    printf("%i: x = %.3f\tF = %.3f\n", i, x, res);
    x += px;
  }
}

int main() {
  float x1, x2, px, a, b, c;

  printf("Input x1, x2, px:\n");
  scanf("%f %f %f", &x1, &x2, &px);

  printf("Input a, b, c:\n");
  scanf("%f %f %f", &a, &b, &c);

  printf("          Results :\n");
  printf("\nwhile:\n");
  while_loop(a, b, c, x1, x2, px);
  printf("\ndo while:\n");
  do_while(a, b, c, x1, x2, px);
  printf("\ngoto:\n");
  go_to(a, b, c, x1, x2, px);
  printf("\nfor_loop:\n");
  for_loop(a, b, c, x1, x2, px);
}
