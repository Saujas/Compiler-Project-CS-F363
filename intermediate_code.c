#include "intermediate_code.h"
#include "symbol_table.h"

char* operator_string_map[OPERATOR_SIZE] = {
    "COPY", "ADD", "SUB", "MUL", "DIV", "MEM_READ", "MEM_WRITE", "GT",
    "GE", "LT", "LE", "EQ", "NE", "AND", "OR"
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
    printf("OP: %-4s:\tArg1: %-4s\tArg2: %-4s\tResult: %-4s\n", operator_string_map[t->op], t->arg1, t->arg2, t->result);
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

    AST child = node->child;

    while(child) {
        generate_ir_util(child, list);
        child = child->next;
    }

    process_node(node, list);
    return;
}

void process_node(AST node, tuple_list* list) {

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
            char *empty = "";
            Tuple new_tup = make_tuple(op, node_t->name, empty, node->child->leaf_token->lexeme, node_t->symbol, NULL, node3);
            add_tuple(list, new_tup);
        }
    }
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
               return evaluate_array(node->child, list, parent_scope);
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
        Temporary lhs = evaluate_expression(node->child->next, list, parent_scope);
        Temporary rhs = evaluate_expression(node->child->next->next, list, parent_scope);

        Temporary node_t = create_temporary();
        int width = 0;
        if(node->label == RELATIONAL_EXPR || node->label == NEW8) {
            width = 1;
        }
        else {
            width = lhs->symbol->width;
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

        Tuple new_tuple = make_tuple(op, lhs->name, rhs->name, node_t->name, lhs->symbol, rhs->symbol, node_t->symbol);
        add_tuple(list, new_tuple);

        return node_t;
    }

    Temporary test_node = create_temporary();
    strcpy(test_node->name, "CASE MISSED");
    return test_node;
}

Temporary evaluate_array(AST node, tuple_list* list, Symbol_Table_Tree parent_scope) {
    AST index = node->next;

    int width = 0;
    if(node->symbol_table_node->array_datatype == 0)
        width = 2;
    else if(node->symbol_table_node->array_datatype == 1)
        width = 4;
    else if(node->symbol_table_node->array_datatype == 2)
        width = 1;

    char* str_width = (char*) malloc(sizeof(char) * 2);
    sprintf(str_width, "%d", width);

    Temporary temp1 = create_temporary();
    add_temp_symboltable(temp1->symbol, parent_scope, 2);

    Symbol_Node* arg1 = NULL;
    if(index->leaf_token->token == ID) {
        arg1 = index->symbol_table_node;
    }

    Tuple new_tup1 = make_tuple(MULTIPLY, index->leaf_token->lexeme, str_width, temp1->name, arg1, NULL, temp1->symbol);

    Temporary temp2 = create_temporary();
    add_temp_symboltable(temp2->symbol, parent_scope, 2);
    Tuple new_tup2 = make_tuple(ADDITION, node->leaf_token->lexeme, temp1->name, temp2->name, node->symbol_table_node, temp1->symbol, temp2->symbol);

    Temporary temp3 = create_temporary();
    add_temp_symboltable(temp3->symbol, parent_scope, width);
    Tuple new_tup3 = make_tuple(MEM_READ, temp2->name, "", temp3->name, temp2->symbol, NULL, temp3->symbol);

    add_tuple(list, new_tup1);
    add_tuple(list, new_tup2);
    add_tuple(list, new_tup3);

    return temp3;
}