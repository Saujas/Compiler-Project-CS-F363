
#include <float.h>
#include "lexer_def.h"

union value {
    int num;
    float rnum;
};

typedef union value Value;

struct node {
    // char token[MAX_TOKEN_SIZE];
    enum tokens token;
    char lexeme[MAX_TOKEN_SIZE];
    unsigned int line_no;
    Value val;
    int tag; // {0, 1, 2} 0 - other, 1 - int, 2 - float
};

typedef struct node Node;

int remove_comments(char* buf_head);
int flushBuffer(char* buf_head);
FILE* open_file(char* filename);
int string_flush();
int buffer_read(FILE* fp);
Node* create_node();
Node* get_token(char* fp);
int lexical_analyzer(char* filename);
