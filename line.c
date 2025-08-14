// 8. Write a recursive "divide-and-conquer" program to draw an approximation to
// the line segment connecting two points (x1, y1) and (x2, y2) by drawing
// points using only integer coordinates. (Hint: first draw a point close to the
// middle.)

#include <stdio.h>
#include <stdlib.h>

#define SZ 25

int page[SZ][SZ];

void error(const char *const msg)
{
   fprintf(stderr, "Error: ");
   fprintf(stderr, "%s\n", msg);
   exit(-1);
}

void point(int x, int y)
{
   page[x][y] = 1;
}

void draw(int x1, int y1, int x2, int y2)
{
   if ((x1 < 0) || (y1 < 0) || (x2 < 0) || (y2 < 0))
      error("negative coordinates not supported");

   if ((x1 >= SZ) || (y1 >= SZ) || (x2 >= SZ) || (y2 >= SZ))
      error("point outside of page");

   int mx = (x1 + x2) / 2;
   int my = (y1 + y2) / 2;

   if ((mx == x1) && (my == y1))
      return;

   if ((mx == x2) && (my == y2))
      return;

   point(mx, my);

   draw(x1, y1, mx, my);
   draw(mx, my, x2, y2);
}

void print_page(void)
{
   for (int j=0; j<SZ; j++) {
      for (int i=0; i<SZ; i++)
         printf("%c", page[i][j] ? '*' : ' ');
      printf("\n");
   }
}

int main(void)
{
   draw(0, 0, SZ-1, SZ-1);
   draw(SZ-1, 0, 0, SZ-1);
   print_page();
   return 0;
}
