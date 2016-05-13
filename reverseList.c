#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct list_node {
   char * data;
   struct list_node * nextPtr;
};
typedef struct list_node* list_node_ptr;
void reverseList ( struct list_node ** list );
void printList( struct list_node * list );


int main ( int argc , char ** argv ) {
   /****************************************************************************
    *                      SETUP
    *                      =====
    * creating      list_ptr : A -> B -> C -> NULL
    * creating one_elem_list : D -> NULL
    * creating zero_elem_list : NULL
   ****************************************************************************/
   char * a_data = "A_DATA",
        * b_data = "B_DATA",
        * c_data = "C_DATA",
        * d_data = "D_DATA",
        * e_data = "E_DATA";
   struct list_node A,B,C,D,E;
   A.data = a_data;
   B.data = b_data;
   C.data = c_data;
   D.data = d_data;
   E.data = e_data;


   A.nextPtr = &B;
   B.nextPtr = &C;
   C.nextPtr = &D;
   D.nextPtr = NULL;
   list_node_ptr list_ptr = &A;

   list_node_ptr one_elem_list_ptr = &E;
   E.nextPtr = NULL;

   list_node_ptr zero_elem_list_ptr = NULL;

   /****************************************************************************
    *                      TESTING
    *                      =======
    * Print list_ptr, reverse it, then print again
    * Print one_elem_list, reverse it, then print again
    * Print zero_elem_list, reverse it, then print again
    * Attempt to do the next->next thing on one_elem_list
   ****************************************************************************/
   printf("\n============== reversing multi_elem_list  ===============\n");

   printList( list_ptr );
   reverseList ( &list_ptr );
   printList( list_ptr );

   printf("\n============== reversing one_elem_list_ptr ===============\n");

   printList( one_elem_list_ptr );
   reverseList ( &one_elem_list_ptr );
   printList( one_elem_list_ptr );

   printf("\n============== reversing zero_elem_list_ptr ===============\n");

   printList( zero_elem_list_ptr );
   reverseList ( &zero_elem_list_ptr );
   printList( zero_elem_list_ptr );

   printf("\n============== testing next->next thing ===================\n");
/* Figuring out what was the problem with this nextPtr->nextPtr thing */
#if 0
   struct list_node * wtf_ptr = one_elem_list_ptr->nextPtr->nextPtr;
#else
   list_node_ptr first = &E;
   list_node_ptr second = first->nextPtr->nextPtr;
#endif

   return 0;
}

/********************************************************************************
 *                   REVERSAL ALGORITHM
 * Traverse list making current point to previous
********************************************************************************/
void reverseList ( struct list_node ** list ){
   printf ("reveseList() called\n");
   struct list_node * prev = NULL,
                    * current = *list,
                    * tmp_next;

   /* A -> B -> C -> D -> NULL */
   while ( current != NULL ){
      /* A <- prev    current -> D */
      tmp_next = current->nextPtr;
      /* A <- prev    current -> tmp_next */
      current->nextPtr = prev;
      /* A <- prev <- current    tmp_next */
      prev = current;
      current = tmp_next;
      /* A <- B    <-  prev      current */
   }
   /*    A <- B    <-  C      <-  prev(=D)     current(=NULL) */
   *list = prev;

   /* Note that if *list was NULL to start with, then prev will be NULL from
    * it's declaration, therefore *list = prev; keeps the same empty list */
}

void printList( struct list_node * list ){
   struct list_node* current = list;
   while(current != NULL ){
      printf("Current.data = %s\n", current->data);
      current = current->nextPtr;
   }
}
