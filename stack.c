#include "stack.h"

stack* create_stack() {
    stack* top = NULL;
    return top;
}

int push(stack** top, symbol s) {
    stack* s1 = (stack*)malloc(sizeof(stack));
    s1->next = *top;
    s1->sym = s;
    *top = s1;
}

symbol pop(stack** top) {
    
    if(!is_empty(*top)) {
        symbol s = (*top)->sym;
        *top = (*top)->next;
        return s;
    }
}

symbol peek(stack* top) {
    if(!is_empty(top)) {
        return top->sym;
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
