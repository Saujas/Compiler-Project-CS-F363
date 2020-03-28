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


Symbol_Table_Tree make_symbol_table_tree_node(Symbol_Table_Tree* parent, Label label, char* name) {
    Symbol_Table_Tree node = (Symbol_Table_Tree*) malloc(sizeof(Symbol_Table_Tree));
    node->parent = parent;
    node->child = NULL;
    node->sibling = NULL;
    node->label = label;
    node->name = name;
    node->table = create_symbol_table(SYMBOL_TABLE_SLOTS);
    
    return node;
}


Symbol_Table_Tree create_symbol_table_tree(AST* root) {
    Symbol_Table_Tree tree = make_symbol_table_tree_node(NULL, PROGRAM, "main");
}