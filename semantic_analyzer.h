// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include "semantic_analyzer_def.h"

/* Function definitions for all functions used in semantic analyzer. Detailed descriptions in semantic_analyzer.c
*/
int check_bound(AST index, AST var);
int type_check_node(AST node, ErrorList* err);
void type_checker(AST root, ErrorList* err, Symbol_Table_Tree tree);
void print_identifier(AST_list* head);
void add_identifier(AST node, AST index, AST_list** head);
void check_identifier(AST node, AST_list** head);
int check_if_redeclared_in_scope(AST_list** head, int *line_num, AST *temp);
int compare_list_node(AST_list** head, AST id, AST index);
void check_if_modified(AST_list** head, AST node, int* current, int* line_no);
int convert_to_list(Symbol_Table_Tree st, Symbol_Node*** head);
int verify_types(AST nt, Symbol_Node*** head, int total, int count, int curr, AST *list, int *error_count);
void check_if_output_modified(Symbol_Node* sym, AST node, int* current, AST *temp);
int is_valid_function(AST node, Symbol_Table_Tree root);
ErrorList* initialize_errors();
void add_sem_error(ErrorList* list, char* str, int line_num);
void sort_errors(ErrorList* list);
void sort_errors_util(Error* temp, int count);
void print_errors(ErrorList* errors);


