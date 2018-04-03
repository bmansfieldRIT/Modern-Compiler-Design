/*
* LLGen code for an L-attributed grammar for simple expressions
*/

{
#include    "symbol_table.h"
}

%lexical get_next_token_class;
%token IDENTIFIER;
%token DIGIT;

%start Main_Program, main;

main {symbol_table sym_tab; int result;}:
    {init_symbol_table(&sym_tab);}
    declarations(sym_tab)
    expression(sym_tab, &result)
    {prints("result = %d\n", result);}
;

declarations(symbol_table sym_tab):
    declaration(sym_tab) [ ',' declaration(sym_tab) ]* ';'
;

declarations(symbol_table sym_tab) {symbol_entry *sym_snt;}:
    IDENTIFIER {sym_ent = look_up(sym_tab, Token.repr);}
    '=' DIGIT  {sym_ent->value = Token.repr - '0';}
;

expression(symbol_table, sym_tab; int *e) {int t;}:
    term(sym_tab, &t)                   {*e = t;}
    expression_tail_option(sym_tab, e)
;

expression_tail_option(symbol_table, sym_tab; int *e) {int t;}:
    '-' term(sym_tab, &t)               {*e -= t;}
    expression_tail_option(sym_tab, e)
|
;

term(symbol_table sym_tab; int *t):
    IDENTIFIER      {*t = look_up(sym_tab, Token.repr)->value;}
;
