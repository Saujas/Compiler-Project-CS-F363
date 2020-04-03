#include "semantic_analyzer.h"

char* tc_string_map_copy[AST_LABEL_NUMBER] = {
    "AST_PROGRAM", "MODULE_DECLARATIONS", "MODULE_DECLARATION", "OTHER_MODULES", "AST_DRIVER", "AST_MODULE", "INPUT_PLIST", "NEW1",
    "OUTPUT_PLIST", "NEW2", "DATA_TYPE", "DATA_TYPE2", "RANGE", "RANGE2", "STATEMENTS", "VAR", "ASSIGNMENT_STMT", 
    "LVALUE_ARR_STMT", "MODULE_REUSE_STMT", "ID_LIST", "NEWX", "EXPRESSION", "NEW6", "NEW7", "NEW8", "RELATIONAL_EXPR", 
    "DECLARE_STMT", "AST_FOR", "AST_WHILE", "CONDITIONAL_STMT", "CASE_STMT_T", "CASE_STMT_F", "NUMERIC_CASES", "NUMERIC_CASE", "IO_READ", "IO_WRITE", "AST_DEFAULT"
};

char * tc_non_terminals_string_map_copy[NON_TERMINAL_SIZE] = {"program", "moduleDeclarations", "moduleDeclaration", "otherModules", "driverModule", "module", "ret", "input_plist",
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
        if(lhs->symbol_table_node->datatype == 3) {
            if(expression_node && expression_node->child && expression_node->child->symbol_table_node && expression_node->child->symbol_table_node->datatype == 3) {
                if(expression_node->child->symbol_table_node->array_datatype != lhs->symbol_table_node->array_datatype) {
                    printf("Line: %d - Array can be assigned to array with same type only\n", lhs->leaf_token->line_no);
                    flag = 1;
                }
                else if(lhs->symbol_table_node->range[0].tag == 0 && expression_node->child->symbol_table_node->range[0].tag == 0) {
                    if(lhs->symbol_table_node->range[0].range_pointer.value != expression_node->child->symbol_table_node->range[0].range_pointer.value) {
                        printf("Line: %d - Array can be assigned to array with same type only\n", lhs->leaf_token->line_no);
                        flag = 1;
                    }
                }
                else if(lhs->symbol_table_node->range[1].tag == 0 && expression_node->child->symbol_table_node->range[1].tag == 0) {
                    if(lhs->symbol_table_node->range[1].range_pointer.value != expression_node->child->symbol_table_node->range[1].range_pointer.value) {
                        printf("Line: %d - Array can be assigned to array with same type only\n", lhs->leaf_token->line_no);
                        flag = 1;
                    }
                }
            }
            else {
                printf("Line: %d - Array can be assigned to array with same type only\n", lhs->leaf_token->line_no);
                    flag = 1;
            }
        }
        else {

            int expression_type = extract_type(expression_node);
            int lhs_type = get_id_type(lhs);
            

            printf("%s: %d %d\n", lhs->leaf_token->lexeme, lhs_type, expression_type);

            if(expression_type != lhs_type) {
                printf("Line: %d - Invalid types in assignment\n", lhs->leaf_token->line_no);
                flag = 1;
            }
        }

    }

    if(node->rule_num == 40 && node->tag == 0) {
        if(!search_symbol_table(node->leaf_token->lexeme, node->current_scope))
            flag = 1;
        else if((node->symbol_table_node->datatype == 3) || (node->symbol_table_node->datatype == 2)) {
            printf("Line: %d - Incompatible datatype of variable %s\n", node->leaf_token->line_no, node->leaf_token->lexeme);
            flag = 1;
        }
    }

    if(node->rule_num == 101 && node->tag == 1) {
        if(!search_symbol_table(node->child->leaf_token->lexeme, node->current_scope))
            flag = 1;
        else if(node->child->symbol_table_node && node->child->symbol_table_node->datatype != 0) {
            printf("Line: %d - Incompatible datatype in For loop variable %s\n", node->child->leaf_token->line_no, node->child->leaf_token->lexeme);
            flag = 1;
        }

        Symbol_Node* temp1 = search_current_scope(node->child->leaf_token->lexeme, node->child->current_scope);
        if(temp1) {
            printf("Line: %d - For loop variable is declared again\n", temp1->node->leaf_token->line_no);
            flag = 1;
        }
    }

    if(node->rule_num == 103 && node->tag == 1) {
        if(!search_symbol_table(node->child->leaf_token->lexeme, node->current_scope))
            flag = 1;
        else if(node->child->symbol_table_node->datatype == 2) {
            AST temp1 = node->child->next;
            if(temp1->label == NUMERIC_CASES) {
                printf("Line: %d - Switch with boolean variable can have only true and false cases\n", node->child->leaf_token->line_no);
                flag = 1;
            }
        }
        else if(node->child->symbol_table_node->datatype == 0) {
            int check = 0;
            AST temp1 = node->child->next->child->next;
            while(temp1) {
                if(temp1->label == AST_DEFAULT) {
                    check = 1;
                    break;
                }
                temp1 = temp1->child->next;
            }
            if(!check) {
                printf("Line: %d - Switch with integer variable must have default\n", node->child->leaf_token->line_no);
                flag = 1;
            }
        }
        else {
            printf("Line: %d - Switch must have integer or boolean variable only\n", node->child->leaf_token->line_no);
            flag = 1;
        }
    }

    return flag;
}
