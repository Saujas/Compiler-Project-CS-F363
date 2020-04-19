// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include "ast.h"

// Array of strings of non-leaf AST nodes
char* ast_string_map[AST_LABEL_NUMBER] = {
    "AST_PROGRAM", "MODULE_DECLARATIONS", "MODULE_DECLARATION", "OTHER_MODULES", "AST_DRIVER", "AST_MODULE", "INPUT_PLIST", "NEW1",
    "OUTPUT_PLIST", "NEW2", "DATA_TYPE", "DATA_TYPE2", "RANGE", "RANGE2", "STATEMENTS", "VAR", "ASSIGNMENT_STMT", 
    "LVALUE_ARR_STMT", "MODULE_REUSE_STMT", "ID_LIST", "NEWX", "EXPRESSION", "NEW6", "NEW7", "NEW8", "RELATIONAL_EXPR", 
    "DECLARE_STMT", "AST_FOR", "AST_WHILE", "CONDITIONAL_STMT", "CASE_STMT_T", "CASE_STMT_F", "NUMERIC_CASES", "NUMERIC_CASE", "IO_READ", "IO_WRITE", "AST_DEFAULT"
};

// Array of strings of non terminals used in the grammar
char * ast_non_terminals_string_map[NON_TERMINAL_SIZE] = {"program", "moduleDeclarations", "moduleDeclaration", "otherModules", "driverModule", "module", "ret", "input_plist",
    "new1", "output_plist", "new2", "dataType", "dataType2", "type", "range", "range2", "moduleDef", "statements", "new3",
    "statement", "ioStmt", "var", "var2", "whichID", "simpleStmt", "assignmentStmt", "whichStmt", "lvalueIDstmt", "lvalueArrStmt", 
    "Index", "moduleReuseStmt", "optional", "idList", "newX", "expression", "new4", "AorBExpr", "arithmeticExpr", "new6",
    "term", "new7", "factor", "PlusMinus", "MulDiv", "relationalOP", "logicalOP", "boolKey", "boolExpr", "new8", "relationalExpr",
    "declareStmt", "iterativeStmt", "conditionalStatement", "caseStmt", "numericCases", 
    "numericCase", "new11", "Default", "NT_value"};

// Array of strings of terminals used in the grammar
char * t_string_map_copy1[TOKEN_NUMBERS] = {"INTEGER", "REAL", "BOOLEAN", "OF", "ARRAY", "START",
            "END", "DECLARE", "MODULE", "DRIVER", "PROGRAM", "GET_VALUE", "PRINT",
            "USE", "WITH", "PARAMETERS", "TRUE", "FALSE", "TAKES", "INPUT", "RETURNS",
            "AND", "OR", "FOR", "IN", "SWITCH", "CASE", "BREAK", "DEFAULT", "WHILE", "PLUS", 
            "MINUS", "MUL", "DIV", "LT", "LE", "GE", "GT", "EQ", "NE", "DEF", "DRIVERDEF",
            "ENDDEF", "DRIVERENDDEF", "COLON", "RANGEOP", "SEMICOL", "COMMA", "ASSIGNOP", 
            "SQBO", "SQBC", "BO", "BC", "COMMENTMARK", "NUM", "RNUM", "ID", "ERROR", "E", "$"
};

// Main function which generates entire AST
AST generate_AST(t_node* root, int flag) {
    if(root == NULL) {
        return NULL;
    }

    AST ast = (AST) malloc(sizeof(AST_Node));
    
    create_AST_Util(root);

    ast = root->tree_node;

    if(flag) {
        printf("\n\n ***AST IN-ORDER TRAVERSAL***\n\n");
        print_ast(ast, NULL);
    }

    return ast;
}

// Recursive function which traverses parse tree
// in post order to generate AST
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

// Makes a new AST leaf node corresponding to AST semantic rules
AST create_leaf_node(t_node* parse_tree_node, int label, int rule_num) {
    int l = label;
    int tag = 0;
    AST parent = parse_tree_node->parent->tree_node;
    AST child = NULL;
    AST next = NULL;
    Node* node = (Node*) malloc(sizeof(Node));
    *(node) = parse_tree_node->node.leaf;

    return create_NT_node(l, tag, rule_num, parent, child, next, node);
}

// Makes a new AST non leaf node corresponding to AST semantic rules
AST create_NT_node(Label label, int tag, int rule_num, AST parent, AST child, AST next, Node* node) {
    AST new_node = (AST) malloc(sizeof(AST_Node));

    new_node->label = label;
    new_node->tag = tag;
    new_node->rule_num = rule_num;
    new_node->parent = parent;
    new_node->child = child;
    new_node->next = next;
    new_node->leaf_token = node;
    new_node->symbol_table_node = NULL;

    return new_node;
}

// Forms links between siblings of a node
void link_children(t_node* node) {

    t_node* temp = node;

    while(temp->sibling) {
        if(temp->tree_node)
            temp->tree_node->next = temp->sibling->tree_node;
        temp = temp->sibling;
    }

    return;
}

// Links an AST node's children to itself 
void link_parent(t_node* node) {

    AST temp = node->tree_node;

    while(temp) {
        temp->parent = node->parent->tree_node;
        temp = temp->next;
    }

    return;
}

// Traverses AST to print it in-order
void print_ast(AST root, AST parent) {
    
    if(root == NULL) {
        return;
    }
    print_ast(root->child, root);

    print_ast_node(root, parent);
    

    if(root->child==NULL) {
        return;
    }
    
    parent = root;
    root = root->child;
    root = root->next;
    while(root) {
        print_ast(root, parent);
        root = root->next;
    }

    return;
}

// Traverses AST to print it in pre-order
void print_ast_preorder(AST root, AST parent) {
    
    if(root == NULL) {
        return;
    }

    print_ast_node(root, parent);
    print_ast_preorder(root->child, root);
    

    if(root->child==NULL) {
        return;
    }
    
    parent = root;
    root = root->child;
    root = root->next;
    while(root) {
        print_ast_preorder(root, parent);
        root = root->next;
    }

    return;
}

// Printing a node of AST
void print_ast_node(AST node, AST parent) {
    if(node->tag == 0) { //Print a leaf node with its value
        printf("Lexeme: %-20s  Line No: %-3d  Token: %-20s  ", node->leaf_token->lexeme, node->leaf_token->line_no, t_string_map_copy1[node->leaf_token->token]);
        if(node->leaf_token->tag == 1)
            printf("Value: %-15d  ", node->leaf_token->val.num);
        else if(node->leaf_token->tag == 2)
            printf("Value: %-15f  ", node->leaf_token->val.rnum);
        else
            printf("Value: %-15s  ", "-");
        
        printf("Parent Node: %-20s  ", ast_string_map[parent->label]);
        printf("Leaf Node: Yes  ");
        printf("Node Symbol: %-20s", "-");
        printf("Rule Number: %-10d\n\n", node->rule_num);
    }
    else { //Printing an internal node with blank lexeme and token
        printf("Lexeme: %-20s  Line No: %-3s  Token: %-20s  Value: %-15s  ", "-", "-", "-", "-");
        if(parent == NULL)
            printf("Parent Node: ROOT%16s  ", " ");
        else
            printf("Parent Node: %-20s  ", ast_string_map[parent->label]);
        
        printf("Leaf Node: No   ");
        printf("Node Symbol: %-20s", ast_string_map[node->label]);
        printf("Rule Number: %-10d\n\n", node->rule_num);
    }
}

// Creates and links AST nodes from parse tree as per AST semantic rules
void convert_to_AST_node(t_node* node) {
    int rule_num = node->rule_num;
    Label label;
    int tag;
    AST parent = NULL;
    AST child = NULL;
    AST sibling = NULL;
    t_node* temp, *temp2;

    switch(rule_num) {
        
        case 3:
        case 6:
        case 10:
        case 13:
        case 16:
        case 31:
        case 34:
        case 49:
        case 61:
        case 64:
        case 112:
            node->tree_node = NULL; // AST rules deriving NULL
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
        case 104: //new change
        case 106:
        case 110:
            node->tree_node = node->child->tree_node; // AST rules storing only first child of parse tree node
            break;

        case 30:
        case 48:
        case 55:
        case 60:
        case 70:
        case 78:
        case 109:
            node->tree_node = node->child->sibling->tree_node; // AST rules storing only second child of parse tree node
            break;

        case 9:
            node->tree_node = node->child->sibling->sibling->tree_node; // AST rules storing only third child of parse tree node
            break;

        case 41:
            node->tree_node = node->child->sibling->sibling->tree_node;
            node->tree_node->label = IO_WRITE; // AST node for IO_WRITE rule
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
        case 105: //Creating AST leaf node
            node->tree_node = create_leaf_node(node->child, -1, rule_num);
            break;

        case 1: // Root AST node
            label = AST_PROGRAM;
            tag = 1;
            temp = node->child;

            if (temp->tree_node) {
                child = temp->tree_node;

                temp2 = temp;
                temp = temp->sibling;

                while(temp) {
                    if(temp->tree_node) {
                        temp2->tree_node->next = temp->tree_node;
                        temp2 = temp;
                    }

                    temp = temp->sibling;
                }
            }
            else {
                temp = temp->sibling;
                
                if(temp->tree_node) {
                    child = temp->tree_node;

                    temp2 = temp;
                    temp = temp->sibling;

                    while(temp) {
                        if(temp->tree_node) {
                            temp2->tree_node->next = temp->tree_node;
                            temp2 = temp;
                        }
                        temp = temp->sibling;
                    }
                }
                else {
                    temp = temp->sibling;

                    child = temp->tree_node;
                    temp->tree_node->next = temp->sibling->tree_node;
                }
            }

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 2:
        case 5:
        case 32:
        case 65:
        case 107: // Rules which use same non terminal as a list
            if (rule_num == 2)
                label = MODULE_DECLARATIONS;
            else if(rule_num == 5)
                label = OTHER_MODULES;
            else if(rule_num == 32)
                label = STATEMENTS;
            else if(rule_num == 65)
                label = EXPRESSION;
            else if(rule_num == 107)
                label = NUMERIC_CASES;

            tag = 1;
            child = node->child->tree_node;

            link_children(node->child);
            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 4:
            node->tree_node = create_leaf_node(node->child->sibling->sibling, MODULE_DECLARATION, rule_num);
            break;

        case 7: // AST node for driver module definition
            label = AST_DRIVER;
            tag = 1;
            temp = node->child->sibling->sibling->sibling->sibling;
            if(temp->tree_node) {
                child = temp->tree_node;
                child->next = create_leaf_node(temp->child, -1, 30);
                temp->child->tree_node = child->next;

                child->next->next = create_leaf_node(temp->child->sibling->sibling, -1, 30);
                temp->child->sibling->sibling->tree_node = child->next->next;
            }
            else {
                child = create_leaf_node(temp->child, -1, 30);
                temp->child->tree_node = child;

                child->next = create_leaf_node(temp->child->sibling->sibling, -1, 30);
                temp->child->sibling->sibling->tree_node = child->next;
            }

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 8: // AST node for non driver module definition
            label = AST_MODULE;
            
            tag = 1;
            child = create_leaf_node(node->child->sibling->sibling, -1, rule_num);
            node->child->sibling->sibling->tree_node = child;
 
            temp = node->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling;
            child->next = temp->tree_node;

            temp = temp->sibling->sibling->sibling;
            

            if(temp->tree_node != NULL) {
                child->next->next = temp->tree_node;
                temp = temp->sibling;
                if(temp->tree_node) {
                    child->next->next->next = temp->tree_node;

                    child->next->next->next->next = create_leaf_node(temp->child, -1, 30);
                    temp->child->tree_node = child->next->next->next->next;

                    child->next->next->next->next->next = create_leaf_node(temp->child->sibling->sibling, -1, 30);
                    temp->child->sibling->sibling->tree_node = child->next->next->next->next->next;
                }
                else {

                    child->next->next->next = create_leaf_node(temp->child, -1, 30);
                    temp->child->tree_node = child->next->next->next;

                    child->next->next->next->next = create_leaf_node(temp->child->sibling->sibling, -1, 30);
                    temp->child->sibling->sibling->tree_node = child->next->next->next->next;
                }
            }
            else {
                temp = temp->sibling;

                if(temp->tree_node) {
                    child->next->next = temp->tree_node;
                    child->next->next->next = create_leaf_node(temp->child, -1, 30);
                    temp->child->tree_node = child->next->next->next;

                    child->next->next->next->next = create_leaf_node(temp->child->sibling->sibling, -1, 30);
                    temp->child->sibling->sibling->tree_node = child->next->next->next->next;
                }
                else {
                    child->next->next = create_leaf_node(temp->child, -1, 30);
                    temp->child->tree_node = child->next->next;

                    child->next->next->next = create_leaf_node(temp->child->sibling->sibling, -1, 30);
                    temp->child->sibling->sibling->tree_node = child->next->next->next;
                }
            }
            
            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child->sibling->sibling);
            break;

        case 11: // AST node for input and output list of a function
        case 14:
            if(rule_num == 11)
                label = INPUT_PLIST;
            else if(rule_num == 14)
                label = OUTPUT_PLIST;

            tag = 1;
            child = create_leaf_node(node->child, -1, rule_num);
            node->child->tree_node = child;

            child->next = node->child->sibling->sibling->tree_node;
            child->next->next = node->child->sibling->sibling->sibling->tree_node;

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 12:
        case 15:
            if (rule_num == 12)
                label = NEW1;
            else if (rule_num == 15)
                label = NEW2;

            tag = 1;
            child = create_leaf_node(node->child->sibling, -1, rule_num);
            node->child->sibling->tree_node = child;

            child->next = node->child->sibling->sibling->sibling->tree_node;
            child->next->next = node->child->sibling->sibling->sibling->sibling->tree_node;

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 20: // AST node for datatype rule
        case 24:
            if (rule_num == 20)
                label = DATA_TYPE;
            else if (rule_num == 24)
                label = DATA_TYPE2;

            tag = 1;

            child = node->child->sibling->sibling->tree_node;
            child->next = node->child->sibling->sibling->sibling->sibling->sibling->tree_node;

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 28: // AST node for range rule
            label = RANGE;
            tag = 1;

            child = create_leaf_node(node->child, -1, rule_num);
            node->child->tree_node = child;
            child->next = create_leaf_node(node->child->sibling->sibling, -1, rule_num);
            node->child->sibling->sibling->tree_node = child->next;

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 29:
            label = RANGE2;
            tag = 1;

            child = node->child->tree_node;
            child->next = node->child->sibling->sibling->tree_node;

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;
        
        case 40: // AST node for IO_READ rule
            node->tree_node = create_leaf_node(node->child->sibling->sibling, -1, rule_num);
            node->tree_node->label = IO_READ;
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

            child = create_leaf_node(node->child, -1, rule_num);
            node->child->tree_node = child;
            child->next = node->child->sibling->tree_node;

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 56:
            label = LVALUE_ARR_STMT;
            tag = 1;

            child = node->child->sibling->tree_node;
            child->next = node->child->sibling->sibling->sibling->sibling->tree_node;

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 59: // AST node for function call rule
            label = MODULE_REUSE_STMT;
            tag = 1;

            temp = node->child;

            if(temp->tree_node != NULL) {
                child = temp->tree_node;
                child->next = create_leaf_node(node->child->sibling->sibling->sibling, -1, rule_num);
                node->child->sibling->sibling->sibling->tree_node = child->next;
                child->next->next = node->child->sibling->sibling->sibling->sibling->sibling->sibling->tree_node;
            }
            else {
                child = create_leaf_node(node->child->sibling->sibling->sibling, -1, rule_num);
                node->child->sibling->sibling->sibling->tree_node = child;
                child->next = node->child->sibling->sibling->sibling->sibling->sibling->sibling->tree_node;
            }

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 63:
            label = NEWX;
            tag = 1;

            child = create_leaf_node(node->child->sibling, -1, rule_num);
            node->child->sibling->tree_node = child;
            child->next = node->child->sibling->sibling->tree_node;

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 100: // AST node for declare statement
            label = DECLARE_STMT;
            tag = 1;

            child = node->child->sibling->tree_node;
            child->next = node->child->sibling->sibling->sibling->tree_node;

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 101: // AST node for FOR statement
            label = AST_FOR;
            tag = 1;
            temp = node->child->sibling->sibling;

            child = create_leaf_node(temp, -1, rule_num);
            temp->tree_node = child;
            child->next = temp->sibling->sibling->tree_node;
            temp = temp->sibling->sibling->sibling->sibling;

            if(temp->sibling->tree_node) {
                child->next->next = temp->sibling->tree_node;            
                
                child->next->next->next = create_leaf_node(temp, -1, 1010);
                temp->tree_node = child->next->next->next;

                child->next->next->next->next = create_leaf_node(temp->sibling->sibling, -1, 1010);
                temp->sibling->sibling->tree_node = child->next->next->next->next;
            }

            else {
                child->next->next = create_leaf_node(temp, -1, 1010);
                temp->tree_node = child->next->next;

                child->next->next->next = create_leaf_node(temp->sibling->sibling, -1, 1010);
                temp->sibling->sibling->tree_node = child->next->next->next;
            }

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 102: // AST node for while statement
            label = AST_WHILE;
            tag = 1;

            temp = node->child->sibling->sibling;

            child = temp->tree_node;
            temp = temp->sibling->sibling;

            if(temp->sibling->tree_node) {
                child->next = temp->sibling->tree_node;

                child->next->next = create_leaf_node(temp, -1, 1020);
                temp->tree_node = child->next->next;

                child->next->next->next = create_leaf_node(temp->sibling->sibling, -1, 1020);
                temp->sibling->sibling->tree_node = child->next->next->next;
            }
            else {
                child->next = create_leaf_node(temp, -1, 1020);
                temp->tree_node = child->next;

                child->next->next = create_leaf_node(temp->sibling->sibling, -1, 1020);
                temp->sibling->sibling->tree_node = child->next->next;
            }

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 103: // AST node for switch statement
            label = CONDITIONAL_STMT;
            tag = 1;
            temp = node->child->sibling->sibling;

            child = create_leaf_node(temp, -1, rule_num);
            temp->tree_node = child;
            child->next = node->child->sibling->sibling->sibling->sibling->sibling->sibling->tree_node;

            temp = node->child->sibling->sibling->sibling->sibling;

            child->next->next = create_leaf_node(temp, -1, 1030);
            temp->tree_node = child->next->next;

            temp2 = get_switch_end_node(temp->sibling->sibling);
            child->next->next->next = create_leaf_node(temp2, -1, 1030);
            temp2->tree_node = child->next->next->next;


            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;
       
        case 108: // AST node for case of a switch
            label = NUMERIC_CASE;
            tag = 1;

            child = node->child->tree_node;
            child->next = node->child->sibling->sibling->tree_node;

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 71:
        case 72:
        case 75:
        case 96:
            node->tree_node = node->child->sibling->tree_node;
            break;

        case 74:
        case 77:
        case 95:
        case 99: // AST node which stores inherited information
            node->tree_node = extract_inherited(node);
            break;

        case 73:
        case 76:
        case 94:
            node->tree_node = node->child->sibling->sibling->tree_node;
            break;

        case 98: // AST node for relational expression
            label = RELATIONAL_EXPR;
            tag = 1;
            child = node->child->tree_node;
            child->next = extract_inherited(node);
            child->next->next = node->child->sibling->tree_node;

            node->tree_node = create_NT_node(label, tag, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

        case 111: // AST node for default statement
            child = create_leaf_node(node->child, -1, rule_num);
            node->child->tree_node = child;

            child->next = node->child->sibling->sibling->tree_node;
            
            node->tree_node = create_NT_node(AST_DEFAULT, 1, rule_num, parent, child, sibling, NULL);
            link_parent(node->child);
            break;

    }
}

// Function which extracts inherited information from an expression node
AST extract_inherited(t_node* node) {
    int rule_num = node->parent->rule_num;
    AST inherited = NULL;
    t_node* parent = node->parent;
    Label label;
    AST child = NULL, temp;

    switch(rule_num) {
        case 71:
        case 72:
        case 75:
        case 96:
            
            inherited = parent->child->tree_node;
            break;

        case 73:
        case 76:
        case 94:

            if (rule_num == 73)
                label = NEW6;
            else if (rule_num == 76)
                label = NEW7;
            else if (rule_num == 94)
                label = NEW8;

            child = parent->child->tree_node;
            child->next = extract_inherited(parent);
            child->next->next = parent->child->sibling->tree_node;

            inherited = create_NT_node(label, 1, rule_num, NULL, child, NULL, NULL);

            break;
    }

    return inherited;
}

// Function to find start and end nodes of a switch statement for storing scope
t_node* get_switch_end_node(t_node* temp) {
    t_node* ans;
    if(temp->child->tag == 0) {
        ans = temp->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling;
    }
    else {
        t_node* temp2 = temp->child->child->sibling;
        while(temp2->child->tag == 0) {
            temp2 = temp2->child->sibling->child->sibling;
        }
        ans = temp2->child->sibling;
    }
    return ans;
}

// To count total number and size of parse tree nodes
void count_parse_tree_nodes(t_node* root, int* count, int *size) {
    if(root == NULL)
        return;
    *count += 1;
    *size += sizeof(t_node);
    t_node* temp = root->child;
    while(temp) {
        count_parse_tree_nodes(temp, count, size);
        temp = temp->sibling;
    }
    return;
}

// To count total number and size of AST nodes
void count_ast_nodes(AST root, int* count, int *size) {
    if(root == NULL)
        return;
    *count += 1;
    *size += sizeof(AST_Node);
    AST temp = root->child;
    while(temp) {
        count_ast_nodes(temp, count, size);
        temp = temp->next;
    }
    return;
}

// To calculate and display total amount of allocated memory to parse tree and AST
void calculate_allocated_memory(t_node* root, AST tree) {

    int parse_tree_count = 0;
    int ast_count = 0;
    int parse_tree_size = 0;
    int ast_size = 0;
    count_parse_tree_nodes(root, &parse_tree_count, &parse_tree_size);
    count_ast_nodes(tree, &ast_count, &ast_size);

    printf("\nParse tree number of nodes = %d\t Allocated memory = %d bytes\n", parse_tree_count, parse_tree_size);
    printf("\nAST number of nodes = %d\t Allocated memory = %d bytes\n", ast_count, ast_size);

    int compression = ((parse_tree_size-ast_size)*100)/parse_tree_size;
    printf("\nCompression percentage = %d%%\n\n", compression);

    return;
}
