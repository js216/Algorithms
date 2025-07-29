// 1. Write a program to fill in a two-dimensional array of boolean values by
// setting a[i} [j] to 1 if the greatest common divisor of i and j is 1 and to 0
// otherwise.

#include <stdio.h>

#define ARR_SZ 25

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

void fill(int a[ARR_SZ][ARR_SZ])
{
   for (int i=1; i<ARR_SZ; i++)
      for (int j=1; j<ARR_SZ; j++)
         a[i][j] = (gcd(i, j) == 1);
}

void print(int a[ARR_SZ][ARR_SZ])
{
   for (int i=1; i<ARR_SZ; i++) {
      printf("a[%2d] = ", i);
      for (int j=1; j<ARR_SZ; j++)
         printf("%d", a[i][j]);
      printf("\n");
   }
}

int main()
{
   int a[ARR_SZ][ARR_SZ];
   fill(a);
   print(a);
}
