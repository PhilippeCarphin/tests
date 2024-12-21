/* template - example template for loadable builtin */

/* See Makefile for compilation details. */

#include <config.h>

#if defined (HAVE_UNISTD_H)
#  include <unistd.h>
#endif
#include "bashansi.h"
#include <stdio.h>
#include <errno.h>

#include "loadables.h"

#if !defined (errno)
extern int errno;
#endif

#include <string.h>

/*
 * single-line commands like 'cmd arg1 arg2 ; cmd2 arg21 arg 22 ; ...'
 * are parsed to a COMMAND *cmd with cmd->type == cm_connection
 * which is like a binary tree where non-leaf nodes are of type cm_connection
 * and the leaf nodes are of type cm_simple that contain a WORD_LIST
 */
static void phil_simple_print_command(COMMAND *cmd){
    switch(cmd->type){
        case cm_connection:
            phil_simple_print_command(cmd->value.Connection->first);
            phil_simple_print_command(cmd->value.Connection->second);
            break;
        case cm_simple:{
                WORD_LIST *word = cmd->value.Simple->words;
                while(word){
                    fprintf(stdout, "\"%s\"", word->word->word);
                    if(word->next){
                        fputc(' ', stdout);
                    }
                    word = word->next;
                }
                fprintf(stdout, "\n");
            }
            break;
        default:
            fprintf(stderr, "Unimplemented type: %d\n", cmd->type);
            break;
    }
}
int split_cmd_builtin (WORD_LIST *list)
{
    int rval = EXECUTION_SUCCESS;

    PARAMS()
    rval = EXECUTION_SUCCESS;
    reset_internal_getopt ();
    int opt;
    while ((opt = internal_getopt (list, "h")) != -1)
    {
        switch (opt)
        {
            case 'h':
                builtin_help();
                return(EXECUTION_SUCCESS);
            CASE_HELPOPT;
            default:
            builtin_usage();
            return (EX_USAGE);
        }
    }
    list = loptend;

    /*
     * Here we parse a string into a tree-like structure of type COMMAND
     * as defined in command.h.  Which is a typed union (the field type
     * says which type we have in the union and the field value is the union)
     *
     * The function 'parse_string_to_command()' is only available since bash 5
     * so this builtin cannot be loaded in bash 4-.
     */
    COMMAND *cmd = parse_string_to_command(list->word->word, 0);
    phil_simple_print_command(cmd);
    return 0;
}

/* Called when `template' is enabled and loaded from the shared object.  If this
   function returns 0, the load fails. */
int shell_split_builtin_load (char *name)
{
    fprintf(stderr, "%s(%s)\n", __func__, name);
    return (1);
}

/* Called when `template' is disabled. */
void shell_split_builtin_unload (char *name)
{
    fprintf(stderr, "%s()\n", __func__);
}

char *template_doc[] = {
    "Print each command from a string of code",
    (char *)NULL
};

struct builtin shell_split_struct = {
    .name = "shell-split",			/* builtin name */
    .function = split_cmd_builtin,		/* function implementing the builtin */
    .flags = BUILTIN_ENABLED,		/* initial flags for builtin */
    .long_doc = template_doc,			/* array of long documentation strings. */
    .short_doc = "tilde-expand STRING",			/* usage synopsis; becomes short_doc */
    .handle = 0 				/* reserved for internal use */
};
