#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_NUMBERS 30
#define MAX_TOKEN_SIZE 30

char * patterns[TOKEN_NUMBERS] = {"integer","real","boolean","of", "array","start",
                "end","declare","module","driver","program", "get_value",
                "print","use","with","parameters","true", "false","takes","input","returns",
                "AND","OR","for", "in", "switch","case","break","default","while"};

char * tokens[TOKEN_NUMBERS] = {"INTEGER","REAL","BOOLEAN","OF","ARRAY","START",
                        "END","DECLARE","MODULE","DRIVER","PROGRAM","GET_VALUE", "PRINT",
                        "USE","WITH","PARAMETERS","TRUE","FALSE","TAKES","INPUT","RETURNS",
                        "AND","OR","FOR","IN", "SWITCH", "CASE","BREAK","DEFAULT","WHILE"};


struct node {
    char token[MAX_TOKEN_SIZE];
    char lexeme[MAX_TOKEN_SIZE];
    unsigned int line_no;
};

typedef struct node Node;

int remove_comments(char* buf_head);
int flushBuffer(char* buf_head);
FILE* open_file(char* filename);
int string_flush();
int buffer_read(FILE* fp);
Node get_token(char* fp);
int lexical_analyzer(char* filename);
