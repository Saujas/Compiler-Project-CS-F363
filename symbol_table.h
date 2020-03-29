#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table_def.h"
#include "parser_def.h"
#include "lexer_def.h"
#include "ast_def.h"

int check_if_defined(Symbol_Table_Tree current, char* lexeme);
int check_if_declared(Symbol_Table_Tree current, char* lexeme);
void insert_symbol(Symbol_Table* symbol_table, char* key, Symbol_Node* node);
int hash(char* key, int slots);
Symbol_Table* create_symbol_table(int slots);
Symbol_Table_Tree make_symbol_table_tree_node(Symbol_Table_Tree parent, Label label, char* name);
Symbol_Table_Tree create_symbol_table_tree(AST root);
Symbol_Node* make_symbol_node(AST node, int datatype, int assigned, int width, int offset, void* memory, int usage, Range range[2], int array_datatype);
void traverse_ast(AST node, Symbol_Table_Tree current);
