#ifndef _AST_
#define _AST_

#include <stdio.h>
#include "parser_def.h"

typedef enum {
    PROGRAM, MODULE_DECLARATIONS, MODULE_DECLARATION, OTHER_MODULES, DRIVER, MODULE, INPUT_PLIST, NEW1,
    OUTPUT_PLIST, NEW2, DATA_TYPE, ARRAY, DATA_TYPE2, ARRAY2, TYPE, RANGE, RANGE2, STATEMENTS, INPUT_IO,
    OUTPUT_IO, VAR, VAR2, ASSIGNMENT_STMT, LVALUE_ARR_STMT, INDEX, MODULE_REUSE_STMT, ID_LIST, NEWX, EXPRESSION,
    NEW4, AORB_EXPRESSION, ARITHMETIC_EXPR, NEW6, TERM, NEW7, PLUS_MINUS, MUL_DIV, RELOP, LOGICALOP, BOOLKEY, 
    BOOL_EXPR, NEW8, RELATIONAL_EXPR, DECLARE_STMT, FOR, WHILE, CONDITIONAL_STMT, CASE_STMT_T, CASE_STMT_F, NUMERIC_CASES, 
    NUMERIC_CASE, NEW11, DEFAULT,
} Label;

typedef struct ast_node {
    Label label;
    int tag;
    int rule_num;
    
    struct ast_node* parent;
    struct ast_node* next;
    struct ast_node* concatenated;
    struct ast_node* child;

    Node* leaf_token;

} AST_Node;

typedef AST_Node* AST;

#endif