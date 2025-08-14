// 9. Write a recursive program for solving the Josephus problem (see Chapter 3).

#include <stdio.h>
#include <stdlib.h>

// chapter 3 version (array)
void jos3(int N, int M)
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

/***********************************************************
 * RECURSIVE JOSEPHUS
 ***********************************************************/

struct list {
   int val;
   struct list *next;
};

void josrec(struct list *l, int M)
{
   // check if only one item remains
   if (l == l->next) {
      printf("%d ", l->val);
      free(l);
      return;
   }

   // go around the list M-1 times
   for (int i=0; i < M - 1; i++)
      l = l->next;

   // remove the next element from the list
   struct list *dead = l->next;
   printf("%d ", dead->val);
   l->next = dead->next;
   free(dead);

   // repeat, recursively
   josrec(l, M);
}

// chapter 5 (recursion)
void jos5(int N, int M)
{
   // allocate an arary of list nodes
   struct list *l[N];
   for (int i=0; i<N; i++)
      l[i] = malloc(sizeof(struct list));

   // create circular list of everyone
   for (int i=0; i<N; i++) {
      l[i]->val = i + 1;
      if (i < N - 1)
         l[i]->next = l[i + 1];
      else
         l[i]->next = l[0];
   }

   // start the recursive procedure
   josrec(l[N - 1], M);

   printf("\n");
}

int main(void)
{
   jos3(9, 5);
   jos5(9, 5);
   return 0;
}
