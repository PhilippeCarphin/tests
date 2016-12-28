#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum HELLO {A,B,C,D,E,F,G,H};

int h_binrep(enum HELLO h, char *dst)
{
   int i = 8*sizeof(enum HELLO);
   char *p = dst;
   for(;i--;){
      *p++ = '0' + ((h >> i)&1u);
   }
   *p = '\0';
   return 0;
}

int *c_binrep(char byte, char *dst)
{
   int i = 8*sizeof(char);
   char *p = dst;
   for(;i--;){
      *p++ = '0' + ((byte >> i)&1u);
   }
   *p = '\0';
   return 0;
}

char *i_binrep(int n, char *dst)
{
   int i = 8*sizeof(int);
   char *p = dst;
   for(;i--;){
      *p++ = '0' + ((n >> i)&1u);
   }
   *p = '\0';
   return 0;
}

char *l_binrep(long unsigned int n, char *dst)
{
   int i = 8*sizeof(long int);
   char *p = dst;
   for(;i--;){
      *p++ = '0' + ((n >> i)&1u);
      if( i%8 == 0)
         *p++ = ' ';
   }
   *p = '\0';
   return 0;
}


int main ( int argc , char ** argv ) {

   char *bin = malloc ( 8*sizeof(char) + 1 );
   for( char c = 'A'; c <= 'Z'; ++c){
      c_binrep(c,bin);
      printf("'%c' = %s\n",c,bin);
   }
   char *integer = malloc ( 8*sizeof(int) + 1);

   char *lui = malloc( 8*sizeof(long unsigned int) + 1);

   long unsigned int hi = 0x8080808080808080;
   long unsigned int lo = 0x0101010101010101;
   long unsigned int lw = 0x030134ff00124124;

   long unsigned int one = 1;
   long unsigned int two = 2;
   long unsigned int zero = 0;

   l_binrep(one - two,lui);
   printf("one minus two  : %s\n",lui);
   l_binrep(zero - one,lui);
   printf("zero minus one : %s\n",lui);
   l_binrep(zero - two,lui);
   printf("zero minus two : %s\n",lui);

   long unsigned int nlw = ~lw;
   long unsigned int di = lw - lo;
   long unsigned int dAnlw = di & nlw;
   long unsigned int rep = dAnlw & hi;
   l_binrep(hi,lui);  printf(" hi : %s\n",lui);
   l_binrep(lo,lui);  printf(" lo : %s\n",lui);
   l_binrep(lw,lui);  printf(" lw : %s\n",lui);
   l_binrep(-lw,lui); printf("-lw : %s\n",lui);
   l_binrep(lw,lui);  printf(" lw : %s\n",lui);
   l_binrep(lo,lui);  printf(" lo : %s\n",lui);
   l_binrep(di,lui);  printf(" di : %s\n",lui);
   l_binrep(nlw,lui); printf("nlw : %s\n",lui);
   l_binrep(rep,lui); printf("rep : %s\n",lui);

   printf("sizeof(long unsigned int):%lu\n", sizeof(long unsigned int));

   char *enm = malloc( 8*sizeof(enum HELLO) +1);
   enum HELLO h = C;
   h_binrep(h, enm);
   printf("Representation of enum %c : %s\n",'A' + h, enm);

   int i = -1;
   i_binrep(i,integer);
   printf("Representation of integer %d : %s\n",i,integer);

   printf("Size of enum : %lu  and  size of int : %lu\n", sizeof(enum HELLO), sizeof(int));
   
   return 0;
}
