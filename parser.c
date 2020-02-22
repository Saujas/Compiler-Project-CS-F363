#include "parser.h"
#include "lexer.h"
#include "tree.h"

rules* grammar[NON_TERMINAL_SIZE];
rules parse_table[NON_TERMINAL_SIZE][TOKEN_NUMBERS];
first_set all_first_sets[NON_TERMINAL_SIZE];
follow_set all_follow_sets[NON_TERMINAL_SIZE];
stack* Stack;
t_node* parse_tree;

char * token_string_map[TOKEN_NUMBERS] = {"INTEGER", "REAL", "BOOLEAN", "OF", "ARRAY", "START",
            "END", "DECLARE", "MODULE", "DRIVER", "PROGRAM", "GET_VALUE", "PRINT",
            "USE", "WITH", "PARAMETERS", "TRUE", "FALSE", "TAKES", "INPUT", "RETURNS",
            "AND", "OR", "FOR", "IN", "SWITCH", "CASE", "BREAK", "DEFAULT", "WHILE", "PLUS", 
            "MINUS", "MUL", "DIV", "LT", "LE", "GE", "GT", "EQ", "NE", "DEF", "DRIVERDEF",
            "ENDDEF", "DRIVERENDDEF", "COLON", "RANGEOP", "SEMICOL", "COMMA", "ASSIGNOP", 
            "SQBO", "SQBC", "BO", "BC", "COMMENTMARK", "NUM", "RNUM", "ID", "ERROR", "E", "$"
};

char * non_terminals_string_map[NON_TERMINAL_SIZE] = {"program", "moduleDeclarations", "moduleDeclaration", "otherModules", "driverModule", "module", "ret", "input_plist",
    "new1", "output_plist", "new2", "dataType", "dataType2", "type", "range", "range2", "moduleDef", "statements", "new3",
    "statement", "ioStmt", "var", "var2", "whichID", "simpleStmt", "assignmentStmt", "whichStmt", "lvalueIDstmt", "lvalueArrStmt", 
    "Index", "moduleReuseStmt", "optional", "idList", "newX", "expression", "new4", "AorBExpr", "arithmeticExpr", "new6",
    "term", "new7", "factor", "PlusMinus", "MulDiv", "relationalOP", "logicalOP", "boolKey", "boolExpr", "new8", "relationalExpr",
    "declareStmt", "iterativeStmt", "conditionalStatement", "caseStmt", "numericCases", 
    "numericCase", "new11", "Default"};

int parser(char* filename) {
    
    Node ** token_stream;
    lookup_table *table;
    int tokens_parsed = lexical_analyzer(filename, &token_stream, &table);

    // printf("*******************Lexical Analyzer Output: **********************\n");
    int i;
    int flag = 0;
    for(i=0; i<tokens_parsed; i++) {
        Node * n = token_stream[i];
        if(n->token==ERROR) {
            // if(strlen(n->lexeme)>20)
            //     printf("Error on line number %d: %s (Length of identifier cannot exceed 20)\n", n->line_no, n->lexeme);
            // else
            //     printf("Error on line number %d: %s\n", n->line_no, n->lexeme);
            flag = 1;            
        }
        // else if(n->tag==0) {
        //     printf("Token: %s\t", token_string_map[n->token]);
        //     printf("Lexeme: %s\t", n->lexeme);
        //     printf("Line number: %d\t\n", n->line_no);
        // }
        // else if(n->tag==1){
        //     printf("Token: %s\t", token_string_map[n->token]);
        //     printf("Value: %d\t", n->val.num);
        //     printf("Line number: %d\t\n", n->line_no);
        // }
        // else {
        //     printf("Token: %s\t", token_string_map[n->token]);
        //     printf("Value: %f\t", n->val.rnum);
        //     printf("Line number: %d\t\n", n->line_no);
        // }
    }

    read_grammar(GRAMMAR_FILE);
    find_first_sets();
    find_follow_sets();
    compute_parse_table();

    int parsed = parse_tokens(token_stream, tokens_parsed);
    printf("Parsed: %d\n\n", parsed);
    // inorder_traversal(parse_tree);

    return 1;
}

int parse_tokens(Node** token_stream, int tokens_parsed) {
    int ct = 0;
    int flag2 = 0;
    /* ERROR HANDLING
        1. If terminals do not match
        2. If corresponding to a non terminal, there is an error entry in the parse table
        3. If stack becomes empty before end of input
        4. If input becomes empty before end of stack, need to check if rest of the stack symbols derive E
    */

    parse_tree = initialize_tree();
    Stack = initialize_stack();
    while(!is_empty(Stack)) {
        
        stack_ele current_top = peek(Stack);
        tokens c_token;
        int c_line;
        Node* n;
        if(ct == tokens_parsed) {
            c_token = $;
        }
        else {
            n = token_stream[ct];
            c_token = n->token;
            c_line = n->line_no;
        }

        if(c_token==ERROR) {
            if(strlen(n->lexeme)>20)
                printf("\tLexical error on line number %d: %s (Length of identifier cannot exceed 20)\n", n->line_no, n->lexeme);
            else
                printf("\tLexical error on line number %d: %s\n", n->line_no, n->lexeme);
            ct++;
            printf("\n");
            continue;
        }

        if( current_top.sym.tag == 1) {
            rules r = parse_table[current_top.sym.sym.non_terminal][c_token];
            int j;
            
            if(r.count_of_symbols == -1) {
                flag2 = 1;
                follow_set fs = all_follow_sets[current_top.sym.sym.non_terminal];
                int k;
                int flag = 0;
                for(k=0; k<fs.count; k++) {
                    if(c_token == fs.follow_set_token[k]) {
                        flag = 1;
                        pop(&Stack);
                        break;
                    }
                }
                if(flag) {
                    printf("\tSyntax error on line number %d: %s\n\n", c_line, token_string_map[c_token]);
                    continue;
                }
                else {
                    printf("\tSyntax error on line number %d: %s\n\n", c_line, token_string_map[c_token]);
                    ct++;
                    continue;
                }
            }
            
            else {
                pop(&Stack);
                t_node* parent = current_top.ptr;

                printf("%s --> ", non_terminals_string_map[current_top.sym.sym.non_terminal]);
                for(j=r.count_of_symbols-1; j>=0; j--) {
                    symbol c_sym = r.rule[j];
                    if(r.rule[r.count_of_symbols - j - 1].tag == 0)
                        printf("%s ", token_string_map[r.rule[r.count_of_symbols - j -1].sym.terminal]);
                    else
                        printf("%s ", non_terminals_string_map[r.rule[r.count_of_symbols - j -1].sym.non_terminal]);
                    if((c_sym.tag == 0) && (c_sym.sym.terminal == E)) {
                        t_node* new_tn;
                        Node n1 = *n;
                        n1.token = E;
                        strcpy(n1.lexeme, "E");
                        new_tn = create_leaf(n1);
                        insert_node(&parent, new_tn);
                        continue;
                    }
                    else {
                        t_node* new_tn;
                        if(c_sym.tag == 1) {
                            new_tn = create_internal(c_sym.sym.non_terminal);
                            // printf("\nNon terminal node: %s, Parent: %s\n", non_terminals_string_map[c_sym.sym.non_terminal], non_terminals_string_map[parent->node.internal]);
                        }
                        else {
                            Node n1;
                            n1.token = c_sym.sym.terminal;
                            new_tn = create_leaf(n1);
                            // printf("\nTerminal Node: %s, Parent: %s\n", token_string_map[new_tn->node.leaf.token], non_terminals_string_map[parent->node.internal]);
                        }
                        insert_node(&parent, new_tn);
                        stack_ele new_ele;
                        new_ele.sym = c_sym;
                        new_ele.ptr = new_tn;
                        push(&Stack, new_ele);
                    }
                }

                printf("\n\n");
            }
        }

        else {
            if( current_top.sym.sym.terminal == n->token) {
                stack_ele ele = pop(&Stack);
                ele.ptr->node.leaf.tag = n->tag;
                strcpy(ele.ptr->node.leaf.lexeme, n->lexeme);
                ele.ptr->node.leaf.line_no = n->line_no;
                // printf("Symbol Matched: %s\n", token_string_map[current_top.sym.terminal]);
                ct++;
            }
            else {
                flag2 = 1;
                printf("\tSyntax error on line number %d: %s\n\n", c_line, token_string_map[c_token]);
                pop(&Stack);
            }
        }
    }
    
    int parsed = (is_empty(Stack)) && (ct == tokens_parsed) && (!flag2);
    return parsed;
}


stack* initialize_stack() {
    stack* st = create_stack();
    symbol s1;
    s1.sym.non_terminal = program;
    s1.tag = 1;
    stack_ele top_ele;
    top_ele.sym = s1;
    top_ele.ptr = parse_tree;

    push(&st, top_ele);
    return st;
}

int read_grammar(char* filename) {
    FILE* fp = fopen(filename, "r");

    if( fp == NULL) {
        printf("Error in opening file\n");
        exit(0);
    }

    int i;
    for(i=0; i<NON_TERMINAL_SIZE; i++) {
        grammar[i] = NULL;
    }

    char buf[MAX_RULE_LENGTH];
    char * token, *nt;
    char* delim = " ";
    char** rule;

    while( fscanf(fp, "%[^\n]\n", buf) != EOF ) {
        // printf("%s\n", buf);
        token = strtok(buf, delim);
        nt = (char *) malloc(sizeof(char) * strlen(token));
        strcpy(nt, token);
        
        token = strtok(NULL, delim);
        rule = (char ** ) malloc(sizeof(char*));
        int count = 0;       
        while(token != NULL) {
            rule[count] = (char *) malloc(sizeof(char) * strlen(token));
            rule[count] = token;
            
            token = strtok(NULL, delim);
            count++;
            rule = (char**) realloc(rule, sizeof(char *) * (count+1));
        }

        symbol lhs = convert_to_symbol(nt);

        symbol rhs[count];
        for(i=0; i<count; i++) {
            rhs[i] = convert_to_symbol(rule[i]);
            if(rhs[i].tag == 0) {
                // printf("%s:%s ", rule[i], token_string_map[rhs[i].sym.terminal]);
            }
            else {
                // printf("%s:%s ", rule[i], non_terminals_string_map[rhs[i].sym.non_terminal]);
            }
        }

        addRule(grammar, rhs, lhs, count);
    }

    for(i=0; i<NON_TERMINAL_SIZE; i++) {
        
        rules* temp = grammar[i];
        while(temp) {
            // printf("%s --> ", non_terminals_string_map[i]);
            symbol* symbols = temp->rule;
            int j;
            for(j=0; j<(temp->count_of_symbols); j++) {
                symbol res = symbols[j];
                // if(res.tag == 0) {
                //     printf("%s ", token_string_map[res.sym.terminal]);
                // }
                // else {
                //     printf("%s ", non_terminals_string_map[res.sym.non_terminal]);
                // }
            }
            // printf("\n");
            temp = temp->next;
        }
        // printf("\n");
    }
    fclose(fp);
}

symbol convert_to_symbol(char* str) {
    symbol res;

    int i;
    for(i=0; i<NON_TERMINAL_SIZE; i++) {
        if(strcmp(str, non_terminals_string_map[i])==0) {
            res.sym.non_terminal = i;
            res.tag = 1;
            return res;
        }
    }

    for(i=0; i<TOKEN_NUMBERS; i++) {
        if(strcmp(str, token_string_map[i]) == 0) {
            res.sym.terminal = i;
            res.tag = 0;
            return res;
        }
    }

    return res;
}

int addRule(rules** grammar, symbol* rule, symbol nt, int count) {
    
    rules* new_rule = (rules*) malloc(sizeof(rules));
    new_rule->next = NULL;new_rule->count_of_symbols = count;
    new_rule->rule = (symbol*) malloc(sizeof(symbol)*count);

    int i;
    for(i=0; i<count; i++) {
        new_rule->rule[i] = rule[i];
    }
    
    if(grammar[nt.sym.non_terminal] == NULL) {
        grammar[nt.sym.non_terminal] = new_rule;
    }
    else {
        rules* temp = grammar[nt.sym.non_terminal];
        while(temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = new_rule;
    }

    return 1;
}

int compute_parse_table() {

    int i, j;
    for(i=0; i<NON_TERMINAL_SIZE; i++) {
        for(j=0; j<TOKEN_NUMBERS; j++) {
            parse_table[i][j].rule=NULL;
            parse_table[i][j].next=NULL;
            parse_table[i][j].count_of_symbols=-1;
        }
    }
    for(i=0; i<NON_TERMINAL_SIZE; i++) {
        rules *temp = grammar[i];
        while(temp) {

            first_set fs = find_first_set_rule(temp->rule, temp->count_of_symbols);
            int k;
            int flag = 0;
            for(k=0; k<fs.count; k++) {
                if(fs.first_set_token[k]==E) {
                    flag = 1;
                    continue;
                }
                parse_table[i][fs.first_set_token[k]].rule = temp->rule;
                parse_table[i][fs.first_set_token[k]].count_of_symbols = temp->count_of_symbols;
            }
            if(flag) {
                follow_set fs = all_follow_sets[i];
                int l;
                for(l=0; l<fs.count; l++) {
                    parse_table[i][fs.follow_set_token[l]].rule = temp->rule;
                    parse_table[i][fs.follow_set_token[l]].count_of_symbols = temp->count_of_symbols;
                }
            }
            // printf("%s --> ", non_terminals_string_map[i]);
            // for(j = 0; j<fs.count; j++) {
            //     printf("%s ", token_string_map[fs.first_set_token[j]]);
            // }
            // printf("\n");
            temp = temp->next;
        }
    }

    // print_parse_table();

    return 1;
}

int print_parse_table() {
    int i, j;
    for(i=0; i<NON_TERMINAL_SIZE; i++) {
        printf("%s: \n", non_terminals_string_map[i]);
        for(j=0; j<TOKEN_NUMBERS; j++) {
            rules r = parse_table[i][j];
            if(r.count_of_symbols == -1) {
                // printf("%s: Error\n", token_string_map[j]);
            }
            else {
                int k;
                printf("\t%s: %s --> ", token_string_map[j], non_terminals_string_map[i]);
                for(k=0; k<r.count_of_symbols; k++) {
                    symbol sym = r.rule[k];
                    if(sym.tag == 1)
                        printf("%s ", non_terminals_string_map[sym.sym.non_terminal]);
                    else
                        printf("%s ", token_string_map[sym.sym.terminal]);
                }
                printf("\n");
            }
        }
    }

    return 1;
}

first_set find_first_set_rule(symbol* rule, int count) {
    // printf("\n\n****\n\n");
    first_set fs_rule;
    fs_rule.first_set_token = NULL;
    fs_rule.count = 0;
    int i, flag = 0;
    for(i=0; i<count; i++) {

        symbol s = rule[i];

        if(s.tag == 0) {
            if(fs_rule.first_set_token == NULL) {
                fs_rule.count = 1;
                fs_rule.first_set_token = (tokens*) malloc(sizeof(tokens) * fs_rule.count);
            }
            else {
                fs_rule.count += 1;
                fs_rule.first_set_token = (tokens *) realloc(fs_rule.first_set_token, sizeof(tokens) * fs_rule.count);
            }

            fs_rule.first_set_token[fs_rule.count-1] = s.sym.terminal;
            break;
        }
        else {
            first_set nt1 = all_first_sets[rule[i].sym.non_terminal];
            int add_e = 0;
            if( i==(count-1))
                add_e = 1;
            flag = merge_first_first(&fs_rule, nt1, add_e);
            if(!flag) {
                break;
            }
        }
    }

    return fs_rule;
}


first_set compute_first_set(int nt) {
    if(all_first_sets[nt].first_set_token != NULL) {
        return all_first_sets[nt];
    }

    rules* temp = grammar[nt];
    first_set current_set = all_first_sets[nt];

    while(temp) {
    
        symbol* res = temp->rule;

        if((res[0].tag==0) && !check_if_duplicate_first(current_set, res[0].sym.terminal)) {

            if(current_set.first_set_token == NULL) {
                current_set.first_set_token = (tokens *) malloc(sizeof(tokens));
                current_set.count = 1;
            }
            else {
                current_set.count += 1;
                current_set.first_set_token = (tokens *) realloc(current_set.first_set_token, sizeof(tokens)*current_set.count);
            }

            current_set.first_set_token[current_set.count-1] = res[0].sym.terminal;
        }
        
        else if(res[0].tag == 1) {

            int j, flag=0;
            for(j=0; j<(temp->count_of_symbols); j++) {

                if(res[j].tag == 1) {
                    first_set new_fs = compute_first_set(res[j].sym.non_terminal);

                    int add_e = (j == temp->count_of_symbols - 1);
                    flag = merge_first_first(&current_set, new_fs, add_e);
                    
                    if(!flag)
                        break;
                }
                else {
                    if(!check_if_duplicate_first(current_set, res[j].sym.terminal)) {
                        if(current_set.first_set_token == NULL) {
                            current_set.first_set_token = (tokens *) malloc(sizeof(tokens));
                            current_set.count = 1;
                        }
                        else {
                            current_set.count += 1;
                            current_set.first_set_token = (tokens *) realloc(current_set.first_set_token, sizeof(tokens)*current_set.count);
                        }

                        current_set.first_set_token[current_set.count-1] = res[j].sym.terminal;
                        break;
                    }
                }    
            }
        }

        temp = temp->next;
    }

    return current_set;
}

int find_first_sets() {
    int i;
    for(i=0; i<NON_TERMINAL_SIZE; i++) {
        all_first_sets[i] = compute_first_set(i);
    }

    // for(i=0; i<NON_TERMINAL_SIZE; i++) {
    //     int j;
    //     printf("%s --> ", non_terminals_string_map[i]);
    //     for(j=0; j<all_first_sets[i].count; j++) {
    //         printf("%s, ", token_string_map[all_first_sets[i].first_set_token[j]]);
    //     }
    //     printf("\n");
    // }
    // printf("%d, %s\n", grammar[new11]->count_of_symbols, non_terminals_string_map[grammar[new11]->rule[1].sym.non_terminal]);

    return 1;
}

follow_set compute_follow_set(int nt, int* changed) {

    follow_set current_set = all_follow_sets[nt];

    int i;
    for(i=0; i<NON_TERMINAL_SIZE; i++) {
        
        rules* temp_inner = grammar[i];
        while(temp_inner) {
            symbol* res = temp_inner->rule;
            
            int j;
            for(j=0; j<temp_inner->count_of_symbols; j++) {

                if(res[j].tag == 1 && res[j].sym.non_terminal==nt) {
                    
                    // printf("%s %s %d\n", non_terminals_string_map[nt], token_string_map[res[j+1].sym.terminal], check_if_exists(current_set, res[j+1].sym.terminal));
                    if(j != (temp_inner->count_of_symbols-1)) {

                        if((res[j+1].tag == 0) && !check_if_exists(current_set, res[j+1].sym.terminal)) {
                            if(current_set.follow_set_token == NULL) {
                                current_set.follow_set_token = (tokens *) malloc(sizeof(tokens));
                                current_set.count = 1;
                            }
                            else {
                                current_set.count += 1;
                                current_set.follow_set_token = (tokens *) realloc(current_set.follow_set_token, sizeof(tokens)*current_set.count);
                            }
                            current_set.follow_set_token[current_set.count-1] = res[j+1].sym.terminal;
                            *changed = 1;
                                                
                        }
                        else if(res[j+1].tag==1) {
                            int flag = 0;
                            for(; (j+1)<(temp_inner->count_of_symbols); j++) {

                                if(res[j+1].tag==1) {
                                    // printf("%s %s %s\n", non_terminals_string_map[nt], non_terminals_string_map[i],non_terminals_string_map[res[j+1].sym.non_terminal]);
                                    first_set new_fs = all_first_sets[res[j+1].sym.non_terminal];
                                    
                                    flag = 0;
                                    // printf("current: %d new_fs: %d\n", current_set.count, new_fs.count);
                                    *changed = max(*changed, merge_follow_first(&current_set, new_fs));

                                    int k3;
                                    for(k3=0; k3<new_fs.count; k3++) {
                                        tokens ctok = new_fs.first_set_token[k3];
                                        if(ctok == E) {
                                            flag = 1;
                                        }
                                    }
                                    
                                    if(!flag) {
                                        break;
                                    }
                                }

                                else {
                                    if(!check_if_exists(current_set, res[j+1].sym.terminal)) {
                                        if(current_set.follow_set_token == NULL) {
                                            current_set.follow_set_token = (tokens *) malloc(sizeof(tokens));
                                            current_set.count = 1;
                                        }
                                        else {
                                            current_set.count += 1;
                                            current_set.follow_set_token = (tokens *) realloc(current_set.follow_set_token, sizeof(tokens)*current_set.count);
                                        }
                                        current_set.follow_set_token[current_set.count-1] = res[j+1].sym.terminal;
                                        *changed = 1;
                                        break;
                                    }
                                }
                                
                            }

                            if(j==(temp_inner->count_of_symbols-1) && res[j].tag==1 && flag) {
                                follow_set new_fs = all_follow_sets[i];
                                *changed = max(*changed, merge_follow_follow(&current_set, new_fs));
                            }
                        }
                    }
                    else if(i==nt) {
                        continue;
                    }
                    else {

                        follow_set new_fs = all_follow_sets[i];
                        *changed = max(*changed, merge_follow_follow(&current_set, new_fs));
                    }
                }
            }
            temp_inner = temp_inner->next;
        }
    }
    return current_set;
}

int check_if_exists(follow_set current_set, tokens t) {
    int i, exists=0;
    for(i=0; i<current_set.count; i++) {
        if(t == current_set.follow_set_token[i]) {
            exists=1;
            break;
        }
    }

    return exists;
}

int check_if_duplicate_first(first_set current_set, tokens t) {
    int i, exists=0;
    for(i=0; i<current_set.count; i++) {
        if(t == current_set.first_set_token[i]) {
            exists=1;
            break;
        }
    }

    return exists;
}

int merge_first_first(first_set* current_set, first_set new_set, int add_e) {
    int empty_exists = 0, i;

    // printf("%d\n", new_set.count);

    if(new_set.first_set_token == NULL)
        return empty_exists;
    else {
        for(i=0; i<new_set.count; i++) {
            tokens new_token = new_set.first_set_token[i];
            if((new_token == E) && !add_e) {
                empty_exists = 1;
                continue;
            }

            if(!check_if_duplicate_first(*current_set, new_token)) {
                if(current_set->first_set_token == NULL) {
                    current_set->first_set_token = (tokens *)malloc(sizeof(tokens));
                    current_set->count = 1;
                }
                else {
                    current_set->count += 1;
                    current_set->first_set_token = (tokens*) realloc(current_set->first_set_token, sizeof(tokens) * current_set->count);
                }
                current_set->first_set_token[current_set->count-1] = new_token;
            }
        }
    }
    return empty_exists;
}

int merge_follow_first(follow_set* current_set, first_set new_set) {
    int changed = 0, i;
    if(new_set.first_set_token == NULL)
        return changed;

    else {
        for(i=0; i<new_set.count; i++) {
            tokens new_token = new_set.first_set_token[i];
            if(new_token == E)
                continue;

            if(!check_if_exists(*current_set, new_token)) {
                if(current_set->follow_set_token == NULL) {
                    current_set->follow_set_token = (tokens *)malloc(sizeof(tokens));
                    current_set->count = 1;
                }
                else {
                    current_set->count += 1;
                    current_set->follow_set_token = (tokens*) realloc(current_set->follow_set_token, sizeof(tokens) * current_set->count);
                }
                current_set->follow_set_token[current_set->count-1] = new_token;
                changed = 1;
            }
        }
    }
    return changed;
}

int merge_follow_follow(follow_set* current_set, follow_set new_set) {
    int changed = 0, i;
    if(new_set.follow_set_token == NULL)
        return changed;

    else {
        for(i=0; i<new_set.count; i++) {
            tokens new_token = new_set.follow_set_token[i];

            if(!check_if_exists(*current_set, new_token)) {
                if(current_set->follow_set_token == NULL) {
                    current_set->follow_set_token = (tokens *)malloc(sizeof(tokens));
                    current_set->count = 1;
                }
                else {
                    current_set->count += 1;
                    current_set->follow_set_token = (tokens*) realloc(current_set->follow_set_token, sizeof(tokens) * current_set->count);
                }
                current_set->follow_set_token[current_set->count-1] = new_token;
                changed = 1;
            }
        }
    }
    return changed;
}

int max(int a, int b) {
    return (a >= b ? a: b);
}

int find_follow_sets() {
    follow_set first;
    first.follow_set_token = (tokens*)malloc(sizeof(tokens));
    first.count = 1;
    first.follow_set_token[0] = $;
    all_follow_sets[0] = first;
    int i, changed = 0;
    while(1) {
        changed = 0;
        for(i=1; i<NON_TERMINAL_SIZE; i++) {
            all_follow_sets[i] = compute_follow_set(i, &changed);
        }
        if(!changed) {
            break;
        }
    }
    // printf("Done\n");
    // for(i=0; i<NON_TERMINAL_SIZE; i++) {
    //     int j;
    //     printf("%s --> ", non_terminals_string_map[i]);
    //     for(j=0; j<all_follow_sets[i].count; j++) {
    //         printf("%s, ", token_string_map[all_follow_sets[i].follow_set_token[j]]);
    //     }
    //     printf("\n");
    // }
}


// int main_parser(char* filename) {
//     Node ** token_stream;
//     lookup_table *table;
//     parse_token_stream(filename, token_stream, table);
//     read_grammar("grammar.txt");
// }