#include"tree.h"

char * nt_string_map[NON_TERMINAL_SIZE] = {"program", "moduleDeclarations", "moduleDeclaration", "otherModules", "driverModule", "module", "ret", "input_plist",
    "new1", "output_plist", "new2", "dataType", "dataType2", "type", "range", "range2", "moduleDef", "statements", "new3",
    "statement", "ioStmt", "var", "var2", "whichID", "simpleStmt", "assignmentStmt", "whichStmt", "lvalueIDstmt", "lvalueArrStmt", 
    "Index", "moduleReuseStmt", "optional", "idList", "newX", "expression", "new4", "AorBExpr", "arithmeticExpr", "new6",
    "term", "new7", "factor", "PlusMinus", "MulDiv", "relationalOP", "logicalOP", "boolKey", "boolExpr", "new8", "relationalExpr",
    "declareStmt", "iterativeStmt", "conditionalStatement", "caseStmt", "numericCases", 
    "numericCase", "new11", "Default"};

char * t_string_map[TOKEN_NUMBERS] = {"INTEGER", "REAL", "BOOLEAN", "OF", "ARRAY", "START",
            "END", "DECLARE", "MODULE", "DRIVER", "PROGRAM", "GET_VALUE", "PRINT",
            "USE", "WITH", "PARAMETERS", "TRUE", "FALSE", "TAKES", "INPUT", "RETURNS",
            "AND", "OR", "FOR", "IN", "SWITCH", "CASE", "BREAK", "DEFAULT", "WHILE", "PLUS", 
            "MINUS", "MUL", "DIV", "LT", "LE", "GE", "GT", "EQ", "NE", "DEF", "DRIVERDEF",
            "ENDDEF", "DRIVERENDDEF", "COLON", "RANGEOP", "SEMICOL", "COMMA", "ASSIGNOP", 
            "SQBO", "SQBC", "BO", "BC", "COMMENTMARK", "NUM", "RNUM", "ID", "ERROR", "E", "$"
};

t_node* initialize_tree() {
    t_node* root = create_internal(program);

    return root;
}

t_node* create_internal(non_terminals nt) {
    t_node* intern = (t_node*) malloc(sizeof(t_node));
    intern->tag = 1;
    intern->sibling = NULL;
    intern->child = NULL;
    intern->node.internal = nt;

    return intern;
}

t_node* create_leaf(Node n) {
    t_node* leaf = (t_node*) malloc(sizeof(t_node));
    leaf->tag = 0;
    leaf->sibling = NULL;
    leaf->child = NULL;
    leaf->node.leaf = n;

    return leaf;
}

int insert_node(t_node** parent, t_node* child) {
    
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

int inorder_traversal(t_node* root) {
    if(root == NULL) {
        return 0;
    }

    while(root) {
        inorder_traversal(root->child);
        print_tnode(root);
        root = root->sibling;
    }

    return 1;
}

int print_tnode(t_node* n) {
    if(n==NULL) {
        return 0;
    }

    if(n->tag == 0) {
        printf("Lexeme: %s, Token: %s, Line No: %d\n", n->node.leaf.lexeme, t_string_map[n->node.leaf.token], n->node.leaf.line_no);
    }
    else {
        printf("Non Terminal: %s\n", nt_string_map[n->node.internal]);
    }

    return 1;
}