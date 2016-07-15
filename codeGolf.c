#include <stdio.h>
int main(){
   int N,n,m;
   scanf("%d",&N);
   while(N--){
      float t=1,s=0,c=0,x;
      scanf("%f",&x);
      for(n=0;n<60;)
         m=n%2,s+=t*m,c+=t*!m,t*=(m?-1:1)*x/++n;
      printf("%f\n%f\n",s,c);
   }
}
