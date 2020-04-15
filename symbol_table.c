#include "symbol_table.h"
#include "semantic_analyzer.h"

char* ast_string_map_copy[AST_LABEL_NUMBER] = {
    "AST_PROGRAM", "MODULE_DECLARATIONS", "MODULE_DECLARATION", "OTHER_MODULES", "AST_DRIVER", "AST_MODULE", "INPUT_PLIST", "NEW1",
    "OUTPUT_PLIST", "NEW2", "DATA_TYPE", "DATA_TYPE2", "RANGE", "RANGE2", "STATEMENTS", "VAR", "ASSIGNMENT_STMT", 
    "LVALUE_ARR_STMT", "MODULE_REUSE_STMT", "ID_LIST", "NEWX", "EXPRESSION", "NEW6", "NEW7", "NEW8", "RELATIONAL_EXPR", 
    "DECLARE_STMT", "AST_FOR", "AST_WHILE", "CONDITIONAL_STMT", "CASE_STMT_T", "CASE_STMT_F", "NUMERIC_CASES", "NUMERIC_CASE", "IO_READ", "IO_WRITE", "AST_DEFAULT"
};

char * ast_non_terminals_string_map_copy[NON_TERMINAL_SIZE] = {"program", "moduleDeclarations", "moduleDeclaration", "otherModules", "driverModule", "module", "ret", "input_plist",
    "new1", "output_plist", "new2", "dataType", "dataType2", "type", "range", "range2", "moduleDef", "statements", "new3",
    "statement", "ioStmt", "var", "var2", "whichID", "simpleStmt", "assignmentStmt", "whichStmt", "lvalueIDstmt", "lvalueArrStmt", 
    "Index", "moduleReuseStmt", "optional", "idList", "newX", "expression", "new4", "AorBExpr", "arithmeticExpr", "new6",
    "term", "new7", "factor", "PlusMinus", "MulDiv", "relationalOP", "logicalOP", "boolKey", "boolExpr", "new8", "relationalExpr",
    "declareStmt", "iterativeStmt", "conditionalStatement", "caseStmt", "numericCases", 
    "numericCase", "new11", "Default", "NT_value"};

int hash_symbol_table(char* key, int slots) {
    int result = 0;
    int i;

    for(i=0; i<strlen(key); i++)
        result = (result + key[i]) % slots;

    return result % slots;
}

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

    if(label != INPUT_PLIST && label != OUTPUT_PLIST) {

        if(parent==NULL) {
            
        }

        else if(parent->child == NULL) {
            parent->child = node;
        }
        else {
            // printf("%s %s\n", ast_string_map_copy[parent->label], name);
            Symbol_Table_Tree temp = parent->child;

            while(temp->sibling) {
                // printf("%s %s\n", ast_string_map_copy[parent->label], temp->sibling->name);
                temp = temp->sibling;
            }

            temp->sibling = node;
        }
    }
    
    return node;
}

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

Symbol_Table_Tree create_symbol_table_tree(AST root, ErrorList* err) {
    
    Symbol_Table_Tree tree = make_symbol_table_tree_node(NULL, AST_PROGRAM, "main", 0, 0, 0, -1);
    traverse_ast(root, tree, err);
    printf("\n**\nAST traversed\n**\n");

    print_symbol_tables(tree);

    return tree;
}

void print_symbol_tables(Symbol_Table_Tree tree) {
    if(tree==NULL)
        return;
    printf("\nIn scope:\n");
    printf("Label: %s\n", ast_string_map_copy[tree->label]);
    printf("Name: %s\n", tree->name);
    printf("Scope start: %d\n", tree->start);
    printf("Scope end: %d\n", tree->end);
    printf("Nested level: %d\n\n", tree->level);
    // if(tree->parent)
    //     printf("Parent: %s\n\n", tree->parent->name);
    if(tree->is_function && tree->is_defined) {
        printf("In input_plist:\n");
        printf("Scope start: %d\n", tree->input->start);
        printf("Scope end: %d\n", tree->input->end);
        printf("Nested level: %d\n", tree->input->level);
        print_slots(tree->input->table);
        printf("In output_plist:\n");
        printf("Scope start: %d\n", tree->output->start);
        printf("Scope end: %d\n", tree->output->end);
        printf("Nested level: %d\n", tree->output->level);
        print_slots(tree->output->table);
        printf("In function:\n");
    }
    if(tree->table != NULL)
        print_slots(tree->table);
    
    // print_symbol_tables(tree->child);

    Symbol_Table_Tree temp = tree->child;
    while(temp) {
        print_symbol_tables(temp);
        temp = temp->sibling;
    }    
}

void print_slots(Symbol_Table* table) {
    int slots = table->number_of_slots;
    int i;
    for(i=0; i<slots; i++) {
        printf("In slot %d\n", i);
        print_symbols(table->slots[i]);
    }
    printf("\n");
}

void print_symbols(Slots_List* list) {
    if(list->head==NULL)
        return;
    int count = list->count;
    Symbol_List* temp = list->head;
    while(count) {
        Symbol_Node* symbol = temp->symbol;
        printf("Name of variable: %s ", symbol->node->leaf_token->lexeme);
        printf("Datatype: %d, Offset: %d, Width: %d\t", symbol->datatype, symbol->offset, symbol->width);
        if(symbol->datatype == 3) {
            if(symbol->range[0].tag == 0 && symbol->range[1].tag == 0)
                printf("Array range: %d..%d", symbol->range[0].range_pointer.value, symbol->range[1].range_pointer.value);
            else if(symbol->range[0].tag == 0 && symbol->range[1].tag == 1)
                printf("Array range: %d..%s", symbol->range[0].range_pointer.value, symbol->range[1].range_pointer.id->node->leaf_token->lexeme);
            else if(symbol->range[0].tag == 1 && symbol->range[1].tag == 0)
                printf("Array range: %s..%d", symbol->range[0].range_pointer.id->node->leaf_token->lexeme, symbol->range[1].range_pointer.value);
            else if(symbol->range[0].tag == 1 && symbol->range[1].tag == 1)
                printf("Array range: %s..%s", symbol->range[0].range_pointer.id->node->leaf_token->lexeme, symbol->range[1].range_pointer.id->node->leaf_token->lexeme);
        }
        count--;
        temp = temp->next;
        printf("\n");
    }
}

Symbol_Node* make_symbol_node(AST node, int datatype, int assigned, int width, int offset, int usage, Range* range, int array_datatype) {
    Symbol_Node* symbol_node = (Symbol_Node*) malloc(sizeof(Symbol_Node));
    symbol_node->node = node;
    symbol_node->datatype = datatype;
    symbol_node->usage = usage;
    symbol_node->assigned = assigned;
    symbol_node->offset = offset;
    symbol_node->width = width;
    // range = (Range*) malloc(sizeof(Range)*2);
    if(range != NULL) {
        symbol_node->range[0] = range[0];
        symbol_node->range[1] = range[1];
    }
    symbol_node->array_datatype = array_datatype;
    // printf("symbol node made\n");
    return symbol_node;
}

Symbol_Table_Tree get_parent_scope(Symbol_Table_Tree current) {
    
    Symbol_Table_Tree parent_module = current;

    while(parent_module->parent && parent_module->parent->parent != NULL) {
        parent_module = parent_module->parent;
    }

    return parent_module;
}

void traverse_ast(AST node, Symbol_Table_Tree current,ErrorList* err) {
    if(!node)
        return;

    // if(node->tag == 1) {
    //     printf("%s\n", ast_string_map_copy[node->label]);
    // }
    // else {
    //     printf("%s\n", node->leaf_token->lexeme);
    // }

    // Width: 2 for INT, 8: REAL, 1: BOOLEAN, 8: ARRAY OFFSET
    int data_width[4] = {2, 8, 1, 8};

    // Module call's current scope doesn't have to be changed
    if(!(node->tag == 0 && node->rule_num == 59)) {
        node->current_scope = current;
    }
    // printf("%d\n", node->rule_num);
    
    Symbol_Table_Tree new = current;

    // Symbol_Table_Tree parent_module = current;

    // while(parent_module->parent && parent_module->parent->parent != NULL) {
    //     parent_module = parent_module->parent;
    // }

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
        
        if(defined) {
            //printf("Line %d - %s Module already defined\n", node->child->leaf_token->line_no, name);
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: MODULE: ");
            strcat(str, name);
            strcat(str, " CANNOT BE OVERLOADED");
            add_sem_error(err,str,node->child->leaf_token->line_no);
            // exit(-1);
            return;
        }

        else if(declared && (!called) && (!defined)) {
            // Symbol_Table_Tree temp = current->child;
            // while(temp) {
            //     if((strcmp(temp->name, name)==0)) {
            //         temp->is_redundant=1;
            //         break;
            //     }
            //     temp = temp->sibling;
            // }
            //printf("Line %d - Redundant declaration found for module %s\n", node->child->leaf_token->line_no, name);
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: MODULE: ");
            strcat(str, name);
            strcat(str, " DEFINITON AND DECLARATION BOTH APPEAR BEFORE ITS CALL");
            add_sem_error(err,str,node->child->leaf_token->line_no);
            return;
            // Symbol_Table_Tree temp = current->child;

            // while(temp) {
            //     if(strcmp(name, temp->name) == 0) {
            //         new = temp;
            //         new->is_defined = 1;
            //         break;
            //     }
            //     temp = temp->sibling;
            // }
        }

        else if( !declared && !defined) {
            new = make_symbol_table_tree_node(current, AST_MODULE, name, 1, start, end, 1);
            new->input = make_symbol_table_tree_node(current, INPUT_PLIST, name, 0, start, end, 0);
            new->output = make_symbol_table_tree_node(current, OUTPUT_PLIST, name, 0, start, end, 0);
            new->is_defined = 1;
            // new->is_declared = 1;
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
        
        
        if(defined) {
            // error
            //printf("DRIVER Module is already defined\n");
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: DRIVER MODULE ALREADY DEFINED");
            add_sem_error(err,str,-1);
            // exit(-1);
            return;
        }
        else {
            new = make_symbol_table_tree_node(current, AST_DRIVER, "AST_DRIVER", 0, start, end, 1);
            new->is_defined = 1;
            new->is_declared = 1;
        }
    }

    // Top-level module declarations
    if(node->tag == 0 && node->rule_num == 4) {
        char* name = node->leaf_token->lexeme;
        int declared = check_if_declared(current, name);

        if(declared) {
            // error
            //printf("Line %d - %s Module is already declared\n", node->leaf_token->line_no, name);
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: MODULE: ");
            strcat(str, name);
            strcat(str, " IS RE-DECLARED");
            add_sem_error(err,str,node->leaf_token->line_no);
            // exit(-1);
        }

        else {
            new = make_symbol_table_tree_node(current, MODULE_DECLARATION, name, 1, 0, 0, 0);
            new->input = make_symbol_table_tree_node(current, INPUT_PLIST, name, 0, 0, 0, 0);
            new->output = make_symbol_table_tree_node(current, OUTPUT_PLIST, name, 0, 0, 0, 0);
            new->is_declared = 1;
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
        
        if(!declared) {
            //printf("Line %d - %s Incorrect Function Call, Module not found\n", temp_node->leaf_token->line_no, name);
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: INCORRECT FUNCTION CALL, MODULE: ");
            strcat(str, name);
            strcat(str, " NOT FOUND");

            add_sem_error(err,str,temp_node->leaf_token->line_no);
            temp_node->current_scope = NULL;
            //printf("%s\n", str);
            // exit(-1);
        }
        else {
            // Storing function's symbol table in its call (in id)
            temp_node->current_scope = temp;
            temp->is_called = 1;
        }
    }

    // New for loop
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
    
    // New while loop
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
        int flag = 0;

        while(temp) {
            flag = 0;
            type = temp->child->next->leaf_token;
            int offset = 0, width = 0;

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
                
                if(search_current_scope(temp->child->leaf_token->lexeme, current->input)==NULL) {
                    symbol_node = make_symbol_node(temp->child, datatype, 0, width, offset, 1, NULL, -1);
                    flag = 1;
                }
                else {
                    //printf("Line: %d - Variable %s already declared\n", temp->child->leaf_token->line_no, temp->child->leaf_token->lexeme);
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"ERROR: VARIABLE: ");
                    strcat(str, temp->child->leaf_token->lexeme);
                    strcat(str, " IS RE-DECLARED");
                    add_sem_error(err,str,temp->child->leaf_token->line_no);
                    flag = 0;
                }
            }
            else {
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

                range[0].tag = 0;
                range[0].range_pointer.value = range1->leaf_token->val.num;

                range[1].tag = 0;
                range[1].range_pointer.value = range2->leaf_token->val.num;

                int val1 = range[0].range_pointer.value, val2 = range[1].range_pointer.value, width = 0, offset = 0;

                if(val1 > 0 && val2 > val1) {
                    width = data_width[array_datatype] * (val2 - val1 + 1);
                    offset = parent_module->last_offset;
                    flag = 1;
                }
                else {
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"ERROR: ARRAY: ");
                    strcat(str, temp->child->leaf_token->lexeme);
                    strcat(str, " SHOULD HAVE POSITIVE BOUNDS WITH LOWER LIMIT LESS THAN UPPER LIMIT");
                    add_sem_error(err,str,temp->child->leaf_token->line_no);
                    flag = 0;
                }

                if(search_current_scope(temp->child->leaf_token->lexeme, current->input)==NULL) {
                    symbol_node = make_symbol_node(temp->child, datatype, 0, width, offset, 1, range, array_datatype);
                    flag = 1;
                }
                else{
                    //printf("Line: %d - Variable %s already declared\n", temp->child->leaf_token->line_no, temp->child->leaf_token->lexeme);
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"ERROR: VARIABLE: ");
                    strcat(str, temp->child->leaf_token->lexeme);
                    strcat(str, " IS RE-DECLARED");
                    add_sem_error(err,str,temp->child->leaf_token->line_no);
                    flag = 0;
                }
            }
            if(flag) {
                symbol_node->param_order = param_order;
                param_order++;
                insert_symbol(current->input->table, temp->child->leaf_token->lexeme, symbol_node);
                parent_module->last_offset += width;
            }
            temp = temp->child->next->next;
        }
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

            if(search_current_scope(temp->child->leaf_token->lexeme, current->output)==NULL) {
                symbol_node = make_symbol_node(temp->child, datatype, 0, width, offset, 1, NULL, -1);
                symbol_node->param_order = param_order;
                param_order++;
                insert_symbol(current->output->table, temp->child->leaf_token->lexeme, symbol_node);
                parent_module->last_offset += width;
            }
            else{
                //printf("Line: %d - Variable %s already declared\n", temp->child->leaf_token->line_no, temp->child->leaf_token->lexeme);
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"ERROR: VARIABLE: ");
                strcat(str, temp->child->leaf_token->lexeme);
                strcat(str, " IS RE-DECLARED");
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
            // printf("Hi\n");

            int offset = parent_module->last_offset;
            int width = data_width[datatype];
            // printf("%s %s\n", temp->child->child->leaf_token->lexeme, current->name);

            if(search_current_scope(temp->child->child->leaf_token->lexeme, current)==NULL) {
                symbol_node = make_symbol_node(temp->child->child, datatype, 0, width, offset, 1, NULL, -1);
                insert_symbol(current->table, temp->child->child->leaf_token->lexeme, symbol_node);
                parent_module->last_offset += width;
            }
            else{
                //printf("Line: %d - Variable %s already declared\n", temp->child->child->leaf_token->line_no, temp->child->child->leaf_token->lexeme);
                char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                strcpy(str,"ERROR: VARIABLE: ");
                strcat(str, temp->child->child->leaf_token->lexeme);
                strcat(str, " IS RE-DECLARED");
                add_sem_error(err,str,temp->child->child->leaf_token->line_no);
            }

            temp = temp->child->child->next;
            while(temp) {
                if(search_current_scope(temp->child->leaf_token->lexeme, current)==NULL) {
                    offset = parent_module->last_offset;
                    symbol_node = make_symbol_node(temp->child, datatype, 0, width, offset, 1, NULL, -1);
                    insert_symbol(current->table, temp->child->leaf_token->lexeme, symbol_node);
                    parent_module->last_offset += width;
                }
                else{
                    //printf("Line: %d - Variable %s already declared\n", temp->child->leaf_token->line_no, temp->child->leaf_token->lexeme);
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"ERROR: VARIABLE: ");
                    strcat(str, temp->child->leaf_token->lexeme);
                    strcat(str, " IS RE-DECLARED");
                    add_sem_error(err,str,temp->child->leaf_token->line_no);
                }
                temp = temp->child->next;
            }
            
        }
        else {
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

            if(range1->leaf_token->token == NUM) {
                range[0].tag = 0;
                range[0].range_pointer.value = range1->leaf_token->val.num;
                if(range1->leaf_token->val.num <= 0) {
                    //printf("Line: %d - Variable used as array index has to be positive: %d\n", range1->leaf_token->line_no, range1->leaf_token->val.num);
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"ERROR: NUMBER USED AS ARRAY INDEX HAS TO BE POSITIVE");
                    add_sem_error(err,str,range1->leaf_token->line_no);
                    flag = 0;
                }
            }
            else {
                // printf("Hi\n");
                Symbol_Node* temp1 = search_symbol_table(range1->leaf_token->lexeme, current);
                if(temp1 != NULL) {
                    if(temp1->datatype == 0) {
                        range[0].tag = 1;
                        range[0].range_pointer.id = temp1;
                    }
                    else {
                        flag = 0;
                        //printf("Line: %d - Variable used as array index: %s, has to have integer datatype\n", temp->child->child->leaf_token->line_no, temp1->node->leaf_token->lexeme);
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"ERROR: VARABLE: ");
                        strcat(str, range1->leaf_token->lexeme);
                        strcat(str, " USED AS ARRAY INDEX HAS TO BE INTEGER");
                        add_sem_error(err,str,temp->child->child->leaf_token->line_no);
                    }
                }
                else {
                   // printf("Line: %d - Variable used as array index: %s is not declared\n", range1->leaf_token->line_no, range1->leaf_token->lexeme);
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"ERROR: VARIABLE: ");
                    strcat(str, range1->leaf_token->lexeme);
                    strcat(str, " USED AS ARRAY INDEX NOT DECLARED");
                    add_sem_error(err,str,range1->leaf_token->line_no);
                    flag = 0;
                }
            }

            if(range2->leaf_token->token == NUM) {
                range[1].tag = 0;
                range[1].range_pointer.value = range2->leaf_token->val.num;
                if(range2->leaf_token->val.num <= 0) {
                    //printf("Line: %d - Variable used as array index has to be positive: %d\n", range2->leaf_token->line_no, range2->leaf_token->val.num);
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"ERROR: NUMBER USED AS ARRAY INDEX HAS TO BE POSITIVE");
                    add_sem_error(err,str,range2->leaf_token->line_no);
                    flag = 0;
                }
                if(range[0].tag == 0 && range[0].range_pointer.value >= range[1].range_pointer.value) {
                    //printf("Line: %d - Lower array limit greater than upper array limit\n", range2->leaf_token->line_no);
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"ERROR: LOWER ARRAY LIMIT GREATER THAN UPPER ARRAY LIMIT");
                    add_sem_error(err,str,range2->leaf_token->line_no);
                    flag = 0;
                }
            }
            else {
                Symbol_Node* temp1 = search_symbol_table(range2->leaf_token->lexeme, current);
                if(temp1 != NULL) {
                    if(temp1->datatype == 0) {
                        range[1].tag = 1;
                        range[1].range_pointer.id = temp1;
                    }
                    else {
                        flag = 0;
                        //printf("Line: %d - Variable used as array index: %s, has to have integer datatype\n", temp->child->child->leaf_token->line_no, temp1->node->leaf_token->lexeme);
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"ERROR: VARABLE: ");
                        strcat(str, range2->leaf_token->lexeme);
                        strcat(str, " USED AS ARRAY INDEX HAS TO BE INTEGER");
                        add_sem_error(err,str,temp->child->child->leaf_token->line_no);
                    }
                }
                else {
                    //printf("Line: %d - Variable used as array index: %s is not declared\n", range2->leaf_token->line_no, range2->leaf_token->lexeme);
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"ERROR: VARIABLE: ");
                    strcat(str, range2->leaf_token->lexeme);
                    strcat(str, " USED AS ARRAY INDEX NOT DECLARED");
                    add_sem_error(err,str,range2->leaf_token->line_no);
                    flag = 0;
                }
            }

            if(flag) {

                int width = 2, offset = parent_module->last_offset;
                int val1 = range[0].range_pointer.value, val2 = range[1].range_pointer.value;

                if(range[0].tag == 0 && range[1].tag == 0) {

                    if(val1 > 0 && val2 > val1) {
                        width = data_width[array_datatype] * (val2 - val1 + 1);
                        offset = parent_module->last_offset;
                    }
                }

                if(search_current_scope(temp->child->child->leaf_token->lexeme, current)==NULL) {
                    symbol_node = make_symbol_node(temp->child->child, datatype, 0, width, offset, 1, range, array_datatype);
                    insert_symbol(current->table, temp->child->child->leaf_token->lexeme, symbol_node);
                    parent_module->last_offset += width;
                }
                else {
                    //printf("Line: %d - Variable %s already declared\n", temp->child->child->leaf_token->line_no, temp->child->child->leaf_token->lexeme);
                    char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                    strcpy(str,"ERROR: VARIABLE: ");
                    strcat(str, temp->child->child->leaf_token->lexeme);
                    strcat(str, " IS RE-DECLARED");
                    add_sem_error(err,str,temp->child->child->leaf_token->line_no);
                }

                temp = temp->child->child->next;
                while(temp) {
                    if(search_current_scope(temp->child->leaf_token->lexeme, current)==NULL) {
                        offset = parent_module->last_offset;
                        symbol_node = make_symbol_node(temp->child, datatype, 0, width, offset, 1, range, array_datatype);
                        insert_symbol(current->table, temp->child->leaf_token->lexeme, symbol_node);
                        parent_module->last_offset += width;
                    }
                    else {
                        //printf("Line: %d - Variable %s already declared\n", temp->child->leaf_token->line_no, temp->child->leaf_token->lexeme);
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"ERROR: VARIABLE: ");
                        strcat(str, temp->child->leaf_token->lexeme);
                        strcat(str, " IS RE-DECLARED");
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

        if(!temp) {
            //printf("Line: %d - Variable %s not declared\n", node->leaf_token->line_no, name);
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: VARIABLE: ");
            strcat(str, name);
            strcat(str, " NOT DECLARED");
            add_sem_error(err,str,node->leaf_token->line_no);
        }

        node->symbol_table_node = temp;

    }

    if((node->rule_num == 52 || node->rule_num == 42 || node->rule_num == 58 || node->rule_num == 69
    || node->rule_num == 103 || node->rule_num == 101) && node->tag == 0) {
        char* name = node->leaf_token->lexeme;

        Symbol_Node* temp = search_symbol_table(name, current);

        if(!temp) {
            // printf("Line: %d - Variable %s not declared\n", node->leaf_token->line_no, name);
            char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: VARIABLE: ");
            strcat(str, name);
            strcat(str, " NOT DECLARED");
            add_sem_error(err,str,node->leaf_token->line_no);
        }

        node->symbol_table_node = temp;
    }

    if(node->rule_num == 59 && node->tag == 1) {
        AST temp = node->child;
        
        while(temp) {
            AST temp2 = temp;
            if(temp->tag == 1) {
                
                while((temp2->rule_num == 62 || temp2->rule_num == 63) && (temp2->tag == 1)) {
                    char* name = temp2->child->leaf_token->lexeme;
                    
                    temp2->child->symbol_table_node = search_symbol_table(name, current);

                    if(temp2->child->symbol_table_node == NULL) {
                        //printf("Line: %d - Variable %s not declared\n", temp2->child->leaf_token->line_no, name);
                        char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
                        strcpy(str,"ERROR: VARIABLE: ");
                        strcat(str, name);
                        strcat(str, " NOT DECLARED");
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
        traverse_ast(temp, new, err);
        temp = temp->next;
    }    

}
