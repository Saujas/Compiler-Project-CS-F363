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

AST create_leaf_node(t_node* parse_tree_node, int label) {
    int l = label;
    int tag = 0;
    int rule_num = parse_tree_node->rule_num;
    AST parent = parse_tree_node->parent->tree_node;
    AST child = NULL;
    AST next = NULL;
    Node* node = (Node*) malloc(sizeof(Node));
    *(node) = parse_tree_node->node.leaf;

    return create_node(l, tag, rule_num, parent, child, next, node);
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

void link_children(t_node* node) {

    t_node* temp = node;

    while(temp->sibling) {
        temp->tree_node->next = temp->sibling->tree_node;
        temp = temp->sibling;
    }

    return;
}

void link_parent(t_node* node) {
    
    t_node* temp = node;

    while(temp) {
        temp->tree_node->parent = temp->parent->tree_node;
        temp = temp->sibling;
    }

    return;
}

void convert_to_AST_node(t_node* node) {
    int rule_num = node->rule_num;

    Label label;
    int tag;
    AST parent = NULL;
    AST child = NULL;
    AST sibling = NULL;

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

        // 15 rules done

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
        case 110:
            node->tree_node = node->child->tree_node;
            break;

        // 31 rules done

        case 30:
        case 48:
        case 55:
        case 60:
        case 70:
        case 78:
        case 109:
            node->tree_node = node->child->sibling->tree_node;
            break;

        // 38 rules done

        case 9:
        case 41:
        case 111:
            node->tree_node = node->child->sibling->sibling->tree_node;
            break;

        // 41 rules done

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
            node->tree_node = create_leaf_node(node->child, -1);
            // node->child->tree_node->parent = node->tree_node->parent;
            break;

        // 73 rules done

        case 1:
            label = PROGRAM;
            tag = 1;
            child = node->child->tree_node;

            link_children(node->child);
            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);

            break;

        case 2:
        case 5:
        case 31:
        case 65:
        case 107:
            if (rule_num == 2)
                label = MODULE_DECLARATIONS;
            else if(rule_num == 5)
                label = OTHER_MODULES;
            else if(rule_num==31)
                label = STATEMENTS;
            else if(rule_num==65)
                label = EXPRESSION;
            else if(rule_num==107)
                label = NUMERIC_CASES;

            tag = 1;
            child = node->child->tree_node;

            link_children(node->child);
            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 4:
            node->tree_node = create_leaf_node(node->child->sibling->sibling, MODULE_DECLARATION);
            // node->child->tree_node->parent = node->tree_node->parent;
            break;

        case 7:
            label = DRIVER;
            tag = 1;
            child = node->child->sibling->sibling->sibling->sibling->tree_node;

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 8:
            label = MODULE;
            tag = 1;
            child = create_leaf_node(node->child->sibling->sibling, -1);
 
            t_node* temp = node->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling;
            child->next = temp->tree_node;
            
            t_node* temp2 = temp;
            temp = temp->sibling->sibling->sibling;

            if(temp->tree_node != NULL) {
                temp2->tree_node->next = temp->tree_node;
                
                temp2 = temp;
                temp = temp->sibling;
                temp2->tree_node->next = temp->tree_node;
            }
            else {
                temp = temp->sibling;
                child->next->next = temp->tree_node;
            }
            
            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 11:
        case 14:
            if(rule_num == 11)
                label = INPUT_PLIST;
            else if(rule_num == 14)
                label = OUTPUT_PLIST;

            tag = 1;
            child = create_leaf_node(node->child, -1);

            child->next = node->child->sibling->sibling->tree_node;
            child->next->next = node->child->sibling->sibling->sibling->tree_node;

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 12:
        case 15:
            if (rule_num == 12)
                label = NEW1;
            else if (rule_num == 15)
                label = NEW2;

            tag = 1;
            child = create_leaf_node(node->child->sibling, -1);

            child->next = node->child->sibling->sibling->sibling->tree_node;
            child->next->next = node->child->sibling->sibling->sibling->sibling->tree_node;

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 20:
        case 24:
            if (rule_num == 20)
                label = DATA_TYPE;
            else if (rule_num == 24)
                label = DATA_TYPE2;

            tag = 1;

            child = node->child->sibling->sibling->tree_node;
            child->next = node->child->sibling->sibling->sibling->sibling->sibling->tree_node;

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 28:
            label = RANGE;
            tag = 1;

            child = create_leaf_node(node->child, -1);
            child->next = create_leaf_node(node->child->sibling->sibling, -1);

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 29:
            label = RANGE2;
            tag = 1;

            child = node->child->tree_node;
            child->next = node->child->sibling->sibling->tree_node;

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;
        
        case 40:
            node->tree_node = create_leaf_node(node->child->sibling->sibling, -1);
            break;

        case 42:
        case 52:
        case 62:
            if(rule_num==42)
                label = VAR;
            else if(rule_num==52)
                label = ASSIGNMENT_STMT;
            else if(rule_num==62)
                label = ID_LIST;
            
            tag = 1;

            child = create_leaf_node(node->child, -1);
            child->next = node->child->sibling->tree_node;

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 56:
            label = LVALUE_ARR_STMT;
            tag = 1;

            child = node->child->sibling->tree_node;
            child->next = node->child->sibling->sibling->sibling->sibling->tree_node;

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 59: 
            label = MODULE_REUSE_STMT;
            tag = 1;

            t_node* temp = node->child;

            if(temp->tree_node != NULL) {
                child = temp->tree_node;
                child->next = create_leaf_node(node->child->sibling->sibling->sibling, -1);
                child->next->next = node->child->sibling->sibling->sibling->sibling->sibling->sibling->tree_node;
            }
            else {
                child = create_leaf_node(node->child->sibling->sibling->sibling, -1);
                child->next = node->child->sibling->sibling->sibling->sibling->sibling->sibling->tree_node;
            }

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 63:
            label = NEWX;
            tag = 1;

            child = create_leaf_node(node->child->sibling, -1);
            child->next = node->child->sibling->sibling->tree_node;

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 100:
            label = DECLARE_STMT;
            tag = 1;

            child = node->child->sibling->tree_node;
            child->next = node->child->sibling->sibling->sibling->tree_node;

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 101:
            label = FOR;
            tag = 1;

            child = create_leaf_node(node->child->sibling->sibling, -1);
            child->next = node->child->sibling->sibling->sibling->sibling->tree_node;
            child->next->next = node->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->tree_node;

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 102:
            label = WHILE;
            tag = 1;

            child = node->child->sibling->sibling->tree_node;
            child->next = node->child->sibling->sibling->sibling->sibling->sibling->tree_node;

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 103:
            label = CONDITIONAL_STMT;
            tag = 1;

            child = create_leaf_node(node->child->sibling->sibling, -1);
            child->next = node->child->sibling->sibling->sibling->sibling->sibling->sibling->tree_node;

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 104:
        case 105:
            if(rule_num==104)
                label = CASE_STMT_T;
            else if(rule_num==105)
                label = CASE_STMT_F;

            tag = 1;
            t_node* temp = node->child->sibling->sibling;

            if(temp->tree_node == NULL) {
                child = node->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->tree_node;
            }
            else {
                child = temp->tree_node;
                child->next = node->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->tree_node;
            }

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 108:
            label = NUMERIC_CASE;
            tag = 1;

            child = create_leaf_node(node->child, -1);
            child->next = node->child->sibling->sibling->tree_node;

            node->tree_node = create_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

    }
}

