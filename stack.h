// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include "parser_def.h"
#include "tree.h"
// #include "lexer_def.h"

/* Structure for a single stack element, containing a symbol(non-terminal enum or token enum),
   and a pointer to a tree node to be used in tree.c for parse tree creation
*/
typedef struct {
    symbol sym;
    t_node* ptr;
} stack_ele;

typedef struct _stack{
    stack_ele ele;
    struct  _stack* next;
} stack;

/* Function definitions for all functions used in stack. Detailed descriptions in stack.c
*/
int push(stack** top, stack_ele s);
stack_ele pop(stack** top);
int is_empty(stack* top);
int size(stack* top);
stack_ele peek(stack* top);
stack* create_stack();
