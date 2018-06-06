#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
   if(argc < 2){
      exit(1);
   }
   size_t chunk = atoi(argv[1]);
   size_t limit = atoi(argv[2]);
   size_t current_total = 0;
   while(current_total < limit){
      if(malloc(chunk * sizeof(int)) == NULL){
         exit(127);
      }
      current_total += chunk;
   }

   return 0;
}
