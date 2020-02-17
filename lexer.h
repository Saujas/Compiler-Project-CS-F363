
#include <float.h>
#include "lexer_def.h"
#include "lookup_table.h"

union value {
    int num;
    float rnum;
};

typedef union value Value;

struct node {
    // char token[MAX_TOKEN_SIZE];
    tokens token;
    char lexeme[MAX_TOKEN_SIZE];
    unsigned int line_no;
    Value val;
    int tag; // {0, 1, 2} 0 - other, 1 - int, 2 - float
};

typedef struct node Node;

FILE* open_file(char* filename);
int string_flush(char *str);
int buffer_read(FILE* fp);
Node* create_node();
Node* get_token(FILE* fp, lookup_table table);
int lexical_analyzer(char* filename);
