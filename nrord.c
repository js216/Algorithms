#include <stdio.h>
#include <stdlib.h>

void error(const char *const msg)
{
   fprintf(stderr, "Error: ");
   fprintf(stderr, "%s\n", msg);
   exit(-1);
}

/***********************************************************
 * TREE IMPLEMENTATION
 ***********************************************************/

struct tree {
   char val;
   struct tree *l;
   struct tree *r;
};

struct tree *nn(char val, struct tree *l, struct tree *r)
{
    struct tree *n = malloc(sizeof(*n));
    if (n == NULL)
       error("cannot malloc");
    n->val = val;
    n->l = l;
    n->r = r;
    return n;
}

void visit(struct tree *t)
{
   printf("%c ", t->val);
}

void in_rec(struct tree *t)
{
   if (t->l)
      in_rec(t->l);
   visit(t);
   if (t->r)
      in_rec(t->r);
}

void post_rec(struct tree *t)
{
   if (t->l)
      post_rec(t->l);
   if (t->r)
      post_rec(t->r);
   visit(t);
}

/***********************************************************
 * FRAME STACK IMPLEMENTATION
 ***********************************************************/

#define STACK_DEPTH 1000

enum state {
   ENTRY,
   FIRST_CALL,
   SECOND_CALL,
};

struct frame {
   // arguments & local variables
   struct tree *t;

   // link register
   int lr;
};

int sp;
struct frame stack_data[STACK_DEPTH];

void stack_reset(void)
{
   sp = 0;
}

int stack_empty(void)
{
   return sp == 0;
}

void stack_push(struct frame f)
{
   stack_data[sp] = f;
   sp++;
}

void stack_pop(void)
{
   if (stack_empty())
      error("cannot pop from empty stack");
   sp--;
}

struct frame* stack_peek(void)
{
   if (stack_empty())
      error("cannot peek into empty stack");
   return &stack_data[sp - 1];
}

/***********************************************************
 * RECURSION REMOVED
 ***********************************************************/

// 6. Mechanically remove the recursion from the recursive inorder tree
// traversal algorithm to get a nonrecursive implementation.
void in_nonrec(struct tree *t)
{
   if (t == NULL)
      error("null root given");

   stack_push((struct frame){.t=t, .lr=ENTRY});
   struct frame *f;

descend:
   f = stack_peek();

   if (f->lr == ENTRY) {
      f->lr = FIRST_CALL;
      if (f->t->l) {
         stack_push((struct frame){.t=f->t->l, .lr=ENTRY});
         goto descend;
      }
   }

   if (f->lr == FIRST_CALL) {
      visit(f->t);
      f->lr = SECOND_CALL;

      if (f->t->r) {
         stack_push((struct frame){.t=f->t->r, .lr=ENTRY});
         goto descend;
      }
   }

   stack_pop();
   if (stack_empty())
      return;
   goto descend;

   error("never reached");
   return;
}

// 7. Mechanically remove the recursion from the recursive postorder tree
// traversal algorithm to get a nonrecursive implementation.
void post_nonrec(struct tree *t)
{
   if (t == NULL)
      error("null root given");

   stack_push((struct frame){.t=t, .lr=ENTRY});
   struct frame *f;

descend:
   f = stack_peek();

   if (f->lr == ENTRY) {
      f->lr = FIRST_CALL;
      if (f->t->l) {
         stack_push((struct frame){.t=f->t->l, .lr=ENTRY});
         goto descend;
      }
   }

   if (f->lr == FIRST_CALL) {
      f->lr = SECOND_CALL;

      if (f->t->r) {
         stack_push((struct frame){.t=f->t->r, .lr=ENTRY});
         goto descend;
      }
   }

   if (f->lr == SECOND_CALL) {
      visit(f->t);
   }

   stack_pop();
   if (stack_empty())
      return;
   goto descend;

   error("never reached");
   return;
}

/***********************************************************
 * USAGE & TESTING
 ***********************************************************/

struct tree* build_4_2(void)
{
   return nn('P',

      nn('M',
         nn('S',
            nn('A', NULL, NULL),
            nn('A', NULL, NULL)),
         NULL),

      nn('L',
         NULL,
         nn('E',
            NULL,
            nn('R',
               nn('T', NULL, NULL),
               nn('E',
                  nn('E', NULL, NULL),
                  NULL))))
   );
}

struct tree* build_4_3(void)
{
   return nn('E',

      nn('O',
         nn(' ',
            nn('A', NULL, NULL),
            nn('C', NULL, NULL)),
         nn('P',
            nn('M', NULL, NULL),
            nn('L', NULL, NULL))),

      nn('T',
         nn('E',
            nn('T', NULL, NULL),
            nn(' ', NULL, NULL)),
         nn('E',
            nn('R', NULL, NULL),
            nn('E', NULL, NULL)))
   );
}

struct tree* build_4_8(void)
{
   return nn('E',

      nn('A',
         nn('A',
            NULL,
            nn('S', NULL, NULL)),

         nn('R',
            nn('T',
               nn('M', NULL,
                  nn('P', NULL,
                     nn('L', NULL,
                        nn('E', NULL, NULL)))),
               NULL),
            nn('E', NULL, NULL))),

      NULL
   );
}

void all_orders(struct tree *t)
{
   printf("In (rec):       ");
   in_rec(t);

   printf("\nIn (non-rec):   ");
   in_nonrec(t);

   printf("\n\nPost (rec):     ");
   post_rec(t);

   printf("\nPost (non-rec): ");
   post_nonrec(t);

   printf("\n");
}

int main(void)
{
   printf("Tree from Fig. 4.2:\n========================================\n");
   all_orders(build_4_2());

   printf("\nTree from Fig. 4.3:\n========================================\n");
   all_orders(build_4_3());

   printf("\n");

   return 0;
}
