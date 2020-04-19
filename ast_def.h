// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#ifndef _AST_
#define _AST_

#include <stdio.h>
#include "parser_def.h"
#include "symbol_table_def.h"
#include "label.h"

typedef struct symbol_table_tree_node* Symbol_Table_Tree;
typedef struct symbol_node Symbol_Node;

// Structure for a node of the abstract syntax tree
// Contains a pointer to a lexeme for all leaf nodes
// Also has a pointer for symbol table node created later for variables
typedef struct ast_node {
    Label label;
    int tag;
    int rule_num;
    
    struct ast_node* parent;
    struct ast_node* next;
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