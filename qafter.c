// 8. Give the contents of the queue after each operation in the sequence E AS * Y
// * * QUE *** ST* ** I* ON * *. Here a letter means "put" (the letter)
// and "*" means "get."

#include <stdio.h>
#include <string.h>

#define max 100

static int queue[max+1], head, tail;

void put(int v)
{
   queue[tail++] = v;
   if (tail > max)
      tail = 0;
}

int get(void)
{
   int t = queue[head++];
   if (head > max)
      head = 0;
   return t;
}

void queueinit(void)
{
   head = 0;
   tail = 0;
}

int queueempty(void)
{
   return head == tail;
}

void printout(void)
{
   for (int i=head; i<tail; i++)
      printf("%c ", queue[i]);
   printf("\n");
}

int main(void)
{
   queueinit();

   char *str = "EAS*Y**QUE***ST***I*ON**";

   for (size_t i=0; i<strlen(str); i++) {
      if (str[i] == '*')
         get();
      else
         put(str[i]);
      printout();
   }

   return 0;
}
