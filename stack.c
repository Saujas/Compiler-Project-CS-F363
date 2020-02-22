#include "stack.h"

stack* create_stack() {
    stack* top = NULL;
    return top;
}

int push(stack** top, stack_ele s) {
    stack* s1 = (stack*)malloc(sizeof(stack));
    s1->next = *top;
    (s1->ele).ptr = s.ptr;
    (s1->ele).sym = s.sym;
    *top = s1;

    return 1;
}

stack_ele pop(stack** top) {
    
    if(!is_empty(*top)) {
        stack_ele s = (*top)->ele;
        *top = (*top)->next;
        return s;
    }
}

stack_ele peek(stack* top) {
    if(!is_empty(top)) {
        return top->ele;
    }
}

int is_empty(stack* top) {
    if(top==NULL) {
        return 1;
    }
    return 0;

}

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
