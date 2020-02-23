#ifndef TREE
#define TREE

#include"lexer_def.h"
#include"parser_def.h"
#include<stdio.h>
#include<stdlib.h>

typedef union {
    Node leaf;
    non_terminals internal; 
} tnode_ele;

typedef struct tn {
    tnode_ele node;
    int tag;
    struct tn* sibling;
    struct tn* child;
} t_node;

int insert_node(t_node** parent, t_node *child);
t_node* create_leaf(Node n);
t_node* create_internal(non_terminals nt);
int inorder_traversal(t_node* root, non_terminals parent);
t_node* initialize_tree();
int print_tnode(t_node* n, non_terminals parent);

#endif