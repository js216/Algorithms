#include <stdio.h>
#include <stdlib.h>

#define N_ELEM 5

struct node {
   int key;
   struct node *next;
};

struct node *head, *z;

void listinitialize(void)
{
   head = (struct node *) malloc(sizeof *head);
   z = (struct node *) malloc(sizeof *z);
   head->next = z;
   z->next = z;
}

void deletenext(struct node *t)
{
   t->next = t->next->next;
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

void printfrom(struct node *t)
{
   while (t && (t->next != t)) {
      printf("%d ", t->key);
      t = t->next;
   }
   printf("(end)\n");
}

// 2. Implement a routine movenexttofront (struct node *t) for a linked list
// that moves the node following the node pointed to by t to the beginning of
// the list. (Figure 3.3 is an example of this for the special case when t
// points to the next-to-last node in the list.)

void movenexttofront(struct node *t)
{
   if (t->next == t->next->next)
      return;

   struct node *after = t->next->next;
   t->next->next = head->next;
   head->next = t->next;
   t->next = after;
}

// 3. Implement a routine exchange (struct node *t, struct node *u) for a linked
// list that exchanges the positions of the nodes after the nodes pointed to by
// t and u.

void exchange(struct node *t, struct node *u)
{
   if ((t->next == t->next->next) || (u->next == u->next->next))
      return;

   struct node *tt = t->next;
   struct node *uu = u->next;

   t->next = uu;
   u->next = tt;

   struct node *uuu = uu->next;
   struct node *ttt = tt->next;

   uu->next = ttt;
   tt->next = uuu;
}

int main(void)
{
   listinitialize();

   struct node *x1 = insertafter(1, head);
   struct node *x2 = insertafter(2, x1);
   struct node *x3 = insertafter(3, x2);
   struct node *x4 = insertafter(4, x3);
   insertafter(5, x4);

   printf("Order before: ");
   printfrom(head);

   printf("Order after:  ");
   movenexttofront(x4);
   printfrom(head);

   printf("Swap 2 <-> 3: ");
   exchange(x1, x2);
   printfrom(head);

   return 0;
}
