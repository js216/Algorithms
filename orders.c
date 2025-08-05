#include <stdio.h>
#include <stdlib.h>

struct tree;

void error(void)
{
   fprintf(stderr, "Error!\n");
   exit(-1);
}

/***********************************************************
 * LIST
 ***********************************************************/

struct list {
   struct tree *val;
   struct list *next;
};

struct list *head, *z, *t, *last;

void deletenext(struct list *t)
{
   if ((t->next == head) || (t->next == z))
      return;

   struct list *del = t->next;
   t->next = t->next->next;
   free(del);
}

struct list *insertafter(struct tree *v, struct list *t)
{
   struct list *x;
   x = (struct list *) malloc(sizeof *x);
   x->val = v;
   x->next = t->next;
   t->next = x;
   return x;
}

void listinitialize(void)
{
   head = (struct list *) malloc(sizeof *head);
   z = (struct list *) malloc(sizeof *z);
   head->next = z;
   z->next = z;
   last = head;
   head->val = NULL;
   z->val = NULL;
}

/***********************************************************
 * STACK
 ***********************************************************/

void stackinit(void)
{
   head = (struct list *) malloc(sizeof *head);
   z = (struct list *) malloc(sizeof *z);
   head->next = z;
   head->val = 0;
   z->next = z;
}

void push(struct tree *v)
{
   t = (struct list *) malloc(sizeof *t);
   t->val = v;
   t->next = head->next;
   head->next = t;
}

struct tree *pop(void)
{
   struct tree *x;
   t = head->next;
   head->next = t->next;
   x = t->val;
   free(t);
   return x;
}

struct tree *peekstack(void)
{
   t = head->next;
   if (t)
      return t->val;
   else
      return NULL;
}

int stackempty(void)
{
   return head->next == z;
}

/***********************************************************
 * QUEUE
 ***********************************************************/

struct tree* get(void)
{
   if (head->next == z)
      return 0;

   struct tree *x = head->next->val;
   deletenext(head);

   if (head->next == z)
      last = head;

   return x;
}

void put(struct tree *v)
{
   last = insertafter(v, last);
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

void visit(struct tree *t)
{
   printf("%c ", t->val);
}

void printstack(void)
{
   struct list *n = head;
   while (n && (n->next != n)) {
      if (n->val)
         printf("%c ", n->val->val);
      n = n->next;
   }
}

void pre_stack(struct tree *t, int pr)
{
   stackinit();

   push (t);
   while (!stackempty())
   {
      t = pop();
      visit(t);

      // 5. Give the contents of the stack each time a node is visited during
      // the preorder traversal depicted in Figure 4.9.
      if (pr) {
         printf(" : ");
         printstack();
         printf("\n");
      }

      if (t->r != NULL)
         push(t->r);
      if (t->l != NULL)
         push(t->l);
   }
}

void pre_rec(struct tree *t)
{
   visit(t);
   if (t->l)
      pre_rec(t->l);
   if (t->r)
      pre_rec(t->r);
}

void in_stack(struct tree *t)
{
   stackinit();

   while (t || !stackempty())
   {
      while (t) {
         push(t);
         t = t->l;
      }

      t = pop();
      visit(t);
      t = t->r;
   }
}

void in_rec(struct tree *t)
{
   if (t->l)
      in_rec(t->l);
   visit(t);
   if (t->r)
      in_rec(t->r);
}

// 9. Give a stack-based implementation of postorder traversal of a binary tree.
void post_stack(struct tree *t)
{
   // track last visited to know if returning from a right child
   struct tree *last = NULL;
   stackinit();

   while (t || !stackempty()) {
      if (t) {
         push(t);
         t = t->l;
      } else {
         struct tree *peek = peekstack();
         if (peek->r && last != peek->r) {
            t = peek->r;
         } else {
            visit(peek);
            last = pop();
            t = NULL;
         }
      }
   }
}

void post_rec(struct tree *t)
{
   if (t->l)
      post_rec(t->l);
   if (t->r)
      post_rec(t->r);
   visit(t);
}

void printqueue(void)
{
   struct list *n = head;
   while (n && (n != last)) {
      if (n->val && n->val->val)
         printf("%c ", n->val->val);
      n = n->next;
   }
}

void level_queue(struct tree *t, int pr)
{
   listinitialize();

   push (t);
   while (!stackempty())
   {
      t = get();
      visit(t);

      // 6. Give the contents of the queue each time a node is visited during
      // the level order traversal depicted in Figure 4.12.
      if (pr) {
         printf(" : ");
         printqueue();
         printf("\n");
      }

      if (t->l != NULL)
         put(t->l);
      if (t->r != NULL)
         put(t->r);
   }
}

// 10. Write a program to implement level-order traversal of a forest
// represented as a binary tree.
void level_forest(struct tree *t)
{
   listinitialize();

   push (t);
   while (!stackempty())
   {
      t = get();
      visit(t);

      if (t->l) {
         // put first child in the queue
         put(t->l);

         // put other children in queue
         for (struct tree *c = t->l->r; c; c = c->r)
            put(c);
      }
   }
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

// 1. Give the order in which the nodes are visited when the tree in Figure 4.3
// is visited in preorder, inorder, postorder, and level order.
void all_orders(struct tree *t)
{
   printf("Pre (stack):   ");
   pre_stack(t, 0);

   printf("\nPre (rec):     ");
   pre_rec(t);

   printf("\n\nIn (stack):    ");
   in_stack(t);

   printf("\nIn (rec):      ");
   in_rec(t);

   printf("\n\nPost (stack):  ");
   post_stack(t);

   printf("\nPost (rec):    ");
   post_rec(t);

   printf("\n\nLevel (queue): ");
   level_queue(t, 0);

   printf("\n\nPre-order, show stack contents:\n");
   pre_stack(t, 1);

   printf("\n\nLevel, show queue contents:\n");
   level_queue(t, 1);

   printf("\n");
}

int main(void)
{
   printf("Tree from Fig. 4.2:\n==============================\n");
   all_orders(build_4_2());

   printf("\nTree from Fig. 4.3:\n==============================\n");
   all_orders(build_4_3());

   printf("\nTree from Fig. 4.8:\n==============================\n");
   level_forest(build_4_8());
   printf("\n");

   return 0;
}
