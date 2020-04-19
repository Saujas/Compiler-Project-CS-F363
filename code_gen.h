// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "intermediate_code_def.h"
#include "lexer_def.h"
#include "parser_def.h"
#include "symbol_table_def.h"
#include "ast_def.h"

/* Function definitions for all functions used in code generation. Detailed descriptions in code_gen.c
*/
int generate_code(tuple_list* list, Symbol_Table_Tree tree, char* filename);
int generate_tuple_code(tuple* tup, Symbol_Table_Tree tree, FILE* fp);
int get_ar_size(tuple* tup, Symbol_Table_Tree tree, FILE* fp);
char* read_operand(Symbol_Node* node, char* arg);
int check_if_float(char* str);
char* generate_dynamic_label();
void print_args(struct tup* tup);