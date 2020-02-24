// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include "lookup_table.h"

// Array of strings for keywords
char * patterns[KEYWORD_NUMBERS] = {"integer","real","boolean","of", "array","start",
                "end","declare","module","driver","program", "get_value",
                "print","use","with","parameters","true", "false","takes","input","returns",
                "AND","OR","for", "in", "switch","case","break","default","while"
};

// Enums correspodning to keywords
tokens keywords[KEYWORD_NUMBERS] = {INTEGER, REAL, BOOLEAN, OF, ARRAY, START, END, DECLARE, MODULE, DRIVER, PROGRAM, GET_VALUE,
            PRINT, USE, WITH, PARAMETERS, TRUE, FALSE, TAKES, INPUT, RETURNS, AND, OR, FOR, IN, SWITCH, 
            CASE, BREAK, DEFAULT, WHILE
};

// Initializing lookup table with predefined number of slots. Lexer calls this function before tokenizing input
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

// Hash value of a string calculated by summing the ASCII values of all its characters modulo SLOT_SIZE,
// which is predefined as 41, since a prime number helps in unique hashing
int hash(char* str, int no_of_slots) {
    int hash = 0;
    int i;

    for(i=0; i<strlen(str); i++)
        hash = (hash + str[i]) % no_of_slots;

    return hash % no_of_slots;
}

// Searching if a particular id is present in the lookup table or not.
// If it is, it is tokenised as a keyword, else an ID
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

// Adding a single keyword to the lookup table. Keywords are hashed according to hash function,
// and then added to the corresponding slot
// Each slot has a linked list of items
int add_item(tokens token_name, char* lexeme, lookup_table table) {
    int h = hash(lexeme, table.no_of_slots);
    List l = (List) malloc(sizeof(Entry));
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

// Populating lookup table with each keyword present in the above enums
int populate_table(lookup_table table) {
    int i;
    for(i=0; i<KEYWORD_NUMBERS; i++) {
        add_item(keywords[i], patterns[i], table);
    }
    // print_table(table);
    return 1;
}

// Printing entire lookup table for debugging
int print_table(lookup_table table) {
    int i;
    List item;
    for(i=0; i<table.no_of_slots; i++) {
        item = table.slots[i];
        while(item != NULL) {
            printf("Token: %d, Lexeme: %s\n", item->token, item->lexeme);
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
