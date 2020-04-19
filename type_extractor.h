// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include <stdio.h>
#include<stdlib.h>

#include "symbol_table_def.h"
#include "ast_def.h"
#include "label.h"
#include "semantic_analyzer_def.h"

/* Function definitions for all functions used in type extractor. Detailed descriptions in type_extractor.c
*/
int get_id_type(AST node);
int extract_type(AST node, ErrorList* err);
