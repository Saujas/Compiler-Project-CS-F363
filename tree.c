// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include"tree.h"

// Array of strings of all non-terminals
char * nt_string_map[NON_TERMINAL_SIZE] = {"program", "moduleDeclarations", "moduleDeclaration", "otherModules", "driverModule", "module", "ret", "input_plist",
    "new1", "output_plist", "new2", "dataType", "dataType2", "type", "range", "range2", "moduleDef", "statements", "new3",
    "statement", "ioStmt", "var", "var2", "whichID", "simpleStmt", "assignmentStmt", "whichStmt", "lvalueIDstmt", "lvalueArrStmt", 
    "Index", "moduleReuseStmt", "optional", "idList", "newX", "expression", "new4", "AorBExpr", "arithmeticExpr", "new6",
    "term", "new7", "factor", "PlusMinus", "MulDiv", "relationalOP", "logicalOP", "boolKey", "boolExpr", "new8", "relationalExpr",
    "declareStmt", "iterativeStmt", "conditionalStatement", "caseStmt", "numericCases", 
    "numericCase", "new11", "Default"};

// Array of strings of all tokens
char * t_string_map[TOKEN_NUMBERS] = {"INTEGER", "REAL", "BOOLEAN", "OF", "ARRAY", "START",
            "END", "DECLARE", "MODULE", "DRIVER", "PROGRAM", "GET_VALUE", "PRINT",
            "USE", "WITH", "PARAMETERS", "TRUE", "FALSE", "TAKES", "INPUT", "RETURNS",
            "AND", "OR", "FOR", "IN", "SWITCH", "CASE", "BREAK", "DEFAULT", "WHILE", "PLUS", 
            "MINUS", "MUL", "DIV", "LT", "LE", "GE", "GT", "EQ", "NE", "DEF", "DRIVERDEF",
            "ENDDEF", "DRIVERENDDEF", "COLON", "RANGEOP", "SEMICOL", "COMMA", "ASSIGNOP", 
            "SQBO", "SQBC", "BO", "BC", "COMMENTMARK", "NUM", "RNUM", "ID", "ERROR", "E", "$"
};

// Initialise tree with start symbol program
t_node* initialize_tree() {
    t_node* root = create_internal(program);
    root->rule_num = 1;//new additions

    return root;
}

// Creating a new internal node
t_node* create_internal(non_terminals nt) {
    t_node* intern = (t_node*) malloc(sizeof(t_node));
    intern->tag = 1;
    intern->sibling = NULL;
    intern->child = NULL;
    intern->node.internal = nt;
    intern->rule_num = 0;//new additions
    intern->parent = NULL;//new additions
    return intern;
}

// Creating a new leaf node
t_node* create_leaf(Node n) {
    t_node* leaf = (t_node*) malloc(sizeof(t_node));
    leaf->tag = 0;
    leaf->sibling = NULL;
    leaf->child = NULL;
    leaf->node.leaf = n;
    leaf->rule_num = 0;//new additions
    leaf->parent = NULL;//new additions

    return leaf;
}

// Inserting a node with given parent.
// If the parent node has a child, it is inserted as a sibling of its child
int insert_node(t_node** parent, t_node* child) {

    child->parent = (*parent);//new additions
    if((*parent)->child == NULL) {
        (*parent)->child = child;
    }
    else {
        t_node* temp = (*parent)->child;
        (*parent)->child = child;
        child->sibling = temp;
    }

    return 1;
}

// Print entire parse tree into file with given name
int print_parse_tree(t_node* root, char* fname) {
    // FILE* fp = fopen(fname, "w");

    inorder_traversal(root, -1, NULL);
    // fclose(fp);
}

// Traverse tree inorder - Left child, then parent, then sibling(s)
// Recursive implementation
int inorder_traversal(t_node* root, non_terminals parent, FILE* fp) {
    if(root == NULL) {
        return 0;
    }
    inorder_traversal(root->child, root->node.internal, fp);
    print_tnode(root, parent, fp);
    if(root->child==NULL)
        return 0;
    
    t_node* org_root = root;
    root = root->child;
    root = root->sibling;
    while(root) {
        inorder_traversal(root, org_root->node.internal, fp);
        root = root->sibling;
    }

    return 1;
}

int print_tnode(t_node* n, non_terminals parent, FILE* fp) {
    if(n==NULL) {
        return 0;
    }

    if(n->tag == 0) { //Print a leaf node with its value
        printf("Lexeme: %-20s  Line No: %-3d  Token: %-20s  ", n->node.leaf.lexeme, n->node.leaf.line_no, t_string_map[n->node.leaf.token]);
        if(n->node.leaf.tag == 1)
            printf("Value: %-15d  ", n->node.leaf.val.num);
        else if(n->node.leaf.tag == 2)
            printf("Value: %-15f  ", n->node.leaf.val.rnum);
        else
            printf("Value: %-15s  ", "-");
        
        printf("Parent Node: %-20s  ", nt_string_map[parent]);
        printf("Leaf Node: Yes  ");
        printf("Node Symbol: %-20s", "-");
        printf("Rule Number: %-10d\n\n", n->rule_num);
    }
    else { //Printing an internal node with blank lexeme and token
        printf("Lexeme: %-20s  Line No: %-3s  Token: %-20s  Value: %-15s  ", "-", "-", "-", "-");
        if(parent == -1)
            printf("Parent Node: ROOT%16s  ", " ");
        else
            printf("Parent Node: %-20s  ", nt_string_map[parent]);
        
        printf("Leaf Node: No   ");
        printf("Node Symbol: %-20s", nt_string_map[n->node.internal]);
        printf("Rule Number: %-10d\n\n", n->rule_num);
    }

    return 1;
}