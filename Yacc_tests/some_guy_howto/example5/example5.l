%{
#include <stdio.h>
#include "y.tab.h"
// This line was not in the how-to, but I needed to add it
// otherwise, I was getting 'example.l:9:1 error: 'yylval' undeclared
extern int yylval;
%}
%%
[0-9]+                  yylval=atoi(yytext); return NUMBER;
heat                    return TOKHEAT;
on|off                  yylval=!strcmp(yytext,"on"); return STATE;
target                  return TOKTARGET;
temperature             return TOKTEMPERATURE;
\n                      /* ignore end of line */;
[ \t]+                  /* ignore whitespace */;
%%
