#include "type_extractor.h"

char* tc_string_map[AST_LABEL_NUMBER] = {
    "AST_PROGRAM", "MODULE_DECLARATIONS", "MODULE_DECLARATION", "OTHER_MODULES", "AST_DRIVER", "AST_MODULE", "INPUT_PLIST", "NEW1",
    "OUTPUT_PLIST", "NEW2", "DATA_TYPE", "DATA_TYPE2", "RANGE", "RANGE2", "STATEMENTS", "VAR", "ASSIGNMENT_STMT", 
    "LVALUE_ARR_STMT", "MODULE_REUSE_STMT", "ID_LIST", "NEWX", "EXPRESSION", "NEW6", "NEW7", "NEW8", "RELATIONAL_EXPR", 
    "DECLARE_STMT", "AST_FOR", "AST_WHILE", "CONDITIONAL_STMT", "CASE_STMT_T", "CASE_STMT_F", "NUMERIC_CASES", "NUMERIC_CASE", "IO_READ", "IO_WRITE"
};

char * tc_non_terminals_string_map[NON_TERMINAL_SIZE] = {"program", "moduleDeclarations", "moduleDeclaration", "otherModules", "driverModule", "module", "ret", "input_plist",
    "new1", "output_plist", "new2", "dataType", "dataType2", "type", "range", "range2", "moduleDef", "statements", "new3",
    "statement", "ioStmt", "var", "var2", "whichID", "simpleStmt", "assignmentStmt", "whichStmt", "lvalueIDstmt", "lvalueArrStmt", 
    "Index", "moduleReuseStmt", "optional", "idList", "newX", "expression", "new4", "AorBExpr", "arithmeticExpr", "new6",
    "term", "new7", "factor", "PlusMinus", "MulDiv", "relationalOP", "logicalOP", "boolKey", "boolExpr", "new8", "relationalExpr",
    "declareStmt", "iterativeStmt", "conditionalStatement", "caseStmt", "numericCases", 
    "numericCase", "new11", "Default"};

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

void type_checker(AST node) {
    if(root == NULL) {
        return;
    }

    type_check_node(root);
    // print_ast(root->child);

    if(root->child==NULL) {
        return;
    }
    
    root = root->child;

    while(root) {
        type_checker(root);
        root = root->next;
    }
    
    return;
}

int check_bound(AST index, AST var) {
    if(var->symbol_table_node->range[0].tag == 0 && var->symbol_table_node->range[1].tag == 0) {
        int id = index->leaf_token->val.num;

        if( id < var->symbol_table_node->range[0].range_pointer.value || id > var->symbol_table_node->range[1].range_pointer.value) {
            return 0;
        }
    }

    return 1;
}

void type_check_node(AST node) {

    int rule_num = node->rule_num;
    int flag = 0;
    
    if (rule_num == 52) {

        // ASSIGNMENT STATEMENT

        AST lhs = node->child;
        AST expression_node = node->child->next;

        if(node->child->next->label == LVALUE_ARR_STMT) {
            
            expression_node = node->child->next->child->next;

            if(lhs->symbol_table_node->datatype != 3) {
                printf("Line: %d - Variable %s not of array type\n", lhs->leaf_token->line_no, lhs->leaf_token->lexeme);
                flag = 1;
            }
            else {
                // Checking array type used on LHS of assignment statement
                AST index = lhs->next->child;

                // Checking bounds in case of static indexing
                if(index->rule_num == 57) {
                    int bound = check_bound(index, lhs);

                    if(bound == 0) {
                        printf("Line: %d - Array out of bounds error\n", lhs->leaf_token->line_no);
                        flag = 1;
                    }
                }
                // In case ID is used, check if ID is type integer
                else if(index->rule_num == 58) {
                    if(index->symbol_table_node->datatype != 0) {
                        printf("Line: %d -  Array index type is not integer\n", index->leaf_token->line_no);
                        flag = 1;
                    }
                }
            }
        }


    }
}