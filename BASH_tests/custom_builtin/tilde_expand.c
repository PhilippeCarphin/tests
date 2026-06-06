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

int tilde_expand_builtin (WORD_LIST *list)
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

    fprintf(stderr, "list=%p\n", list);
    if(list == NULL){
        fprintf(stderr, "Requires at least one argument\n");
        return 1;
    }
    char *expanded=bash_tilde_expand(list->word->word, 0);
    puts(expanded);
    WORD_LIST *word = list;
    while(word){
        fprintf(stderr, "word=%s\n", word->word->word);
        word = word->next;
    }

    return (rval);
}

/* Called when `template' is enabled and loaded from the shared object.  If this
   function returns 0, the load fails. */
int tilde_expand_builtin_load (char *name)
{
    fprintf(stderr, "%s(%s)\n", __func__, name);
    return (1);
}

/* Called when `template' is disabled. */
void tilde_expand_builtin_unload (char *name)
{
    fprintf(stderr, "%s()\n", __func__);
}

char *template_doc[] = {
    "Perform tilde expansion on STRING",
    "",
    "See the section 'Tilde Expansion' in the bash manual",
    (char *)NULL
};

struct builtin tilde_expand_struct = {
    .name = "tilde-expand",			/* builtin name */
    .function = tilde_expand_builtin,		/* function implementing the builtin */
    .flags = BUILTIN_ENABLED,		/* initial flags for builtin */
    .long_doc = template_doc,			/* array of long documentation strings. */
    .short_doc = "tilde-expand STRING",			/* usage synopsis; becomes short_doc */
    .handle = 0 				/* reserved for internal use */
};
