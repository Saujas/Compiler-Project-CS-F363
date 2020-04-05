#include "type_extractor.h"
#include "semantic_analyzer_def.h"

int check_bound(AST index, AST var);
int type_check_node(AST node, ErrorList* err);
void type_checker(AST root, ErrorList* err);
void print_identifier(AST_list* head);
void add_identifier(AST node, AST index, AST_list** head);
void check_identifier(AST node, AST_list** head);
int check_if_redeclared_in_scope(AST_list** head);
int compare_list_node(AST_list** head, AST id, AST index);
void check_if_modified(AST_list** head, AST node, int* current);
int convert_to_list(Symbol_Table_Tree st, Symbol_Node*** head);
int verify_types(AST nt, Symbol_Node*** head, int total, int count, int curr);
void check_if_output_modified(Symbol_Node* sym, AST node, int* current);

ErrorList* initialize_errors();
void add_sem_error(ErrorList* list, char* str, int line_num);
void sort_errors(ErrorList* list);
void sort_errors_util(Error* temp, int count);
void print_errors(ErrorList* errors);


