#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "intermediate_code_def.h"
#include "lexer_def.h"
#include "parser_def.h"
#include "symbol_table_def.h"
#include "ast_def.h"

int generate_code(tuple_list* list, Symbol_Table_Tree tree, char* filename);
int generate_tuple_code(tuple* tup, FILE* fp);
int initialize_bss(tuple_list* list, Symbol_Table_Tree tree, FILE* fp);
char* read_operand(Symbol_Node* node, char* arg);
int check_if_float(char* str);
void print_args(struct tup* tup);