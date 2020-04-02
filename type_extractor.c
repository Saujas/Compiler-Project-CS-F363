#include "type_extracator.h"

int get_types(AST root) {
    if(!root) {
        return;
    }
    AST temp = root->child;
    while(temp) {
        get_types(temp);
        temp = temp->sibling;
    }
    get_type_of_node(root);
    return;
} 

int get_type_of_node(AST node) {
    if (node->rule_num == 42 && node->tag == 1) {
        node->data_type = ;

    }

}