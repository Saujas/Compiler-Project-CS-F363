#include"lookup_table.h"

lookup_table initialize_lookup_table(int no_of_slots) {
    lookup_table table;
    table.no_of_slots = no_of_slots;

    table.slots = (List* ) malloc(sizeof(List) *  no_of_slots);
    int i;
    for(i = 0; i<no_of_slots; i++) {
        table.slots[i] = NULL;
    }
    
    populate_table(table);

    return table;
}

int hash(char* str, int no_of_slots) {
    int hash = 0;
    int i;

    for(i=0; i<strlen(str); i++)
        hash = (hash + str[i]) % no_of_slots;

    return hash % no_of_slots;
}

List search(char* id, lookup_table table) {
    int h = hash(id, table.no_of_slots);
    List item = table.slots[h];

    while(item != NULL) {
        if( strcmp(item->lexeme, id) == 0) {
            return item;
        }   
        item = item->next;
    }

    return NULL;
}

int add_item(enum tokens token_name, char* lexeme, lookup_table table) {
    int h = hash(lexeme, table.no_of_slots);

    List l = (List) malloc(sizeof(Node));
    l->token = token_name;
    strcpy(l->lexeme, lexeme);
    l->next = NULL;

    List item = table.slots[h];

    if(item == NULL) {
        table.slots[h] = l;
    }
    else {
        while((item->next) != NULL) {
            item = item->next;    
        }

        item->next = l;
    }

    return 1;
}

int populate_table(lookup_table table) {
    int i;
    for(i=0; i<TOKEN_NUMBERS; i++) {
        add_item(keywords[i], patterns[i], table);
    }

    return 1;
}

int print_table(lookup_table table) {
    int i;
    List item;
    for(i=0; i<table.no_of_slots; i++) {
        item = table.slots[i];
        while(item != NULL) {
            printf("Token: %s, Lexeme: %s\n", token_string_map[item->token], item->lexeme);
            item = item->next;
        }
    }

    return 1;
}

// int main() {
//     lookup_table table = initialize_lookup_table(41);
//     print_table(table);
//     return 0;
// }
