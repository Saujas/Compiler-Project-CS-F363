#include "parser_def.h"
#include "tree.h"
// #include "lexer_def.h"

typedef struct {
    symbol sym;
    t_node* ptr;
} stack_ele;

typedef struct _stack{
    stack_ele ele;
    struct  _stack* next;
} stack;

int push(stack** top, stack_ele s);
stack_ele pop(stack** top);
int is_empty(stack* top);
int size(stack* top);
stack_ele peek(stack* top);
stack* create_stack();
