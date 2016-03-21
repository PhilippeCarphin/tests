#include <stdio.h>
int main( int argc, char ** argv )
{

	printf("Value of argc : %d \n", argc);

   /* Like getdef */


   if ( argc < 3 ){
      printf("      getdef [-v] [-e experiment_home] file key\n");
   }else{
      int i = 0;
      for ( ; i<argc ; ++i){
         printf("argv[%d] : %s \n", i, argv[i]);
      }
   }
   printf("argv[%d-1] : %s\n", argc-1, argv[argc-1]);
   printf("argv[%d-2] : %s\n", argc-2, argv[argc-2]);
	return 0;
}
