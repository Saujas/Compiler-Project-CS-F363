#ifndef _SYMBOLTABLEDEF_
#define _SYMBOLTABLEDEF_

#include <stdio.h>
#include <stdlib.h>

#include "ast_def.h"
#include "label.h"

typedef struct ast_node* AST;

#define SYMBOL_TABLE_SLOTS 41

struct symbol_node {
    AST node;
    int datatype;
    int assigned;
    int width;
    int offset;    
};

typedef struct symbol_node Symbol_Node;

struct symbol_list {
    Symbol_Node* symbol;
    struct symbol_list* next;
};

typedef struct symbol_list Symbol_List;

struct slots_list {
    Symbol_List* head;
    int count;
};

typedef struct slots_list Slots_List;

struct symbol_table{
    Slots_List** slots;
    int number_of_slots;
};

typedef struct symbol_table Symbol_Table;

struct symbol_table_tree_node {
    Symbol_Table* table;

    struct symbol_table_tree_node* parent;
    struct symbol_table_tree_node* child;
    struct symbol_table_tree_node* sibling;

    Label label;
    char* name;
    
};

typedef struct symbol_table_tree_node* Symbol_Table_Tree;

#endif