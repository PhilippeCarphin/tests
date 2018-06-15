#define _DEFAULT_SOURCE
#include "options.h"


#define PHIL_DEBUG
#include "../debug.h"
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>

#include "api.h"
/*
 * Here we are implementing the parse_args() function.  To do this, only a
 */
/*
 * couple of building blocks are necessary:
 * 1) Complete the struct option array, the short_opts string, and the
 * parse_option() funciton.
 * 2) Implement the parse_posargs function. 
 */

/*******************************************************************************
 * Option specififcation passed to getopt_long to specify the names and types of
 * your command line options
*******************************************************************************/
static struct option options[] = {
      // TODO : COMPLETE THIS
      // long name | has_args | flag | short name
		{ "help",         0,        0,      'h'},
		{ "int_value",    1,        0,      'i'},
		{ "path",         1,        0,      'p'},
		{ "float",        1,        0,      'f'},
		{0,0,0,0}
	};

// TODO : COMPLETE THIS (a colon after means it takes an argument)
static char *short_opts = "hi:p:f:";

/*******************************************************************************
 * This function is driven by the parse_opts function that uses getopt_long.
 * It will call this function for each option on the command line.
*******************************************************************************/
static void show_usage();
static int parse_option(int opt, char *optarg, struct MyOpts *opts)
{
   // TODO : COMPLETE THIS
   switch(opt){
      case 'h':
         show_usage();
         break;
      case 'p':
         opts->a_path = strdup(optarg);
         break;
      case 'i':
         opts->a_flag = 1; // true
         break;
      case 'f':
         if(sscanf(optarg, "%f", &(opts->float_param)) != 1)
            return -1;
         break;
      default:
         fprintf(stderr, "Unknown option %c (%d)\n", opt, opt);
         show_usage();
         return -1;
         break;
   }

   return 0;
}
static void show_usage(){fprintf(stderr, "SHOW_USAGE TODO\n");}

/*******************************************************************************
 * In this section, you implement the parse_posargs function, you can do
 * whatever you want to do with them.  This is an example
*******************************************************************************/
// TODO : COMPLETE THIS
static int command(const char *command_name, enum Command *cmd);
static int parse_posargs(int posargc, char *posargv[], struct MyOpts *opts)
{
   if(posargc < 1){
      fprintf(stderr, "Error: No subcommand\n");
      return -1;
   }

   if(command(posargv[0], &(opts)->cmd)){
      fprintf(stderr, "Unknown command %s\n", posargv[1]);
      return -1;
   }

   opts->elements = posargv+1;
   opts->nb_elements = posargc-1;
   // Maybe do something with the other positionnal arguments
   return 0;
}
static int command(const char *command_name, enum Command *cmd)
{
   struct NameValue {const char *name; const int value;};// Library
   static struct NameValue cmd_value [] = {
      {"first_name", FIRST_CMD,},
      {"second_name", SECOND_CMD},
      {NULL,0}
   };
   for(struct NameValue *nv = cmd_value; nv->name != NULL; nv++){
      if(strcmp(command_name, nv->name) == 0){
         *cmd = nv->value;
         return 0;
      }
   }
   return -1;
}


/*******************************************************************************
 * This can be seen as a driver for the for getopt_long that uses parse_option
 * and parse_posargs.  The exported function is parse_args
*******************************************************************************/
// You don't have to touch this.
static int parse_opts(int argc, char *argv[], struct MyOpts *opts, int *posargc, char ***posargv);
static int parse_posargs(int posargc, char *posargv[], struct MyOpts *opts);
int parse_args(int argc, char *argv[], struct MyOpts **opts)
{
   *opts = malloc(sizeof **opts);
   int posargc;
   char **posargv;
   if(parse_opts(argc, argv, *opts, &posargc, &posargv)){ return -1; }
   if(parse_posargs(posargc, posargv, *opts)){ return -1; }
   return 0;
}
static int parse_opts(int argc, char *argv[], struct MyOpts *opts, int *posargc, char ***posargv)
{
	int opt;
	int index;
	while(( opt = getopt_long(argc, argv, short_opts, options, &index)) != -1 ){
      if(parse_option(opt, optarg, opts)){
         fprintf(stderr, "error parsing argument %s of option %c at index %d\n", optarg, opt, index);
      }
	}
   *posargc = argc - optind;
   *posargv = argv + optind;
   return 0;
}
