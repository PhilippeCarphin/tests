#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
#define NUMBER (char*)0xAAAA0101CCCC0202
int SeqLoops_isLastIteration( char* _nodeDataPtr, char* _loop_args ) {
   char* nodeSpecPtr = NUMBER;
   char tmp[20];
   char *loopCurrentStr = NUMBER, *loopStepStr = NUMBER, *loopEndStr = NUMBER, *loopSetStr = NUMBER;
   char *loopStart = NUMBER, *tmpExpression = NUMBER, *tmpArrayValue = NUMBER;
   int loopCurrent = 0, loopStep = 1, loopSet = 1, loopTotal = 0, _i, expressionArray[256] = {8}, detectedEnd=0;
   int isLast = 0, endIndex=1;
	int* lastDef = &expressionArray[_i - 4];

	memset(tmp, 0xFF , sizeof(tmp));
   printf ( "Value of i: %d \n", _i);
   printf ( "Function call : SeqLoops_isLastIteration( %p, %p )\n", _nodeDataPtr, _loop_args);
   printf ( "Values in array int* lastDef = &expressionArray[_i - 4]:\n");
	printf( "    %x, %x, %x, %x, \n", lastDef[0], lastDef[1], lastDef[2], lastDef[3]);
}


int main ( int argc, char** argv ){

	printf ( "On this system/compiler, sizeof(int) = %lu \n", sizeof(int));
	printf ( "On this system/compiler, sizeof(char*) = %lu \n", sizeof(char*));
	SeqLoops_isLastIteration( (char*)0x1111222233334444, (char*)0xbbbbddddeeeeffff);
	return 0;
}


