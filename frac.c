// 3. Implement a procedure to reduce a given fraction to lowest terms, using
// struct fraction { int numerator; int denominator; }

#include <stdio.h>

struct frac {
   int num;
   int den;
};

int gcd(int u, int v)
{
   int t;
   while (u > 0)
   {
      if (u < v)
      { t = u; u = v; v = t; }
      u = u-v;
   }
   return v;
}

struct frac reduce(int u, int v)
{
   const int g = gcd(u, v);
   return (struct frac){u/g, v/g};
}

int main()
{
   int x, y;
   while (scanf("%d %d", &x, &y) != EOF) {
      struct frac r = reduce(x, y);
      printf("%d %d\n", r.num, r.den);
   }
}
