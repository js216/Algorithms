// 1. Write a recursive program to draw a binary tree so that the root appears
// at the center of the page, the root of the left subtree is at the center of
// the left half of the page, etc.

#include <stdio.h>
#include <stdlib.h>

#define NCOL 80
#define NROW 20

char page[NROW][NCOL];

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

void set_pixel(struct tree *t, double x, int y)
{
   if (t == NULL)
      return;

   const unsigned int ix = ((x + 1.0) / 2.0) * (NCOL - 1);
   const unsigned int iy = y;

   if (ix >= NCOL)
      error("x out of range");

   if (iy >= NROW)
      error("y out of range");

   if (page[iy][ix] != '\0')
      error("pixel already occupied");

   page[iy][ix] = t->val;
}

void render_tree(struct tree *t, double x0, double x1, int y)
{
   if (t != NULL) {
      const double c = (x0 + x1)/2;
      set_pixel(t, c, y);
      render_tree(t->l, x0, c, y+1);
      render_tree(t->r, c, x1, y+1);
   }
}

void clear_page(void)
{
   for (int i=0; i<NROW; i++)
      for (int j=0; j<NCOL; j++)
         page[i][j] = '\0';
}

void print_page(void)
{
   for (int i=0; i<NROW; i++) {
      for (int j=0; j<NCOL; j++)
         printf("%c", (page[i][j] == '\0') ? ' ' : page[i][j]);
      printf("\n");
   }
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
   clear_page();
   struct tree *t = simple();

   render_tree(t, -1, 1, 0);
   print_page();

   return 0;
}
