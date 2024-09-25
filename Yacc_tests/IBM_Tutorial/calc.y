%{
#include <stdio.h>
%}

%token INTEGER
%left '+' '-'
%left '*' '/'

%%

program:
                program expression '\n'         = { printf("RESULT: %d\n", $2); }
|               /* NOTHING */
;

expression:
                INTEGER
|               expression '+' expression       = { printf("Doing an addition\n"); $$ = $1 + $3; }
|               expression '-' expression       = { $$ = $1 - $3; }
|               expression '*' expression       = { $$ = $1 * $3; }
|               expression '/' expression       = { $$ = $1 / $3; }
;
