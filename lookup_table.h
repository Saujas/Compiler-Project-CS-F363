// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lexer_def.h"

//Slot size defined as 41, a prime number, which is good for hashing
#define SLOT_SIZE 41
#define KEYWORD_NUMBERS 30

//Each entry in the lookup_table is a structure containing a token, its lexeme, and a pointer to the next entry
struct entry {
    tokens token;
    char lexeme[MAX_TOKEN_SIZE];
    struct entry* next;
};

typedef struct entry Entry;

typedef Entry* List;

//The entire lookup table is an array of multiple slots, with count in no_of_slots
struct lookup {
    List *slots;
    int no_of_slots;
};

typedef struct lookup lookup_table;

/* Function definitions for all functions used in lookup_table. Detailed descriptions in lookup_table.c
*/
lookup_table initialize_lookup_table(int no_of_slots);
int hash(char* str, int no_of_slots);
List search(char* id, lookup_table table);
int add_item(tokens token_name, char* lexeme, lookup_table table);
int populate_table(lookup_table table);
int print_table(lookup_table table);