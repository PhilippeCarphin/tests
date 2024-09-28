#include <stdio.h>
extern int yyparse(void);
int main(void){
    yyparse();
}

void yyerror(char *s){
    fprintf(stderr, "%s\n", s);;
}

int yywrap(void){
    return 1;
}
