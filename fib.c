// 5. Mechanically remove the recursion from the fibonacci program given in the
// text to get a nonrecursive implementation.

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

enum state {
   ENTRY,
   FIRST_CALL,
   SECOND_CALL,
};

struct frame {
   int N;   // function argument
   int n1;  // function local variable
   int ret; // value returned from function
   int lr;  // "link register": where to resume execution
};

struct frame stack_mem[STACK_MAX];
int sp;

void stack_push(struct frame f)
{
   if (sp >= STACK_MAX)
      error("stack overflow");
   stack_mem[sp] = f;
   sp = sp + 1;
}


struct frame stack_pop(void)
{
   if (sp <= 0)
      error("stack underflow");
   sp = sp - 1;
   return stack_mem[sp];
}

struct frame* stack_peek(void)
{
   if (sp <= 0)
      error("stack empty");
   return &stack_mem[sp - 1];
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
 * FIBONACCI FUNCTIONS
 ***********************************************************/

int fib1(int N)
{
   if (N <= 1)
      return 1;
   return fib1(N-1) + fib1(N-2);
}

// claude.ai (modified)
int fib2(int N)
{
   struct frame* current;
   int return_value;

   stack_reset();

   stack_push((struct frame){N, 0, 0, ENTRY});

descend:
   current = stack_peek();

   if (current->lr == ENTRY) {
      if (current->N <= 1) {
         current->ret = 1;
         goto done;
      }
      current->lr = FIRST_CALL;
      stack_push((struct frame){.N=current->N - 1, .n1=0, .ret=0, .lr=ENTRY});
      goto descend;

   }

   else if (current->lr == FIRST_CALL) {
      current->lr = SECOND_CALL;
      stack_push((struct frame){.N=current->N - 2, .n1=0, .ret=0, .lr=ENTRY});
      goto descend;
   }

   else if (current->lr == SECOND_CALL) {
      current->ret = current->n1 + current->ret;
   }

   else {
      error("invalid link register");
   }

done:
   return_value = current->ret;
   stack_pop();

   if (!stack_empty()) {
      struct frame* parent = stack_peek();
      if (parent->lr == FIRST_CALL) {
         parent->n1 = return_value;
      } else if (parent->lr == SECOND_CALL) {
         parent->ret = return_value;
      }
   } else {
      return return_value;
   }
   goto descend;

   error("should not reach here");
   return 0;
}

// claude.ai (second attempt, modified)
int fib3(int N)
{
   struct frame* top;
   stack_reset();
   stack_push((struct frame){N, 0, 0, ENTRY});

descend:
   if (stack_empty())
      error("did not expect empty stack");

   top = stack_peek();

   if (top->lr == ENTRY) {
      if (top->N <= 1) {
         top->ret = 1;
      } else {
         top->lr = FIRST_CALL;
         stack_push((struct frame){top->N - 1, 0, 0, ENTRY});
         goto descend;
      }
   }

   else if (top->lr == FIRST_CALL) {
      top->n1 = top->ret;
      top->lr = SECOND_CALL;
      stack_push((struct frame){top->N - 2, 0, 0, ENTRY});
      goto descend;
   }

   else if (top->lr == SECOND_CALL) {
      top->ret = top->n1 + top->ret;
   }

   int result = top->ret;

   stack_pop();
   if (stack_empty())
      return result;

   stack_peek()->ret = result;
   goto descend;

   return 0;
}

// rewritten from memory
int fib4(int N)
{
   struct frame *f;
   stack_reset();
   stack_push((struct frame){N, 0, 0, ENTRY});

descend:
   f = stack_peek();

   if (f->lr == ENTRY) {
      if (f->N <= 1) {
         f->ret = 1;
      } else {
         f->lr = FIRST_CALL;
         stack_push((struct frame){f->N - 1, 0, 0, ENTRY});
         goto descend;
      }
   }

   // after the first recursive call
   else if (f->lr == FIRST_CALL) {
      f->n1 = f->ret;
      f->lr = SECOND_CALL;
      stack_push((struct frame){f->N - 2, 0, 0, ENTRY});
      goto descend;
   }

   // after the second recursive call
   else if (f->lr == SECOND_CALL) {
      f->ret = f->n1 + f->ret;
   }

   else {
      error("invalid link register");
   }

   // we're done when there's nothing left on the stack
   int result = f->ret;
   stack_pop();
   if (stack_empty())
      return result;

   // when there's still frames left on the stack, carry the return value to the
   // frame below the one just popped
   stack_peek()->ret = result;

   goto descend;

   error("never reached");
   return 0;
}

/***********************************************************
 * TESTING
 ***********************************************************/

void test(int (*f)(int))
{
   for (int i=0; i<15; i++)
      printf("%d ", f(i));

   printf("\n");
}

int main(void)
{
   test(fib1);
   test(fib2);
   test(fib3);
   test(fib4);

   return 0;
}
