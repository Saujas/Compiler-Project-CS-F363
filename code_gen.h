#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "intermediate_code_def.h"
#include "lexer_def.h"
#include "parser_def.h"
#include "symbol_table_def.h"
#include "ast_def.h"

int generate_code(tuple_list* list, char* filename);
int generate_tuple_code(tuple* tup, FILE* fp);
void print_args(struct tup* tup);