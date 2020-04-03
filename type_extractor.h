#include <stdio.h>
#include<stdlib.h>
#include "symbol_table_def.h"
#include "ast_def.h"
#include "label.h"

int check_bound(AST index, AST var);
int type_check_node(AST node);
int get_id_type(AST node);
int extract_type(AST node);
void type_checker(AST root);
