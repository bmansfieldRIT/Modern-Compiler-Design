/*
* A trivial code generator for the demo compiler of Section 1.2
*/

#include    "parser.h"      /* for types AST_node and Expression */
#include    "thread.h"      /* for Thread_AST() and Thread_start */
#include    "backend.h"     /* for self-check */
#include    "stack.h"
                    /* PRIVATE */
static AST_node *Active_node_pointer;

void Expression_D(int digit){
    Push(digit);
}

void Expression_P(int oper){
    int e_left = Pop();
    int e_right = Pop();
    switch(oper){
        case '+':
            Push(e_left + e_right);
            break;
        case '*':
            Push(e_left * e_right);
            break;
    }
}

void Print(void){
    printf("%d\n", Pop());
}

static void Trivial_code_generation(void){
    printf("#include    \"stack.h\"nint main(void) {\n")
    while (Active_node_pointer != 0){
        /* there is only one type, Expression: */
        switch(expr->type) {
            case 'D':
                printf("Expression_D(%d);\n", expr->value);
                break;
            case 'P':
                printf("Expression_P(%d);", expr->value);
                break;
        }
        Active_node_pointer = Active_node_pointer->successor;
    }
    printf("Print()");
    printf("return 0;}\n");
}
                    /* PUBLIC */
void Process(AST_node *icode){
    Thread_AST(icode);
    Active_node_pointer = Thread_start;
    Trivial_code_generation();
}
