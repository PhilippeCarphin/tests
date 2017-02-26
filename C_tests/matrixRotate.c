#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int matrix[5][5] = { 1,1,1,1,1,
                0,0,0,0,0,
                0,0,0,0,0,
                0,0,0,0,0,
                0,0,0,0,0};

void printMatrix( int *M, int width, int height)
{
   for(int i = 0; i < height; ++i){
      for(int j = 0; j < width; ++j){
         printf("%d ", M[i*width + j]);
      }
      printf("\n");
   }
}


int main(void){
   printMatrix(matrix,5,5);
   return 0;
}

   
