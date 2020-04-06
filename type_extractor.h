#include <stdio.h>
#include<stdlib.h>

#include "symbol_table_def.h"
#include "ast_def.h"
#include "label.h"
#include "semantic_analyzer_def.h"

int get_id_type(AST node);
int extract_type(AST node, ErrorList* err);
