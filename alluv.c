// 6. Give all the values that u and v take on when ged is invoked with the initial
// call gcd (12345, 56789).

#include <stdio.h>

int gcd(int u, int v)
{
   int t;
   while (u > 0) {
      printf("u=%d, v=%d\n", u, v);
      if (u < v) {
         t = u;
         u = v;
         v = t;
      }
      u = u-v;
   }
   return v;
}

int main()
{
   gcd(12345, 56789);
}
