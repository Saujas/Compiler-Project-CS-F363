#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table_def.h"
#include "parser_def.h"
#include "lexer_def.h"
#include "ast_def.h"
#include "semantic_analyzer_def.h"

int check_if_defined(Symbol_Table_Tree current, char* lexeme);
int check_if_declared(Symbol_Table_Tree current, char* lexeme);
void insert_symbol(Symbol_Table* symbol_table, char* key, Symbol_Node* node);
int hash_symbol_table(char* key, int slots);
Symbol_Node* search_symbol_table(char* id, Symbol_Table_Tree table_tree_node);
Symbol_Node* search_current_scope(char* id, Symbol_Table_Tree table_tree_node);
Symbol_Table* create_symbol_table(int slots);
Symbol_Table_Tree make_symbol_table_tree_node(Symbol_Table_Tree parent, Label label, char* name, int is_function);
Symbol_Table_Tree create_symbol_table_tree(AST root, ErrorList* err);
Symbol_Node* make_symbol_node(AST node, int datatype, int assigned, int width, int offset, void* memory, int usage, Range range[2], int array_datatype);
void traverse_ast(AST node, Symbol_Table_Tree current, ErrorList* Err);
void print_symbol_tables(Symbol_Table_Tree tree);
void print_slots(Symbol_Table* table);
void print_symbols(Slots_List* list);
