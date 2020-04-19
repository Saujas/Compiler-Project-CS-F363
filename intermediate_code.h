// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include "intermediate_code_def.h"
#include "label.h"

/* Function definitions for all functions used in intermediate code generation. Detailed descriptions in intermediate_code.c
*/
int process_node(AST node, tuple_list* list);
void generate_ir_util(AST node, tuple_list* list);
tuple_list* generate_ir(AST root);
void add_tuple(tuple_list* list, Tuple t);
Tuple make_tuple(oper op, char* arg1, char* arg2, char* result, Symbol_Node* node1, Symbol_Node* node2, Symbol_Node* node3);
Temporary create_temporary();
char* create_label();
void add_temp_symboltable(Symbol_Node* symbol, Symbol_Table_Tree parent_scope, int width);
Temporary evaluate_expression(AST node, tuple_list* list, Symbol_Table_Tree parent_scope);
Temporary evaluate_array(AST node, AST index, tuple_list* list, Symbol_Table_Tree parent_scope);
char* get_limit(AST node, int id);
void print_tuple(Tuple t);
void print_tuple_list(tuple_list* list);