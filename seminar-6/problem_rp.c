#include <assert.h>
#include <fenv.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct frep
{
  unsigned exp;
  unsigned frac;
};

struct frep
as_frep (float f)
{
  struct frep res;
  // TODO: your code here
  res.exp = (*(unsigned *) &f) >> 23;
  res.exp = res.exp & 0b011111111;
  res.frac = (*(unsigned *) &f) & 0x7fffff;
  return res;
}

int
main ()
{
  // TODO: input 2 numbers: x, y
  float x, y;
  int check = scanf ("%f%f", &x, &y);
  assert (check == 2);

  fesetround (FE_DOWNWARD);
  check = fegetround();
  switch (check)
    {
    case FE_UPWARD:
      printf ("FE_UPWARD\n"); break;
    case FE_DOWNWARD:
      printf ("FE_DOWNWARD\n"); break;
    case FE_TONEAREST:
      printf ("FE_TONEAREST\n"); break;
    case FE_TOWARDZERO:
      printf ("FE_TOWARDZERO\n"); break;
    default:
      printf ("unknown\n");
    };


  // output 4 numbers: explow, fraclow, exphigh, frachigh
  unsigned explow, fraclow, exphigh, frachigh;
  float approx = x / y;
  float approx_check = approx * y;
  if (approx_check == x)
    {
      struct frep p = as_frep (approx);
      explow = p.exp;
      fraclow = p.frac;
      exphigh = p.exp;
      frachigh = p.frac;
    }

  if (approx_check > x)
    {
      struct frep p2 = as_frep (approx);
      struct frep p1 = { p2.exp, p2.frac - 1 };
      explow = p1.exp;
      fraclow = p1.frac;
      exphigh = p1.exp;
      frachigh = p2.frac;
    }

  if (approx_check < x)
    {
      struct frep p1 = as_frep (approx);
      struct frep p2 = { p1.exp, p1.frac + 1 };
      explow = p1.exp;
      fraclow = p1.frac;
      exphigh = p1.exp;
      frachigh = p2.frac;
    }

  printf ("x / y = %f; (x / y) * y = %f\n", approx, approx_check);
  printf ("0x%x 0x%x 0x%x 0x%x\n", explow, fraclow, exphigh, frachigh);
}
