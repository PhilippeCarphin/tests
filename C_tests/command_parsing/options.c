#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "options.h"
#include "string_associator.h"

/*
 * This file has N basic parts
 * 
 * the parse_opts() function is to be called in the main will parse the command
 * line arguments into the struct my_opts.
 *
 * To define the options, one must modify the 
 * struct option options[] array in parse_opts.
 * and complete the function's switch with the options.
 *
 * Use the string_associator to facilitate the association of the enums with
 * the strings.
 *
 * It is also recommended to also complete the print_opts() function.
 */
 

struct string_associator flag_associator[] = {
	{ FLAG_YELLOW, "yellow"},
	{ FLAG_GREEN, "green"},
	{ FLAG_RED, "red"},
	{ FLAG_BLUE, "blue"},
	{ 0, 0}
};

struct string_associator cmd_associator[] = {
	{CMD_DO_A, "do_a"},
	{CMD_DO_B, "do_b"},
	{0,0}
};

static int show_usage();

/******************************************************************************
 *
 ******************************************************************************/
int parse_opts(int argc, char * const * argv, struct my_options *opts)
{	
	printf("%s()\n",__FUNCTION__);
	int retval = 0;
	
	int opt;
	int index;
	
	struct option options[] = {
		{ "help", 0,  0, 'h' },
		{ "int_value", 1, 0, 'i'},
		{ "string_value", 1, 0, 's'},
		{ "flag", 1, 0, 'f'		},
		{0,0,0,0}
	};
	
	while(( opt = getopt_long(argc, argv, "hi:s:f:", options, &index)) != -1 ){
		printf("%s() : opt = %d, optarg = %s\n", __FUNCTION__, opt, optarg);
		switch(opt){
			case 'h':
				show_usage();
				break;
			case 's':
				printf("We are at line %d\n",__LINE__);
				opts->string_arg = strdup(optarg);
				break;
			case 'i':
				opts->int_value = atoi(optarg);
				break;
			case 'f':
				opts->flag_value = int_associated_to(optarg, flag_associator);
				break;
			default:
				printf("Unknown option %c (%d)\n", opt, opt);
				break;
		}
	}
	return retval;
}

/******************************************************************************
 *
 ******************************************************************************/
int show_usage()
{
	puts("TODO WRITE HELP TEXT\n");
	return 0;
}

/******************************************************************************
 *
 ******************************************************************************/
int print_opts(struct my_options *opts)
{
	printf("%s()\n",__FUNCTION__);
	printf("\tint_value : %d\n", opts->int_value);
	printf("\tstring_arg : %s\n", opts->string_arg);
//	printf("\tflag_arg : %s\n", str_associated_to(opts->flag_value, flag_associator));
	printf("\tflag_arg : %d\n", opts->flag_value);
	return 0;
}



