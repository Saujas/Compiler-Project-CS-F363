// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lexer_def.h"

#define SLOT_SIZE 41
#define KEYWORD_NUMBERS 30

struct entry {
    tokens token;
    char lexeme[MAX_TOKEN_SIZE];
    struct entry* next;
};

typedef struct entry Entry;

typedef Entry* List;

struct lookup {
    List *slots;
    int no_of_slots;
};

typedef struct lookup lookup_table;

lookup_table initialize_lookup_table(int no_of_slots);
int hash(char* str, int no_of_slots);
List search(char* id, lookup_table table);
int add_item(tokens token_name, char* lexeme, lookup_table table);
int populate_table(lookup_table table);
int print_table(lookup_table table);