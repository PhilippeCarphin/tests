#include <stdlib.h>
#include <string.h>
#include <stdio.h>

double sinus(double x){
   int n=1,f=n;
   double p=x,s=x;
l:
   p*=-x*x;
   
   f*=++n*n++;
   fprintf(stdout, "f(%d) = %d, px = %f, s = %f, term(n) = %f\n",n,f,p,s,p/f);

   s += p/f;
   if(n<9) goto l;

   return s;
}

double get_double()
{
   char * r = 0;
   size_t s = 8;
   getline(&r,&s,stdin);
   /* printf("line read = %s\n",r);  */
   float d;
   sscanf(r,"%f",&d);
   /* printf("double read = %f\n",d); */
   return d;
}

int main ( int argc , char ** argv ) {


   double val=get_double();
   printf("sin(%f) = %f\n",val,sinus(val));

   return 0;
}
