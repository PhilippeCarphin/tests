#include <stdio.h>
int main(){
   int N,n,m;
   float t,s,c,x;
   scanf("%d",&N);
   while(N--){
      scanf("%f",&x);
      s=c=0;n=0;t=1;
      while(n<60)
         m=n%2,s+=t*m,c+=t*!m,t*=(m?-1:1)*x/++n;
      printf("%.3f\n%.3f\n",s,c);
   }
}
