#include "intermediate_code.h"
#include "symbol_table.h"

char* operator_string_map[OPERATOR_SIZE] = {
    "COPY", "ADD", "SUB", "MUL", "DIV", "MEM_READ", "MEM_WRITE", "GT",
    "GE", "LT", "LE", "EQ", "NE", "AND", "OR", "LABEL", "IF_TRUE", "IF_FALSE", "GOTO"
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

        if(node->child->next->label == CASE_STMT_T || node->child->next->label == CASE_STMT_F) {
            char* str[2] = {"true", "false"};
            int key;
            if(node->child->next->label == CASE_STMT_T) {
                key = 0;
            }
            else {
                key = 1;
            }

            char* label1 = create_label();
            char* label2 = create_label();

            Temporary t0 = create_temporary();
            add_temp_symboltable(t0->symbol, parent_scope, 1);
            Tuple new_tup0 = make_tuple(EQUAL, id->leaf_token->lexeme, str[key], t0->name, id->symbol_table_node, NULL, t0->symbol);
            add_tuple(list, new_tup0);

            Tuple new_tup1 = make_tuple(IF_TRUE, t0->name, "", label1, t0->symbol, NULL, NULL);
            add_tuple(list, new_tup1);
            Tuple new_tup2 = make_tuple(IF_FALSE, t0->name, "", label2, t0->symbol, NULL, NULL);
            add_tuple(list, new_tup2);

            Tuple new_tup3 = make_tuple(LABEL, "", "", label1, NULL, NULL, NULL);
            add_tuple(list, new_tup3);

            generate_ir_util(node->child->next->child, list);

            Tuple new_tup4 = make_tuple(GOTO, "", "", label_end, NULL, NULL, NULL);
            add_tuple(list, new_tup4);
            
            Tuple new_tup5 = make_tuple(LABEL, "", "", label2, NULL, NULL, NULL);
            add_tuple(list, new_tup5);

            generate_ir_util(node->child->next->child->next, list);

            Tuple new_tup9 = make_tuple(LABEL, "", "", label_end, NULL, NULL, NULL);
            add_tuple(list, new_tup9);

            return 1;
        }
        else {

            AST temp = node->child->next;

            while(temp->label != AST_DEFAULT) {
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
    }

    return 0;
}

Temporary evaluate_expression(AST node, tuple_list* list, Symbol_Table_Tree parent_scope) {

    if(node == NULL) {
        return NULL;
    }

    if(node->tag == 0) {
        Temporary node_t = create_temporary();

        int width = 0;
        if(node->leaf_token->token == NUM)
            width = 2;
        else if(node->leaf_token->token == RNUM)
            width = 4;

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
                    width = 4;
                else if(node->child->symbol_table_node->array_datatype == 2)
                    width = 1;

                Temporary temp1 = create_temporary();
                add_temp_symboltable(temp1->symbol, parent_scope, width);
                Tuple new_tup = make_tuple(MEM_READ, temp0->name, "", temp1->name, temp0->symbol, NULL, temp1->symbol);
                
                add_tuple(list, new_tup);
                return temp1;
           }
           else {
               // to be completed
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
                width = 4;
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
                width = 4;
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

Temporary evaluate_array(AST node, AST index, tuple_list* list, Symbol_Table_Tree parent_scope) {

    int width = 0;
    if(node->symbol_table_node->array_datatype == 0)
        width = 2;
    else if(node->symbol_table_node->array_datatype == 1)
        width = 4;
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
    else if(node->symbol_table_node->range[1].tag == 0) {
        new_tup0 = make_tuple(SUBTRACTION, index->leaf_token->lexeme, node->symbol_table_node->range[1].range_pointer.id->node->leaf_token->lexeme, temp0->name, arg1, 
        node->symbol_table_node->range[1].range_pointer.id, temp0->symbol);
    }

    Tuple new_tup1 = make_tuple(MULTIPLY, temp0->name, str_width, temp1->name, temp0->symbol, NULL, temp1->symbol);

    Temporary temp2 = create_temporary();
    add_temp_symboltable(temp2->symbol, parent_scope, 2);
    Tuple new_tup2 = make_tuple(ADDITION, node->leaf_token->lexeme, temp1->name, temp2->name, node->symbol_table_node, temp1->symbol, temp2->symbol);

    add_tuple(list, new_tup0);
    add_tuple(list, new_tup1);
    add_tuple(list, new_tup2);

    return temp2;
}