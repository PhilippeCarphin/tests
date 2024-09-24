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

extern char *strerror ();

int
tilde_expand_builtin (list)
     WORD_LIST *list;
{
  int opt, rval;

  rval = EXECUTION_SUCCESS;
  reset_internal_getopt ();
  while ((opt = internal_getopt (list, "")) != -1)
    {
      switch (opt)
	{
	CASE_HELPOPT;
	default:
	  builtin_usage ();
	  return (EX_USAGE);
	}
    }
  list = loptend;

  return (rval);
}

/* Called when `template' is enabled and loaded from the shared object.  If this
   function returns 0, the load fails. */
int
tilde_expand_builtin_load (name)
     char *name;
{
  return (1);
}

/* Called when `template' is disabled. */
void
tilde_expand_builtin_unload (name)
     char *name;
{
}

char *template_doc[] = {
	"Short description.",
	""
	"Longer description of builtin and usage.",
	(char *)NULL
};

struct builtin template_struct = {
	"tilde-expand",			/* builtin name */
	tilde_expand_builtin,		/* function implementing the builtin */
	BUILTIN_ENABLED,		/* initial flags for builtin */
	template_doc,			/* array of long documentation strings. */
	"Perform tilde expansion",			/* usage synopsis; becomes short_doc */
	0				/* reserved for internal use */
};
