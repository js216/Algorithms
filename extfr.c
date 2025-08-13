// 3. Write a recursive program to compute the external path length of a tree
// represented as a binary tree.

#include <stdio.h>
#include <stdlib.h>

int len;

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
    n->val = val;
    n->l = l;
    n->r = r;
    return n;
}

void extfr_len(struct tree *t, int n)
{
   if (t == NULL)
      return;

   // external node: count its path length
   if (t->l == NULL) {
      printf("ext node %c, depth %d\n", t->val, n);
      len += n;
   }

   // internal node: traverse it
   extfr_len(t->l, n+1);
   extfr_len(t->r, n);
}

/***********************************************************
 * USAGE & TESTING
 ***********************************************************/

struct tree* draw_4_8(void)
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

int main(void)
{
   len = 0;
   extfr_len(draw_4_8(), 0);
   printf("Total external length: %d\r\n", len);
   return 0;
}
