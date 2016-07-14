#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main ( int argc , char ** argv ) {

   size_t N,n,m,i;float t,s,c,x;char*l=0;
   getline(&l,&i,stdin);
   sscanf(l,"%lu",&N);
d:
   getline(&l,&i,stdin);
   sscanf(l,"%f",&x);
   s=c=0;n=0;t=1;
l:
   m=n%2;
   s += t*m;
   c += t*!m;
   t *= (m?-1:1)*x/++n;
   if(n<60)goto l;
   printf("%.3f\n%.3f\n",c,s);
   if(--N)goto d;

   return 0;
}
