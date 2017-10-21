#include <stdio.h>
#include <stdlib.h>
#include "options.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int test_opts();
int main(int argc, char *argv[]) {
	
	test_opts();
	
	return 0;
}

int test_opts()
{
	
	int argc = 7;
	
	char *argv[] = {"-h", "--int_value", "345", "--string_value", "Hello_world", "--flag", "yellow"};
	
	printf("%s() : argv : \n", __FUNCTION__);
	
	for(unsigned int i = 0; i < argc; ++i){
		printf("\targv[%d] = %s\n",i, argv[i]);
	}
	
	struct my_options opts;
	parse_opts(argc, argv, &opts);
	print_opts(&opts);
	
	return 0;
}
