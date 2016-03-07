#include <stdio.h>

/********************************************************************************
 * Given a loop definition given by start, end, step, 
 * returns 1 if the given iteration is part of this definition and
 * returns 0 otherwise
********************************************************************************/
int isInDefinition( int iteration, int start, int end, int step) {
	if( ((start - iteration) % step )== 0 ){
		if( ( step > 0 && start <= iteration && iteration <= end ) ||
			 ( step < 0 && end <= iteration && iteration <= start )  ) {
			return 1;
		}
	}
	return 0;
}

/********************************************************************************
 * Returns the last iteration of the definition given by start, end, step
 * (because end may not be the the last iteration of definition).
********************************************************************************/
int lastDefIteration( int iteration, int start, int end, int step ){
	return start + step * ((end-start)/step);
}

int showBits(double num){
   int i = 0;
   unsigned int bits = (unsigned int) num;
   int bit = 3;
   for (i = 0; i< sizeof(float)*8 ; i++){
      if(i%8 == 0)
         printf(" ");
      bit = bits % 2;
      printf("%d",bit);
      bits = bits /2;
   }
   printf("\n");
}

int main ( int argc, int argv )
{
	int start = 1,
		 end = 8,
		 step = 2,
		 set = 3;
	printf ( " Definition is : start = %d, end = %d, step = %d \n", start,end,step);
	printf ( " (end - start)/step : %d \n lastIteration : %d \n\n" , (end - start)/step, start + step * ((end - start)/step) );

	end = -10;
	step = -2;
	printf ( " Definition is : start = %d, end = %d, step = %d \n", start,end,step);
	printf ( " (end - start)/step : %d \n lastIteration : %d \n\n" , (end - start)/step, start + step * ((end - start)/step) );
	printf ( " isInDefinition (-3) : %d \n\n", isInDefinition(-3,start,end,step));
	printf ( " (-5) / (2) = %d \n" , (-5) / 2 );
	
	printf ( " Programming modulo is not math modulo:  -15 % -10 = %d \n", -15 % -10);
	printf ( " In math that would be -15 = -2*10 + 5 ===> -15 % 10 = 5 \n");
	printf ( " Programming modulo is not math modulo:  -15 % 10 = %d \n", -15 % 10);
	printf ( " In math that would be -15 = 2*(-10) + 5 ===> -15 % 10 = 5 \n");
	
	printf ( " a mod n == 0 in negative town -10 % -5 : %d \n" , -10 % -5 );
	printf ( " integer division in negative town -5/2 : %d \n" , -5/2 );
	printf ( " integer division in negative town 5/-2 : %d \n" , 5/-2 );
	printf ( "Sizeof(double): %d \n" , sizeof(double));
	printf ( " integer division in negative town -5/2.0 : %d%d \n" , -5/2.0 );
   float k = 8;
   int i = 0;
   for (i = 0; i < 10 ; i++){
      k = -5 / 2.0;
      printf ( " integer division in negative town -5/2.0 : %p \n" ,k);
      showBits(k);
   }
   int b = -5/2.0;
	printf ( "Float to int : %d\n" , (int)-5/2.0 );
  showBits(1024 - 1);
  showBits(5/2.0);
  

	return 0;
}
