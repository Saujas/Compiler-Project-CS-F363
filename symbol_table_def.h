#ifndef _SYMBOLTABLEDEF_
#define _SYMBOLTABLEDEF_

#include <stdio.h>
#include <stdlib.h>

#include "ast_def.h"
#include "label.h"
typedef struct ast_node* AST;
typedef struct symbol_node Symbol_Node;

#define SYMBOL_TABLE_SLOTS 41

union array_range {
    Symbol_Node* id;
    int value;
};

typedef struct {
    union array_range range_pointer;
    int tag;
} Range;


struct symbol_node {
    AST node;
    int datatype;
    int assigned;
    int width;
    int offset;
    void* memory;
    int usage;
    Range range[2];
    int array_datatype;
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

struct symbol_table {
    Slots_List** slots;
    int number_of_slots;
};

typedef struct symbol_table Symbol_Table;

struct symbol_table_tree_node {
    Symbol_Table* table;

    struct symbol_table_tree_node* parent;
    struct symbol_table_tree_node* child;
    struct symbol_table_tree_node* sibling;

    int is_defined;
    int is_declared;
    int is_called;

    Label label;
    char* name;
    
};

typedef struct symbol_table_tree_node* Symbol_Table_Tree;

#endif