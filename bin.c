// 5. Write a function binary(int x) that prints out the binary equivalent of a
// number.

#include <stdio.h>

void binary(int x)
{
   while (x) {
      printf("%d", x & 1);
      x = x >> 1;
   }
   printf("\n");
}

int main()
{
   binary(128);
}
