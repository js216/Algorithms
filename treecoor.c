// 4. Give the coordinates produced when the recursive tree-drawing procedure
// given in the text is applied to the binary tree in Figure 4.2.

#include <stdio.h>
#include <stdlib.h>

int x;
int y;

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
   int x;
   int y;
   struct tree *l;
   struct tree *r;
};

struct tree *nn(char val, struct tree *l, struct tree *r)
{
    struct tree *n = malloc(sizeof(*n));
    n->val = val;
    n->l = l;
    n->r = r;
    return n;
}

void visit(struct tree *t)
{
   t->x = ++x;
   t->y = y;

   printf("Node('%c'), x=%d, y=%d\n", t->val, x, y);
}

void traverse(struct tree *t)
{
   y++;
   if (t != NULL)
   {
      traverse(t->l);
      visit (t);
      traverse(t->r);
   }
   y--;
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

int main(void)
{
   struct tree *t = build_4_2();

   x = 0;
   y = 0;
   traverse(t);

   return 0;
}
