#include "lex.h"
#include <stdio.h>

int main(void){
    start_lex();
    do {
        get_next_token();
        switch (Token.class){
            case IDENTIFIER:
                printf("Identifier: %s\n", Token.repr);
                break;
            case INTEGER:
                printf("Integer: %s\n", Token.repr);
                break;
            case ERRONEOUS:
                printf("Erroneous Token: %s\n", Token.repr);
                break;
            case EOF:
                printf("End-of-file pseudotoken: %s\n", Token.repr);
                break;
            default:
                printf("Operator or separator: %s\n", Token.repr);
                break;
        }
    } while (Token.class != EOF);
    return 0;
}
