%{
#include    "tree.h"
%}

%union {
    struct expr *expr;
    struct term *term;
}

%type <expr> expression;
%type <term> term;

%token IDENTIFIER

%start main

%%

main:
    expression  {print_expr($1); printf("\n");}
;

expression:
    expression '-' term
    {$$ = new_expr(); $$->type = '-'; $$->expr = $1; $$->term = $3;}
|
    term
    {$$ = new_expr(); $$->type = 'T'; $$->expr = $1; $$->term = $1;}
;

term:
    IDENTIFIER
    {$$ = new_term(); $$->type = 'I';}
;

%%

#include    "lex.h"

int main(void){
    start_lex();
    yyparse();
    return 0;
}

int yylex(void){
    get_next_token();
    return Token.class;
}
