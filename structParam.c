#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define SHOW_ADDR

struct Phil {
   int a;
   int b;
};
unsigned long long int stackBase;

int takesStruct ( struct Phil Phil_param ){

   int stackMarker = 0;
#ifdef SHOW_ADDR
   printf("takesStruct(): Address of Phil_param:%llu\n",(unsigned long long int)&Phil_param - stackBase);
   printf("takesStruct(): Adress of stackMarker:%llu\n",(unsigned long long int)&stackMarker - stackBase);
#endif
   printf("takesStruct(): Phil_param.a = %d\n",Phil_param.a);
   printf("takesStruct(): Phil_param.b = %d\n",Phil_param.b);
   Phil_param.a = 8;
   Phil_param.b = 8;
   printf("takesStruct(): Phil_param.a = %d\n",Phil_param.a);
   printf("takesStruct(): Phil_param.b = %d\n",Phil_param.b);

   return 0;
}

int takesStructPtr ( struct Phil * Phil_param ){

   int stackMarker = 0;
#ifdef SHOW_ADDR
   printf("takesStructPtr(): Address of Phil_param:%llu\n",(unsigned long long int)Phil_param -  stackBase );
   printf("takesStructPtr(): Adress of stackMarker:%llu\n", (unsigned long long int)&stackMarker - stackBase);
#endif
   printf("takesStructPtr(): Phil_param->a = %d\n",Phil_param->a);
   printf("takesStructPtr(): Phil_param->b = %d\n",Phil_param->b);
   Phil_param->a = 8;
   Phil_param->b = 8;
   printf("takesStructPtr(): Phil_param->a = %d\n",Phil_param->a);
   printf("takesStructPtr(): Phil_param->b = %d\n",Phil_param->b);

   return 0;
}

int main ( int argc , char ** argv ) {
   struct Phil phil;
   stackBase = (((unsigned long long int)&phil >> 12 ) << 12);
   phil.a = 1234;
   phil.b = 5678;
#ifdef SHOW_ADDR
   printf("main(): Adress of phil: %llu\n", (unsigned long long int)&phil - stackBase);
#endif

   printf("main(): phil.a = %d\n",phil.a);
   printf("main(): phil.b = %d\n",phil.b);

   takesStruct(phil);

   printf("main(): phil.a = %d\n",phil.a);
   printf("main(): phil.b = %d\n",phil.b);

   takesStructPtr(&phil);

   printf("main(): phil.a = %d\n",phil.a);
   printf("main(): phil.b = %d\n",phil.b);
   return 0;
}
