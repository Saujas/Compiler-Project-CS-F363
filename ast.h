#include<stdio.h>
#include<stdlib.h>
#include "ast_def.h"
#include "tree.h"

AST generate_AST(t_node* root);
void create_AST_Util(t_node* node);
AST create_leaf_node(t_node* parse_tree_node, int label, int rule_num);
AST create_NT_node(Label label, int tag, int rule_num, AST parent, AST child, AST next, Node* node);
void link_children(t_node* node);
void link_parent(t_node* node);
void convert_to_AST_node(t_node* node);
void print_ast(AST root);
void print_ast_node(AST node);
AST extract_inherited(t_node* node);
t_node* get_switch_end_node(t_node* temp);