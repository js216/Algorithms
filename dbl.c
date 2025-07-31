// 5. Write procedures for insertion and deletion in a doubly linked list.

#include <stdio.h>
#include <stdlib.h>

struct node {
   int key;
   struct node *next;
   struct node *prev;
};

struct node *head, *z;

void listinitialize(void)
{
   head = (struct node *) malloc(sizeof *head);
   z = (struct node *) malloc(sizeof *z);
   head->next = z;
   head->prev = head;
   z->next = z;
   z->prev = head;
}

void print_fwd(struct node *t)
{
   printf("FWD:  ");
   while (t && (t->next != t)) {
      if (t->prev == t)
         printf("(start) ");
      else
         printf("%d ", t->key);
      t = t->next;
   }
   printf("(end)\n");
}

void print_back(struct node *t)
{
   printf("BACK: ");
   while (t && (t->prev != t)) {
      if (t->next == t)
         printf("(end) ");
      else
         printf("%d ", t->key);
      t = t->prev;
   }
   printf("(start)\n");
}

struct node *insert_before(int v, struct node *t)
{
   if (t == head)
      return t;

   struct node *x;
   x = (struct node *) malloc(sizeof *x);
   x->key = v;

   x->prev = t->prev;
   x->next = t;

   t->prev->next = x;
   t->prev = x;
   return x;
}

void delete(struct node *t)
{
   if ((t == head) || (t == z))
      return;
   t->prev->next = t->next;
   t->next->prev = t->prev;
   free(t);
}

int main(void)
{
   listinitialize();

   struct node *x1 = insert_before(1, z);
   struct node *x2 = insert_before(2, z);
   insert_before(3, x1);
   insert_before(4, x2);
   delete(x2);

   print_fwd(head);
   print_back(z);

   return 0;
}
