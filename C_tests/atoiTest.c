#include <stdio.h>

#include <stdlib.h>
#include <string.h>

int main ( int argc, char* argv[]){
	char* str = "BONJOUR";
	int number = atoi(str);

	printf("Number is : %d \n", number);
	printf("Number is : %d \n", atoi("1:TL_MINIMAL"));
	printf("Number is : %d \n", atoi("3:TL_MINIMAL"));

	return 0;
}
