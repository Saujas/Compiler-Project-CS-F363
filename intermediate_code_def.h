// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#ifndef _INTERMEDIATE_CODE_
#define _INTERMEDIATE_CODE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table_def.h"
#include "ast_def.h"
#include "semantic_analyzer_def.h"
#include "lexer_def.h"
#include "parser_def.h"

#define OPERATOR_SIZE 31

// List of enums for each operator used for intermediate code
typedef enum {
    COPY, ADDITION, SUBTRACTION, MULTIPLY, DIVIDE, MEM_READ, MEM_WRITE, GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL, EQUAL, NOT_EQUAL, BOOLEAN_AND, BOOLEAN_OR, LABEL, IF_TRUE, IF_FALSE, GOTO,
    READ, WRITE, EXIT, RETURN, PARAM_OP, PARAM, CALL, FUN_LABEL, MEM_ALLOC, ADD_DYNAMIC, WRITE_2,
    LINE_BREAK
} oper;

// Structure of a tuple used per operator in intermediate code
typedef struct tup {
    
    oper op;
    char* arg1;
    char* arg2;
    char* result;

    struct tup* next;

    Symbol_Node* node1, *node2, *node3;
} tuple;

// List of tuples
typedef struct {
    struct tup* head;
    struct tup* tail;

    int count;
} tuple_list;

typedef struct tup* Tuple;

// Structure for temporaries used in intermediate code
typedef struct {
    Symbol_Node* symbol;
    char* name;
} temporary;

typedef temporary* Temporary;

#endif