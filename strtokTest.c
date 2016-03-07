#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SEQ_MAXFIELD 1000

void printTable(char * table){
	int i = 0;
	for(i=0; i< 50; ++i)
	{	
		printf("%x-", table[i]);
	}
	printf("\n");

	for(i=0; i< 50; ++i)
	{	
		printf("-%c-", table[i]);
	}
	printf("\n");
}

void arropos(int pos){
	int i = 0;
	for(i=0; i < pos ; i++)
		printf("   ");
	printf("^\n");
}
int main( int argc, char** argv)
{
	printf("=============================================\n");
	printf("=============================================\n");
	char table[50] = "FULL;IMP_HIGH;HELLO";
	printTable(table);

	char* token = strtok(table,";");

	printf("=============================================\n");

	printTable(table);

	unsigned long int pos = token - table;
	arropos(pos);

	printf("=============================================\n");
	token = strtok(NULL,";");
	pos = token - table;
	printTable(table);
	arropos(pos);
}


