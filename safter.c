// 7. Give the contents of the stack after each operation in the sequence EAS * Y
// ** QUE ***ST*** I * ON* *. Here a letter means "push" (the letter)
// and "*" means "pop."

#include <stdio.h>
#include <string.h>

#define MAX 100

char key[MAX+2];
int next [MAX+2];
int x, head, z;

void listinitialize(void)
{
   head = 0;
   z = 1;
   x = 2;
   next[head] = z;
   next[z] = z;
}

void deletenext(int t)
{
   next[t] = next[next[t]];
}

int insertafter(char v, int t)
{
   key[x] = v;
   next[x] = next[t];
   next[t] = x;
   return x++;
}

void printfrom(int t)
{
   while (next[t] != t) {
      printf("%c ", key[t]);
      t = next[t];
   }
   printf("\n");
}

void push(int v)
{
   insertafter(v, head);
}

char pop(void)
{
   char x = key[next[head]];
   deletenext(head);
   return x;
}

int main(void)
{
   listinitialize();

   char *str = "EAS*Y**QUE***ST***I*ON**";

   for (size_t i=0; i<strlen(str); i++) {
      if (str[i] == '*')
         pop();
      else
         push(str[i]);
      printfrom(head);
   }

   return 0;
}
