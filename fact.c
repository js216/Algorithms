// Mechanically remove recursion from the recursive factorial program.

#include <stdio.h>
#include <stdlib.h>

void error(const char *const msg)
{
   fprintf(stderr, "Error: ");
   fprintf(stderr, "%s\n", msg);
   exit(-1);
}

/***********************************************************
 * STACK IMPLEMENTATION
 ***********************************************************/

#define STACK_MAX 1024

int stack_mem[STACK_MAX];
int sp;

void stack_push(int v)
{
   if (sp >= STACK_MAX)
      error("stack overflow");
   stack_mem[sp] = v;
   sp = sp + 1;
}


int stack_pop(void)
{
   if (sp <= 0)
      error("stack underflow");
   sp = sp - 1;
   return stack_mem[sp];
}

int stack_empty(void)
{
   if (sp == 0) {
      return 1;
   }
   return 0;
}

void stack_reset(void)
{
   sp = 0;
}

/***********************************************************
 * FACTORIAL FUNCTIONS
 ***********************************************************/

int fact_rec(int N)
{
   if (N == 0)
      return 1;
   return N * fact_rec(N - 1);
}

int fact_norec(int N)
{
   int acc;
   stack_reset();

descend:
   if (N == 0) {
      acc = 1;
      goto unwind;
   }
   stack_push(N);
   N = N - 1;
   goto descend;

unwind:
   while (!stack_empty())
      acc *= stack_pop();

   return acc;
}

/***********************************************************
 * TESTING
 ***********************************************************/

int main(void)
{
   printf("%d\r\n", fact_rec(7));
   printf("%d\r\n", fact_norec(7));
   return 0;
}
