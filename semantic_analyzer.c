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
            
            if(!lhs->symbol_table_node) {
                flag = 1;
            }
            else if(lhs->symbol_table_node && lhs->symbol_table_node->datatype != 3) {
                printf("Line: %d - Variable %s not of array type\n", lhs->leaf_token->line_no, lhs->leaf_token->lexeme);
                flag = 1;
            }
            else if(lhs->symbol_table_node && lhs->symbol_table_node->datatype == 3) {
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
                    if(index->symbol_table_node && index->symbol_table_node->datatype != 0) {
                        printf("Line: %d -  Array index type is not integer\n", index->leaf_token->line_no);
                        flag = 1;
                    }
                    else if(!index->symbol_table_node) {
                        flag = 1;
                    }
                }
            }
        }

        if(lhs->symbol_table_node && lhs->symbol_table_node->datatype == 3 && lhs->next->label != LVALUE_ARR_STMT) {
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
        else if(node->child->symbol_table_node && node->child->symbol_table_node->datatype == 0) {
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

    // WHILE LOOP SEMANTICS
    if(node->rule_num == 102) {
        int type = extract_type(node->child);
        
        if(type != 2) {
            printf("Line: - Incompatible expression used in while construct\n");
            flag = 1;
        }
        else {
            AST_list** id_used = (AST_list **)malloc(sizeof(AST_list *));
            check_identifier(node->child, id_used);
            // print_identifier(*id_used);

            if((*id_used) == NULL) {
                printf("Line: - No identifier used in while construct\n");
                flag = 1;
            }
            
            if(!flag) {
                int is_redeclared = check_if_redeclared_in_scope(id_used);
                if(is_redeclared) {
                    printf("Line: - Identifier used in while construct cannot be redeclared\n");
                    flag = 1;
                }
            }

            if(!flag) {
                int is_modified = 0;
                check_if_modified(id_used, node, &is_modified);

                if(!is_modified) {
                    printf("No variable modified\n");
                    flag = 1;
                }
                else {
                    printf("ALL GOOD\n");
                }
            }
        }
    }

    return flag;
}

void check_if_modified(AST_list** head, AST node, int* current) {
    
    if(node == NULL || (*current) == 1)
        return;

    if(node->rule_num == 52 && node->tag == 1) {
        
        AST id = node->child;
        AST index = NULL;

        if(id->next && id->next->label == LVALUE_ARR_STMT && id->next->child) {
            index = id->next->child;
        }

        *current = compare_list_node(head, id, index);
        printf("%d\n", *current);

        if((*current) == 1) {
            return;
        }


    }

    AST temp = node->child;

    while(temp) {
        check_if_modified(head, temp, current);
        temp = temp->next;
    }

    return;

}

int compare_list_node(AST_list** head, AST id, AST index) {
    
    AST_list* temp = *head;

    if(id->symbol_table_node && id->symbol_table_node->datatype != 3) {
        while(temp) {
            // printf("%d: %s %s\n", id->leaf_token->line_no, id->leaf_token->lexeme, temp->node->leaf_token->lexeme);
            if( strcmp(id->leaf_token->lexeme, temp->node->leaf_token->lexeme) == 0 && (id->symbol_table_node->node->current_scope == temp->node->symbol_table_node->node->current_scope)) {
                return 1;
            }
            temp = temp->next;
        }
    }

    else {
        while(temp) {
            if(strcmp(id->leaf_token->lexeme, temp->node->leaf_token->lexeme) == 0 && strcmp(index->leaf_token->lexeme, temp->index->leaf_token->lexeme) == 0 && 
            (id->symbol_table_node->node->current_scope == temp->node->symbol_table_node->node->current_scope) && 
            (index->symbol_table_node->node->current_scope == temp->index->symbol_table_node->node->current_scope)) {
                return 1;
            }
            temp = temp->next;
        }
    }

    return 0;
}

int check_if_redeclared_in_scope(AST_list** head) {
    int is_redeclared = 0;

    AST_list* temp = *head;

    while(temp) {
        is_redeclared = search_current_scope(temp->node->leaf_token->lexeme, temp->node->current_scope) ? 1 : is_redeclared;
        temp = temp->next;
    }

    return is_redeclared;
}

void check_identifier(AST node, AST_list** head) {
    if(node == NULL)
        return;

    if(node->tag == 0) {

        if(node->symbol_table_node && node->symbol_table_node->datatype == 3) {
            AST index = node->next;
            // add node, index
            add_identifier(node, index, head);
        }
        else if(node->symbol_table_node) {
            // add node, NULL
            add_identifier(node, NULL, head);
        }
    }

    AST temp = node->child;

    while(temp) {
        check_identifier(temp, head);
        temp = temp->next;
    }

    return;
}

void add_identifier(AST node, AST index, AST_list** head) {
    
    AST_list* n = (AST_list*) malloc(sizeof(AST_list));
    n->index = index;
    n->next = NULL;
    n->node = node;

    if(head == NULL) {
        *head = n;
        return;
    }
    else {
        n->next = *head;
        *head = n;
    }

    return;
}

void print_identifier(AST_list* head) {
    AST_list* temp = head;

    while(temp) {
        printf("%s\n", temp->node->leaf_token->lexeme);
        temp = temp->next;
    }

    return;
}