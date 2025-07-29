// 9. Find the largest pair of numbers representable as integers in your C
// system whose greatest common divisor is 1.

#include <stdio.h>

int main()
{
   int m = 2;
   int n = 1;

   int mp=m, np=n;

   for (;;) {
      // Calkin–Wilf tree
      m = mp + np;
      n = mp;

      if ((m<0) || (n<0)) {
         printf("%d %d\n", mp, np);
         return 0;
      }

      mp = m;
      np = n;
   }
}
