#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

float sinus(float x){
   size_t n=0,m;float t=1,s=0,c=0;
l:
   m=n%2;
   fprintf(stderr, "m=%lu, !m=%d\n",m,!m);
   s += t*m;
   c += t*!m;
   t *= (m?-1:1)*x/++n;
   if(n<19)goto l;
   return s;
}

float get_float()
{
   char * r = 0;
   size_t s = 8;
   getline(&r,&s,stdin);
   /* printf("line read = %s\n",r);  */
   float d;
   sscanf(r,"%f",&d);
   /* printf("float read = %f\n",d); */
   return d;
}

int main ( int argc , char ** argv ) {

   fprintf(stderr, "Size of int = %lu, sizeof size_t = %lu, sizeof(long unsigned int) = %lu\n", sizeof(int), sizeof(size_t),sizeof(long unsigned int));
   size_t N,n,m,i;float t,s,c,x;char*l=0;
   /* Read number of values */
   getline(&l,&i,stdin);
   sscanf(l,"%lu",&N);
   fprintf(stderr, "number of values to read N = %lu, size read = %lu\n",N,i);
d:

   getline(&l,&i,stdin);
   sscanf(l,"%f",&x);
   printf("float read = %f\n",x);
   /* Read a value */
l:
   s=c=0;n=0;t=1;

   /* Calculate sine and cosine */
   m=n%2;
   /* fprintf(stderr, "m=%lu, !m=%d\n",m,!m); */
   /* s += t*m; */
   /* c += t*!m; */
   /* t *= (m?-1:1)*x/++n; */
   /* if(n<19)goto l; */

   /* output sine and cosine */

   /* goto d if number of values read is smaller than N */
   if(--N)goto d;

   return 0;
}
