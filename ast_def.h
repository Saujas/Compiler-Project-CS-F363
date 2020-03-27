#ifndef _AST_
#define _AST_

#include <stdio.h>
#include "parser_def.h"
#define AST_LABEL_NUMBER 36

typedef enum {
    AST_PROGRAM, MODULE_DECLARATIONS, MODULE_DECLARATION, OTHER_MODULES, AST_DRIVER, AST_MODULE, INPUT_PLIST, NEW1,
    OUTPUT_PLIST, NEW2, DATA_TYPE, DATA_TYPE2, RANGE, RANGE2, STATEMENTS, VAR, ASSIGNMENT_STMT, 
    LVALUE_ARR_STMT, MODULE_REUSE_STMT, ID_LIST, NEWX, EXPRESSION, NEW6, NEW7, NEW8, RELATIONAL_EXPR, 
    DECLARE_STMT, AST_FOR, AST_WHILE, CONDITIONAL_STMT, CASE_STMT_T, CASE_STMT_F, NUMERIC_CASES, NUMERIC_CASE, IO_READ,
    IO_WRITE
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