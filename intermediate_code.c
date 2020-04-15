#include "intermediate_code.h"
#include "symbol_table.h"

char* operator_string_map[OPERATOR_SIZE] = {
    "COPY", "ADD", "SUB", "MUL", "DIV", "MEM_READ", "MEM_WRITE", "GT",
    "GE", "LT", "LE", "EQ", "NE", "AND", "OR", "LABEL", "IF_TRUE", "IF_FALSE", "GOTO",
    "READ", "WRITE", "exit", "return", "param_op", "param", "call", "function"
};

int temp_var;
int label;

Tuple make_tuple(oper op, char* arg1, char* arg2, char* result, Symbol_Node* node1, Symbol_Node* node2, Symbol_Node* node3) {
    Tuple t = (Tuple) malloc(sizeof(tuple));
    
    t->arg1 = (char*) malloc((strlen(arg1) * sizeof(char)));
    strcpy(t->arg1, arg1);
    
    t->arg2 = (char*) malloc((strlen(arg2) * sizeof(char)));
    strcpy(t->arg2, arg2);
    
    t->result = (char*) malloc((strlen(result) * sizeof(char)));
    strcpy(t->result, result);
    
    t->node1 = node1;
    t->node2 = node2;
    t->node3 = node3;

    t->next = NULL;
    t->op = op;

    return t;
}

void add_tuple(tuple_list* list, Tuple t) {
    if(list->head == NULL) {
        list->head = t;
        list->tail = t;
    }
    else {
        list->tail->next = t;
        list->tail = t;
    }

    list->count += 1;
    return;
}

void add_temp_symboltable(Symbol_Node* symbol, Symbol_Table_Tree parent_node, int width) {

    if(width == 1) {
        symbol->datatype = 2;
    }
    if(width == 2) {
        symbol->datatype = 0;
    }
    if(width == 8) {
        symbol->datatype = 1;
    }

    symbol->width = width;
    symbol->offset = parent_node->last_offset;
    parent_node->last_offset += width;
}

char* create_label() {
    char* l = (char*) malloc(sizeof(char)*5);
    int i;
    for(i=0; i<5; i++) {
        l[i] = '\0';
    }

    l[0] = 'L';
    
    char str2[10];
    sprintf(str2, "%d", label);
    for(i=0; i<3; i++) {
        l[i+1] = str2[i];
    }

    label += 1;
    return l;
}

Temporary create_temporary() {

    Temporary node_t = (Temporary) malloc(sizeof(temporary));

    node_t->name = (char*) malloc(sizeof(char) * 5);
    int i;
    for(i=0; i<5; i++) {
        node_t->name[i] = '\0';
    }

    node_t->name[0] = 't';

    char str2[10];
    sprintf(str2, "%d", temp_var);
    for(i=0; i<3; i++) {
        node_t->name[i+1] = str2[i];
    }

    temp_var += 1;

    node_t->symbol = (Symbol_Node*) malloc(sizeof(Symbol_Node));
    node_t->symbol->node = NULL;

    return node_t;
}

void print_tuple_list(tuple_list* list) {
    Tuple temp = list->head;

    while(temp) {
        print_tuple(temp);
        temp = temp->next;
    }

    return;
}

void print_tuple(Tuple t) {
    if(t->op == LABEL) {
        printf("%s:\n", t->result);
        return;
    }
    printf("\tOP:%-4s:\tArg1: %-4s\tArg2: %-4s\tResult: %-4s\n", operator_string_map[t->op], t->arg1, t->arg2, t->result);
    return;
}

tuple_list* generate_ir(AST root) {
    
    temp_var = 0;
    label = 0;

    tuple_list* list = (tuple_list*) malloc(sizeof(tuple_list));

    list->count = 0;
    list->head = NULL;
    list->tail = NULL;

    generate_ir_util(root, list);
    print_tuple_list(list);

    return list;
}

void generate_ir_util(AST node, tuple_list* list) {
    
    if(!node) {
        return;
    }

    int processed = process_node(node, list);
    if(processed) {
        return;
    }

    AST child = node->child;

    while(child) {
        generate_ir_util(child, list);
        child = child->next;
    }

    return;
}

int process_node(AST node, tuple_list* list) {

    oper op;

    // AST_DRIVER
    if(node->rule_num == 7 && node->tag == 1) {
        Tuple new_tup = make_tuple(FUN_LABEL, "", "", "main", NULL, NULL, NULL);
        add_tuple(list, new_tup);

        generate_ir_util(node->child, list);

        new_tup = make_tuple(EXIT, "", "", "", NULL, NULL, NULL);
        add_tuple(list, new_tup);

        return 1;
    }

    // AST MODULE
    if(node->rule_num == 8 && node->tag == 1) {
        Tuple new_tup = make_tuple(FUN_LABEL, "", "", node->child->leaf_token->lexeme, NULL, NULL, NULL);
        add_tuple(list, new_tup);
        
        AST temp = node->child->next->next;
        
        if(temp->next)
            temp = temp->next;

        generate_ir_util(temp, list);

        new_tup = make_tuple(RETURN, "", "", "", NULL, NULL, NULL);
        add_tuple(list, new_tup);

        return 1;
    }
    
    // assignment statement
    if(node->rule_num == 52 && node->tag == 1) {

        if(node->child->symbol_table_node->datatype != 3) {
            
            oper op = COPY;

            char* arg1 = node->child->leaf_token->lexeme;
            Symbol_Node* node3 = node->child->symbol_table_node;

            Symbol_Table_Tree parent_scope = get_parent_scope(node->current_scope);
            
            Temporary node_t = evaluate_expression(node->child->next, list, parent_scope);

            // Symbol_Node* result = (Symbol_Node*) malloc(sizeof(Symbol_Node));

            // add_temp_symboltable(node, result, new_temp);
            Tuple new_tup = make_tuple(op, node_t->name, "", node->child->leaf_token->lexeme, node_t->symbol, NULL, node3);
            add_tuple(list, new_tup);
        }
        else if(node->child->symbol_table_node->datatype == 3 && node->child->next->label != LVALUE_ARR_STMT) {
            
            AST lhs = node->child, rhs = node->child->next->child;
            Symbol_Node* l1 = NULL, *h1 = NULL, *l2 = NULL, *h2 = NULL;
            Symbol_Table_Tree parent_scope = get_parent_scope(lhs->current_scope);

            Temporary i1 = create_temporary();
            add_temp_symboltable(i1->symbol, parent_scope, 2);
            Temporary i2 = create_temporary();
            add_temp_symboltable(i2->symbol, parent_scope, 2);
            
            char *name1, *name2, *name3, *name4;
            name1 = get_limit(lhs, 0);
            name2 = get_limit(lhs, 1);
            name3 = get_limit(rhs, 0);
            name4 = get_limit(rhs, 1);
            
            if(lhs->symbol_table_node->range[0].tag == 1) {
                l1 = lhs->symbol_table_node->range[0].range_pointer.id;
            }
            if(lhs->symbol_table_node->range[1].tag == 1) {
                h1 = lhs->symbol_table_node->range[1].range_pointer.id;
            }
            if(rhs->symbol_table_node->range[0].tag == 1) {
                l2 = rhs->symbol_table_node->range[0].range_pointer.id;
            }
            if(rhs->symbol_table_node->range[1].tag == 1) {
                h2 = rhs->symbol_table_node->range[1].range_pointer.id;
            }

            Tuple new_tup0 = make_tuple(COPY, name1, "", i1->name, l1, NULL, i1->symbol);
            add_tuple(list, new_tup0);

            Tuple new_tup1 = make_tuple(COPY, name2, "", i2->name, l2, NULL, i2->symbol);
            add_tuple(list, new_tup1);

            char* label1 = create_label();
            char* label2 = create_label();
            char* label3 = create_label();

            Tuple new_tup2 = make_tuple(LABEL, "", "", label1, NULL, NULL, NULL);
            add_tuple(list, new_tup2);

            Temporary temp = create_temporary();
            add_temp_symboltable(temp->symbol, parent_scope, 1);
            Tuple new_tup3 = make_tuple(LESS_EQUAL, i1->name, name2, temp->name, i1->symbol, h1, temp->symbol);
            add_tuple(list, new_tup3);

            Tuple new_tup5 = make_tuple(IF_TRUE, temp->name, "", label2, temp->symbol, NULL, NULL);
            add_tuple(list, new_tup5);
            Tuple new_tup6 = make_tuple(IF_FALSE, temp->name, "", label3, temp->symbol, NULL, NULL);
            add_tuple(list, new_tup6);

            Tuple new_tup7 = make_tuple(LABEL, "", "", label2, NULL, NULL, NULL);
            add_tuple(list, new_tup7);

            AST iterator1 = (AST) malloc(sizeof(AST_Node));
            iterator1->leaf_token = (Node*) malloc(sizeof(Node));
            
            strcpy(iterator1->leaf_token->lexeme, i1->name);
            iterator1->leaf_token->token = ID;
            iterator1->symbol_table_node = i1->symbol;

            AST iterator2 = (AST) malloc(sizeof(AST_Node));
            iterator2->leaf_token = (Node*) malloc(sizeof(Node));
            
            strcpy(iterator2->leaf_token->lexeme, i2->name);
            iterator2->leaf_token->token = ID;
            iterator2->symbol_table_node = i2->symbol;

            Temporary t0 = evaluate_array(rhs, iterator2, list, parent_scope);
            Temporary t1 = create_temporary();
            int width[3] = {2, 8, 1};
            add_temp_symboltable(t1->symbol, parent_scope, width[rhs->symbol_table_node->array_datatype]);
            Tuple new_tup8 = make_tuple(MEM_READ, t0->name, "", t1->name, t0->symbol, NULL, t1->symbol);
            add_tuple(list, new_tup8);

            Temporary t2 = evaluate_array(lhs, iterator1, list, parent_scope);
            Tuple new_tup9 = make_tuple(MEM_WRITE, t1->name, "", t2->name, t1->symbol, NULL, t2->symbol);
            add_tuple(list, new_tup9);

            Temporary t3 = create_temporary();
            add_temp_symboltable(t3->symbol, parent_scope, 2);
            Tuple new_tup10 = make_tuple(ADDITION, i1->name, "1", t3->name, i1->symbol, NULL, t3->symbol);
            Tuple new_tup11 = make_tuple(COPY, t3->name, "", i1->name, t3->symbol, NULL, i1->symbol);

            Tuple new_tup12 = make_tuple(ADDITION, i2->name, "1", t3->name, i2->symbol, NULL, t3->symbol);
            Tuple new_tup13 = make_tuple(COPY, t3->name, "", i2->name, t3->symbol, NULL, i2->symbol);

            add_tuple(list, new_tup10);
            add_tuple(list, new_tup11);
            add_tuple(list, new_tup12);
            add_tuple(list, new_tup13);

            Tuple new_tup14 = make_tuple(GOTO, "", "", label1, NULL, NULL, NULL);
            Tuple new_tup15 = make_tuple(LABEL, "", "", label3, NULL, NULL, NULL);
            add_tuple(list, new_tup14);
            add_tuple(list, new_tup15);

            return 1;
        }
        else {
            AST lhs = node->child, index = node->child->next->child;
            Symbol_Table_Tree parent_scope = get_parent_scope(lhs->current_scope);
            Temporary temp0 = evaluate_array(lhs, index, list, parent_scope);

            Temporary temp1 = evaluate_expression(index->next, list, parent_scope);

            Tuple new_tuple0 = make_tuple(MEM_WRITE, temp1->name, "", temp0->name, temp1->symbol, NULL, temp0->symbol);
            add_tuple(list, new_tuple0);
        }

        return 1;
    }

    if(node->rule_num == 101 && node->tag == 1) {
        AST itr = node->child, ll = itr->next->child, ul = itr->next->child->next;
        Symbol_Table_Tree parent_scope = get_parent_scope(itr->current_scope);

        Tuple label_tup;
        char* label1 = create_label();
        char* label2 = create_label();
        char* label3 = create_label();
        // printf("labels:%s %s %s\n", label1, label2, label3);
        Tuple new_tup = make_tuple(COPY, ll->leaf_token->lexeme, "", itr->leaf_token->lexeme, NULL, NULL, itr->symbol_table_node);
        add_tuple(list, new_tup);

        label_tup = make_tuple(LABEL, "", "", label1, NULL, NULL, NULL);
        add_tuple(list, label_tup);
        // IF

        Temporary new_temp = create_temporary();
        add_temp_symboltable(new_temp->symbol, parent_scope, 1);
        Tuple new_tup1 = make_tuple(LESS_EQUAL, itr->leaf_token->lexeme, ul->leaf_token->lexeme, new_temp->name, itr->symbol_table_node, ul->symbol_table_node, new_temp->symbol);
        add_tuple(list, new_tup1);
        
        Tuple new_tup2 = make_tuple(IF_TRUE, new_temp->name, "", label2, new_temp->symbol, NULL, NULL);
        add_tuple(list, new_tup2);
        Tuple new_tup3 = make_tuple(IF_FALSE, new_temp->name, "", label3, new_temp->symbol, NULL, NULL);
        add_tuple(list, new_tup3);

        label_tup = make_tuple(LABEL, "", "", label2, NULL, NULL, NULL);
        add_tuple(list, label_tup);
        // INSIDE FOR

        generate_ir_util(itr->next->next, list);

        Temporary temp0 = create_temporary();
        add_temp_symboltable(temp0->symbol, parent_scope, 2);

        Tuple new_tup4 = make_tuple(ADDITION, itr->leaf_token->lexeme, "1", temp0->name, itr->symbol_table_node, NULL, temp0->symbol);
        add_tuple(list, new_tup4);

        Tuple new_tup5 = make_tuple(COPY, temp0->name, "", itr->leaf_token->lexeme, temp0->symbol, NULL, itr->symbol_table_node);
        add_tuple(list, new_tup5);

        Tuple new_tup6 = make_tuple(GOTO, label1, "", "", NULL, NULL, NULL);
        add_tuple(list, new_tup6);

        // OUTSIDE FOR
        label_tup = make_tuple(LABEL, "", "", label3, NULL, NULL, NULL);
        add_tuple(list, label_tup);
        
        return 1;
    }

    if(node->rule_num == 102 && node->tag == 1) {
        Symbol_Table_Tree parent_scope = get_parent_scope(node->current_scope);

        char* label1 = create_label();
        char* label2 = create_label();
        char* label3 = create_label();

        Tuple new_tup0 = make_tuple(LABEL, "", "", label1, NULL, NULL, NULL);
        add_tuple(list, new_tup0);

        Temporary temp0 = evaluate_expression(node->child, list, parent_scope);
        
        Tuple new_tup1 = make_tuple(IF_TRUE, temp0->name, "", label2, temp0->symbol, NULL, NULL);
        add_tuple(list, new_tup1);

        Tuple new_tup2 = make_tuple(IF_FALSE, temp0->name, "", label3, temp0->symbol, NULL, NULL);
        add_tuple(list, new_tup2);

        Tuple new_tup3 = make_tuple(LABEL, "", "", label2, NULL, NULL, NULL);
        add_tuple(list, new_tup3);

        generate_ir_util(node->child->next, list);

        Tuple new_tup4 = make_tuple(GOTO, label1, "", "", NULL, NULL, NULL);
        add_tuple(list, new_tup4);

        Tuple new_tup5 = make_tuple(LABEL, "", "", label3, NULL, NULL, NULL);
        add_tuple(list, new_tup5);

        return 1;
    }

    if(node->rule_num == 103 && node->tag == 1) {
        AST id = node->child;
        Symbol_Table_Tree parent_scope = get_parent_scope(id->current_scope);
        char* label_end = create_label();
        int count = 0;
        

        AST temp = node->child->next;

        while(temp->label != AST_DEFAULT) {
            if(id->symbol_table_node->datatype == 2 && count==2) {
                break;
            }
            count++;
            char* label1 = create_label();
            char* label2 = create_label();
            AST curr = temp->child->child;

            Temporary t = create_temporary();
            add_temp_symboltable(t->symbol, parent_scope, 1);
            Tuple new_tup0 = make_tuple(EQUAL, id->leaf_token->lexeme, curr->leaf_token->lexeme, t->name, id->symbol_table_node, curr->symbol_table_node, t->symbol);
            add_tuple(list, new_tup0);

            Tuple new_tup1 = make_tuple(IF_TRUE, t->name, "", label1, t->symbol, NULL, NULL);
            add_tuple(list, new_tup1);
            Tuple new_tup2 = make_tuple(IF_FALSE, t->name, "", label2, t->symbol, NULL, NULL);
            add_tuple(list, new_tup2);

            Tuple new_tup3 = make_tuple(LABEL, "", "", label1, NULL, NULL, NULL);
            add_tuple(list, new_tup3);
            generate_ir_util(curr->next, list);
            Tuple new_tup4 = make_tuple(GOTO, "", "", label_end, NULL, NULL, NULL);
            add_tuple(list, new_tup4);

            Tuple new_tup5 = make_tuple(LABEL, "", "", label2, NULL, NULL, NULL);
            add_tuple(list, new_tup5);

            temp = temp->child->next;
        }

        generate_ir_util(temp->child, list);
        Tuple new_tup = make_tuple(LABEL, "", "", label_end, NULL, NULL, NULL);
        add_tuple(list, new_tup);

        return 1;
    }

    if(node->rule_num == 40 && node->tag == 0) {
        if(node->symbol_table_node->datatype != 3) {
            AST id = node;
            Symbol_Table_Tree parent_scope = get_parent_scope(id->current_scope);

            Temporary t = create_temporary();
            add_temp_symboltable(t->symbol, parent_scope, id->symbol_table_node->width);

            Tuple new_tup = make_tuple(READ, "", "", t->name, NULL, NULL, t->symbol);
            add_tuple(list, new_tup);

            Tuple new_tup1 = make_tuple(COPY, t->name, "", id->leaf_token->lexeme, t->symbol, NULL, id->symbol_table_node);
            add_tuple(list, new_tup1);

            return 1;
        }
        else {
            Symbol_Table_Tree parent_scope = get_parent_scope(node->current_scope);
            int flag1;
            int flag2;

            Tuple label_tup;
            char* label1 = create_label();
            char* label2 = create_label();
            char* label3 = create_label();

            Symbol_Node* ll_sym = NULL;
            Symbol_Node* ul_sym = NULL;
            char* ll;
            char* ul;
            Symbol_Node* sym_node = node->symbol_table_node;

            Temporary itr = create_temporary();
            add_temp_symboltable(itr->symbol, parent_scope, 2);

            if(sym_node->range[0].tag == 1) {
                ll_sym = sym_node->range[0].range_pointer.id;
                flag1 = 1;
            }
            else {
                ll = (char*) malloc(sizeof(char) * 3);
                sprintf(ll, "%d", sym_node->range[0].range_pointer.value);
                flag1 = 0;
            }

            if(sym_node->range[1].tag == 1) {
                ul_sym = sym_node->range[1].range_pointer.id;
                flag2 = 1;
            }
            else {
                ul = (char*) malloc(sizeof(char) * 3);
                sprintf(ul, "%d", sym_node->range[1].range_pointer.value);
                flag2 = 0;
            }

            if(flag1) {                    
                Tuple new_tup = make_tuple(COPY, ll_sym->node->leaf_token->lexeme, "", itr->name, ll_sym, NULL, itr->symbol);
                add_tuple(list, new_tup);
            }
            else {
                Tuple new_tup = make_tuple(COPY, ll, "", itr->name, NULL, NULL, itr->symbol);
                add_tuple(list, new_tup);
            }

            label_tup = make_tuple(LABEL, "", "", label1, NULL, NULL, NULL);
            add_tuple(list, label_tup);
            // IF

            Temporary new_temp = create_temporary();
            add_temp_symboltable(new_temp->symbol, parent_scope, 1);

            if(flag2) {
                Tuple new_tup1 = make_tuple(LESS_EQUAL, itr->name, ul_sym->node->leaf_token->lexeme, new_temp->name, itr->symbol, ul_sym, new_temp->symbol);
                add_tuple(list, new_tup1);
            }
            else {
                Tuple new_tup1 = make_tuple(LESS_EQUAL, itr->name, ul, new_temp->name, itr->symbol, NULL, new_temp->symbol);
                add_tuple(list, new_tup1);
            }
            
            Tuple new_tup2 = make_tuple(IF_TRUE, new_temp->name, "", label2, new_temp->symbol, NULL, NULL);
            add_tuple(list, new_tup2);
            Tuple new_tup3 = make_tuple(IF_FALSE, new_temp->name, "", label3, new_temp->symbol, NULL, NULL);
            add_tuple(list, new_tup3);

            label_tup = make_tuple(LABEL, "", "", label2, NULL, NULL, NULL);
            add_tuple(list, label_tup);
            
            AST iterator = (AST) malloc(sizeof(AST_Node));
            iterator->leaf_token = (Node*) malloc(sizeof(Node));
            // iterator->leaf_token->lexeme = (char*) malloc(sizeof(char)*(strlen(itr->name)));
            
            strcpy(iterator->leaf_token->lexeme, itr->name);
            iterator->leaf_token->token = ID;
            iterator->symbol_table_node = itr->symbol;

            // printf("%s\n", iterator->leaf_token->lexeme);
            

            Temporary temp_arr = evaluate_array(node, iterator, list, parent_scope);
            // printf("HI\n");
            Tuple new_tup4 = make_tuple(READ, "", "", temp_arr->name, NULL, NULL, temp_arr->symbol);
            add_tuple(list, new_tup4);

            Temporary temp0 = create_temporary();
            add_temp_symboltable(temp0->symbol, parent_scope, 2);

            Tuple new_tup5 = make_tuple(ADDITION, itr->name, "1", temp0->name, itr->symbol, NULL, temp0->symbol);
            add_tuple(list, new_tup5);

            Tuple new_tup6 = make_tuple(COPY, temp0->name, "", itr->name, temp0->symbol, NULL, itr->symbol);
            add_tuple(list, new_tup6);

            Tuple new_tup7 = make_tuple(GOTO, label1, "", "", NULL, NULL, NULL);
            add_tuple(list, new_tup7);

            // OUTSIDE FOR
            label_tup = make_tuple(LABEL, "", "", label3, NULL, NULL, NULL);
            add_tuple(list, label_tup);
            
            return 1;
        }
    }

    if(node->label == IO_WRITE) {
        if(node->rule_num == 46 || node->rule_num == 47 || node->rule_num == 43 || node->rule_num == 44 || ((node->rule_num == 42)&&(node->child->symbol_table_node->datatype != 3))) {
            Symbol_Table_Tree parent_scope = get_parent_scope(node->current_scope);
            AST temp = node;
            Symbol_Node* sym = NULL;

            int width;
            if(node->rule_num == 42) {
                width = node->child->symbol_table_node->width;
                temp = node->child;
                sym = temp->symbol_table_node;
            }
            else if(node->rule_num == 43)
                width = 2;
            else if(node->rule_num == 44)
                width = 8;
            else
                width = 1;
            
            // Temporary t = create_temporary();
            // add_temp_symboltable(t->symbol, parent_scope, width);
            

            // Tuple new_tup = make_tuple(COPY, temp->leaf_token->lexeme, "", t->name, sym, NULL, t->symbol);
            // add_tuple(list, new_tup);

            Tuple new_tup1 = make_tuple(WRITE, "", "", temp->leaf_token->lexeme, NULL, NULL, sym);
            add_tuple(list, new_tup1);

            return 1;
        }

        else if(node->rule_num == 42 && node->child->symbol_table_node->datatype == 3) {
            Symbol_Table_Tree parent_scope = get_parent_scope(node->current_scope);
            if(node->child->next) {

                Temporary t1 = evaluate_array(node->child, node->child->next, list, parent_scope);

                Tuple new_tup1 = make_tuple(WRITE, "", "", t1->name, NULL, NULL, t1->symbol);
                add_tuple(list, new_tup1);

                return 1;

            }
            else {
                Symbol_Table_Tree parent_scope = get_parent_scope(node->child->current_scope);
                int flag1;
                int flag2;

                Tuple label_tup;
                char* label1 = create_label();
                char* label2 = create_label();
                char* label3 = create_label();

                Symbol_Node* ll_sym = NULL;
                Symbol_Node* ul_sym = NULL;
                char* ll;
                char* ul;
                Symbol_Node* sym_node = node->child->symbol_table_node;
                // int datatype = sym_node->array_datatype;
                // int width;
                // int arr[3] = {2, 4, 1};
                // width = arr[datatype];

                Temporary itr = create_temporary();
                add_temp_symboltable(itr->symbol, parent_scope, 2);

                if(sym_node->range[0].tag == 1) {
                    ll_sym = sym_node->range[0].range_pointer.id;
                    flag1 = 1;
                }
                else {
                    ll = (char*) malloc(sizeof(char) * 3);
                    sprintf(ll, "%d", sym_node->range[0].range_pointer.value);
                    flag1 = 0;
                }

                if(sym_node->range[1].tag == 1) {
                    ul_sym = sym_node->range[1].range_pointer.id;
                    flag2 = 1;
                }
                else {
                    ul = (char*) malloc(sizeof(char) * 3);
                    sprintf(ul, "%d", sym_node->range[1].range_pointer.value);
                    flag2 = 0;
                }

                // printf("labels:%s %s %s\n", label1, label2, label3);

                if(flag1) {                    
                    Tuple new_tup = make_tuple(COPY, ll_sym->node->leaf_token->lexeme, "", itr->name, ll_sym, NULL, itr->symbol);
                    add_tuple(list, new_tup);
                }
                else {
                    Tuple new_tup = make_tuple(COPY, ll, "", itr->name, NULL, NULL, itr->symbol);
                    add_tuple(list, new_tup);
                }

                label_tup = make_tuple(LABEL, "", "", label1, NULL, NULL, NULL);
                add_tuple(list, label_tup);
                // IF

                Temporary new_temp = create_temporary();
                add_temp_symboltable(new_temp->symbol, parent_scope, 1);

                if(flag2) {
                    Tuple new_tup1 = make_tuple(LESS_EQUAL, itr->name, ul_sym->node->leaf_token->lexeme, new_temp->name, itr->symbol, ul_sym, new_temp->symbol);
                    add_tuple(list, new_tup1);
                }
                else {
                    Tuple new_tup1 = make_tuple(LESS_EQUAL, itr->name, ul, new_temp->name, itr->symbol, NULL, new_temp->symbol);
                    add_tuple(list, new_tup1);
                }
                
                Tuple new_tup2 = make_tuple(IF_TRUE, new_temp->name, "", label2, new_temp->symbol, NULL, NULL);
                add_tuple(list, new_tup2);
                Tuple new_tup3 = make_tuple(IF_FALSE, new_temp->name, "", label3, new_temp->symbol, NULL, NULL);
                add_tuple(list, new_tup3);

                label_tup = make_tuple(LABEL, "", "", label2, NULL, NULL, NULL);
                add_tuple(list, label_tup);
                
                AST iterator = (AST) malloc(sizeof(AST_Node));
                iterator->leaf_token = (Node*) malloc(sizeof(Node));
                // iterator->leaf_token->lexeme = (char*) malloc(sizeof(char)*(strlen(itr->name)));
                
                strcpy(iterator->leaf_token->lexeme, itr->name);
                iterator->leaf_token->token = ID;
                iterator->symbol_table_node = itr->symbol;

                // printf("%s\n", iterator->leaf_token->lexeme);
                

                Temporary temp_arr = evaluate_array(node->child, iterator, list, parent_scope);
                // printf("HI\n");
                Tuple new_tup4 = make_tuple(WRITE, "", "", temp_arr->name, NULL, NULL, temp_arr->symbol);
                add_tuple(list, new_tup4);

                

                Temporary temp0 = create_temporary();
                add_temp_symboltable(temp0->symbol, parent_scope, 2);

                Tuple new_tup5 = make_tuple(ADDITION, itr->name, "1", temp0->name, itr->symbol, NULL, temp0->symbol);
                add_tuple(list, new_tup5);

                Tuple new_tup6 = make_tuple(COPY, temp0->name, "", itr->name, temp0->symbol, NULL, itr->symbol);
                add_tuple(list, new_tup6);

                Tuple new_tup7 = make_tuple(GOTO, label1, "", "", NULL, NULL, NULL);
                add_tuple(list, new_tup7);

                // OUTSIDE FOR
                label_tup = make_tuple(LABEL, "", "", label3, NULL, NULL, NULL);
                add_tuple(list, label_tup);
                
                return 1;
            }
        }
    }

    if(node->rule_num == 59 && node->tag == 1) {
        int op_exists = node->child->tag;
        
        AST input = node->child->next;
        AST output = node->child;
        AST fun_name = node->child;

        if(op_exists) {
            input = input->next;
            fun_name = fun_name->next;
        }

        while(input) {
            Tuple label_tup = make_tuple(PARAM, "", "", input->child->leaf_token->lexeme, NULL, NULL, input->child->symbol_table_node);
            add_tuple(list, label_tup);

            input = input->child->next;
        }

        while(op_exists && output) {
            Tuple label_tup = make_tuple(PARAM_OP, "", "", output->child->leaf_token->lexeme, NULL, NULL, output->child->symbol_table_node);
            add_tuple(list, label_tup);

            output = output->child->next;
        }

        Tuple new_tup = make_tuple(CALL, "", "", fun_name->leaf_token->lexeme, NULL, NULL, NULL);
        add_tuple(list, new_tup);

        return 1;    
    }

    return 0;
}

Temporary evaluate_expression(AST node, tuple_list* list, Symbol_Table_Tree parent_scope) {

    if(node == NULL) {
        return NULL;
    }

    if(node->tag == 0) {
        Temporary node_t = create_temporary();

        int width = 1;
        if(node->leaf_token->token == NUM)
            width = 2;
        else if(node->leaf_token->token == RNUM)
            width = 8;

        add_temp_symboltable(node_t->symbol, parent_scope, width);

        Tuple new_tuple = make_tuple(COPY, node->leaf_token->lexeme, "", node_t->name, NULL, NULL, node_t->symbol);
        add_tuple(list, new_tuple);

        return node_t;
    }

    if(node->rule_num == 42 && node->tag == 1 && node->child->leaf_token->token == ID) {

        if(node->child->symbol_table_node->datatype != 3) {
        
            Temporary node_t = create_temporary();
            int width = node->child->symbol_table_node->width;
            add_temp_symboltable(node_t->symbol, parent_scope, width);
            
            // COPY: arg1 = node->name, arg2 = empty, result = temp
            Tuple new_tuple = make_tuple(COPY, node->child->leaf_token->lexeme, "", node_t->name, node->child->symbol_table_node, NULL, node_t->symbol);
            add_tuple(list, new_tuple);
            
            return node_t;
        }
        else {
            /*
            a = arr[i]
            to deal with this
            mul i width t0
            plus arr t0 t1 
            mem_read t1 t2
            return t2
            or 

            arr1 = arr2
            for i in [arr2.range0...arr2.range1]
              arr1[i] = arr2[i]

            basically execute the for loop
            */

           if(node->child->next && node->child->next->tag == 0) {
                Temporary temp0 = evaluate_array(node->child, node->child->next, list, parent_scope);
                int width = 0;
                if(node->child->symbol_table_node->array_datatype == 0)
                    width = 2;
                else if(node->child->symbol_table_node->array_datatype == 1)
                    width = 8;
                else if(node->child->symbol_table_node->array_datatype == 2)
                    width = 1;

                Temporary temp1 = create_temporary();
                add_temp_symboltable(temp1->symbol, parent_scope, width);
                Tuple new_tup = make_tuple(MEM_READ, temp0->name, "", temp1->name, temp0->symbol, NULL, temp1->symbol);
                
                add_tuple(list, new_tup);
                return temp1;
           }
        }
    }

    if(node->label == EXPRESSION) {

        // hardcoding case where a = - (5)
        // to optimize code

        if(node->child->next->tag == 0) {
            Temporary node_t = create_temporary();

            int width = 0;
            Symbol_Node* arg1 = NULL;
            if(node->child->next->leaf_token->token == NUM) {
                width = 2;
            }
            else if(node->child->next->leaf_token->token == RNUM) {
                width = 8;
            }
            else if(node->child->next->leaf_token->token == ID) {
                width = node->child->next->symbol_table_node->width;
                arg1 = node->child->next->symbol_table_node;
            }
            add_temp_symboltable(node_t->symbol, parent_scope, width);

            Tuple new_tuple = make_tuple(MULTIPLY, node->child->next->leaf_token->lexeme, "-1", node_t->name, arg1, NULL, node_t->symbol);
            add_tuple(list, new_tuple);

            return node_t;
        }

        // more optimization possible
        Temporary temp1 = evaluate_expression(node->child->next, list, parent_scope);
        
        if(node->child->leaf_token->token == PLUS)
            return temp1;

        Temporary node_t = create_temporary();
        int width = temp1->symbol->width;
        add_temp_symboltable(node_t->symbol, parent_scope, width);

        Tuple new_tuple = make_tuple(MULTIPLY, temp1->name, "-1", node_t->name, temp1->symbol, NULL, node_t->symbol);
        add_tuple(list, new_tuple);

        return node_t;
    }

    if(node->label == NEW6 || node->label == NEW7 || node->label == RELATIONAL_EXPR || node->label == NEW8) {
        
        Symbol_Node* arg1 = NULL, *arg2 = NULL;
        AST node1 = NULL, node2 = NULL;
        int width = 0;
        Temporary lhs, rhs;
        
        if(node->child->next->tag == 1 && node->child->next->label == VAR && node->child->next->child->symbol_table_node->datatype !=3) {
            node1 = node->child->next->child;
            arg1 = node1->symbol_table_node;
            width = arg1->width;
        }
        else if(node->child->next->tag == 0) {
            node1 = node->child->next;
            if(node1->leaf_token->token == NUM)
                width = 2;
            else if(node1->leaf_token->token == RNUM)
                width = 8;
            else if(node1->leaf_token->token == TRUE || node1->leaf_token->token == FALSE)
                width = 1;
        }
        else {
            lhs = evaluate_expression(node->child->next, list, parent_scope);
            arg1 = lhs->symbol;
            width = arg1->width;
        }

        if(node->child->next->next->tag == 1 && node->child->next->next->label == VAR && node->child->next->next->child->symbol_table_node->datatype !=3) {
            node2 = node->child->next->next->child;
            arg2 = node2->symbol_table_node;
        }
        else if(node->child->next->next->tag == 0) {
            node2 = node->child->next->next;
        }
        else {
            rhs = evaluate_expression(node->child->next->next, list, parent_scope);
            arg2 = rhs->symbol;
        }
        
        Temporary node_t = create_temporary();
        if(node->label == RELATIONAL_EXPR || node->label == NEW8) {
            width = 1;
        }

        add_temp_symboltable(node_t->symbol, parent_scope, width);
        
        tokens sign = node->child->leaf_token->token;
        oper op;
        if(sign == PLUS)
            op = ADDITION;
        else if(sign == MINUS)
            op = SUBTRACTION;
        else if(sign == MUL)
            op = MULTIPLY;
        else if(sign == DIV)
            op = DIVIDE;
        else if(sign == GT)
            op = GREATER;
        else if(sign == GE)
            op = GREATER_EQUAL;
        else if(sign == LT)
            op = LESS;
        else if(sign == LE)
            op = LESS_EQUAL;
        else if(sign == EQ)
            op = EQUAL;
        else if(sign == NE)
            op = NOT_EQUAL;
        else if(sign == AND)
            op = BOOLEAN_AND;
        else if(sign == OR)
            op = BOOLEAN_OR;
        
        Tuple new_tuple;
        if(node1==NULL && node2==NULL) {
            new_tuple = make_tuple(op, lhs->name, rhs->name, node_t->name, arg1, arg2, node_t->symbol);
        }
        else if(node1==NULL && node2 != NULL) {
            new_tuple = make_tuple(op, lhs->name, node2->leaf_token->lexeme, node_t->name, arg1, arg2, node_t->symbol);
        }
        else if(node1!=NULL && node2==NULL) {
            new_tuple = make_tuple(op, node1->leaf_token->lexeme, rhs->name, node_t->name, arg1, arg2, node_t->symbol);
        }
        else if(node1 != NULL && node2!=NULL) {
            new_tuple = make_tuple(op, node1->leaf_token->lexeme, node2->leaf_token->lexeme, node_t->name, arg1, arg2, node_t->symbol);
        }
        
        add_tuple(list, new_tuple);

        return node_t;
    }

    Temporary test_node = create_temporary();
    strcpy(test_node->name, "CASE MISSED");
    return test_node;
}

char* get_limit(AST node, int id) {
    char* name = (char*) malloc(sizeof(char)*5);

    // id = 0 for low, 1 for high

    if(node->symbol_table_node->range[id].tag == 0) {
        sprintf(name, "%d", node->symbol_table_node->range[id].range_pointer.value);
    }
    else {
        strcpy(name, node->symbol_table_node->range[id].range_pointer.id->node->leaf_token->lexeme);
    }

    return name;
}

Temporary evaluate_array(AST node, AST index, tuple_list* list, Symbol_Table_Tree parent_scope) {

    int width = 0;
    if(node->symbol_table_node->array_datatype == 0)
        width = 2;
    else if(node->symbol_table_node->array_datatype == 1)
        width = 8;
    else if(node->symbol_table_node->array_datatype == 2)
        width = 1;

    char* str_width = (char*) malloc(sizeof(char) * 2);
    sprintf(str_width, "%d", width);
    
    Temporary temp0 = create_temporary();
    add_temp_symboltable(temp0->symbol, parent_scope, 2);

    Temporary temp1 = create_temporary();
    add_temp_symboltable(temp1->symbol, parent_scope, 2);

    Symbol_Node* arg1 = NULL;
    if(index->leaf_token->token == ID) {
        arg1 = index->symbol_table_node;
    }
    
    // subtract current index from lower index
    Tuple new_tup0;
    if(node->symbol_table_node->range[0].tag == 0) {
        char* li = (char*) malloc(sizeof(char)*4);
        sprintf(li, "%d", node->symbol_table_node->range[0].range_pointer.value);
        new_tup0 = make_tuple(SUBTRACTION, index->leaf_token->lexeme, li, temp0->name, arg1, NULL, temp0->symbol);
    }
    else if(node->symbol_table_node->range[0].tag == 1) {
        new_tup0 = make_tuple(SUBTRACTION, index->leaf_token->lexeme, node->symbol_table_node->range[0].range_pointer.id->node->leaf_token->lexeme, temp0->name, arg1, 
        node->symbol_table_node->range[0].range_pointer.id, temp0->symbol);
    }
    

    Tuple new_tup1 = make_tuple(MULTIPLY, temp0->name, str_width, temp1->name, temp0->symbol, NULL, temp1->symbol);

    Temporary temp2 = create_temporary();
    add_temp_symboltable(temp2->symbol, parent_scope, 2);
    Tuple new_tup2 = make_tuple(ADDITION, node->leaf_token->lexeme, temp1->name, temp2->name, node->symbol_table_node, temp1->symbol, temp2->symbol);
    // printf("HI\n");
    add_tuple(list, new_tup0);
    add_tuple(list, new_tup1);
    add_tuple(list, new_tup2);
    // printf("HI\n");
    return temp2;
}