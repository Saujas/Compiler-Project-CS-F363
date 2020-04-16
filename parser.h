// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include "parser_def.h"
#include "stack.h"

/* Defined name of grammar file here which can be changed as suited
*/
#define GRAMMAR_FILE "grammar.txt"
#define MAX_RULE_LENGTH 500

/* Function definitions for all functions used in parser. Detailed descriptions in parser.c
*/
t_node** parser(char* filename, char* output_fname, int* has_parsed, int flag);
int parse_tokens(Node** token_stream, int tokens_parsed);
int read_grammar(char* filename);
int addRule(rules** grammar, symbol* rule, symbol nt, int count_of_symbols, int rule_num);//new additions
int main_parser(char* filename);
symbol convert_to_symbol(char* str);
first_set compute_first_set(int nt);
int find_first_sets();
follow_set compute_follow_set(int nt, int* changed);
int find_follow_sets();
first_set find_first_set_rule(symbol* rule, int count);
int create_parse_table();
int print_parse_table();
int check_if_exists(follow_set current_set, tokens t);
int check_if_duplicate_first(first_set current_set, tokens t);
int merge_first_first(first_set *current_set, first_set new_set, int add_e);
int merge_follow_first(follow_set *current_set, first_set new_set);
int merge_follow_follow(follow_set *current_set, follow_set new_set);
int max(int a, int b);
stack* initialize_stack();