#include "parser_def.h"
// #include "lexer_def.h"

typedef struct _stack{
    symbol sym;
    struct  _stack* next;
} stack;

int push(stack** top, symbol s);
symbol pop(stack** top);
int is_empty(stack* top);
int size(stack* top);
symbol peek(stack* top);
stack* create_stack();
