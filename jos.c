// 4. Write a program to solve the Josephus problem, using an array instead of a
// linked list.

#include <stdio.h>

void jos(int N, int M)
{
   int alive[N];
   for (int i=0; i<N; i++)
      alive[i] = 1;

   int die = 0;
   for (int i=0; i<N; i++) {
      // step around the circle M times (skip the dead)
      for (int j=0; j<M; j++) {
         die = (die + 1) % N;
         while (!alive[die])
            die = (die + 1) % N;
      }

      // kill!
      alive[die] = 0;

      // report who died
      if (die == 0)
         printf("%d ", N);
      else
         printf("%d ", die);
   }
   printf("\n");
}

int main(void)
{
   jos(9, 5);
   return 0;
}
