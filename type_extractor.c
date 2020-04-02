#include "type_extractor.h"

int get_types(AST root) {
    if(!root) {
        return;
    }
    AST temp = root->child;
    while(temp) {
        get_types(temp);
        temp = temp->next;
    }
    get_type_of_node(root);
    return;
} 

int get_type_of_node(AST node) {
    switch(node->rule_num) {
        case 42:
            if(node->tag == 1) {
                if(node->child->symbol_table_node->datatype == 3)
                    node->data_type = node->child->symbol_table_node->array_datatype;
                else
                    node->data_type = node->child->symbol_table_node->datatype;
            }
            break;
        
        case 43:
        case 67:
            if(node->tag == 0)
                node->data_type = 0;
            break;

        case 44:
        case 68:
            if(node->tag == 0)
                node->data_type = 1;
            break;
        
        case 46:
        case 47:
        case 92:
        case 93:
            if(node->tag == 0)
                node->data_type = 2;
            break;

        case 65:
            if(node->tag == 1)
                node->data_type = node->child->next->data_type;
            break;

        case 69:
            if(node->tag == 0)
                node->data_type = node->symbol_table_node->datatype;
            break;
        
    }    
}