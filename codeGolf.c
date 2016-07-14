#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

float sinus(float x){
   int n=0,m;float t=1,s=0,c=0;
l:
   m=n%2;
   fprintf(stderr, "m=%d, !m=%d\n",m,!m);
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

   /* Read number of values */
d:
   ;
   /* Read a value */

   /* Calculate sine and cosine */

   /* output sine and cosine */

   /* goto d if number of values read is smaller than N */

   
   /* float val=get_float(); */
   float val = 5.0;
   printf("sin(%f) = %f\n",val,sinus(val));

   return 0;
}
