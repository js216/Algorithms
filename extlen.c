// 2. Write a recursive program to compute the external path length of a binary
// treе.

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

void ext_len(struct tree *t, int n)
{
   if (t == NULL)
      return;

   // external node: count its path length
   if ((t->l == NULL) && (t->r == NULL)) {
      len += n;
      return;
   }

   // internal node: traverse it
   ext_len(t->l, n+1);
   ext_len(t->r, n+1);
}

/***********************************************************
 * USAGE & TESTING
 ***********************************************************/

struct tree* simple(void)
{
   return nn('R',
         nn('A',
            nn('a', NULL, NULL),
            nn('b', NULL, NULL)),
         nn('B',
            nn('1', NULL, NULL),
            nn('2', NULL, NULL))
   );
}

int main(void)
{
   len = 0;
   ext_len(simple(), 0);
   printf("%d\r\n", len);
   return 0;
}
