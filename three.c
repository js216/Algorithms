// 8. Write a program to compute the greatest common divisor of three integers
// u, v, and w.

#include <stdio.h>

int gcd(int u, int v)
{
   int t;
   while (u > 0) {
      if (u < v) {
         t = u;
         u = v;
         v = t;
      }
      u = u-v;
   }
   return v;
}

int gcd3(int u, int v, int w)
{
   return gcd(gcd(u, v), w);
}

int main()
{
   printf("%d\n", gcd3(9, 3, 3));
}
