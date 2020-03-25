#include "ast.h"

AST generate_AST(t_node* root) {
    if(root == NULL) {
        return NULL;
    }

    AST ast = (AST) malloc(sizeof(AST_Node));
    
    create_AST_Util(root);

    ast = root->tree_node;

    return ast;
}

void create_AST_Util(t_node* node) {
    if(node == NULL) {
        return;
    }

    t_node* temp = node->child;

    while(temp) {
        create_AST_Util(temp);
        temp = temp->sibling;
    }

    if(node->rule_num == 0)
        return;

    convert_to_AST_node(node);
    return;

}

AST create_leaf_node(t_node* parse_tree_node) {
    int label = -1;
    int tag = 0;
    int rule_num = parse_tree_node->rule_num;
    AST parent = parse_tree_node->parent->tree_node;
    AST child = NULL;
    AST next = NULL;
    Node* node = (Node*) malloc(sizeof(Node)); 
    *(node) = parse_tree_node->node.leaf;

    return create_node(label, tag, rule_num, parent, child, next, node);
}

AST create_node(Label label, int tag, int rule_num, AST parent, AST child, AST next, Node* node) {
    AST new_node = (AST) malloc(sizeof(AST_Node));

    new_node->label = label;
    new_node->tag = tag;
    new_node->rule_num = rule_num;
    new_node->parent = parent;
    new_node->child = child;
    new_node->next = next;
    new_node->leaf_token = node;

    return new_node;
}

void convert_to_AST_node(t_node* node) {
    int rule_num = node->rule_num;

    switch(rule_num) {
        
        case 3:
        case 6:
        case 10:
        case 13:
        case 16:
        case 32:
        case 34:
        case 49:
        case 61:
        case 64:
        case 74:
        case 77:
        case 95:
        case 99:
        case 112:
            node->tree_node = NULL;
            break;

        case 33:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 45:
        case 50:
        case 51:
        case 53:
        case 54:
        case 66:
        case 79:
        case 97:
        case 106:
            node->tree_node = node->child->tree_node;
            break;

        case 30:
        case 48:
        case 55:
        case 60:
        case 70:
        case 78:
            node->tree_node = node->child->sibling->tree_node;
            break;

        case 9:
            node->tree_node = node->child->sibling->sibling->tree_node;
            break;

        case 17:
        case 18:
        case 19:
        case 21:
        case 22:
        case 23:
        case 25:
        case 26:
        case 27:
        case 43:
        case 44:
        case 46:
        case 47:
        case 57:
        case 58:
        case 67:
        case 68:
        case 69:
        case 80:
        case 81:
        case 82:
        case 83:
        case 84:
        case 85:
        case 86:
        case 87:
        case 88:
        case 89:
        case 90:
        case 91:
        case 92:
        case 93:
            node->tree_node = create_leaf_node(node->child);
            node->child->tree_node->parent = node->tree_node;
            break;

    }
}

