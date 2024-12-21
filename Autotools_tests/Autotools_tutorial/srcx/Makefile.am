# Some kind of language built with variable names
bin_PROGRAMS = hello
hello_SOURCES = main.c

lib_LTLIBRARIES = libgreet.la
libgreet_la_SOURCES = greet.c

hello_LDADD = $(lib_LTLIBRARIES)
