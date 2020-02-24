// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include "stack.h"

//Create empty stack
stack* create_stack() {
    stack* top = NULL;
    return top;
}

//Push an element to top of stack
int push(stack** top, stack_ele s) {
    stack* s1 = (stack*)malloc(sizeof(stack));
    s1->next = *top;
    (s1->ele).ptr = s.ptr;
    (s1->ele).sym = s.sym;
    *top = s1;

    return 1;
}

//Pop an element at the top of the stack
stack_ele pop(stack** top) {
    
    if(!is_empty(*top)) {
        stack_ele s = (*top)->ele;
        *top = (*top)->next;
        return s;
    }
}

//Get the elemet at the top of the stack but don't remove it
stack_ele peek(stack* top) {
    if(!is_empty(top)) {
        return top->ele;
    }
}

//Check if stack empty
int is_empty(stack* top) {
    if(top==NULL) {
        return 1;
    }
    return 0;

}

//Get cuurent size of stack
int size(stack* top) {
    if(!is_empty(top)) {
        stack* temp = top;
        int count=0;
        while(temp) {
            count++;
            temp=temp->next;
        }
        return count;
    }
    else {
        return 0;
    }
}
