#include "semantic_analyzer.h"
#include "symbol_table.h"
#include "type_extractor.h"

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

int is_valid_function(AST node, Symbol_Table_Tree root) {
    char* id = node->leaf_token->lexeme;
    
    if(node->current_scope == NULL)
        return 0;
    
    Symbol_Table_Tree temp = root->child;
    while(temp) {
        if((strcmp(temp->name, id)==0)) {  
            if(temp->is_defined==0) {
                return 0;
            }
            else {
                return 1;   
            }
        }
        temp = temp->sibling;
    }
    return 1;
}

void type_checker(AST root, ErrorList* err, Symbol_Table_Tree tree) {
    
    if(root == NULL) {
        return;
    }

    int error;    
    if(root->rule_num==8 && root->tag==1 && !(is_valid_function(root->child, tree))) {
        return;
    }
    error = type_check_node(root, err);

    if(root->child==NULL) {
        return;
    }
    
    root = root->child;
    while(root) {
        type_checker(root, err, tree);
        root = root->next;
    }

    return;
}

int type_check_node(AST node, ErrorList* err) {
    // if(node->tag == 0)
    //     printf("%d\n", node->leaf_token->line_no);

    int rule_num = node->rule_num;
    int flag = 0;

    
    // ASSIGNMENT STATEMENTS
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
                //printf("Line: %d - Variable %s not of array type\n", lhs->leaf_token->line_no, lhs->leaf_token->lexeme);
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"ERROR:VARIABLE NOT OF ARRAY TYPE");
                add_sem_error(err,str,lhs->leaf_token->line_no);
                flag = 1;
            }
            else if(lhs->symbol_table_node && lhs->symbol_table_node->datatype == 3) {
                // Checking array type used on LHS of assignment statement
                AST index = lhs->next->child;

                // Checking bounds in case of static indexing
                if(index->rule_num == 57) {
                    int bound = check_bound(index, lhs);

                    if(bound == 0) {
                        //printf("Line: %d - Array out of bounds error\n", lhs->leaf_token->line_no);
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"ERROR: ARRAY INDEX OUT OF BOUNDS");
                        add_sem_error(err,str,lhs->leaf_token->line_no);
                        flag = 1;
                    }
                }
                // In case ID is used, check if ID is type integer
                else if(index->rule_num == 58) {
                    if(index->symbol_table_node && index->symbol_table_node->datatype != 0) {
                        //printf("Line: %d -  Array index type is not integer\n", index->leaf_token->line_no);
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"ERROR: ARRAY INDEX IS NOT INTEGER");
                        add_sem_error(err,str,index->leaf_token->line_no);
                        flag = 1;
                    }
                    else if(!index->symbol_table_node) {
                        flag = 1;
                    }
                }
            }
        }

        if(lhs->symbol_table_node && lhs->symbol_table_node->datatype == 3 && lhs->next->label != LVALUE_ARR_STMT) {
            if(expression_node && expression_node->child &&  expression_node->child->next == NULL && 
            expression_node->child->symbol_table_node && expression_node->child->symbol_table_node->datatype == 3) {
                
                if(expression_node->child->symbol_table_node->array_datatype != lhs->symbol_table_node->array_datatype) {
                    // printf("HII1\n");
                    //printf("Line: %d - Array can be assigned to array with same type only\n", lhs->leaf_token->line_no);
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    // printf("QQQQQ %d %d %d\n", lhs->leaf_token->line_no, lhs->symbol_table_node->array_datatype, expression_node->child->symbol_table_node->array_datatype);
                    strcpy(str,"ERROR: ARRAY CAN BE ASSIGNED TO ARRAY WITH SAME TYPE ONLY");
                    add_sem_error(err,str,lhs->leaf_token->line_no);
                    flag = 1;
                }
                if(lhs->symbol_table_node->range[0].tag == 0 && expression_node->child->symbol_table_node->range[0].tag == 0) {
                    // printf("HII2\n");
                    // printf("%d %d\n", lhs->symbol_table_node->range[1].tag, expression_node->child->symbol_table_node->range[1].tag);
                    if(lhs->symbol_table_node->range[0].range_pointer.value != expression_node->child->symbol_table_node->range[0].range_pointer.value) {
                       // printf("Line: %d - Array can be assigned to array with same type only\n", lhs->leaf_token->line_no);
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        // printf("RRRRR%d\n", lhs->leaf_token->line_no);
                        strcpy(str,"ERROR: ARRAY CAN BE ASSIGNED TO ARRAY WITH SAME TYPE ONLY");
                        add_sem_error(err,str,lhs->leaf_token->line_no);
                        flag = 1;
                    }
                }
                if(lhs->symbol_table_node->range[1].tag == 0 && expression_node->child->symbol_table_node->range[1].tag == 0) {
                    // printf("HII3\n");
                    if(lhs->symbol_table_node->range[1].range_pointer.value != expression_node->child->symbol_table_node->range[1].range_pointer.value) {
                        //printf("Line: %d - Array can be assigned to array with same type only\n", lhs->leaf_token->line_no);
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        // printf("EEEEE%d\n", lhs->leaf_token->line_no);
                        strcpy(str,"ERROR: ARRAY CAN BE ASSIGNED TO ARRAY WITH SAME TYPE ONLY");
                        add_sem_error(err,str,lhs->leaf_token->line_no);
                        flag = 1;
                    }
                }
            }
            else {
                //printf("Line: %d - Array can be assigned to array with same type only\n", lhs->leaf_token->line_no);
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                // printf("WWWWW%d\n", lhs->leaf_token->line_no);
                strcpy(str,"ERROR: ARRAY CAN BE ASSIGNED TO ARRAY WITH SAME TYPE ONLY");
                add_sem_error(err,str,lhs->leaf_token->line_no);
                flag = 1;
            }
        }
        else {

            int expression_type = extract_type(expression_node, err);
            int lhs_type = get_id_type(lhs);

            // if(lhs->leaf_token->line_no == 131)
            //     printf("%s: %d %d\n", lhs->leaf_token->lexeme, lhs_type, expression_type);

            if(expression_type != lhs_type) {
               // printf("Line: %d - Invalid types in assignment\n", lhs->leaf_token->line_no);
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"ERROR: INVALID TYPES IN ASSIGNMENT");
                add_sem_error(err,str,lhs->leaf_token->line_no);
                flag = 1;
            }
        }
        // printf("HIIIII\n");

    }

    // IO READ STATEMENT
    if(node->rule_num == 40 && node->tag == 0) {
        if(!search_symbol_table(node->leaf_token->lexeme, node->current_scope))
            flag = 1;
        else if((node->symbol_table_node->datatype == 2)) {
           // printf("Line: %d - Incompatible datatype of variable %s\n", node->leaf_token->line_no, node->leaf_token->lexeme);
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: INCOMPATIBLE DATA TYPE OF VARIABLE");
            add_sem_error(err,str,node->leaf_token->line_no);
            flag = 1;
        }
    }

    // IO WRITE STATEMENT
    if(node->rule_num == 42 && node->label == IO_WRITE && node->tag == 1) {
        if(node->child->symbol_table_node == NULL) {
            flag = 1;
            return flag;
        }

        if(node->child->symbol_table_node->datatype == 3 && node->child->next) {
            if((node->child->next->leaf_token->token == ID) && node->child->next->symbol_table_node == NULL) {
                flag = 1;
                return flag;
            }

            else if(node->child->next->leaf_token->token == NUM && !check_bound(node->child->next, node->child)) {
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str, "ERROR: INVALID INDEX USED IN ARRAY");
                add_sem_error(err, str, node->child->leaf_token->line_no);
                flag = 1;
                return flag;
            }
        }

        else if(node->child->symbol_table_node->datatype != 3 && node->child->next) {
            printf("HI\n");
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str, "ERROR: NON ARRAY VARIABLE CANNOT HAVE INDEX");
            add_sem_error(err, str, node->child->leaf_token->line_no);
            flag = 1;
            return flag;
        }
    }

    // FOR Statement
    if(node->rule_num == 101 && node->tag == 1) {
        if(!search_symbol_table(node->child->leaf_token->lexeme, node->current_scope))
            flag = 1;

        else if(node->child->symbol_table_node && node->child->symbol_table_node->datatype != 0) {
            //printf("Line: %d - Incompatible datatype in For loop variable %s\n", node->child->leaf_token->line_no, node->child->leaf_token->lexeme);
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: INCOMPATIBLE DATA TYPE IN FOR LOOP VARIABLE");
            add_sem_error(err,str,node->child->leaf_token->line_no);
            flag = 1;
        }

        Symbol_Node* temp1 = search_current_scope(node->child->leaf_token->lexeme, node->child->current_scope);
        if(temp1) {
            //printf("Line: %d - For loop variable is declared again\n", temp1->node->leaf_token->line_no);
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: FOR LOOP VARIABLE DECLARED AGAIN");
            add_sem_error(err,str,temp1->node->leaf_token->line_no);
            flag = 1;
        }

        AST_list** id_used = (AST_list **)malloc(sizeof(AST_list *));
        
        add_identifier(node->child, NULL, id_used);
        int current = 0;
        int line_num = 0;
        
        check_if_modified(id_used, node->child->next->next, &current, &line_num);
        
        if(current) {
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: FOR LOOP VARIABLE CANNOT BE ASSIGNED A VALUE INSIDE FOR");
            add_sem_error(err,str,line_num);
            flag = 1;
        }
    }

    
    // WHILE statement
    if(node->rule_num == 103 && node->tag == 1) {
        if(!search_symbol_table(node->child->leaf_token->lexeme, node->current_scope))
            flag = 1;
        else if(node->child->symbol_table_node->datatype == 2) {
            AST temp1 = node->child->next;
            if(temp1->label == NUMERIC_CASES) {
                //printf("Line: %d - Switch with boolean variable can have only true and false cases\n", node->child->leaf_token->line_no);
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"ERROR: SWITCH WITH BOOLEAN VARIABLE CAN HAVE ONLY TRUE AND FALSE CASES");
                add_sem_error(err,str,node->child->leaf_token->line_no);
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
                //printf("Line: %d - Switch with integer variable must have default\n", node->child->leaf_token->line_no);
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"ERROR: SWITCH WITH INTEGER VARIABLE MUST HAVE DEFAULT ");
                add_sem_error(err,str,node->child->leaf_token->line_no);
                flag = 1;
            }
        }
        else {
           // printf("Line: %d - Switch must have integer or boolean variable only\n", node->child->leaf_token->line_no);
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: SWITCH MUST HAVE INTEGER OR BOOLEAN VARIABLE ONLY");
            add_sem_error(err,str,node->child->leaf_token->line_no);
            flag = 1;
        }
    }

    // WHILE LOOP SEMANTICS
    if(node->rule_num == 102) {
        int type = extract_type(node->child, err);
        
        if(type != 2) {
            //printf("Line: - Incompatible expression used in while construct\n");
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: INCOMPATIBLE EXRESSION USED IN WHILE CONSTRUCT");
            add_sem_error(err,str,-1);
            flag = 1;
        }
        else {
            AST_list** id_used = (AST_list **)malloc(sizeof(AST_list *));
            check_identifier(node->child, id_used);
            // print_identifier(*id_used);

            if((*id_used) == NULL) {
                //printf("Line: - No identifier used in while construct\n");
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"ERROR: NO IDENTIFIER USED IN WHILE CONSTRUCT");
                add_sem_error(err,str,-1);
                flag = 1;
            }
            
            if(!flag) {
                int is_redeclared = check_if_redeclared_in_scope(id_used);
                if(is_redeclared) {
                    //printf("Line: - Identifier used in while construct cannot be redeclared\n");
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"ERROR: IDENTIFIER USED IN WHILE CONSTRUCT CANNOT BE REDECLARED");
                    add_sem_error(err,str,-1);
                    flag = 1;
                }
            }

            if(!flag) {
                int is_modified = 0;
                int line_num = 0;
                check_if_modified(id_used, node, &is_modified, &line_num);

                if(!is_modified) {
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"ERROR: NO VARIABLE IN WHILE CONDITION MODIFIED");
                    add_sem_error(err,str,-1);
                    flag = 1;
                }
                else {
                    // printf("ALL GOOD\n");
                }
            }
        }
    }
    //match ipplist and opplist of caller and called, formal and actual params
    // non recursion
    // opplist params must be assigned some values
    if(node->rule_num == 59 && node->tag == 1) {
        AST fun_id;
        if(node->child->tag==0) {
            fun_id = node->child;
        }
        else {
            fun_id = node->child->next;
        }
        

        Symbol_Table_Tree fun_tree = fun_id->current_scope;
        
        if(!fun_tree) {
            flag = 1;
            return flag;
        }

        // If function is not defined
        if(fun_tree && fun_tree->is_defined != 1) {
            flag = 1;
            //printf("Line: %d - Module used in call not defined\n", fun_id->leaf_token->line_no);
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: MODULE USED IN CALL NOT DEFINED");
            add_sem_error(err,str,fun_id->leaf_token->line_no);
            return flag;
        }

        // If recursive call
        if(strcmp(fun_id->leaf_token->lexeme, node->current_scope->name)==0) {
            flag = 1;
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: MODULE IS RECURSIVELY CALLED");
            add_sem_error(err,str,fun_id->leaf_token->line_no);
            return flag;
        }
        

        Symbol_Table_Tree ip_list = fun_tree->input, op_list = fun_tree->output;

        // printf("%s\n", fun_id->leaf_token->lexeme);

        Symbol_Node*** ip_head, ***op_head;
        ip_head = (Symbol_Node***) malloc(sizeof(Symbol_Node**));
        op_head = (Symbol_Node***) malloc(sizeof(Symbol_Node**));

        int ip_count = convert_to_list(ip_list, ip_head);
        int op_count = convert_to_list(op_list, op_head);
        // printf("%d %d\n", ip_count, op_count);

        // checking input first
        int ip_succ = 0;
        AST act_ip = fun_id->next;

        ip_succ = verify_types(act_ip, ip_head, ip_count, ip_count, 0);
        if(!ip_succ) {
            flag = 1;
            //printf("Line: %d - Input parameters do not match\n", fun_id->leaf_token->line_no);
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: INPUT PARAMETERS DO NOT MATCH");
            add_sem_error(err,str,fun_id->leaf_token->line_no);
            return flag;
        }
        

        // checking output now
        int op_succ = 0;
        if(node->child->tag == 0 && op_count == 0) {
            op_succ = 1;
        }
        else if(node->child->tag == 1) {
            AST act_op = node->child;
            op_succ = verify_types(act_op, op_head, op_count, op_count, 0);
        }

        if(!op_succ) {
            flag = 1;
            //printf("Line: %d - Output parameters do not match\n", fun_id->leaf_token->line_no);
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: OUTPUT PARAMETERS DO NOT MATCH");
            add_sem_error(err,str,fun_id->leaf_token->line_no);
            return flag;
        }

        // AST fun_def;
        // int itr;
        // for(itr = 0; itr<ip_count; itr++) {
        //     Symbol_Node* curr_ip = (*ip_head)[itr];
            
        //     if(curr_ip->param_order == 0) {
        //         // printf("%s\n", curr_ip->node->leaf_token->lexeme);
        //         // printf("%s\n", tc_string_map_copy[curr_ip->node->parent->next->label]);

        //         AST parent = curr_ip->node->parent;
        //         if(parent->next && (parent->next->tag == 1) && parent->next->label == OUTPUT_PLIST)
        //             fun_def = parent->next->next;
        //         else
        //             fun_def = parent->next;

        //         break;
        //     }
        // }
        

        // int op_assign_error = 0;
        // int line_num;
        // for(itr = 0; itr<op_count; itr++) {
        //     Symbol_Node* curr_op = (*op_head)[itr];
        //     int current = 0;
        //     check_if_output_modified(curr_op, fun_def, &current);
        //     if(!current) {
        //         op_assign_error = 1;
        //         line_num = curr_op->node->leaf_token->line_no;
        //         // printf("%d\n", line_num);
        //         break;
        //     }
        // }
        

        // if(op_assign_error) {
        //     flag = 1;
        //     // printf("Line: %d - All outputs not assigned value in module\n", fun_id->leaf_token->line_no);
        //     char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
        //     strcpy(str,"ERROR: ALL OUTPUTS NOT ASSIGNED VALUE IN MODULE");
        //     add_sem_error(err,str,line_num);
        //     return flag;
        // }

        // printf("Line: %d - Successful Function Call\n", fun_id->leaf_token->line_no);
    }

    // Function defintion semantics
    if(node->rule_num == 8 && node->tag == 1) {
        AST temp = node->child->next->next;
        if(temp->tag !=1 || temp->label != OUTPUT_PLIST)
            return flag;

        Symbol_Table_Tree op_list = temp->child->current_scope->output;
        printf("%s %s %d\n", op_list->name, node->child->leaf_token->lexeme, node->child->leaf_token->line_no);


        Symbol_Node ***op_head;
        op_head = (Symbol_Node***) malloc(sizeof(Symbol_Node**));

        int op_count = convert_to_list(op_list, op_head);
        printf("%d\n", op_count);
        AST fun_def = node->child->next->next->next;

        int op_assign_error = 0;
        int line_num, itr;
        for(itr = 0; itr<op_count; itr++) {
            Symbol_Node* curr_op = (*op_head)[itr];
            int current = 0;
            check_if_output_modified(curr_op, fun_def, &current);
            if(!current) {
                op_assign_error = 1;
                line_num = curr_op->node->leaf_token->line_no;
                // printf("%d\n", line_num);
                break;
            }
        }
        

        if(op_assign_error) {
            flag = 1;
            // printf("Line: %d - All outputs not assigned value in module\n", fun_id->leaf_token->line_no);
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: ALL OUTPUTS NOT ASSIGNED VALUE IN MODULE");
            add_sem_error(err,str,line_num);
            return flag;
        }
        
    }

    // also need to check whether all functions have been defined

    return flag;
}

int convert_to_list(Symbol_Table_Tree st, Symbol_Node*** head) {
    int i, count = 0;
    Symbol_Table* table = st->table;

    for(i=0; i<table->number_of_slots; i++) {
        count += table->slots[i]->count;
    }

    *head = (Symbol_Node**) malloc(sizeof(Symbol_Node*) * count);
    int c = 0;
    
    for(i=0; i<table->number_of_slots; i++) {
        Symbol_List* temp = table->slots[i]->head;

        while(temp) {
            (*head)[c] = temp->symbol;
            c++;
            temp = temp->next;
        }
    }

    return count;
}

int verify_types(AST nt, Symbol_Node*** head, int total, int count, int curr) {
    int error;
    // No inputs
    if(nt == NULL && count == 0) {
        return 1;
    }
    else if(nt == NULL && count > 0) {
        // Expected input, but got none
        return 0;
    }
    else if(nt != NULL && count == 0) {
        // Did not expect input, but got input
        return 0;
    }
    else {
        AST ip = nt->child;
        if(!(ip->symbol_table_node)) {
            return 0;
        }
        int i;
        for(i=0; i<total; i++) {
            Symbol_Node* temp = (*head)[i];
            if(temp->param_order == curr) {
                // match type
                if(ip->symbol_table_node->datatype != temp->datatype) {
                    return 0;
                }
                else if(ip->symbol_table_node->datatype == 3) {
                    if(ip->symbol_table_node->array_datatype != temp->array_datatype) {
                        return 0;
                    }
                    else {
                        if(ip->symbol_table_node->range[0].tag == 0 && ip->symbol_table_node->range[0].range_pointer.value != temp->range[0].range_pointer.value) {
                            return 0;
                        }
                        if(ip->symbol_table_node->range[1].tag == 0 && ip->symbol_table_node->range[1].range_pointer.value != temp->range[1].range_pointer.value) {
                            return 0;
                        }
                    }
                }

                return verify_types(ip->next, head, total, count - 1, curr + 1);
            }
            continue;
        }
        return 0;
    }
}

void check_if_output_modified(Symbol_Node* sym, AST node, int* current) {
    // if(sym->node->leaf_token->line_no == 60) {
        // printf("%s %d\n", sym->node->leaf_token->lexeme, sym->node->leaf_token->line_no);
    // }
    
    if(node == NULL || (*current) == 1) {
        return;
    }

    if(node->rule_num == 52 && node->tag == 1) {
        AST id = node->child;
        AST index = NULL;
        // printf("%d %s %s\n", id->leaf_token->line_no, sym->node->leaf_token->lexeme, id->leaf_token->lexeme);
        if(id->next && id->next->label == LVALUE_ARR_STMT && id->next->child) {
            index = id->next->child;
        }

        // *current = compare_list_node(head, id, index);

        if(!index) {
            if(strcmp(id->leaf_token->lexeme, sym->node->leaf_token->lexeme) == 0) {
                *current = 1;
            }
        }

        // printf("%d\n", *current);

        if((*current) == 1) {
            return;
        }
    }

    else if(node->rule_num == 40 && node->tag == 0) {
        if(strcmp(node->leaf_token->lexeme, sym->node->leaf_token->lexeme) == 0) {
            *current = 1;
        }
        if((*current) == 1)
            return;
    }

    else if(node->rule_num == 59 && node->tag == 1) {
        if(node->child->tag == 1 && node->child->symbol_table_node == NULL) {
            AST temp = node->child;
            while(temp) {
                if(strcmp(temp->child->leaf_token->lexeme, sym->node->leaf_token->lexeme)==0) {
                    *current = 1;
                }
                if((*current)==1)
                    return;
                temp = temp->child->next;
            }
        }
    }

    AST temp = node->child;

    while(temp) {
        check_if_output_modified(sym, temp, current);
        temp = temp->next;
    }

    return;
}

void check_if_modified(AST_list** head, AST node, int* current, int *line_no) {
    
    if(node == NULL || (*current) == 1)
        return;

    if(node->rule_num == 52 && node->tag == 1) {
        
        AST id = node->child;
        AST index = NULL;

        if(id->next && id->next->label == LVALUE_ARR_STMT && id->next->child) {
            index = id->next->child;
        }

        *current = compare_list_node(head, id, index);
        // printf("%d\n", *current);

        if((*current) == 1) {
            *line_no = id->leaf_token->line_no;
            return;
        }


    }

    else if(node->rule_num == 40 && node->tag == 0) {
        *current = compare_list_node(head, node, NULL);
        if((*current) == 1) {
            *line_no = node->leaf_token->line_no;
            return;
        }
    }

    else if(node->rule_num == 59 && node->tag == 1) {
        if(node->child->symbol_table_node == NULL) {
            AST temp = node->child;
            while(temp) {
                *current = compare_list_node(head, temp->child, NULL);
                if((*current)==1) {
                    *line_no = temp->child->leaf_token->line_no;
                    return;
                }
                temp = temp->child->next;
            }
        }
    }

    AST temp = node->child;

    while(temp) {
        check_if_modified(head, temp, current, line_no);
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

ErrorList* initialize_errors() {

	ErrorList* list = (ErrorList*) malloc(sizeof(ErrorList));
	list->total_errors = 0;
	list->head = NULL;
	return list;
}

void add_sem_error(ErrorList* list, char* str, int line_num) {
	
	Error* error = (Error*)malloc(sizeof(Error));
	error->line_num = line_num;
	error->str = str;
	error->next = list->head;
	list->head = error;
	list->total_errors++;
}

void sort_errors(ErrorList* list) {

	if(!(list->head)) {

		return;
	}

	sort_errors_util(list->head,list->total_errors);
}


void sort_errors_util(Error* temp, int count) {

	if(!(temp->next)) {

		return;
	}	
	sort_errors_util(temp->next,count--);	
	int line_num = temp->line_num;
	char* str = temp->str;
	Error* pretemp = temp;
	temp = temp->next;
	while(temp!=NULL) {

		if(temp->line_num > line_num) {

			break;
		}		
		pretemp->line_num = temp->line_num;
		pretemp->str = temp->str;
		temp = temp->next;
		pretemp = pretemp->next;
	
	}

	pretemp->line_num = line_num;
	pretemp->str = str;
}

void print_errors(ErrorList* errors) {

	Error* temp = errors->head;
	printf("Semantic Errors\n");
	while(temp!=NULL) {
        if(temp->line_num!=-1) {
		    printf("Line No: %d, %s\n",temp->line_num,temp->str);
        }
        else {
		    printf("%s\n",temp->str);
        }
		temp=temp->next;
	}

}
