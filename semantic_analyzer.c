// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include "semantic_analyzer.h"
#include "symbol_table.h"
#include "type_extractor.h"

// Array of strings for non leaf nodes of AST
char* tc_string_map_copy[AST_LABEL_NUMBER] = {
    "AST_PROGRAM", "MODULE_DECLARATIONS", "MODULE_DECLARATION", "OTHER_MODULES", "AST_DRIVER", "AST_MODULE", "INPUT_PLIST", "NEW1",
    "OUTPUT_PLIST", "NEW2", "DATA_TYPE", "DATA_TYPE2", "RANGE", "RANGE2", "STATEMENTS", "VAR", "ASSIGNMENT_STMT", 
    "LVALUE_ARR_STMT", "MODULE_REUSE_STMT", "ID_LIST", "NEWX", "EXPRESSION", "NEW6", "NEW7", "NEW8", "RELATIONAL_EXPR", 
    "DECLARE_STMT", "AST_FOR", "AST_WHILE", "CONDITIONAL_STMT", "CASE_STMT_T", "CASE_STMT_F", "NUMERIC_CASES", "NUMERIC_CASE", "IO_READ", "IO_WRITE", "AST_DEFAULT"
};

// Array of strings for non terminals of grammar
char * tc_non_terminals_string_map_copy[NON_TERMINAL_SIZE] = {"program", "moduleDeclarations", "moduleDeclaration", "otherModules", "driverModule", "module", "ret", "input_plist",
    "new1", "output_plist", "new2", "dataType", "dataType2", "type", "range", "range2", "moduleDef", "statements", "new3",
    "statement", "ioStmt", "var", "var2", "whichID", "simpleStmt", "assignmentStmt", "whichStmt", "lvalueIDstmt", "lvalueArrStmt", 
    "Index", "moduleReuseStmt", "optional", "idList", "newX", "expression", "new4", "AorBExpr", "arithmeticExpr", "new6",
    "term", "new7", "factor", "PlusMinus", "MulDiv", "relationalOP", "logicalOP", "boolKey", "boolExpr", "new8", "relationalExpr",
    "declareStmt", "iterativeStmt", "conditionalStatement", "caseStmt", "numericCases", 
    "numericCase", "new11", "Default", "NT_value"};

// Checking if indices of array are within bounds
int check_bound(AST index, AST var) {
    if(var->symbol_table_node->range[0].tag == 0 && var->symbol_table_node->range[1].tag == 0) {
        int id = index->leaf_token->val.num;

        if( id < var->symbol_table_node->range[0].range_pointer.value || id > var->symbol_table_node->range[1].range_pointer.value) {
            return 0;
        }
    }

    return 1;
}

// Checking if function defintion is valid and not redundant
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

// Main function of semantic analyzer
// Traverses AST in pre order
void type_checker(AST root, ErrorList* err, Symbol_Table_Tree tree) {
    
    if(root == NULL) {
        return;
    }

    int error;    
    if(root->rule_num==8 && root->tag==1 && !(is_valid_function(root->child, tree))) {
        return;
    }
    error = type_check_node(root, err);
    if(error == 2)
        return;

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

// Checks the semantics of each node of the AST
int type_check_node(AST node, ErrorList* err) {
    int rule_num = node->rule_num;
    int flag = 0;

    
    // ASSIGNMENT STATEMENTS
    if (rule_num == 52 && node->tag == 1) {

        AST lhs = node->child;
        AST expression_node = node->child->next;

        // Assignment statement for array element
        if(node->child->next->label == LVALUE_ARR_STMT) {
            
            expression_node = node->child->next->child->next;
            
            if(!lhs->symbol_table_node) {
                flag = 1;
            }
            else if(lhs->symbol_table_node && lhs->symbol_table_node->datatype != 3) {
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Variable: ");
                strcat(str, lhs->leaf_token->lexeme);
                strcat(str, " used as array is not of array type");
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
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"Element of array: ");
                        strcat(str, lhs->leaf_token->lexeme);
                        strcat(str, " is out of bounds");
                        add_sem_error(err,str,lhs->leaf_token->line_no);
                        flag = 1;
                    }
                }
                // In case ID is used, check if ID is type integer
                else if(index->rule_num == 58) {
                    if(index->symbol_table_node && index->symbol_table_node->datatype != 0) {
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"Index of array: ");
                        strcat(str, lhs->leaf_token->lexeme);
                        strcat(str, " is not an integer");
                        add_sem_error(err,str,index->leaf_token->line_no);
                        flag = 1;
                    }
                    else if(!index->symbol_table_node) {
                        flag = 1;
                    }
                }
            }
        }

        // Checking for assignment of array to array
        if(lhs->symbol_table_node && lhs->symbol_table_node->datatype == 3 && lhs->next->label != LVALUE_ARR_STMT) {
            if(expression_node && expression_node->child &&  expression_node->child->next == NULL && 
            expression_node->child->symbol_table_node && expression_node->child->symbol_table_node->datatype == 3) {
                
                if(expression_node->child->symbol_table_node->array_datatype != lhs->symbol_table_node->array_datatype) {
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"Array can be assigned to array with same type only");
                    add_sem_error(err,str,lhs->leaf_token->line_no);
                    flag = 1;
                }
                if(lhs->symbol_table_node->range[0].tag == 0 && expression_node->child->symbol_table_node->range[0].tag == 0) {
                    if(lhs->symbol_table_node->range[0].range_pointer.value != expression_node->child->symbol_table_node->range[0].range_pointer.value) {
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"Array can be assigned to array with same type and bounds only");
                        add_sem_error(err,str,lhs->leaf_token->line_no);
                        flag = 1;
                    }
                }
                if(lhs->symbol_table_node->range[1].tag == 0 && expression_node->child->symbol_table_node->range[1].tag == 0) {
                    if(lhs->symbol_table_node->range[1].range_pointer.value != expression_node->child->symbol_table_node->range[1].range_pointer.value) {
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"Array can be assigned to array with same type and bounds only");
                        add_sem_error(err,str,lhs->leaf_token->line_no);
                        flag = 1;
                    }
                }
            }
            else if(expression_node && expression_node->child &&  expression_node->child->next == NULL && 
            expression_node->child->symbol_table_node && expression_node->child->symbol_table_node->datatype != 3) {
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Variables: ");
                strcat(str, lhs->leaf_token->lexeme);
                strcat(str, " and ");
                strcat(str, expression_node->child->leaf_token->lexeme);
                strcat(str, " are of different types");
                add_sem_error(err,str,lhs->leaf_token->line_no);
                flag = 1;
            }
            else {
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Only an array with same type and bounds can be assigned to array");
                strcat(str, lhs->leaf_token->lexeme);
                add_sem_error(err,str,lhs->leaf_token->line_no);
                flag = 1;
            }
        }
        else {

            int expression_type = extract_type(expression_node, err);
            int lhs_type = get_id_type(lhs);

            // Checking if type of lhs and rhs of expression match
            if(expression_type != lhs_type) {
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Invalid type in assignment to variable: ");
                strcat(str, lhs->leaf_token->lexeme);
                add_sem_error(err,str,lhs->leaf_token->line_no);
                flag = 1;
            }
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
                strcpy(str, "Element of array: ");
                strcat(str, node->child->leaf_token->lexeme);
                strcat(str, " is out of bounds");
                add_sem_error(err, str, node->child->leaf_token->line_no);
                flag = 1;
                return flag;
            }
        }

        else if(node->child->symbol_table_node->datatype != 3 && node->child->next) {
            printf("HI\n");
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str, "Non array variable: ");
            strcat(str, node->child->leaf_token->lexeme);
            strcat(str, " cannot have index");
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
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"For loop variable: ");
            strcat(str, node->child->leaf_token->lexeme);
            strcat(str, " has to have integer datatype"); // Checking datatype of for loop variable
            add_sem_error(err,str,node->child->leaf_token->line_no);
            flag = 1;
        }

        Symbol_Node* temp1 = search_current_scope(node->child->leaf_token->lexeme, node->child->current_scope);
        if(temp1) {
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"Variable: ");
            strcat(str, node->child->leaf_token->lexeme);
            strcat(str, " used as for loop variable is declared again");
            add_sem_error(err,str,temp1->node->leaf_token->line_no);
            flag = 1;
        }

        AST_list** id_used = (AST_list **)malloc(sizeof(AST_list *));
        
        add_identifier(node->child, NULL, id_used);
        int current = 0;
        int line_num = 0;
        
        if(node->child->next->next->label == STATEMENTS)
            check_if_modified(id_used, node->child->next->next, &current, &line_num);
        
        if(current) {
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"For loop variable: ");
            strcat(str, node->child->leaf_token->lexeme);
            strcat(str, " cannot be assigned a value inside for");
            add_sem_error(err,str,line_num);
            flag = 1;
        }
    }

    
    // SWITCH statement
    if(node->rule_num == 103 && node->tag == 1) {
        if(!search_symbol_table(node->child->leaf_token->lexeme, node->current_scope)) {
            flag = 1;
            return flag;
        }

        else if(node->child->symbol_table_node && node->child->symbol_table_node->datatype !=2 && node->child->symbol_table_node->datatype !=0){
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"Variable: ");
            strcat(str, node->child->leaf_token->lexeme);
            strcat(str, " used in switch must have integer or boolean datatype"); // Checking datatype of switch condition variable
            add_sem_error(err,str,node->child->leaf_token->line_no);
            flag = 2;
            return flag;
        }
        int datatype = node->child->symbol_table_node->datatype;
        AST temp = node->child->next;
        int c = 0;
        while(temp && temp->label == NUMERIC_CASES) {            
            if(datatype == 0 && temp->child->child->leaf_token && temp->child->child->leaf_token->token != NUM) {
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Case value is incorrect as condition type is integer");
                add_sem_error(err,str,temp->child->child->leaf_token->line_no);
                flag = 1;
            }
            else if(datatype==2 && temp->child->child->leaf_token && temp->child->child->leaf_token->token == NUM) {
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Case value is incorrect as condition type is boolean");
                add_sem_error(err,str,temp->child->child->leaf_token->line_no);
                flag = 1;
            }
            else if(datatype==2 && temp->child->child->leaf_token && temp->child->child->leaf_token->token == TRUE) {
                if(c==0)
                    c = 1;
                else if(c==2)
                    c = 3;
                else {
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"Case true already present");
                    add_sem_error(err,str,temp->child->child->leaf_token->line_no);
                    flag = 1;
                }
            }
            else if(datatype==2 && temp->child->child->leaf_token && temp->child->child->leaf_token->token == FALSE) {
                if(c==0)
                    c = 2;
                else if(c==1)
                    c = 3;
                else {
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"Case false already present");
                    add_sem_error(err,str,temp->child->child->leaf_token->line_no);
                    flag = 1;
                }
            }

            temp = temp->child->next;
        }
        if(datatype == 2) {
            if(c == 1) {
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Switch with boolean type does not have case false");
                add_sem_error(err,str,node->child->next->next->next->leaf_token->line_no);
                flag = 1;
            }
            else if(c == 2) {
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Switch with boolean type does not have case true");
                add_sem_error(err,str,node->child->next->next->next->leaf_token->line_no);
                flag = 1;
            }
            else if(c == 0) {
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Switch with boolean type does not have case true or case false");
                add_sem_error(err,str,node->child->next->next->next->leaf_token->line_no);
                flag = 1;
            }
            if(temp) {
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Switch with boolean type cannot have default"); // Default case semantics
                add_sem_error(err,str,temp->child->leaf_token->line_no);
                flag = 1;
            }
        }
        else if(datatype == 0) {
            if(!temp) {
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Switch with integer condition type must have default"); // Default case semantics
                add_sem_error(err,str,node->child->next->next->next->leaf_token->line_no);
                flag = 1;
            }
        }
        
    }

    // WHILE LOOP SEMANTICS
    if(node->rule_num == 102) {
        int type = extract_type(node->child, err);
        AST start, end;
        if(node->child->next->label == STATEMENTS) {
            start = node->child->next->next;
            end = start->next;
        }
        else {
            start = node->child->next;
            end = start->next;
        }
        
        if(type != 2) {
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"Exression used in while construct should be of type boolean"); //Checking type of expression used in while condition
            add_sem_error(err,str, (start->leaf_token->line_no) - 1);
            flag = 1;
        }
        else {
            AST_list** id_used = (AST_list **)malloc(sizeof(AST_list *));
            check_identifier(node->child, id_used);

            if((*id_used) == NULL) {
                // char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                // strcpy(str,"No identifier used in while construct");
                // add_sem_error(err,str,(start->leaf_token->line_no) - 1);
                flag = 1;
            }
            
            if(!flag) {
                int line_num = 0;
                AST temp;
                int is_redeclared = check_if_redeclared_in_scope(id_used, &line_num, &temp);
                if(is_redeclared) {
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"Identifier: ");
                    strcat(str, temp->leaf_token->lexeme);
                    strcat(str, " used in while construct cannot be redeclared");
                    add_sem_error(err,str,line_num);
                    flag = 1;
                }
            }

            if(!flag) {
                int is_modified = 0;
                int line_num = 0;
                if(node->child->next->label == STATEMENTS) {
                    check_if_modified(id_used, node, &is_modified, &line_num);
                    line_num = node->child->next->next->next->leaf_token->line_no;
                }
                else {
                    line_num = node->child->next->next->leaf_token->line_no;
                }

                if(!is_modified) {
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"No variable in while condition modified"); //checking if at least one variable in while condition has been modified
                    add_sem_error(err,str, line_num);
                    flag = 1;
                }
            }
        }
    }
    
    // Module reuse statement
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
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"Called module: ");
            strcat(str, fun_id->leaf_token->lexeme);
            strcat(str, " not defined");
            add_sem_error(err,str,fun_id->leaf_token->line_no);
            return flag;
        }

        // If recursive call
        if(strcmp(fun_id->leaf_token->lexeme, node->current_scope->name)==0) {
            flag = 1;
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"Module: ");
            strcat(str, fun_id->leaf_token->lexeme);
            strcat(str, " is recursively called");
            add_sem_error(err,str,fun_id->leaf_token->line_no);
            return flag;
        }
        
        Symbol_Table_Tree ip_list = fun_tree->input, op_list = fun_tree->output;

        Symbol_Node*** ip_head, ***op_head;
        ip_head = (Symbol_Node***) malloc(sizeof(Symbol_Node**));
        op_head = (Symbol_Node***) malloc(sizeof(Symbol_Node**));
        
        // Getting list of formal input and output parameters
        int ip_count = convert_to_list(ip_list, ip_head);
        int op_count = convert_to_list(op_list, op_head);

        // checking input first
        int ip_succ = 0;
        AST act_ip = fun_id->next;
        AST *list_input = (AST*)malloc(sizeof(AST)*ip_count);
        int input_count = 0;
        
        // Checking number and type of actual input parameters
        ip_succ = verify_types(act_ip, ip_head, ip_count, ip_count, 0, list_input, &input_count);
        if(ip_succ == 2) {
            flag = 1;
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"Number of input parameters does not match with that of formal parameters");
            add_sem_error(err,str,fun_id->leaf_token->line_no);
        }
        else if(input_count != 0) {
            flag = 1;
            int i;
            for(i=0; i<input_count; i++) {
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Type of input parameter: ");
                strcat(str, list_input[i]->leaf_token->lexeme);
                strcat(str, " does not match with that of formal parameter");
                add_sem_error(err,str,fun_id->leaf_token->line_no);
            }
        }
        

        // checking output now
        int op_succ = 0;
        AST *list_output;
        int output_count = 0;
        if(node->child->tag == 0 && op_count == 0) {
            op_succ = 1;
        }
        else if(node->child->tag == 0 && op_count) {
            flag = 1;
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"Number of output parameters does not match with that of formal parameters");
            add_sem_error(err,str,fun_id->leaf_token->line_no);
            return flag;
        }
        else if(node->child->tag == 1) {
            AST act_op = node->child;
            list_output = (AST*)malloc(sizeof(AST)*op_count);
            op_succ = verify_types(act_op, op_head, op_count, op_count, 0, list_output, &output_count);
        }

        // Checking number and type of actual input parameters
        if(op_succ == 2) {
            flag = 1;
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"Number of output parameters does not match with that of formal parameters");
            add_sem_error(err,str,fun_id->leaf_token->line_no);
            return flag;
        }

        if(output_count != 0) {
            flag = 1;
            int i;
            for(i=0; i<output_count; i++) {
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Type of output parameter: ");
                strcat(str, list_output[i]->leaf_token->lexeme);
                strcat(str, " does not match with that of formal parameter");
                add_sem_error(err,str,fun_id->leaf_token->line_no);
            }
            return flag;
        }
        return flag;

    }

    // Function defintion semantics
    if(node->rule_num == 8 && node->tag == 1) {
        AST temp = node->child->next->next;
        if(temp->tag !=1 || temp->label != OUTPUT_PLIST)
            return flag;

        Symbol_Table_Tree op_list = temp->child->current_scope;


        Symbol_Node ***op_head;
        op_head = (Symbol_Node***) malloc(sizeof(Symbol_Node**));

        int op_count = convert_to_list(op_list, op_head);
        AST fun_def = node->child->next->next->next;

        int op_assign_error = 0;
        int line_num, itr;
        AST temp1;

        if(fun_def->label != STATEMENTS) {
            fun_def = NULL;
            line_num = node->child->next->next->next->next->leaf_token->line_no;
        }
        else {
            line_num = node->child->next->next->next->next->next->leaf_token->line_no;
        }

        // Checking if all output parameters of function have been modified
        for(itr = 0; itr<op_count; itr++) {
            Symbol_Node* curr_op = (*op_head)[itr];
            int current = 0;
            check_if_output_modified(curr_op, fun_def, &current, &temp1);
            if(!current) {
                flag = 1;
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Output parameter: ");
                strcat(str, temp1->leaf_token->lexeme);
                strcat(str, " not assigned value");
                add_sem_error(err,str,line_num);
                current = 0;
            }
        }
        
    }
    return flag;
}

// Getting a list of symbol nodes of formal parameters
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

// Comparing actual and formal parameters
int verify_types(AST nt, Symbol_Node*** head, int total, int count, int curr, AST *list, int *error_count) {
    int error;
    // No inputs
    if(nt == NULL && count == 0) {
        return 1;
    }
    else if(nt == NULL && count > 0) {
        // Expected input, but got none
        return 2;
    }
    else if(nt != NULL && count == 0) {
        // Did not expect input, but got input
        return 2;
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
                    list[*error_count] = ip;
                    *error_count += 1;
                }
                else if(ip->symbol_table_node->datatype == 3) { // Match for array parameters
                    if(ip->symbol_table_node->array_datatype != temp->array_datatype) {
                        list[*error_count] = ip;
                        *error_count += 1;
                    }
                    else {
                        int c = 0;
                        if(ip->symbol_table_node->range[0].tag == 0 && temp->range[0].tag == 0 && ip->symbol_table_node->range[0].range_pointer.value != temp->range[0].range_pointer.value) {
                            list[*error_count] = ip;
                            *error_count += 1;
                            c += 1;
                        }
                        if(ip->symbol_table_node->range[1].tag == 0 && temp->range[1].tag == 0 && ip->symbol_table_node->range[1].range_pointer.value != temp->range[1].range_pointer.value) {
                            if(!c) {
                                list[*error_count] = ip;
                                *error_count += 1;
                            }
                        }
                    }
                }

                return verify_types(ip->next, head, total, count - 1, curr + 1, list, error_count);
            }
            continue;
        }
        return 0;
    }
}

// Check if all outputs of function have been modified
// by either assignment, get_value, or module reuse statement
void check_if_output_modified(Symbol_Node* sym, AST node, int* current, AST *temp1) {
    
    if(node == NULL || (*current) == 1) {
        *temp1 = sym->node;
        return;
    }

    if(node->rule_num == 52 && node->tag == 1) {
        AST id = node->child;
        AST index = NULL;
        if(id->next && id->next->label == LVALUE_ARR_STMT && id->next->child) {
            index = id->next->child;
        }


        if(!index) {
            if(strcmp(id->leaf_token->lexeme, sym->node->leaf_token->lexeme) == 0) {
                *current = 1;
                *temp1 = sym->node;
            }
        }

        if((*current) == 1) {
            return;
        }
    }

    else if(node->rule_num == 40 && node->tag == 0) {
        if(strcmp(node->leaf_token->lexeme, sym->node->leaf_token->lexeme) == 0) {
            *current = 1;
            *temp1 = sym->node;
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
                    *temp1 = sym->node;
                }
                if((*current)==1)
                    return;
                temp = temp->child->next;
            }
        }
    }

    AST temp = node->child;

    while(temp) {
        check_if_output_modified(sym, temp, current, temp1);
        temp = temp->next;
    }
    *temp1 = sym->node;

    return;
}

// Check if at least one variable has been modified
// by either assignment, get_value, or module reuse statement
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

// Compare two AST nodes
int compare_list_node(AST_list** head, AST id, AST index) {
    
    AST_list* temp = *head;

    if(id->symbol_table_node && id->symbol_table_node->datatype != 3) {
        while(temp) {
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

// Check if variable has been redeclared in a scope, such as while or for
int check_if_redeclared_in_scope(AST_list** head, int *line_num, AST *temp1) {
    int is_redeclared = 0;

    AST_list* temp = *head;

    while(temp) {
        is_redeclared = search_current_scope(temp->node->leaf_token->lexeme, temp->node->current_scope) ? 1 : is_redeclared;
        if(is_redeclared == 1) {
            *line_num = temp->node->leaf_token->line_no;
            *temp1 = temp->node;
            break;
        }
        temp = temp->next;
    }

    return is_redeclared;
}

// Check if identifier has been used
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

// Add identifier to a list of nodes
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

// Print list of identifiers
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

// Add semantic error to list
void add_sem_error(ErrorList* list, char* str, int line_num) {
	
	Error* error = (Error*)malloc(sizeof(Error));
	error->line_num = line_num;
	error->str = str;
	error->next = list->head;
	list->head = error;
	list->total_errors++;
}

// Sort semantic errors by line number
void sort_errors(ErrorList* list) {

	if(!(list->head)) {

		return;
	}

	sort_errors_util(list->head,list->total_errors);
}

// Recursive function to sort errors
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

// Print all sorted semantic errors
void print_errors(ErrorList* errors) {

	Error* temp = errors->head;
	printf("Semantic errors:\n\n");
	while(temp!=NULL) {
        if(temp->line_num!=-1) {
		    printf("Line %d: %s\n",temp->line_num,temp->str);
        }
        else {
		    printf("%s\n",temp->str);
        }
		temp=temp->next;
	}

}
