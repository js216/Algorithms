// 10. Write a recursive implementation of Euclid's algorithm (see Chapter 1).

#include <stdio.h>

// chapter 1 version
int gcd1(int u, int v)
{
   if (v == 0)
      return u;

   while (u > 0) {
      if (u < v) {
         int t = u;
         u = v;
         v = t;
      }
      u = u-v;
   }

   return v;
}

// recursive version
int gcd2(int u, int v)
{
   if (u <= 0)
      return v;

   if (v == 0)
      return u;

   if (u < v) {
      int t = u;
      u = v;
      v = t;
   }
   u = u - v;

   return gcd2(u, v);
}

int main()
{
   printf("%d\n", gcd1(32143252, 4224));
   printf("%d\n", gcd2(32143252, 4224));

   const int max = 1000;
   for (int i=0; i<max; i++)
      for (int j=0; j<max; j++)
         if (gcd1(i,j) != gcd2(i,j)) {
            printf("error: %d, %d\n", i, j);
            return -1;
         }

   return 0;
}
