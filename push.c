// 6. Write procedures for a linked list implementation of pushdown stacks, but
// using parallel arrays.

#include <stdio.h>

#define MAX 100

int key[MAX+2], next [MAX+2];
int x, head, z;

void listinitialize(void)
{
   head = 0;
   z = 1;
   x = 2;
   next[head] = z;
   next[z] = z;
}

void deletenext(int t)
{
   next[t] = next[next[t]];
}

int insertafter(int v, int t)
{
   key[x] = v;
   next[x] = next[t];
   next[t] = x;
   return x++;
}

void printfrom(int t)
{
   while (next[t] != t) {
      printf("%d\n", key[t]);
      t = next[t];
   }
}

void push(int v)
{
   insertafter(v, head);
}

int pop(void)
{
   int x = key[next[head]];
   deletenext(head);
   return x;
}

int main(void)
{
   int x;
   listinitialize();

   push(1);
   push(2);
   push(3);
   push(4);
   printf("pop() gives %0d\n", pop());

   printfrom(head);

   return 0;
}
