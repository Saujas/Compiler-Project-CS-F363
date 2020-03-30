#include "symbol_table.h"

char* ast_string_map_copy[AST_LABEL_NUMBER] = {
    "AST_PROGRAM", "MODULE_DECLARATIONS", "MODULE_DECLARATION", "OTHER_MODULES", "AST_DRIVER", "AST_MODULE", "INPUT_PLIST", "NEW1",
    "OUTPUT_PLIST", "NEW2", "DATA_TYPE", "DATA_TYPE2", "RANGE", "RANGE2", "STATEMENTS", "VAR", "ASSIGNMENT_STMT", 
    "LVALUE_ARR_STMT", "MODULE_REUSE_STMT", "ID_LIST", "NEWX", "EXPRESSION", "NEW6", "NEW7", "NEW8", "RELATIONAL_EXPR", 
    "DECLARE_STMT", "AST_FOR", "AST_WHILE", "CONDITIONAL_STMT", "CASE_STMT_T", "CASE_STMT_F", "NUMERIC_CASES", "NUMERIC_CASE", "IO_READ", "IO_WRITE"
};

char * ast_non_terminals_string_map_copy[NON_TERMINAL_SIZE] = {"program", "moduleDeclarations", "moduleDeclaration", "otherModules", "driverModule", "module", "ret", "input_plist",
    "new1", "output_plist", "new2", "dataType", "dataType2", "type", "range", "range2", "moduleDef", "statements", "new3",
    "statement", "ioStmt", "var", "var2", "whichID", "simpleStmt", "assignmentStmt", "whichStmt", "lvalueIDstmt", "lvalueArrStmt", 
    "Index", "moduleReuseStmt", "optional", "idList", "newX", "expression", "new4", "AorBExpr", "arithmeticExpr", "new6",
    "term", "new7", "factor", "PlusMinus", "MulDiv", "relationalOP", "logicalOP", "boolKey", "boolExpr", "new8", "relationalExpr",
    "declareStmt", "iterativeStmt", "conditionalStatement", "caseStmt", "numericCases", 
    "numericCase", "new11", "Default"};

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

    while(temp->symbol != NULL) {
        if( strcmp(temp->symbol->node->leaf_token->lexeme, id) == 0) {
            return temp->symbol;
        }   
        temp = temp->next;
    }
    if(table_tree_node->parent) {
        return search_symbol_table(id, table_tree_node->parent);
    }

    return NULL;
}


void insert_symbol(Symbol_Table* symbol_table, char* key, Symbol_Node* node) {
    int hash_value = hash_symbol_table(key, symbol_table->number_of_slots);
    Symbol_List* new = (Symbol_List*) malloc(sizeof(Symbol_List));
    new->symbol = node;
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

Symbol_Table_Tree make_symbol_table_tree_node(Symbol_Table_Tree parent, Label label, char* name, int is_function) {
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
    node->input = NULL;
    node->output = NULL;
    node->table = create_symbol_table(SYMBOL_TABLE_SLOTS);

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

Symbol_Table_Tree create_symbol_table_tree(AST root) {
    Symbol_Table_Tree tree = make_symbol_table_tree_node(NULL, AST_PROGRAM, "main", 0);
    traverse_ast(root, tree);
    printf("AST traversed\n");

    print_symbol_tables(tree);

    return tree;
}

void print_symbol_tables(Symbol_Table_Tree tree) {
    if(tree==NULL)
        return;
    printf("\nIn scope:\n");
    printf("Label: %s\n", ast_string_map_copy[tree->label]);
    printf("Name: %s\n\n", tree->name);
    if(tree->is_function && tree->is_defined) {
        print_slots(tree->input->table);
        print_slots(tree->output->table);
    }
    if(tree->table != NULL)
        print_slots(tree->table);
    print_symbol_tables(tree->child);

    Symbol_Table_Tree temp = tree->sibling;
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
}

void print_symbols(Slots_List* list) {
    if(list->head==NULL)
        return;
    int count = list->count;
    Symbol_List* temp = list->head;
    while(count) {
        Symbol_Node* symbol = temp->symbol;
        printf("Name of variable: %s ", symbol->node->leaf_token->lexeme);
        printf("Datatype: %d\t", symbol->datatype);
        if(symbol->datatype == 3) {
            printf("Array range: %d..%d", symbol->range[0].range_pointer.value, symbol->range[1].range_pointer.value);
        }
        count--;
        temp = temp->next;
        printf("\n");
    }
}

Symbol_Node* make_symbol_node(AST node, int datatype, int assigned, int width, int offset, void* memory, int usage, Range* range, int array_datatype) {
    Symbol_Node* symbol_node = (Symbol_Node*) malloc(sizeof(Symbol_Node));
    symbol_node->node = node;
    symbol_node->datatype = datatype;
    symbol_node->usage = usage;
    symbol_node->assigned = assigned;
    symbol_node->offset = offset;
    symbol_node->width = width;
    symbol_node->memory = memory;
    // range = (Range*) malloc(sizeof(Range)*2);
    if(range != NULL) {
        symbol_node->range[0] = range[0];
        symbol_node->range[1] = range[1];
    }
    symbol_node->array_datatype = array_datatype;
    // printf("symbol node made\n");
    return symbol_node;
}

void traverse_ast(AST node, Symbol_Table_Tree current) {
    if(!node)
        return;

    node->current_scope = current;
    
    Symbol_Table_Tree new = current;

    // Module defintions, not driver module
    if(node->tag == 1 && node->rule_num == 8) {
        char * name = node->child->leaf_token->lexeme;
        int declared = check_if_declared(current, name);
        int defined = check_if_defined(current, name);
        
        if(defined) {
            //error;
            printf("%s Module already defined\n", name);
            exit(-1);
        }

        else if( !declared && !defined) {
            new = make_symbol_table_tree_node(current, MODULE_DECLARATION, name, 1);
            new->input = make_symbol_table_tree_node(current, INPUT_PLIST, name, 0);
            new->output = make_symbol_table_tree_node(current, OUTPUT_PLIST, name, 0);
            new->is_defined = 1;
            // new->is_declared = 1;
        }

        else if (declared) {
            Symbol_Table_Tree temp = current->child;

            while(temp) {
                if(strcmp(name, temp->name) == 0) {
                    new = temp;
                    new->is_defined = 1;
                    break;
                }
                temp = temp->sibling;
            }
        }
    }

    // Driver Module definition
    if(node->rule_num == 7) {
        char * name = "AST_DRIVER";
        int defined = check_if_defined(current, name);
        
        if(defined) {
            // error
            printf("DRIVER Module is already defined\n");
            exit(-1);
        }
        else {
            new = make_symbol_table_tree_node(current, AST_DRIVER, "AST_DRIVER", 0);
            new->is_defined = 1;
            new->is_declared = 1;
        }
    }

    // Top-level module declarations
    if(node->tag == 1 && node->rule_num == 4) {
        char* name = node->child->leaf_token->lexeme;
        int declared = check_if_declared(current, name);

        if(declared) {
            // error
            printf("%s Module is already declared\n", name);
            exit(-1);
        }

        else {
            new = make_symbol_table_tree_node(current, MODULE_DECLARATION, name, 1);
            new->input = make_symbol_table_tree_node(current, INPUT_PLIST, name, 0);
            new->output = make_symbol_table_tree_node(current, OUTPUT_PLIST, name, 0);
            new->is_declared = 1;
            new->is_defined = 0;
        }
    }

    // Function Call Handling
    if(node->tag == 1 && node->rule_num == 59) {
        char* name = node->child->leaf_token->lexeme;

        Symbol_Table_Tree temp = current;

        while(temp->parent != NULL) {
            temp = temp->parent;
        }

        temp = temp->child;
        
        int declared = 0; 
        while(temp) {
            if( !strcmp(name, temp->name) && (temp->label == MODULE_DECLARATION)) {
                declared = 1;
                break;
            }
            temp = temp->sibling;
        }

        if(!declared) {
            printf("%s Incorrect Function Call, Module not found\n", name);
            exit(-1);
        }
        else {
            temp->is_called = 1;
        }
    }

    // New for loop
    if(node->rule_num == 101 && node->tag == 1) {
        new = make_symbol_table_tree_node(current, AST_FOR, "FOR", 0);
        new->is_declared = -1;
        new->is_defined = -1;
    }
    
    // New while loop
    if(node->rule_num == 102 && node->tag == 1) {
        new = make_symbol_table_tree_node(current, AST_WHILE, "WHILE", 0);
        new->is_declared = -2;
        new->is_defined = -2;
    }
    
    if(node->rule_num == 11 && node->tag == 1) {
        int datatype;
        int array_datatype;
        Node* type = NULL;
        AST temp = node;
        Symbol_Node* symbol_node;
        while(temp) {
            type = temp->child->next->leaf_token;
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
                symbol_node = make_symbol_node(temp->child, datatype, 0, 0, 0, NULL, 1, NULL, -1);
            }
            else {
                datatype = 3;
                if(strcmp(temp->child->next->child->next->leaf_token->lexeme, "integer")==0) {
                    array_datatype = 0;
                }
                else {
                    array_datatype = 1;
                }
                AST range1 = temp->child->next->child->child;
                AST range2 = range1->next;
                Range range[2];

                range[0].tag = 0;
                range[0].range_pointer.value = range2->leaf_token->val.num;

                range[1].tag = 0;
                range[1].range_pointer.value = range2->leaf_token->val.num;

                symbol_node = make_symbol_node(temp->child, datatype, 0, 0, 0, NULL, 1, range, array_datatype);
            }
            insert_symbol(current->input->table, temp->child->leaf_token->lexeme, symbol_node);
            printf("%d\n", node->rule_num);
            temp = node->child->next->next;
        }
    }

    if(node->rule_num == 14 && node->tag == 1) {
        int datatype;
        Node* type = NULL;
        AST temp = node;
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
            symbol_node = make_symbol_node(temp->child, datatype, 0, 0, 0, NULL, 1, NULL, -1);
            insert_symbol(current->output->table, temp->child->leaf_token->lexeme, symbol_node);
            temp = node->child->next->next;
        }
    }

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
            symbol_node = make_symbol_node(temp->child->child, datatype, 0, 0, 0, NULL, 1, NULL, -1);
            insert_symbol(current->table, temp->child->child->leaf_token->lexeme, symbol_node);
            temp = temp->child->child->next;
            while(temp) {
                symbol_node = make_symbol_node(temp->child, datatype, 0, 0, 0, NULL, 1, NULL, -1);
                insert_symbol(current->table, temp->child->leaf_token->lexeme, symbol_node);
                temp = temp->child->next;
            }
            
        }
        else {
            datatype = 3;
        
            if(strcmp(temp->child->next->child->next->leaf_token->lexeme, "integer")==0) {
                array_datatype = 0;
            }
            else {
                array_datatype = 1;
            }
            AST range1 = temp->child->next->child->child;
            AST range2 = range1->next;
            Range range[2];

            range[0].tag = 0;
            range[0].range_pointer.value = range1->leaf_token->val.num;

            range[1].tag = 0;
            range[1].range_pointer.value = range2->leaf_token->val.num;

            symbol_node = make_symbol_node(temp->child->child, datatype, 0, 0, 0, NULL, 1, range, array_datatype);
            insert_symbol(current->table, temp->child->child->leaf_token->lexeme, symbol_node);
            temp = temp->child->child->next;
            while(temp) {
                symbol_node = make_symbol_node(temp->child, datatype, 0, 0, 0, NULL, 1, range, array_datatype);
                insert_symbol(current->table, temp->child->leaf_token->lexeme, symbol_node);
                temp = temp->child->next;
            }
        }
    }
    printf("%d\n", node->rule_num);
    traverse_ast(node->child, new);
    AST temp = node->next;
    while(temp) {
        traverse_ast(temp, current);
        temp = temp->next;
    }

}
