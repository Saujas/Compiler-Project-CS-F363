#include "intermediate_code_def.h"
#include "label.h"

void process_node(AST node, tuple_list* list);
void generate_ir_util(AST node, tuple_list* list);
tuple_list* generate_ir(AST root);
void add_tuple(tuple_list* list, Tuple t);
Tuple make_tuple(oper op, char* arg1, char* arg2, char* result, Symbol_Node* node1, Symbol_Node* node2, Symbol_Node* node3);

Temporary create_temporary();
void add_temp_symboltable(Symbol_Node* symbol, Symbol_Table_Tree parent_scope, int width);

Temporary evaluate_expression(AST node, tuple_list* list, Symbol_Table_Tree parent_scope);
Temporary evaluate_array(AST node, tuple_list* list, Symbol_Table_Tree parent_scope);

void print_tuple(Tuple t);
void print_tuple_list(tuple_list* list);