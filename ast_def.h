#ifndef _AST_
#define _AST_

#include <stdio.h>
#include "parser_def.h"
#include "symbol_table_def.h"
#include "label.h"

typedef struct symbol_table_tree_node* Symbol_Table_Tree;
typedef struct symbol_node Symbol_Node;

typedef struct ast_node {
    Label label;
    int tag;
    int rule_num;
    
    struct ast_node* parent;
    struct ast_node* next;
    // struct ast_node* concatenated;
    struct ast_node* child;

    Node* leaf_token;

    Symbol_Node* symbol_table_node;

    Symbol_Table_Tree current_scope;

} AST_Node;

typedef AST_Node* AST;

typedef struct list_AST {
    AST node;
    AST index;
    struct list_AST* next;
} AST_list;

#endif