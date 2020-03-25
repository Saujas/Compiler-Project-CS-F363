// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#ifndef TREE
#define TREE

#include"lexer_def.h"
#include"parser_def.h"
#include "ast_def.h"
#include<stdio.h>
#include<stdlib.h>

/* A union of a tree node element which can either be a leaf (token), or an internal node (non-terminal)
*/
typedef union {
    Node leaf;
    non_terminals internal; 
} tnode_ele;

/* A structure of a tree node which contains the above union element, a tag for identification of the union,
   and a pointer to a child and sibling of the tree node
*/
typedef struct tn {
    tnode_ele node;
    int tag;
    struct tn* sibling;
    struct tn* child;
    struct tn* parent;//new additions
    int rule_num;//new additions

    // FOR AST
    AST tree_node;
    AST tree_node_inh;
} t_node;

/* Function definitions for all functions used in tree. Detailed descriptions in tree.c
*/
int insert_node(t_node** parent, t_node *child);
t_node* create_leaf(Node n);
t_node* create_internal(non_terminals nt);
int inorder_traversal(t_node* root, non_terminals parent, FILE* fp);
t_node* initialize_tree();
int print_tnode(t_node* n, non_terminals parent, FILE* fp);
int print_parse_tree(t_node* root, char* fname);

#endif