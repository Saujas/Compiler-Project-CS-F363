#include "parser_def.h"
#include "stack.h"

#define GRAMMAR_FILE "grammar.txt"
#define MAX_RULE_LENGTH 500

int parser(char* filename);
int parse_tokens(Node** token_stream, int tokens_parsed);
int read_grammar(char* filename);
int addRule(rules** grammar, symbol* rule, symbol nt, int count_of_symbols);
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