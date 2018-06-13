#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>

#define NS_PER_SEC 1000000000
#define MS_PER_NS 1000000
#define MAX 5000000

struct Args{
   char * string;
};
typedef int (* function)(struct Args *);
unsigned long getCurrentTime(void);
unsigned long time_lots_of(function f, struct Args *);
typedef int word;
struct LinkedListNode {
   int id;
   struct LinkedListNode *next;
};

struct LinkedListNode *construct_list(int list_length)
{
   struct LinkedListNode *head, *current;

   head = (struct LinkedListNode*) malloc (sizeof *head);
   current = head;
   for(int i = 0; i < list_length; ++i){
      current->next = (struct LinkedListNode*) malloc (sizeof *current);
      current = current->next;
      current->id = rand();
   }

   return head;
}

void go_through_list(struct LinkedListNode *head)
{
   int nb_elem = 0;
   for(struct LinkedListNode *current = head; current != NULL; current = current->next){
      nb_elem++;
      if(current->next != NULL && current->id == current->next->id){
         printf("Found the element with id 1234567\n");
      }
   }
   printf("The list has nb_elem=%d\n", nb_elem);
}


int main ( int argc , char ** argv )
{
   int list_length;
   if(argc > 1){
      list_length = atoi(argv[1]);
   } else {
      list_length = 100000;
   }

   struct LinkedListNode *head = construct_list(list_length);

   unsigned long start_time = getCurrentTime();

   go_through_list(head);

   unsigned long end_time = getCurrentTime();

   printf("end_time - start_time = %lu\n", (end_time - start_time)/1000); 
   return 0;
}










unsigned long getCurrentTime(void)
{
   struct timespec spec;

   clock_gettime(CLOCK_MONOTONIC, &spec);

   return NS_PER_SEC * spec.tv_sec + spec.tv_nsec;
}


unsigned long time_lots_of(function f, struct Args * args)
{
   unsigned long start_time = getCurrentTime(); 
   int i;
   for (i = 0; i < MAX; ++i){
      f(args);
   }
   return getCurrentTime() - start_time;
}
