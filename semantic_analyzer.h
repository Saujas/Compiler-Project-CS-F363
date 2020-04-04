#include "type_extractor.h"

int check_bound(AST index, AST var);
int type_check_node(AST node);
void type_checker(AST root);
void print_identifier(AST_list* head);
void add_identifier(AST node, AST index, AST_list** head);
void check_identifier(AST node, AST_list** head);
int check_if_redeclared_in_scope(AST_list** head);
int compare_list_node(AST_list** head, AST id, AST index);
void check_if_modified(AST_list** head, AST node, int* current);