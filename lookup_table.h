#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_TOKEN_SIZE 30

struct node {
    char* tokenName[MAX_TOKEN_SIZE];
    char* lexeme[MAX_TOKEN_SIZE];
    struct node* next;
};

typedef struct node Node;

typedef Node* List;

struct lookup {
    List *slots;
    int no_of_slots;
};

typedef struct lookup lookup_table;

