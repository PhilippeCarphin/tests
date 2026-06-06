#
# Sample makefile for bash loadable builtin development
#
# Copyright (C) 2022 Free Software Foundation, Inc.

#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

# these should match the ones in Makefile.in (for the make install target)

prefix = /Users/pcarphin/Repositories/github.com/bminor/bash/localinstall
exec_prefix = ${prefix}
libdir = ${exec_prefix}/lib

# ${loadablesdir} is where the example loadable builtins and data files
# are installed (make install target in Makefile.in)

loadablesdir = ${libdir}/bash
DESTDIR =

# include Makefile.inc for all boilerplate definitions

include $(DESTDIR)$(loadablesdir)/Makefile.inc
INC_PLUS = -I$(prefix)/lib/bash

# here, `example' is the name of the shared object
# replace `example' with the appropriate filename

all:	shell_split

shell_split:	shell_split.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(INC_PLUS) $(SHOBJ_XLDFLAGS) -o $@ $< $(SHOBJ_LIBS)

tilde_expand:	tilde_expand.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(INC_PLUS) $(SHOBJ_XLDFLAGS) -o $@ $< $(SHOBJ_LIBS)

shell_split.o: shell_split.c

tilde_expand.o: tilde_expand.c
