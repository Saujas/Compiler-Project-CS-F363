#include "code_gen.h"

int generate_code(tuple_list* list, Symbol_Table_Tree tree, char* filename) {
    
    FILE* fp = fopen(filename, "w");

    if(fp == NULL) {
        printf("Error! in opening file\n");
        return 0;
    }

    // hello world lol
    // fprintf(fp, "section .data\n hello: db 'Hello World!', 10\n helloLen: equ $-hello\n section .text\n global _start\n");
    // fprintf(fp, "_start:\n mov eax, 4\n mov ebx, 1\n mov ecx, hello\n mov edx, helloLen\n int 80h\n mov eax, 1\n mov ebx, 0\n int 80h\n");
    
    printf("No. of tuples: %d\n", list->count);

    fprintf(fp, "extern printf\nsection .data\n");
    fprintf(fp, "\tfmt_integer: db '%s', 10, 0\n", "%d");
    fprintf(fp, "\tfmt_float: db '%s', 10, 0\n", "%f");
    fprintf(fp, "\tfmt_string: db '%s', 10, 0\n", "%s");
    fprintf(fp, "\n");
    
    fprintf(fp, "section .bss\n");

    initialize_bss(list, tree, fp);

    if(list != NULL) {
        fprintf(fp, "section .text\nglobal main\n\n");
        tuple* tuple1 = list->head;
        generate_tuple_code(tuple1, fp);
    }

    // exit program
    fprintf(fp, "\n\n; exiting program\n");
    fprintf(fp, "mov rax, 1\nmov rbx, 0\nint 80h\n");

    fclose(fp);

    return 1;
}

int initialize_bss(tuple_list* list, Symbol_Table_Tree tree, FILE* fp) {

    tuple* tup = list->head;
    Symbol_Table_Tree fun_tree = tree->child;

    while(tup) {
        if(tup->op == FUN_LABEL) {
            Symbol_Table_Tree temp = fun_tree;

            while(temp) {
                if( (strcmp(tup->result, "main") == 0) && (strcmp("AST_DRIVER", temp->name) == 0) || 
                (strcmp(tup->result, temp->name) == 0)) {
                    
                    char s1[30];
                    strcpy(s1, "mem_");
                    strcat(s1, tup->result);

                    fprintf(fp, "\t%s resb %d\n", s1, temp->last_offset);

                    break;
                }
                temp = temp->sibling;
            }
        }
        
        tup = tup->next;
    }

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

int generate_tuple_code(tuple* tup, FILE* fp) {
    
    if(tup == NULL)
        return 0;
    
    if(tup->op == LABEL || tup->op == FUN_LABEL) {
        fprintf(fp, "%s:\n", tup->result);

        if(tup->op == FUN_LABEL) {
            fprintf(fp, "mov rbp, mem_%s\npush rbp\nmov rbp, rsp\n", tup->result);
        }
    }

    if(tup->op == COPY) {
        if(tup->node1) {
            if(tup->node1->datatype == 0)
                fprintf(fp, "mov ax, word [rbp + %d]\nmov word [rbp + %d], ax\n", tup->node1->offset, tup->node3->offset);
            else if(tup->node1->datatype == 1)
                fprintf(fp, "mov rax, qword [rbp + %d]\nmov qword [rbp + %d], rax\n", tup->node1->offset, tup->node3->offset);
            else if(tup->node1->datatype == 2)
                fprintf(fp, "mov al, byte [rbp + %d]\nmov byte [rbp + %d], al\n", tup->node1->offset, tup->node3->offset);
        }
        else {
            if(tup->node3->datatype == 0)
                fprintf(fp, "mov word [rbp + %d], %s\n", tup->node3->offset, tup->arg1);
            else if(tup->node3->datatype == 1)
                fprintf(fp, "mov rax, __float64__(%s)\nmov qword [rbp + %d], rax\n", tup->arg1, tup->node3->offset);
            else if(tup->node3->datatype == 2) {
                if(strcmp(tup->arg1, "true") == 0)
                    fprintf(fp, "mov byte [rbp + %d], 1\n", tup->node3->offset);
                else
                    fprintf(fp, "mov byte [rbp + %d], 0\n", tup->node3->offset);
            }
        }
    }

    if(tup->op == WRITE) {
        if(tup->node3) {
            if(tup->node3->datatype == 0)
                fprintf(fp, "mov rax, 0\nmov ax, [rbp + %d]\nmov rdi, fmt_integer\nmov rsi, rax\nmov rax, 0\ncall printf\n", tup->node3->offset);
            else if(tup->node3->datatype == 1)
                fprintf(fp, "mov rax, qword[rbp + %d]\nmov rdi, fmt_float\nmovq xmm0, rax\nmov eax, 1\ncall printf\n", tup->node3->offset);
            else if(tup->node3->datatype == 2) {
                fprintf(fp, "mov rax, 0\nmov al, byte [rbp + %d]\nmov rdi, fmt_integer\nmov rsi, rax\nmov rax, 0\ncall printf\n", tup->node3->offset); 
            }
        }
        else {
            int i=0, length = strlen(tup->result), j=0, k=0;
            length += 1;
            char str[8];

            fprintf(fp, "sub rsp, %d\n", length);
            
            while(i < (length-1)) {
                if(j==8) {
                    j = 0;
                    k++;
                    fprintf(fp, "mov rax, '%s'\nmov qword [rsp], rax\nadd rsp, 8\n", str);
                }

                str[j] = (tup->result)[i];
                j++;
                i++;
            }
            
            fprintf(fp, "mov rax, '%s'\nmov qword [rsp], rax\n", str);
            fprintf(fp, "add rsp, %d\nmov byte [rsp], 0\nsub rsp, %d\n", j, (length-1));
            fprintf(fp, "mov rax, rsp\nmov rdi, fmt_string\nmov rsi, rax\nmov rax, 0\ncall printf\nadd rsp, %d\n", length);
        }
    }

    print_args(tup);

    generate_tuple_code(tup->next, fp);

    return 1;
}