#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_TOKEN_SIZE 30
#define TOKEN_NUMBERS 30


char * patterns[TOKEN_NUMBERS] = {"integer","real","boolean","of", "array","start",
                "end","declare","module","driver","program", "get_value",
                "print","use","with","parameters","true", "false","takes","input","returns",
                "AND","OR","for", "in", "switch","case","break","default","while"};

char * tokens[TOKEN_NUMBERS] = {"INTEGER","REAL","BOOLEAN","OF","ARRAY","START",
                        "END","DECLARE","MODULE","DRIVER","PROGRAM","GET_VALUE", "PRINT",
                        "USE","WITH","PARAMETERS","TRUE","FALSE","TAKES","INPUT","RETURNS",
                        "AND","OR","FOR","IN", "SWITCH", "CASE","BREAK","DEFAULT","WHILE"};

struct node {
    char token_name[MAX_TOKEN_SIZE];
    char lexeme[MAX_TOKEN_SIZE];
    struct node* next;
};

typedef struct node Node;

typedef Node* List;

struct lookup {
    List *slots;
    int no_of_slots;
};

typedef struct lookup lookup_table;

lookup_table initialize_lookup_table(int no_of_slots);
int hash(char* str, int no_of_slots);
List search(char* id, lookup_table table);
int add_item(char* token_name, char* lexeme, lookup_table table);
int populate_table(lookup_table table);