// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include<stdio.h>
#include<stdlib.h>
#include "ast_def.h"
#include "tree.h"

/* Function definitions for all functions used in AST creation. Detailed descriptions in ast.c
*/
AST generate_AST(t_node* root, int flag);
void create_AST_Util(t_node* node);
AST create_leaf_node(t_node* parse_tree_node, int label, int rule_num);
AST create_NT_node(Label label, int tag, int rule_num, AST parent, AST child, AST next, Node* node);
void link_children(t_node* node);
void link_parent(t_node* node);
void convert_to_AST_node(t_node* node);
void print_ast(AST root, AST parent);
void print_ast_preorder(AST root, AST parent);
void print_ast_node(AST node, AST parent);
AST extract_inherited(t_node* node);
t_node* get_switch_end_node(t_node* temp);
void count_parse_tree_nodes(t_node* root, int* count, int *size);
void count_ast_nodes(AST root, int* count, int *size);
void calculate_allocated_memory(t_node* root, AST tree);