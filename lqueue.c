// 10. Using a linked list, implement the basic operations for a queue.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
   int key;
   struct node *next;
};

struct node *head, *z, *last;

void listinitialize(void)
{
   head = (struct node *) malloc(sizeof *head);
   z = (struct node *) malloc(sizeof *z);
   head->next = z;
   z->next = z;
   last = head;
   head->key = '>';
   z->key = 'z';
}

void deletenext(struct node *t)
{
   if ((t->next == head) || (t->next == z))
      return;

   struct node *del = t->next;
   t->next = t->next->next;
   free(del);
}

int get(void)
{
   if (head->next == z)
      return 0;

   int x = head->next->key;
   deletenext(head);

   if (head->next == z)
      last = head;

   return x;
}

struct node *insertafter(int v, struct node *t)
{
   struct node *x;
   x = (struct node *) malloc(sizeof *x);
   x->key = v;
   x->next = t->next;
   t->next = x;
   return x;
}

void put(int v)
{
   last = insertafter(v, last);
}

void printfrom(struct node *t)
{
   while (t && (t->next != t)) {
      printf("%c ", t->key);
      t = t->next;
   }
   printf("\n");
}

int main(void)
{
   listinitialize();

   char *str = "EAS*Y**QUE***ST***I*ON**";

   for (size_t i=0; i<strlen(str); i++) {
      if (str[i] == '*')
         get();
      else
         put(str[i]);
      printfrom(head);
   }

   return 0;
}
