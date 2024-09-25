%{
#include "y.tab.h"
extern int yylval;
%}

%%

[[:digit:]]+    {
                yylval = atoi(yytext);
                return INTEGER;
        }

[-+/*\n]        return *yytext;

[ \t]+          ;
