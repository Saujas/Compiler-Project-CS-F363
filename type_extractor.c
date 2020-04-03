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

int check_bound(AST index, AST var) {
    if(var->symbol_table_node->range[0].tag == 0 && var->symbol_table_node->range[1].tag == 0) {
        int id = index->leaf_token->val.num;

        if( id < var->symbol_table_node->range[0].range_pointer.value || id > var->symbol_table_node->range[1].range_pointer.value) {
            return 0;
        }
    }

    return 1;
}

void type_checker(AST root) {
    
    if(root == NULL) {
        return;
    }

    int error = type_check_node(root);

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

int type_check_node(AST node) {

    int rule_num = node->rule_num;
    int flag = 0;
    
    if (rule_num == 52 && node->tag == 1) {

        // ASSIGNMENT STATEMENT
        // printf("%s\n", tc_string_map[node->label]);
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

        int expression_type = extract_type(expression_node);
        int lhs_type = get_id_type(lhs);
        printf("%s: %d %d\n", lhs->leaf_token->lexeme, lhs_type, expression_type);

        if(expression_type != lhs_type) {
            printf("Line: %d - Invalid types in assignment\n", lhs->leaf_token->line_no);
            flag = 1;
        }

    }

    return flag;
}

int get_id_type(AST node) {
    Symbol_Node* st = node->symbol_table_node;

    // printf("%s\n", node->leaf_token->lexeme);

    if(st == NULL) {
        // variable not declared
        return -1;
    }
    
    if(st->datatype == 3) {
        return st->array_datatype;
    }

    return st->datatype;
}

// 0: INT, 1: REAL, 2: BOOLEAN, -1: ERROR
int extract_type(AST node) {
    
    if(node == NULL) {
        return -1;
    }

    int error = 0;

    if(node->tag == 1) {

        if(node->label == EXPRESSION || node->label == RELATIONAL_EXPR ||
        node->label == NEW8 || node->label == NEW7 || node->label == NEW6 || node->label == VAR) {
            return extract_type(node->child);
        }

        // INVALID NON TERMINAL WITHIN AN EXPRESSION
        else return -1;
    }

    // if a terminal is encountered,
    // it will either be an operator or a literal

    char* name = node->leaf_token->lexeme;
    tokens token = node->leaf_token->token;

    if(token == PLUS || token == MINUS) {
        AST n1 = node->next;
        AST n2 = node->next->next;

        int t1 = extract_type(n1), t2 = extract_type(n2);

        if(n2 == NULL) {
            if(t1 == 2) {
                error = 1;
            }
            else
                return t1;
        }

        if(t1 != t2 || t1 == 2 || t2 == 2) {
            error = 1;
        }
        else
            return t1;
    }

    if(token == MUL || token == DIV) {
        
        AST n1 = node->next;
        AST n2 = node->next->next;

        int t1 = extract_type(n1), t2 = extract_type(n2);
        
        if(t1 != t2 || t1 == 2 || t2 == 2) {
            error = 1;
        }

        else return t1;
    }

    if(token == GT || token == LT || token == GE || token == LE ||
        token == EQ || token == NE) {
        
        AST n1 = node->next;
        AST n2 = node->next->next;

        int t1 = extract_type(n1), t2 = extract_type(n2);
        
        if(t1 != t2 || t1 == 2 || t2 == 2) {
            error = 1;
        }

        else return 2;
    }

    if(token == AND || token == OR) {
        AST n1 = node->next;

        AST n2 = node->next->next;

        int t1 = extract_type(n1), t2 = extract_type(n2);

        if( !(t1 == 2 && t2 == 2)) {
            error = 1;
        }

        else return 2;
    }

    if(error) {
        printf("Line: %d - Invalid types in expression\n", node->leaf_token->line_no);
        return -1;
    }

    // if it is a literal
    if(token == ID) {
        int type = get_id_type(node);
        node->data_type = type;

        return type;
    }
    else {
        if(token == NUM) {
            return 0;
        }
        else if(token == RNUM)
            return 1;
        else if(token == TRUE || token == FALSE)
            return 2;
    }

    return -1;
}