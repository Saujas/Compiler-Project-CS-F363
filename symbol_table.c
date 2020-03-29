#include "symbol_table.h"


int hash(char* key, int slots) {
    int result = 0;
    int i;

    for(i=0; i<strlen(key); i++)
        result = (result + key[i]) % slots;

    return result % slots;
}


void insert_symbol(Symbol_Table* symbol_table, char* key, Symbol_Node* node) {
    int hash_value = hash(key, symbol_table->slots);
    Symbol_List* new = (Symbol_List*) malloc(sizeof(Symbol_List));
    new->symbol = node;
    new->next = symbol_table->slots[hash_value]->head;
    symbol_table->slots[hash_value]->head = new;
    symbol_table->slots[hash_value]->count += 1;
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

Symbol_Table_Tree make_symbol_table_tree_node(Symbol_Table_Tree parent, Label label, char* name) {
    Symbol_Table_Tree node = (Symbol_Table_Tree) malloc(sizeof(struct symbol_table_tree_node));
    node->parent = parent;
    node->child = NULL;
    node->sibling = NULL;
    node->label = label;
    node->name = name;
    node->is_declared = 0;
    node->is_defined = 0;
    node->is_called = 0;
    node->table = create_symbol_table(SYMBOL_TABLE_SLOTS);

    if(parent->child == NULL) {
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
        if(strcmp(temp->name, lexeme) && (temp->is_defined == 1)) {
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
    Symbol_Table_Tree tree = make_symbol_table_tree_node(NULL, PROGRAM, "main");

    traverse_ast(root, tree);

    return tree;
}

void traverse_ast(AST node, Symbol_Table_Tree current) {
    if(!node)
        return;

    node->current_scope = current;
    
    Symbol_Table_Tree new = current;

    // Module declarations, not driver module
    if(node->tag == 0 && node->rule_num == 8) {
        char * name = node->leaf_token->lexeme;
        int declared = check_if_declared(current, name);
        int defined = check_if_defined(current, name);
        
        if(defined) {
            //error;
            printf("%s Module already defined\n", name);
            exit(-1);
        }

        else if( !declared && !defined) {
            new = make_symbol_table_tree_node(current, MODULE_DECLARATION, name);
            new->is_defined = 1;
            new->is_declared = 1;
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
            new = make_symbol_table_tree_node(current, AST_DRIVER, "AST_DRIVER");
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
            printf("%s Module is already declared\n", name);
            exit(-1);
        }

        else {
            new = make_symbol_table_tree_node(current, MODULE_DECLARATION, name);
            new->is_declared = 1;
            new->is_defined = 0;
        }
    }

    // Function Call Handling
    if(node->tag == 0 && node->rule_num == 59) {
        char* name = node->leaf_token->lexeme;

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

    
}
