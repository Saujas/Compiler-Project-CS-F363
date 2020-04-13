#include "code_gen.h"

int generate_code(tuple_list* list, char* filename) {
    
    FILE* fp = fopen(filename, "w");

    if(fp == NULL) {
        printf("Error! in opening file\n");
        return 0;
    }

    // hello world lol
    // fprintf(fp, "section .data\n hello: db 'Hello World!', 10\n helloLen: equ $-hello\n section .text\n global _start\n");
    // fprintf(fp, "_start:\n mov eax, 4\n mov ebx, 1\n mov ecx, hello\n mov edx, helloLen\n int 80h\n mov eax, 1\n mov ebx, 0\n int 80h\n");
    
    printf("No. of tuples: %d\n", list->count);
    
    if(list != NULL) {
        fprintf(fp, "section .text\nglobal _start\n");
        tuple* tuple1 = list->head;
        generate_tuple_code(tuple1, fp);   
    }

    // exit program
    fprintf(fp, "mov ebx, 0\nint 80h\n");

    fclose(fp);

    return 1;
}

void print_args(struct tup* tup) {
    
    if(tup->node1) {
        printf("%s: %d %d\n", tup->arg1, tup->node1->offset, tup->node1->width);
    }

    if(tup->node2) {
        printf("%s: %d %d\n", tup->arg2, tup->node2->offset, tup->node2->width);
    }

    if(tup->node3) {
        printf("%s: %d %d\n", tup->result, tup->node3->offset, tup->node3->width);
    }

    return;
}

int generate_tuple_code(struct tup* tup, FILE* fp) {
    
    if(tup == NULL)
        return 0;
    
    if(tup->op == LABEL) {
        if(strcmp(tup->result, "main") == 0) {
            fprintf(fp, "_start:\n");    
        }
        else
            fprintf(fp, "%s:\n", tup->result);
    }

    if(tup->op == COPY) {
        if(tup->node1) {
            fprintf(fp, "mov AX, word [%d]\nmov word [%d], AX\n", tup->node1->offset, tup->node3->offset);
        }
        else {
            fprintf(fp, "mov word [%d], '%s'\n", tup->node3->offset, tup->arg1);
        }
    }

    if(tup->op == WRITE) {
        if(tup->node3) {
            fprintf(fp, "movzx EAX, word [%d]\nmov EAX, 4\nint 80h\n", tup->node3->offset);
        }
        else {
            fprintf(fp, "mov EAX, %s\nmov EAX, 4\n,int 80h", tup->result);
        }
    }

    print_args(tup);

    generate_tuple_code(tup->next, fp);

    return 1;
}