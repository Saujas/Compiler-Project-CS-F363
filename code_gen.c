#include "code_gen.h"

int label = 0;
// Integer - Word size, Real - 64 bit, Boolean - Byte
char* reg_offsets[4] = {"word", "qword", "byte", ""};

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

    fprintf(fp, "extern printf\n\nsection .data\n");
    fprintf(fp, "\tfmt_integer: db '%s', 10, 0\n", "%d");
    fprintf(fp, "\tfmt_float: db '%s', 10, 0\n", "%f");
    fprintf(fp, "\tfmt_string: db '%s', 10, 0\n", "%s");
    fprintf(fp, "\tmessage_true: db 'true', 0\n");
    fprintf(fp, "\tmessage_false: db 'false', 0\n");
    fprintf(fp, "\n");
    
    fprintf(fp, "section .bss\n");
    initialize_bss(list, tree, fp);
    fprintf(fp, "\n");

    if(list != NULL) {
        fprintf(fp, "section .text\nglobal main\n\n");
        tuple* tuple1 = list->head;
        generate_tuple_code(tuple1, fp);
    }

    // exit program
    fprintf(fp, "\n\n; exiting program\n");
    fprintf(fp, "\tmov rax, 1\n\tmov rbx, 0\n\tint 80h\n");

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

char* generate_dynamic_label() {
    char* str = (char *) malloc(sizeof(char) * 10);

    sprintf(str, "__L%d__", label);
    label += 1;

    return str;
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
            fprintf(fp, "\tmov rbp, mem_%s\n\tpush rbp\n\tmov rbp, rsp\n", tup->result);
        }
    }

    print_args(tup);

    if(tup->op == COPY) {
        char *res = read_operand(tup->node3, tup->result);

        if(tup->node1) {
            if(tup->node1->datatype == 0)
                fprintf(fp, "\tmov ax, word [rbp + %d]\n\tmov %s, ax\n", tup->node1->offset, res);
            else if(tup->node1->datatype == 1)
                fprintf(fp, "\tmov rax, qword [rbp + %d]\n\tmov %s, rax\n", tup->node1->offset, res);
            else if(tup->node1->datatype == 2)
                fprintf(fp, "\tmov al, byte [rbp + %d]\n\tmov %s, al\n", tup->node1->offset, res);
        }
        else {
            if(tup->node3->datatype == 0)
                fprintf(fp, "\tmov %s, %s\n", res, tup->arg1);
            else if(tup->node3->datatype == 1)
                fprintf(fp, "\tmov rax, __float64__(%s)\n\tmov %s, rax\n", tup->arg1, res);
            else if(tup->node3->datatype == 2) {
                if(strcmp(tup->arg1, "true") == 0)
                    fprintf(fp, "\tmov %s, 1\n", res);
                else
                    fprintf(fp, "\tmov %s, 0\n", res);
            }
        }
    }

    if(tup->op == MEM_WRITE) {
        char *res = read_operand(tup->node3, tup->result);
        fprintf(fp, "\tmov rbx, %s\n", res);

        if(tup->node1) {
            if(tup->node1->datatype == 0)
                fprintf(fp, "\tmov ax, word [rbp + %d]\n\tmov word [rbx], ax\n", tup->node1->offset);
            else if(tup->node1->datatype == 1)
                fprintf(fp, "\tmov rax, qword [rbp + %d]\n\tmov qword [rbx], rax\n", tup->node1->offset);
            else if(tup->node1->datatype == 2)
                fprintf(fp, "\tmov al, byte [rbp + %d]\n\tmov byte [rbx], al\n", tup->node1->offset);
        }
        else {
            if(tup->node3->datatype == 0)
                fprintf(fp, "\tmov word [rbx] %s\n", tup->arg1);
            else if(tup->node3->datatype == 1)
                fprintf(fp, "\tmov rax, __float64__(%s)\n\tmov qword [rbx], rax\n", tup->arg1);
            else if(tup->node3->datatype == 2) {
                if(strcmp(tup->arg1, "true") == 0)
                    fprintf(fp, "\tmov byte [rbx], 1\n");
                else
                    fprintf(fp, "\tmov byte [rbx], 0\n");
            }
        }
    }

    if(tup->op == MEM_READ) {
        char* arg = read_operand(tup->node1, tup->arg1);
        char* res = read_operand(tup->node3, tup->result);
        fprintf(fp, "\tmov rbx, %s\n", arg);

        if(tup->node3->datatype == 0)
            fprintf(fp, "\tmov ax, word [rbx]\n\tmov %s, ax\n", res);
        else if(tup->node3->datatype == 1)
            fprintf(fp, "\tmov rax, qword [rbx]\n\tmov %s, rax\n", res);
        else if(tup->node3->datatype == 2)
            fprintf(fp, "\tmov al, byte [rbx]\n\tmov %s, al\n", res);
    }

    if(tup->op == ADDITION || tup->op == SUBTRACTION || tup->op == MULTIPLY || tup->op == DIVIDE) {
        char operation[5];
        char* arg1 = read_operand(tup->node1, tup->arg1);
        char* arg2 = read_operand(tup->node2, tup->arg2);

        if(tup->node3->datatype == 0) {
            if(tup->op == ADDITION)
                strcpy(operation, "add");
            else if(tup->op == SUBTRACTION)
                strcpy(operation, "sub");
            else if(tup->op == MULTIPLY)
                strcpy(operation, "imul");

            if(tup->op == DIVIDE) {
                if(tup->node3->datatype == 0) {
                    if(tup->node2)
                        fprintf(fp, "\txor dx, dx\n\tmov ax, %s\n\tidiv %s\n\tmov word [rbp + %d], ax\n", arg1, arg2, tup->node3->offset);
                    else
                        fprintf(fp, "\txor dx, dx\n\tmov ax, %s\n\tmov cx, %s\n\tidiv cx\n\tmov word [rbp + %d], ax\n", arg1, arg2, tup->node3->offset);
                }
            }
            else
                fprintf(fp, "\tmov ax, %s\n\t%s ax, %s\n\tmov word [rbp + %d], ax\n", arg1, operation, arg2, tup->node3->offset);
        }
        else if(tup->node3->datatype == 1) {
            if(tup->op == ADDITION)
                strcpy(operation, "fadd");
            if(tup->op == SUBTRACTION)
                strcpy(operation, "fsub");
            if(tup->op == MULTIPLY)
                strcpy(operation, "fmul");
            if(tup->op == DIVIDE)
                strcpy(operation, "fdiv");

            if(strcmp(arg2, "-1") == 0)
                strcpy(arg2, "__float64__(-1.0)");

            fprintf(fp, "\tfinit\n");
            if(tup->node1 && tup->node2) {
                fprintf(fp, "\tfld %s\n\tfld %s\n\t%s\n", arg1, arg2, operation);
            }
            else if(tup->node1 && !tup->node2) {
                fprintf(fp, "\tfld %s\n\tsub rsp, 64\n\tmov rax, %s\n\tmov [rsp], rax\n\t%s qword [rsp]\n\tadd rsp, 64\n", arg1, arg2, operation);
            }
            else if(!tup->node1 && tup->node2) {
                fprintf(fp, "\tsub rsp, 64\n\tmov rax, %s\n\tmov [rsp], rax\n\tfld qword [rsp]\n\tadd rsp, 64\n\t%s %s\n", arg1, operation, arg2);
            }
            else {
                fprintf(fp, "\tsub rsp, 128\n\tmov rax, %s\n\tmov [rsp], rax\n\tfld qword [rsp]\n\tadd rsp, 64\n\tmov rax, %s\n\tmov [rsp], rax\n\t%s qword [rsp]\n", arg1, arg2, operation);
            }

            fprintf(fp, "\tfstp qword [rbp + %d]\n", tup->node3->offset);
        }
        else if(tup->node3->datatype == 3 && tup->op == ADDITION) {
            fprintf(fp, "\tmov rax, rbp\n\tadd rax, %d\n\txor rbx, rbx\n\tmov bx, word [rbp + %d]\n\tadd rax, rbx\n\tmov qword [rbp + %d], rax\n", tup->node1->offset, tup->node2->offset, tup->node3->offset);
        }
    }

    if(tup->op == BOOLEAN_AND || tup->op == BOOLEAN_OR) {
        char operation[4];
        if(tup->op == BOOLEAN_AND)
            strcpy(operation, "and");
        if(tup->op == BOOLEAN_OR)
            strcpy(operation, "or");
        char* arg1 = read_operand(tup->node1, tup->arg1);
        char* arg2 = read_operand(tup->node2, tup->arg2);

        fprintf(fp, "\tmov al, %s\n\t%s al, %s\n\tmov byte [rbp + %d], al\n", arg1, operation, arg2, tup->node3->offset);
    }

    if(tup->op == GREATER || tup->op == GREATER_EQUAL || tup->op == LESS ||
    tup->op == LESS_EQUAL || tup->op == EQUAL || tup->op == NOT_EQUAL) {
        char* arg1 = read_operand(tup->node1, tup->arg1);
        char* arg2 = read_operand(tup->node2, tup->arg2);
        int is_float = 0;

        if((tup->node1 && tup->node1->datatype==1) || (tup->node2 && tup->node2->datatype==1))
            is_float = 1;
        else if(!tup->node1 && !tup->node2)
            is_float = check_if_float(arg1) || check_if_float(arg2);

        if(!tup->node1 && !is_float) {
            fprintf(fp, "\tmov ax, %s\n\tcmp ax, %s\n", arg1, arg2);

        }
        else if(tup->node1 && !is_float) {
            fprintf(fp, "\tcmp %s, %s\n", arg1, arg2);
        }
        else {
            fprintf(fp, "\tfinit\n");
            if(tup->node1 && tup->node2) {
                fprintf(fp, "\tfld %s\n\tfld %s\n\tfcomi\n", arg1, arg2);
            }
            else if(tup->node1 && !tup->node2) {
                fprintf(fp, "\tfld %s\n\tsub rsp, 64\n\tmov rax, %s\n\tmov [rsp], rax\n\tfld qword [rsp]\n\tfcomi\n", arg1, arg2);
            }
            else if(!tup->node1 && tup->node2) {
                fprintf(fp, "\tsub rsp, 64\n\tmov rax, %s\n\tmov [rsp], rax\n\tfld qword [rsp]\n\tadd rsp, 64\n\tfld %s\n\tfcomi\n", arg1, arg2);
            }
            else {
                fprintf(fp, "\tsub rsp, 128\n\tmov rax, %s\n\tmov [rsp], rax\n\tfld qword [rsp]\n\tadd rsp, 64\n\tmov rax, %s\n\tmov [rsp], rax\n\tfld qword [rsp]\n\tfcomi\n", arg1, arg2);
            }
        }

        char operation[5];
        if(tup->op == GREATER)
            strcpy(operation, "jle");
        else if(tup->op == GREATER_EQUAL)
            strcpy(operation, "jl");
        else if(tup->op == LESS)
            strcpy(operation, "jge");
        else if(tup->op == LESS_EQUAL)
            strcpy(operation, "jg");
        else if(tup->op == EQUAL)
            strcpy(operation, "jnz");
        else if(tup->op == NOT_EQUAL)
            strcpy(operation, "jz");

        char* label1 = generate_dynamic_label();
        char* label2 = generate_dynamic_label();
        fprintf(fp, "\t%s %s\n\tMOV byte [rbp + %d], 1\n\tJMP %s\n%s:\n\tMOV byte [rbp + %d], 0\n%s:\t", operation, label1, tup->node3->offset, label2, label1, tup->node3->offset, label2);
    }

    if(tup->op == WRITE) {
        if(tup->node3) {
            int data_type = tup->node3->datatype;

            if(data_type == 3) {
                fprintf(fp, "\tmov rbx, qword [rbp + %d]\n", tup->node3->offset);
                data_type = tup->node3->array_datatype;
            }

            char arg[20];
            if(tup->node3->datatype == 3)
                sprintf(arg, "[rbx]");
            else
                sprintf(arg, "[rbp + %d]", tup->node3->offset);

            if(data_type == 0)
                fprintf(fp, "\tmov rax, 0\n\tmov ax, word %s\n\tmovsx rax, ax\n\tmov rdi, fmt_integer\n\tmov rsi, rax\n\tmov rax, 0\n\tcall printf\n", arg);
            else if(data_type == 1)
                fprintf(fp, "\tmov rax, qword %s\n\tmov rdi, fmt_float\n\tmovq xmm0, rax\n\tmov eax, 1\n\tcall printf\n", arg);
            else if(data_type == 2) {
                char* label1 = generate_dynamic_label();
                char* label2 = generate_dynamic_label();
                fprintf(fp, "\tcmp byte %s, 1\n\tjz %s\n\tmov rax, message_false\n\tjmp %s\n%s:\n\tmov rax, message_true\n%s:\n", arg, label1, label2, label1, label2); 
                fprintf(fp, "\tmov rdi, fmt_string\n\tmov rsi, rax\n\txor rax, rax\n\tcall printf\n");
            }
        }
        else {
            int i=0, length = strlen(tup->result), j=0, k=0;
            length += 1;
            char str[8];

            fprintf(fp, "\tsub rsp, %d\n", length);
            
            while(i < (length-1)) {
                if(j==8) {
                    j = 0;
                    k++;
                    fprintf(fp, "\tmov rax, '%s'\n\tmov qword [rsp], rax\n\tadd rsp, 8\n", str);
                }

                str[j] = (tup->result)[i];
                j++;
                i++;
            }
            
            fprintf(fp, "\tmov rax, '%s'\n\tmov qword [rsp], rax\n", str);
            fprintf(fp, "\tadd rsp, %d\n\tmov byte [rsp], 0\n\tsub rsp, %d\n", j, (length-1));
            fprintf(fp, "\tmov rax, rsp\n\tmov rdi, fmt_string\n\tmov rsi, rax\n\txor rax, rax\n\tcall printf\n\tadd rsp, %d\n", length);
        }
    }

    if(tup->op == GOTO) {
        fprintf(fp, "\tjmp %s\n", tup->arg1);
    }

    if(tup->op == IF_TRUE) {
        fprintf(fp, "\tmov al, byte [rbp + %d]\n\tcmp al, 1\n\tjz %s\n", tup->node1->offset, tup->result);
    }
    if(tup->op == IF_FALSE) {
        fprintf(fp, "\tmov al, byte [rbp + %d]\n\tcmp al, 0\n\tjz %s\n", tup->node1->offset, tup->result);
    }

    generate_tuple_code(tup->next, fp);

    return 1;
}

char* read_operand(Symbol_Node* node, char* arg) {
    char* arg1 = (char*) malloc(sizeof(char)*25);

    if(node) {
        sprintf(arg1, "%s [rbp + %d]", reg_offsets[node->datatype], node->offset);
    }
    else {
        if(check_if_float(arg)) {
            sprintf(arg1, "__float64__(%s)", arg);
        }
        else if(strcmp(arg, "true") == 0)
            strcpy(arg1, "1");
        else if(strcmp(arg, "false") == 0)
            strcpy(arg1, "0");
        else
            strcpy(arg1, arg);
    }
    return arg1;
}

int check_if_float(char* str) {
    int i, n = strlen(str);
    for(i=0; i<n; i++) {
        if(str[i] == '.')
            return 1;
    }

    return 0;
}
