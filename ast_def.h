#ifndef _AST_
#define _AST_

#include <stdio.h>
#include "parser_def.h"
#include "symbol_table_def.h"
#include "label.h"

typedef struct ast_node {
    Label label;
    int tag;
    int rule_num;
    
    struct ast_node* parent;
    struct ast_node* next;
    // struct ast_node* concatenated;
    struct ast_node* child;

    Node* leaf_token;

    Symbol_Table_Tree* current_scope;

} AST_Node;

typedef AST_Node* AST;

#endif