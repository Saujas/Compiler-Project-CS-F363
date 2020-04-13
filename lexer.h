// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include <float.h>
#include "lexer_def.h"
#include "lookup_table.h"

/* Function definitions for all functions used in lexer. Detailed descriptions in lexer.c
*/
FILE* open_file(char* filename);
int string_flush(char *str);
int get_stream(FILE* fp, int offset);
Node* create_node();
int add_error(char ch);
Node* get_next_token(FILE* fp, lookup_table table);
int lexical_analyzer(char* filename, Node*** n, lookup_table** table, int check);
int print_without_comments(char* filename);
