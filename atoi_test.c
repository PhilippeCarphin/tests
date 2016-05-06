#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main ( int argc , char ** argv ) {
   char * null_str = NULL;
   char * empty_str = "";
   printf("sizeof(int):%d\n",sizeof(int));
   printf("sizeof(long int):%d\n",sizeof(long int));
   char * hex_str = "7fffffff";
   //              (7)( f)( f)(f )(f )(f )(f )(f )                           ( F)
   char * b_str = "1111111111111111111111111111111";
   //             ^   ^   ^   ^   ^   ^   ^   ^
   //            32  28  24  20  16  12   8   4
   int n = atoi(empty_str);
   printf("Empty conversion successful: n = %d\n",n);
   n = (int)strtol(hex_str, NULL, 16);
   printf("Hex conversion successful: n = %d\n",n);
   n = (int)strtol(b_str, NULL,2);
   printf("Binary conversion successful: n = %d\n",n);
   long unsigned int m = strtoll("ffffffffff",NULL,16);
   printf("long long unsigned conversion successful: m = %ld\n",m);

   char * neg_str = "-234";
   n = atoi(neg_str);
   printf("Neg conversion successful: n = %d\n",n);


   char * phil = NULL;
   printf("Here is what happens when I print a null string :%s\n",phil);



   return 0;
}

