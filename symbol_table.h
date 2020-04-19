// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table_def.h"
#include "parser_def.h"
#include "lexer_def.h"
#include "ast_def.h"
#include "semantic_analyzer_def.h"

/* Function definitions for all functions used in symbol table. Detailed descriptions in symbol_table.c
*/
int check_if_defined(Symbol_Table_Tree current, char* lexeme);
int check_if_declared(Symbol_Table_Tree current, char* lexeme);
void insert_symbol(Symbol_Table* symbol_table, char* key, Symbol_Node* node);
int hash_symbol_table(char* key, int slots);
Symbol_Node* search_symbol_table(char* id, Symbol_Table_Tree table_tree_node);
Symbol_Node* search_current_scope(char* id, Symbol_Table_Tree table_tree_node);
Symbol_Table* create_symbol_table(int slots);
Symbol_Table_Tree make_symbol_table_tree_node(Symbol_Table_Tree parent, Label label, char* name, int is_function, int start, int end, int level);
Symbol_Table_Tree create_symbol_table_tree(AST root, ErrorList* err, int flag);
Symbol_Node* make_symbol_node(AST node, int datatype, int assigned, int width, int width2, int offset, int offset2, int usage, Range range[2], int array_datatype);
void traverse_ast(AST node, Symbol_Table_Tree current, ErrorList* Err, Slots_List* print_slot_list, Symbol_List** print_list);
void print_symbol_tables(Symbol_Table_Tree tree);
void print_slots(Symbol_Table* table);
void print_symbols(Slots_List* list);
Symbol_Table_Tree get_parent_scope(Symbol_Table_Tree current);
void make_symbol_list(Slots_List* list, Symbol_Node* node, Symbol_List** temp);
void print_all_symbols(Symbol_List *list);
void print_array_info(Symbol_List *list);
void print_activation_record_sizes(Symbol_Table_Tree tree);