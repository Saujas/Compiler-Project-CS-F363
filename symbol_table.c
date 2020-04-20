// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include "symbol_table.h"
#include "semantic_analyzer.h"

// Array of strings for non leaf nodes of AST
char* ast_string_map_copy[AST_LABEL_NUMBER] = {
    "AST_PROGRAM", "MODULE_DECLARATIONS", "MODULE_DECLARATION", "OTHER_MODULES", "AST_DRIVER", "AST_MODULE", "INPUT_PLIST", "NEW1",
    "OUTPUT_PLIST", "NEW2", "DATA_TYPE", "DATA_TYPE2", "RANGE", "RANGE2", "STATEMENTS", "VAR", "ASSIGNMENT_STMT", 
    "LVALUE_ARR_STMT", "MODULE_REUSE_STMT", "ID_LIST", "NEWX", "EXPRESSION", "NEW6", "NEW7", "NEW8", "RELATIONAL_EXPR", 
    "DECLARE_STMT", "AST_FOR", "AST_WHILE", "CONDITIONAL_STMT", "CASE_STMT_T", "CASE_STMT_F", "NUMERIC_CASES", "NUMERIC_CASE", "IO_READ", "IO_WRITE", "AST_DEFAULT"
};

// Array of strings for non terminals of grammar
char * ast_non_terminals_string_map_copy[NON_TERMINAL_SIZE] = {"program", "moduleDeclarations", "moduleDeclaration", "otherModules", "driverModule", "module", "ret", "input_plist",
    "new1", "output_plist", "new2", "dataType", "dataType2", "type", "range", "range2", "moduleDef", "statements", "new3",
    "statement", "ioStmt", "var", "var2", "whichID", "simpleStmt", "assignmentStmt", "whichStmt", "lvalueIDstmt", "lvalueArrStmt", 
    "Index", "moduleReuseStmt", "optional", "idList", "newX", "expression", "new4", "AorBExpr", "arithmeticExpr", "new6",
    "term", "new7", "factor", "PlusMinus", "MulDiv", "relationalOP", "logicalOP", "boolKey", "boolExpr", "new8", "relationalExpr",
    "declareStmt", "iterativeStmt", "conditionalStatement", "caseStmt", "numericCases", 
    "numericCase", "new11", "Default", "NT_value"};

// Hash a variable based on ASCII value
int hash_symbol_table(char* key, int slots) {
    int result = 0;
    int i;

    for(i=0; i<strlen(key); i++)
        result = (result + key[i]) % slots;

    return result % slots;
}

// Search current and all parent scopes
Symbol_Node* search_symbol_table(char* id, Symbol_Table_Tree table_tree_node) {
    Symbol_Table* table = table_tree_node->table;
    int h = hash_symbol_table(id, table->number_of_slots);
    Symbol_List* temp = table->slots[h]->head;
    
    Symbol_Node* temp1 = NULL;

    while(temp) {
        if( strcmp(temp->symbol->node->leaf_token->lexeme, id) == 0) {
            return temp->symbol;
        }   
        
        temp = temp->next;
    }

    
    if(table_tree_node->is_function) {            
        temp1 = search_current_scope(id, table_tree_node->input);
    }
    
    if(table_tree_node->is_function && !temp1) {
        
        temp1 = search_current_scope(id, table_tree_node->output);
    }

    if(table_tree_node->parent && !temp1) {        
        temp1 = search_symbol_table(id, table_tree_node->parent);
    }

    
    return temp1;
}

// Search only current scope
Symbol_Node* search_current_scope(char* id, Symbol_Table_Tree table_tree_node) {
    
    Symbol_Table* table = table_tree_node->table;
    int h = hash_symbol_table(id, table->number_of_slots);
    Symbol_List* temp = table->slots[h]->head;

    while(temp) {
        if( strcmp(temp->symbol->node->leaf_token->lexeme, id) == 0) {
            return temp->symbol;
        }   
        
        temp = temp->next;
    }

    if(table_tree_node->is_function) {
        return search_current_scope(id, table_tree_node->output);
    }

    return NULL;
}

// Insert variable into symbol table slot based on its hash value
void insert_symbol(Symbol_Table* symbol_table, char* key, Symbol_Node* node) {
    int hash_value = hash_symbol_table(key, symbol_table->number_of_slots);
    Symbol_List* new = (Symbol_List*) malloc(sizeof(Symbol_List));
    if(node->node)
        node->node->symbol_table_node = node;
    new->symbol = node;
    new->next = NULL;
    Slots_List* temp = symbol_table->slots[hash_value];
    if(temp->head) {
        new->next = temp->head;
        temp->head = new;
        temp->count += 1;
    }
    else {
        temp->head = new;
        temp->count = 1;
    }
}

// Create a new scope or symbol table
Symbol_Table* create_symbol_table(int slots) {
    Symbol_Table* symbol_table = (Symbol_Table*) malloc(sizeof(Symbol_Table));
    symbol_table->number_of_slots = slots;
    symbol_table->slots = (Slots_List**) malloc(slots*sizeof(Slots_List*));

    int i;
    for(i=0; i<slots; i++) {
        symbol_table->slots[i] = (Slots_List*) malloc(sizeof(Slots_List));
        symbol_table->slots[i]->count = 0;
        symbol_table->slots[i]->head = NULL;
    }
    return symbol_table;
}

// Make a new node for a new scope, having all attributes such as start and end line numbers, and nested level
Symbol_Table_Tree make_symbol_table_tree_node(Symbol_Table_Tree parent, Label label, char* name, int is_function, int start, int end, int level) {
    Symbol_Table_Tree node = (Symbol_Table_Tree) malloc(sizeof(struct symbol_table_tree_node));
    node->parent = parent;
    node->child = NULL;
    node->sibling = NULL;
    node->label = label;
    node->name = name;
    node->is_declared = 0;
    node->is_defined = 0;
    node->is_called = 0;
    node->is_function = is_function;
    node->start = start;
    node->end = end;
    node->level = level;
    node->input = NULL;
    node->output = NULL;
    node->table = create_symbol_table(SYMBOL_TABLE_SLOTS);
    node->last_offset = 0;
    node->last_offset2 = 0;

    if(label != INPUT_PLIST && label != OUTPUT_PLIST) {

        if(parent==NULL) {
            
        }

        else if(parent->child == NULL) {
            parent->child = node;
        }
        else {
            Symbol_Table_Tree temp = parent->child;

            while(temp->sibling) {
                temp = temp->sibling;
            }

            temp->sibling = node;
        }
    }
    
    return node;
}

// Check if a function has been defined
int check_if_defined(Symbol_Table_Tree current, char* lexeme) {
    Symbol_Table_Tree temp = current->child;

    if(temp == NULL)
        return 0;

    while(temp) {
        if((strcmp(temp->name, lexeme)==0) && (temp->is_defined == 1)) {
            return 1;
        }

        temp = temp->sibling;
    }

    return 0;
}

// Check if a module has been declared
int check_if_declared(Symbol_Table_Tree current, char* lexeme) {
    Symbol_Table_Tree temp = current->child;

    if(temp == NULL)
        return 0;

    while(temp) {
        if((strcmp(temp->name, lexeme) == 0) && (temp->is_defined == 0) && (temp->is_declared == 1)) {
            return 1;
        }

        temp = temp->sibling;
    }

    return 0;
}

// Check if a module has been called
int check_if_called(Symbol_Table_Tree current, char* lexeme) {
    Symbol_Table_Tree temp = current->child;

    if(temp == NULL)
        return 0;

    while(temp) {
        if((strcmp(temp->name, lexeme) == 0) && (temp->is_called == 1)) {
            return 1;
        }

        temp = temp->sibling;
    }

    return 0;
}

// Main function to create symbol tables for all variables used in program
Symbol_Table_Tree create_symbol_table_tree(AST root, ErrorList* err, int flag) {
    
    Symbol_Table_Tree tree = make_symbol_table_tree_node(NULL, AST_PROGRAM, "main", 0, 0, 0, -1);
    Slots_List* print_slot_list = (Slots_List*) malloc(sizeof(Slots_List));
    Symbol_List** print_list = (Symbol_List**) malloc(sizeof(Symbol_List*));
    traverse_ast(root, tree, err, print_slot_list, print_list);

    if(flag) {
        sort_errors(err);
        if((err->head) != NULL) {
            printf("Semantic errors occurred\n\n");
            print_errors(err);
        }
        else {
            printf("No semantic errors occurred\n\n");
            printf("Code compiles successfully\n\n");
        }
        if(flag == 1) {
            printf("\n%-20s%-25s%-24s%-10s%-12s%-20s%-17s%-18s%-14s%-12s\n\n", "Variable_name" , "Scope(module name)" , "Scope(line numbers)" , "Width" , "Is_Array" , "Static_or_Dynamic" , "Range_lexemes" , "Type of elememt" , "Offset" , "Nesting level");
            print_all_symbols(*print_list); // Print symbol table
        }
        else if(flag == 2) {
            printf("\n%-27s%-25s%-25s%-25s%-17s%-18s\n\n", "Scope(module name)" , "Scope(line numbers)" , "Variable_name" , "Static_or_Dynamic" , "Range_lexemes" , "Type of elememt");
            print_array_info(*print_list); // Print array information
        }
        else if(flag == 3) {
            printf("\n%-30s%-30s\n\n", "Function name", "Activation record size");
            print_activation_record_sizes(tree->child); //Print activation record sizes of functions
        }
    }

    return tree;
}

// Old testing print function
void print_symbol_tables(Symbol_Table_Tree tree) {
    if(tree==NULL)
        return;
    if(tree->is_function && tree->is_defined) {
        print_slots(tree->input->table);
        print_slots(tree->output->table);
    }
    if(tree->table != NULL)
        print_slots(tree->table);

    Symbol_Table_Tree temp = tree->child;
    while(temp) {
        print_symbol_tables(temp);
        temp = temp->sibling;
    }    
}

// Printing slot wise
void print_slots(Symbol_Table* table) {
    int slots = table->number_of_slots;
    int i;
    for(i=0; i<slots; i++) {
        print_symbols(table->slots[i]);
    }
    printf("\n");
}

// Printing information about each symbol
void print_symbols(Slots_List* list) {
    if(list->head==NULL)
        return;
    int count = list->count;
    Symbol_List* temp = list->head;
    const char* arr[3];
    arr[0] = "integer";
    arr[1] = "real";
    arr[2] = "boolean";
    while(count) {
        Symbol_Node* symbol = temp->symbol;
        printf("%s \t", symbol->node->leaf_token->lexeme);
        printf("%s \t", symbol->node->current_scope->name);
        printf("%d-%d \t", symbol->node->current_scope->start, symbol->node->current_scope->end);
        printf("%d \t", symbol->width2);
        if(symbol->datatype == 3) {
            printf("Yes \t");
            if(symbol->range[0].tag == 0 && symbol->range[1].tag == 0) {
                printf("Static \t");
                printf("[%d,%d] \t", symbol->range[0].range_pointer.value, symbol->range[1].range_pointer.value);
            }
            else if(symbol->range[0].tag == 0 && symbol->range[1].tag == 1) {
                printf("Dynamic \t");
                printf("[%d,%s] \t", symbol->range[0].range_pointer.value, symbol->range[1].range_pointer.id->node->leaf_token->lexeme);
            }
            else if(symbol->range[0].tag == 1 && symbol->range[1].tag == 0) {
                printf("Dynamic \t");
                printf("[%s,%d] \t", symbol->range[0].range_pointer.id->node->leaf_token->lexeme, symbol->range[1].range_pointer.value);
            }
            else if(symbol->range[0].tag == 1 && symbol->range[1].tag == 1) {
                printf("Dynamic \t");
                printf("[%s,%s] \t", symbol->range[0].range_pointer.id->node->leaf_token->lexeme, symbol->range[1].range_pointer.id->node->leaf_token->lexeme);
            }
            printf("%s \t", arr[symbol->array_datatype]);
        }
        else {
            printf("No \t");
            printf("--- \t");
            printf("--- \t");
            printf("%s \t", arr[symbol->datatype]);
        }
        printf("%d \t", symbol->offset2);
        printf("%d \t", symbol->node->current_scope->level);

        count--;
        temp = temp->next;
        printf("\n");
    }
}

// Make a new symbol node for a decalred variable
Symbol_Node* make_symbol_node(AST node, int datatype, int assigned, int width, int width2, int offset, int offset2, int usage, Range* range, int array_datatype) {
    Symbol_Node* symbol_node = (Symbol_Node*) malloc(sizeof(Symbol_Node));
    symbol_node->node = node;
    symbol_node->datatype = datatype;
    symbol_node->usage = usage;
    symbol_node->assigned = assigned;
    symbol_node->offset = offset;
    symbol_node->width = width;
    symbol_node->width2 = width2;
    symbol_node->offset2 = offset2;
    if(range != NULL) {
        symbol_node->range[0] = range[0];
        symbol_node->range[1] = range[1];
    }
    symbol_node->array_datatype = array_datatype;
    return symbol_node;
}

// Get scope of function in which node is present
Symbol_Table_Tree get_parent_scope(Symbol_Table_Tree current) {
    
    Symbol_Table_Tree parent_module = current;

    while(parent_module->parent && parent_module->parent->parent != NULL) {
        parent_module = parent_module->parent;
    }

    return parent_module;
}

// Traverses AST in pre order to make entire symbol table
void traverse_ast(AST node, Symbol_Table_Tree current,ErrorList* err, Slots_List* print_slot_list, Symbol_List** print_list) {
    if(!node)
        return;

    // Width: 2 for INT, 8: REAL, 1: BOOLEAN, 8: ARRAY OFFSET
    int data_width[4] = {2, 8, 1, 8};
    int data_width2[4] = {2, 4, 1, 1};

    // Module call's current scope doesn't have to be changed
    if(!((node->tag == 0 && node->rule_num == 59)||(node->tag == 0 && node->rule_num == 11) || (node->tag == 0 && node->rule_num == 14)||(node->tag == 0 && node->rule_num == 12) || (node->tag == 0 && node->rule_num == 15))) {
        node->current_scope = current;
    }
    
    Symbol_Table_Tree new = current;

    Symbol_Table_Tree parent_module = get_parent_scope(current);

    // Module defintions, not driver module
    if(node->tag == 1 && node->rule_num == 8) {
        char * name = node->child->leaf_token->lexeme;
        int declared = check_if_declared(current, name);
        int defined = check_if_defined(current, name);
        int called = check_if_called(current, name);
        int start, end;
        AST temp1 = node->child->next->next;
        if(temp1->label == OUTPUT_PLIST) {
            if(temp1->next->label == STATEMENTS) {
                start = temp1->next->next->leaf_token->line_no;
                end = temp1->next->next->next->leaf_token->line_no;
            }
            else {
                start = temp1->next->leaf_token->line_no;
                end = temp1->next->next->leaf_token->line_no;
            }
        }
        else {
            if(temp1->label == STATEMENTS) {
                start = temp1->next->leaf_token->line_no;
                end = temp1->next->next->leaf_token->line_no;
            }
            else {
                start = temp1->leaf_token->line_no;
                end = temp1->next->leaf_token->line_no;
            }
        }

        // Checking if recursive call
        if(defined) {
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"Module: ");
            strcat(str, name);
            strcat(str, " cannot be overloaded");
            add_sem_error(err,str,node->child->leaf_token->line_no);
            return;
        }

        else if(declared && (!called) && (!defined)) {
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"Module: ");
            strcat(str, name);
            strcat(str, " definiton and declaration both appear before its call"); // Checking if redundant declaration
            add_sem_error(err,str,node->child->leaf_token->line_no);
            return;
        }

        else if( !declared && !defined) {
            new = make_symbol_table_tree_node(current, AST_MODULE, name, 1, start, end, 1);
            new->input = make_symbol_table_tree_node(current, INPUT_PLIST, name, 0, start, end, 0);
            new->output = make_symbol_table_tree_node(current, OUTPUT_PLIST, name, 0, start, end, 0);
            new->is_defined = 1; // Creating new function symbol table
        }

        else if (declared && called) {
            Symbol_Table_Tree temp = current->child;

            while(temp) {
                if(strcmp(name, temp->name) == 0) {
                    new = temp;
                    new->is_defined = 1;
                    break;
                }
                temp = temp->sibling;
            }
            new->start = start;
            new->end = end;
            new->level = 1;
            new->input->start = start;
            new->input->end = end;
            new->input->level = 0;
            new->output->start = start;
            new->output->end = end;
            new->output->level = 0;
        }

    }

    // Driver Module definition
    if(node->rule_num == 7) {
        
        char * name = "AST_DRIVER";
        int defined = check_if_defined(current, name);

        int start;
        int end;

        if(node->child->tag != 1) {
            start = node->child->leaf_token->line_no;
            end = node->child->next->leaf_token->line_no;
        }
        else {
            start = node->child->next->leaf_token->line_no;
            end = node->child->next->next->leaf_token->line_no;
        }
        
        // Checking if driver already defined
        if(defined) {
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"Driver module already defined");
            add_sem_error(err,str,-1);
            return;
        }
        else {
            new = make_symbol_table_tree_node(current, AST_DRIVER, "driver", 0, start, end, 1);
            new->is_defined = 1;
            new->is_declared = 1;
        }
    }

    // Top-level module declarations
    if(node->tag == 0 && node->rule_num == 4) {
        char* name = node->leaf_token->lexeme;
        int declared = check_if_declared(current, name);

        if(declared) {
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"Module: ");
            strcat(str, name);
            strcat(str, " is re-declared");
            add_sem_error(err,str,node->leaf_token->line_no);
        }

        else {
            new = make_symbol_table_tree_node(current, MODULE_DECLARATION, name, 1, 0, 0, 0);
            new->input = make_symbol_table_tree_node(current, INPUT_PLIST, name, 0, 0, 0, 0);
            new->output = make_symbol_table_tree_node(current, OUTPUT_PLIST, name, 0, 0, 0, 0);
            new->is_declared = 1; // making new symbol table for new module declaration
            new->is_defined = 0;
        }
    }

    // Function Call Handling
    if(node->tag == 1 && node->rule_num == 59) {

        AST temp_node;
        if(node->child->tag == 0) 
            temp_node = node->child;
        else {
            temp_node = node->child->next;
        }

        char* name = temp_node->leaf_token->lexeme;
        Symbol_Table_Tree temp = current;

        while(temp->parent != NULL) {
            temp = temp->parent;
        }

        temp = temp->child;
        
        int declared = 0;
        while(temp) {
            if( strcmp(name, temp->name)==0 && (temp->label == MODULE_DECLARATION || temp->label == AST_MODULE)) {
                declared = 1;
                break;
            }
            temp = temp->sibling;
        }
        
        // Checking if called module has been declared
        if(!declared) {
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"Incorrect function call, module: ");
            strcat(str, name);
            strcat(str, " not found");

            add_sem_error(err,str,temp_node->leaf_token->line_no);
            temp_node->current_scope = NULL;
        }
        else {
            // Storing function's symbol table in its call (in id)
            temp_node->current_scope = temp;
            temp->is_called = 1;
        }
    }

    // New for loop scope
    if(node->rule_num == 101 && node->tag == 1) {
        int start, end;
        if(node->child->next->next->label == STATEMENTS) {
            start = node->child->next->next->next->leaf_token->line_no;
            end = node->child->next->next->next->next->leaf_token->line_no;
        }
        else {
            start = node->child->next->next->leaf_token->line_no;
            end = node->child->next->next->next->leaf_token->line_no;
        }
        int level = current->level + 1;
        new = make_symbol_table_tree_node(current, AST_FOR, "FOR", 0, start, end, level);
        new->is_declared = -1;
        new->is_defined = -1;
    }
    
    // New while loop scope
    if(node->rule_num == 102 && node->tag == 1) {
        int start, end;
        if(node->child->next->label == STATEMENTS) {
            start = node->child->next->next->leaf_token->line_no;
            end = node->child->next->next->next->leaf_token->line_no;
        }
        else {
            start = node->child->next->leaf_token->line_no;
            end = node->child->next->next->leaf_token->line_no;
        }
        int level = current->level + 1;
        new = make_symbol_table_tree_node(current, AST_WHILE, "WHILE", 0, start, end, level);
        new->is_declared = -2;
        new->is_defined = -2;
    }

    // New switch scope
    if(node->rule_num == 103 && node->tag == 1) {
        int start = node->child->next->next->leaf_token->line_no;
        int end = node->child->next->next->next->leaf_token->line_no;
        int level = current->level + 1;
        new = make_symbol_table_tree_node(current, CONDITIONAL_STMT, "SWITCH", 0, start, end, level);
        new->is_declared = -3;
        new->is_defined = -3;
    }
    
    // INPUT PLIST
    if(node->rule_num == 11 && node->tag == 1) {
        int datatype;
        int array_datatype;
        int param_order = 0;
        Node* type = NULL;
        AST temp = node;
        Symbol_Node* symbol_node;
        Symbol_Node* temp1;
        Symbol_Node* temp2;
        int flag = 0;

        while(temp) {
            flag = 0;
            type = temp->child->next->leaf_token;
            int offset = 0, width = 0, offset2 = 0, width2 = 0;

            // For non array type
            if(type != NULL) {
                if(strcmp(type->lexeme, "integer")==0) {
                    datatype = 0;
                }
                else if(strcmp(type->lexeme, "real")==0) {
                    datatype = 1; 
                }
                else if(strcmp(type->lexeme, "boolean")==0) {
                    datatype = 2;
                }

                offset = parent_module->last_offset;
                width = data_width[datatype];
                offset2 = current->input->last_offset2;
                width2 = data_width2[datatype];
                
                if(search_current_scope(temp->child->leaf_token->lexeme, current->input)==NULL) {
                    symbol_node = make_symbol_node(temp->child, datatype, 0, width, width2, offset, offset2, 2, NULL, -1);
                    flag = 1;
                }
                else {
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"Variable: ");
                    strcat(str, temp->child->leaf_token->lexeme);
                    strcat(str, " is re-declared");
                    add_sem_error(err,str,temp->child->leaf_token->line_no);
                    flag = 0;
                }
            }
            else { // For array input parameter
                datatype = 3;
                if(strcmp(temp->child->next->child->next->leaf_token->lexeme, "integer")==0) {
                    array_datatype = 0;
                }
                else if(strcmp(temp->child->next->child->next->leaf_token->lexeme, "real")==0){
                    array_datatype = 1;
                }
                else {
                    array_datatype = 2;
                }
                AST range1 = temp->child->next->child->child;
                AST range2 = range1->next;
                Range range[2];
                // int added = 0;

                // Checking array indices
                if(range1->leaf_token->token == NUM) { // Static bound
                    range[0].tag = 0;
                    range[0].range_pointer.value = range1->leaf_token->val.num;
                    flag = 1;
                    if(range1->leaf_token->val.num <= 0) {
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"Number used as array index has to be positive");
                        add_sem_error(err,str,range1->leaf_token->line_no);
                        flag = 0;
                    }
                }
                else { // Dynamic bound
                    int offset = parent_module->last_offset + 8;
                    int width = 2;
                    // added += 2;

                    temp1 = make_symbol_node(range1, 0, 0, 2, 2, offset, -1, 2, NULL, -1);
                    range[0].tag = 1;
                    range[0].range_pointer.id = temp1;
                    flag = 1;
                }

                if(range2->leaf_token->token == NUM) { // Static bound
                    range[1].tag = 0;
                    range[1].range_pointer.value = range2->leaf_token->val.num;
                    flag = 1;
                    if(range2->leaf_token->val.num <= 0) {
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"Number used as array index has to be positive");
                        add_sem_error(err,str,range2->leaf_token->line_no);
                        flag = 0;
                    }
                    if(range[0].tag == 0 && range[0].range_pointer.value >= range[1].range_pointer.value) {
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"Lower array limit greater than upper array limit");
                        add_sem_error(err,str,range2->leaf_token->line_no);
                        flag = 0;
                    }
                }
                else { // Dynamic bound
                    // int offset = parent_module->last_offset + added + 8;
                    int offset = parent_module->last_offset + 2 + 8;
                    int width = 2;
                    // added += 2;
                    
                    temp2 = make_symbol_node(range2, 0, 0, 2, 2, offset, -1, 2, NULL, -1);
                    range[1].tag = 1;
                    range[1].range_pointer.id = temp2;
                    flag = 1;
                }

                width = 8;
                offset = parent_module->last_offset;
                width2 = 5;
                offset2 = current->input->last_offset2;
                
                if(search_current_scope(temp->child->leaf_token->lexeme, current->input)==NULL) {
                    symbol_node = make_symbol_node(temp->child, datatype, 0, width, width2, offset, offset2, 2, range, array_datatype);
                    // width = width + added;
                    width = width + 4;
                    flag = 1;
                }
                else{
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"Variable: ");
                    strcat(str, temp->child->leaf_token->lexeme);
                    strcat(str, " is re-declared");
                    add_sem_error(err,str,temp->child->leaf_token->line_no);
                    flag = 0;
                }
            }
            if(flag) {
                symbol_node->param_order = param_order;
                param_order++;
                symbol_node->node->current_scope = current->input;
                insert_symbol(current->input->table, temp->child->leaf_token->lexeme, symbol_node);
                make_symbol_list(print_slot_list, symbol_node, print_list);
                parent_module->last_offset += width;
                current->input->last_offset2 += width2;
            }
            temp = temp->child->next->next;
        }
        return;
    }

    // OUTPUT PLIST
    if(node->rule_num == 14 && node->tag == 1) {
        int datatype;
        Node* type = NULL;
        AST temp = node;
        int param_order = 0;
        Symbol_Node* symbol_node;
        while(temp) {
            type = temp->child->next->leaf_token;
            if(strcmp(type->lexeme, "integer")==0) {
                datatype = 0;
            }
            else if(strcmp(type->lexeme, "real")==0) {
                datatype = 1; 
            }
            else if(strcmp(type->lexeme, "boolean")==0) {
                datatype = 2;
            }

            int offset = parent_module->last_offset;
            int width = data_width[datatype];
            int offset2 = current->input->last_offset2;
            int width2 = data_width2[datatype];

            if(search_current_scope(temp->child->leaf_token->lexeme, current->output)==NULL) {
                symbol_node = make_symbol_node(temp->child, datatype, 0, width, width2, offset, offset2, 1, NULL, -1);
                symbol_node->param_order = param_order;
                param_order++;
                symbol_node->node->current_scope = current->output;
                insert_symbol(current->output->table, temp->child->leaf_token->lexeme, symbol_node);
                make_symbol_list(print_slot_list, symbol_node, print_list);
                parent_module->last_offset += width;
                parent_module->last_offset += 8;
                current->input->last_offset2 += width2;
            }
            else{
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Variable: ");
                strcat(str, temp->child->leaf_token->lexeme);
                strcat(str, " is re-declared");
                add_sem_error(err,str,temp->child->leaf_token->line_no);
            }
            temp = temp->child->next->next;
        }
    }

    // DECLARE STATEMENT
    if(node->rule_num == 100 && node->tag == 1) {
        int datatype;
        int array_datatype;
        Node* type = NULL;
        AST temp = node;
        Symbol_Node* symbol_node;
        type = node->child->next->leaf_token;

        // For non array type
        if(type != NULL) {
            if(strcmp(type->lexeme, "integer")==0) {
                datatype = 0;
            }
            else if(strcmp(type->lexeme, "real")==0) {
                datatype = 1; 
            }
            else if(strcmp(type->lexeme, "boolean")==0) {
                datatype = 2;
            }

            int offset = parent_module->last_offset;
            int width = data_width[datatype];
            int offset2 = parent_module->last_offset2;
            int width2 = data_width2[datatype];

            if(search_current_scope(temp->child->child->leaf_token->lexeme, current)==NULL) { // Checking for redeclaration
                symbol_node = make_symbol_node(temp->child->child, datatype, 0, width, width2, offset, offset2, 1, NULL, -1);
                insert_symbol(current->table, temp->child->child->leaf_token->lexeme, symbol_node);
                make_symbol_list(print_slot_list, symbol_node, print_list);
                parent_module->last_offset += width;
                parent_module->last_offset2 += width2;
            }
            else{
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"Variable: ");
                strcat(str, temp->child->child->leaf_token->lexeme);
                strcat(str, " is re-declared");
                add_sem_error(err,str,temp->child->child->leaf_token->line_no);
            }

            temp = temp->child->child->next;
            while(temp) { // Traversing idlist of variables of the same type, and checking for redeclaration for each one
                if(search_current_scope(temp->child->leaf_token->lexeme, current)==NULL) {
                    offset = parent_module->last_offset;
                    offset2 = parent_module->last_offset2;
                    symbol_node = make_symbol_node(temp->child, datatype, 0, width, width2, offset, offset2, 1, NULL, -1);
                    insert_symbol(current->table, temp->child->leaf_token->lexeme, symbol_node);
                    make_symbol_list(print_slot_list, symbol_node, print_list);
                    parent_module->last_offset += width;
                    parent_module->last_offset2 += width2;
                }
                else{
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"Variable: ");
                    strcat(str, temp->child->leaf_token->lexeme);
                    strcat(str, " is re-declared");
                    add_sem_error(err,str,temp->child->leaf_token->line_no);
                }
                temp = temp->child->next;
            }
            
        }
        else { //For array type
            datatype = 3;
        
            if(strcmp(temp->child->next->child->next->leaf_token->lexeme, "integer")==0) {
                array_datatype = 0;
            }
            else if(strcmp(temp->child->next->child->next->leaf_token->lexeme, "real")==0){
                array_datatype = 1;
            }
            else {
                array_datatype = 2;
            }
            AST range1 = temp->child->next->child->child;
            AST range2 = range1->next;
            Range range[2];
            int flag = 1;

            // Checking array indices
            if(range1->leaf_token->token == NUM) { // Static bound
                range[0].tag = 0;
                range[0].range_pointer.value = range1->leaf_token->val.num;
                if(range1->leaf_token->val.num <= 0) {
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"Number used as array index has to be positive");
                    add_sem_error(err,str,range1->leaf_token->line_no);
                    flag = 0;
                }
            }
            else { // Dynamic bound
                Symbol_Node* temp1 = search_symbol_table(range1->leaf_token->lexeme, current);
                if(temp1 != NULL) {
                    if(temp1->datatype == 0) {
                        range[0].tag = 1;
                        range[0].range_pointer.id = temp1;
                    }
                    else {
                        flag = 0;
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"Variable: ");
                        strcat(str, range1->leaf_token->lexeme);
                        strcat(str, " used as array index has to be integer");
                        add_sem_error(err,str,temp->child->child->leaf_token->line_no);
                    }
                }
                else {
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"Variable: ");
                    strcat(str, range1->leaf_token->lexeme);
                    strcat(str, " used as array index not declared"); // Dynamic array index has to be declared
                    add_sem_error(err,str,range1->leaf_token->line_no);
                    flag = 0;
                }
            }

            if(range2->leaf_token->token == NUM) { // Static bound
                range[1].tag = 0;
                range[1].range_pointer.value = range2->leaf_token->val.num;
                if(range2->leaf_token->val.num <= 0) {
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"Number used as array index has to be positive");
                    add_sem_error(err,str,range2->leaf_token->line_no);
                    flag = 0;
                }
                if(range[0].tag == 0 && range[0].range_pointer.value >= range[1].range_pointer.value) {
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"Lower array limit greater than upper array limit");
                    add_sem_error(err,str,range2->leaf_token->line_no);
                    flag = 0;
                }
            }
            else { // Dynamic bound
                Symbol_Node* temp1 = search_symbol_table(range2->leaf_token->lexeme, current);
                if(temp1 != NULL) {
                    if(temp1->datatype == 0) {
                        range[1].tag = 1;
                        range[1].range_pointer.id = temp1;
                    }
                    else {
                        flag = 0;
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"Variable: ");
                        strcat(str, range2->leaf_token->lexeme);
                        strcat(str, " used as array index has to be integer");
                        add_sem_error(err,str,temp->child->child->leaf_token->line_no);
                    }
                }
                else {
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"Variable: ");
                    strcat(str, range2->leaf_token->lexeme);
                    strcat(str, " used as array index not declared"); // Dynamic array index has to be declared
                    add_sem_error(err,str,range2->leaf_token->line_no);
                    flag = 0;
                }
            }

            if(flag) {

                int width = 8, offset = parent_module->last_offset;
                int width2 = 1, offset2 = parent_module->last_offset2;
                int val1 = range[0].range_pointer.value, val2 = range[1].range_pointer.value;

                if(range[0].tag == 0 && range[1].tag == 0) {

                    if(val1 > 0 && val2 > val1) {
                        width = data_width[array_datatype] * (val2 - val1 + 1);
                        offset = parent_module->last_offset;
                        offset2 = parent_module->last_offset2;
                        width2 = data_width2[array_datatype] * (val2 - val1 + 1) + 1;
                    }
                }

                if(search_current_scope(temp->child->child->leaf_token->lexeme, current)==NULL) {
                    symbol_node = make_symbol_node(temp->child->child, datatype, 0, width, width2, offset, offset2, 1, range, array_datatype);
                    insert_symbol(current->table, temp->child->child->leaf_token->lexeme, symbol_node);
                    make_symbol_list(print_slot_list, symbol_node, print_list);
                    parent_module->last_offset += width;
                    parent_module->last_offset2 += width2;
                }
                else {
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"Variable: ");
                    strcat(str, temp->child->child->leaf_token->lexeme);
                    strcat(str, " is re-declared");
                    add_sem_error(err,str,temp->child->child->leaf_token->line_no);
                }

                temp = temp->child->child->next;
                while(temp) {
                    if(search_current_scope(temp->child->leaf_token->lexeme, current)==NULL) {
                        offset = parent_module->last_offset;
                        offset2 = parent_module->last_offset2;
                        symbol_node = make_symbol_node(temp->child, datatype, 0, width, width2, offset, offset2, 1, range, array_datatype);
                        insert_symbol(current->table, temp->child->leaf_token->lexeme, symbol_node);
                        make_symbol_list(print_slot_list, symbol_node, print_list);
                        parent_module->last_offset += width;
                        parent_module->last_offset2 += width2;
                    }
                    else {
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"Variable: ");
                        strcat(str, temp->child->leaf_token->lexeme);
                        strcat(str, " is re-declared");
                        add_sem_error(err,str,temp->child->leaf_token->line_no);
                    }
                    temp = temp->child->next;
                }
            }
        }
    }

    // HANDLING VARIABLE USAGE
    if(node->rule_num == 40 && node->tag == 0) {
        char* name = node->leaf_token->lexeme;
        Symbol_Node* temp;

        temp = search_symbol_table(name, current);

        if(!temp) { // Undeclared variable can't be used
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"Variable: ");
            strcat(str, name);
            strcat(str, " not declared");
            add_sem_error(err,str,node->leaf_token->line_no);
        }

        node->symbol_table_node = temp;

    }

    if((node->rule_num == 52 || node->rule_num == 42 || node->rule_num == 58 || node->rule_num == 69
    || node->rule_num == 103 || node->rule_num == 101) && node->tag == 0) {
        char* name = node->leaf_token->lexeme;

        Symbol_Node* temp = search_symbol_table(name, current);

        if(!temp) { // Undeclared variable can't be used
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"Variable: ");
            strcat(str, name);
            strcat(str, " not declared");
            add_sem_error(err,str,node->leaf_token->line_no);
        }

        node->symbol_table_node = temp;
    }

    // Checking module reuse statement
    if(node->rule_num == 59 && node->tag == 1) {
        AST temp = node->child;
        
        while(temp) { // Checking if actual input and output parameters have been declared or not
            AST temp2 = temp;
            if(temp->tag == 1) {
                
                while((temp2->rule_num == 62 || temp2->rule_num == 63) && (temp2->tag == 1)) {
                    char* name = temp2->child->leaf_token->lexeme;
                    
                    temp2->child->symbol_table_node = search_symbol_table(name, current);

                    if(temp2->child->symbol_table_node == NULL) {
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"Variable: ");
                        strcat(str, name);
                        strcat(str, " not declared");
                        add_sem_error(err,str,temp2->child->leaf_token->line_no);
                    }

                    temp2 = temp2->child->next;
                    if(!temp2)
                        break;
                }
            }
            temp = temp->next;
        }
    }

    AST temp = node->child;
    while(temp) {
        traverse_ast(temp, new, err, print_slot_list, print_list);
        temp = temp->next;
    }    

}

// Make a list of symbol in order of input source code
void make_symbol_list(Slots_List* list, Symbol_Node* node, Symbol_List** temp) {
    Symbol_List* new = (Symbol_List*) malloc(sizeof(Symbol_List));
    new->symbol = node;
    new->next = NULL;
    if(list->head) {
        new->next = list->head;
        new->next->prev = new;
        list->head = new;
        list->count += 1;
    }
    else {
        list->head = new;
        list->count = 1;
        *temp = new;
    }
}

// Print variables from all scopes
void print_all_symbols(Symbol_List *list) {
    const char* arr[3];
    arr[0] = "integer";
    arr[1] = "real";
    arr[2] = "boolean";
    while(list && list->symbol) {
        Symbol_Node* symbol = list->symbol;
        printf("%-20s", symbol->node->leaf_token->lexeme);
        Symbol_Table_Tree temp_tree = get_parent_scope(symbol->node->current_scope);
        printf("%-25s", temp_tree->name);
        char s[10];
        sprintf(s, "%d-%d", symbol->node->current_scope->start, symbol->node->current_scope->end);
        printf("%-24s", s);
        printf("%-10d", symbol->width2);
        if(symbol->datatype == 3) {
            printf("%-12s", "Yes");
            char t[100];
            if(symbol->range[0].tag == 0 && symbol->range[1].tag == 0) {
                printf("%-20s", "Static");
                sprintf(t, "[%d,%d]", symbol->range[0].range_pointer.value, symbol->range[1].range_pointer.value);
                printf("%-17s", t);
            }
            else if(symbol->range[0].tag == 0 && symbol->range[1].tag == 1) {
                printf("%-20s", "Dynamic");
                sprintf(t, "[%d,%s]", symbol->range[0].range_pointer.value, symbol->range[1].range_pointer.id->node->leaf_token->lexeme);
                printf("%-17s", t);
            }
            else if(symbol->range[0].tag == 1 && symbol->range[1].tag == 0) {
                printf("%-20s", "Dynamic");
                sprintf(t, "[%s,%d]", symbol->range[0].range_pointer.id->node->leaf_token->lexeme, symbol->range[1].range_pointer.value);
                printf("%-17s", t);
            }
            else if(symbol->range[0].tag == 1 && symbol->range[1].tag == 1) {
                printf("%-20s", "Dynamic");
                sprintf(t, "[%s,%s]", symbol->range[0].range_pointer.id->node->leaf_token->lexeme, symbol->range[1].range_pointer.id->node->leaf_token->lexeme);
                printf("%-17s", t);
            }
            printf("%-18s", arr[symbol->array_datatype]);
        }
        else {
            printf("%-12s", "No");
            printf("%-20s", "---");
            printf("%-17s", "---");
            printf("%-18s", arr[symbol->datatype]);
        }
        printf("%-14d", symbol->offset2);
        
        printf("%-12d", symbol->node->current_scope->level);

        list = list->prev;
        printf("\n");
    }
}

// Print array information
void print_array_info(Symbol_List *list) {
    const char* arr[3];
    arr[0] = "integer";
    arr[1] = "real";
    arr[2] = "boolean";

    while(list && list->symbol) {
        Symbol_Node* symbol = list->symbol;
        if(symbol->datatype == 3) {
            Symbol_Table_Tree temp_tree = get_parent_scope(symbol->node->current_scope);
            printf("%-27s", temp_tree->name);         
            char s[10];
            sprintf(s, "%d-%d", symbol->node->current_scope->start, symbol->node->current_scope->end);
            printf("%-25s", s);
            printf("%-25s", symbol->node->leaf_token->lexeme);
            char t[100];
            if(symbol->range[0].tag == 0 && symbol->range[1].tag == 0) {
                printf("%-25s", "Static array");
                sprintf(t, "[%d,%d]", symbol->range[0].range_pointer.value, symbol->range[1].range_pointer.value);
                printf("%-17s", t);
            }
            else if(symbol->range[0].tag == 0 && symbol->range[1].tag == 1) {
                printf("%-25s", "Dynamic array");
                sprintf(t, "[%d,%s]", symbol->range[0].range_pointer.value, symbol->range[1].range_pointer.id->node->leaf_token->lexeme);
                printf("%-17s", t);
            }
            else if(symbol->range[0].tag == 1 && symbol->range[1].tag == 0) {
                printf("%-25s", "Dynamic array");
                sprintf(t, "[%s,%d]", symbol->range[0].range_pointer.id->node->leaf_token->lexeme, symbol->range[1].range_pointer.value);
                printf("%-17s", t);
            }
            else if(symbol->range[0].tag == 1 && symbol->range[1].tag == 1) {
                printf("%-25s", "Dynamic array");
                sprintf(t, "[%s,%s]", symbol->range[0].range_pointer.id->node->leaf_token->lexeme, symbol->range[1].range_pointer.id->node->leaf_token->lexeme);
                printf("%-17s", t);
            }
            printf("%-18s", arr[symbol->array_datatype]);
            printf("\n");
        }
        
        list = list->prev;
    }

}

// Print activation record sizes of all functions
void print_activation_record_sizes(Symbol_Table_Tree tree) {
    int x;
    while(tree) {
        x = tree->last_offset2;
        if(tree->input)
            x += tree->input->last_offset2;
        printf("%-30s", tree->name);
        printf("%-30d", x);
        printf("\n");
        tree = tree->sibling;
    }
}