
# PHIL markers are there so I can find the stuff that comes from here
# in the generated `configure` script.

# PHIL AC_INIT
AC_INIT([phil-test],[0.1],[phil103@hotmail.com])
# PHIL Post AC_INIT

# PHIL AC_INIT_AUTOMAKE
# foreign: Allow breaking with strict convention otherwise, the absence of the
# files INSTALL, NEW, README, AUTHORS, ChangeLog, and COPYING will be an error.
# -Wall -Werror: Turn on all automake warnings and report them as errors (these
# are not compilation flags)
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# PHIL AC_PROG_CC
# Check for C compiler
AC_PROG_CC

AC_CHECK_HEADERS([stdlib.h])
AC_PREREQ([2.69])
AC_PROG_RANLIB
AC_PROG_INSTALL
AM_PROG_AR
LT_INIT
# PHIL AC_CONFIG_HEADERS
# Declare 'config.phil.h' as output header: after `autoreconf --install`
# we will have a config.phil.h.in file that will be used by `configure` to
# produce config.phil.h.
AC_CONFIG_HEADERS([config.phil.h])

# PHIL AC_CONFIG_FILES
# Declare `Makefile` and `srcx/Makefile` as output files.  It seems that no
# even if we comment out this line, we at least need a Makefile.am at the root.
AC_CONFIG_FILES([
    Makefile
    srcx/Makefile
])

# PHIL AC_OUTPUT
# Launch it!
AC_OUTPUT
