// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#ifndef LEXER_DEF
#define LEXER_DEF

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_NUMBERS 60
#define MAX_TOKEN_SIZE 30
#define INITIAL_TOKENS_IN_INPUT 30

/* The enums of all tokens are stored here.
   This makes for easy indexing and comparing, since instead comparing a string, we can just compare an enum, which is faster.
   Indexing is simplified since enums can be directly used in place of integer indices. Eg- token_string_map[INTEGER] = "INTEGER"
*/
typedef enum {
            INTEGER, REAL, BOOLEAN, OF, ARRAY, START, END, DECLARE, MODULE, DRIVER, PROGRAM, GET_VALUE,
            PRINT, USE, WITH, PARAMETERS, TRUE, FALSE, TAKES, INPUT, RETURNS, AND, OR, FOR, IN, SWITCH, 
            CASE, BREAK, DEFAULT, WHILE, PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DEF, DRIVERDEF,
            ENDDEF, DRIVERENDDEF, COLON, RANGEOP, SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, COMMENTMARK, NUM, RNUM, ID, ERROR, E, $
} tokens;

/* Union to store either a NUM or an RNUM in case of a number
*/
union value {
    int num;
    float rnum;
};

typedef union value Value;

/* Main definition of the structure for a token read from the source code. It consists of a token as an enum, a lexeme to store the value of the token.
   In case of a number, it stores it as a Value defined from the above union. A tag identifies if a token is a NUM, RNUM or other. Line number also
   included in this structure.
*/
struct node {
    // char token[MAX_TOKEN_SIZE];
    tokens token;
    char lexeme[MAX_TOKEN_SIZE];
    unsigned int line_no;
    Value val;
    int tag; // {0, 1, 2} 0 - other, 1 - int, 2 - float
};

typedef struct node Node;


#endif