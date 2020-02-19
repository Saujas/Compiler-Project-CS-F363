#include "parser.h"
rules* grammar[NON_TERMINAL_SIZE];

char * token_string_map[TOKEN_NUMBERS] = {"INTEGER", "REAL", "BOOLEAN", "OF", "ARRAY", "START",
            "END", "DECLARE", "MODULE", "DRIVER", "PROGRAM", "GET_VALUE", "PRINT",
            "USE", "WITH", "PARAMETERS", "TRUE", "FALSE", "TAKES", "INPUT", "RETURNS",
            "AND", "OR", "FOR", "IN", "SWITCH", "CASE", "BREAK", "DEFAULT", "WHILE", "PLUS", 
            "MINUS", "MUL", "DIV", "LT", "LE", "GE", "GT", "EQ", "NE", "DEF", "DRIVERDEF",
            "ENDDEF", "ENDDRIVERDEF", "COLON", "RANGEOP", "SEMICOL", "COMMA", "ASSIGNOP", 
            "SQBO", "SQBC", "BO", "BC", "COMMENTMARK", "NUM", "RNUM", "ID", "ERROR", "E"
};

char * non_terminals_string_map[NON_TERMINAL_SIZE] = {"program", "moduleDeclarations", "moduleDeclaration", "otherModules", "driverModule", "module", "ret", "input_plist",
    "new1", "output_plist", "new2", "dataType", "dataType2", "type", "range", "range2", "moduleDef", "statements", "new3",
    "statement", "ioStmt", "var", "var2", "whichID", "simpleStmt", "assignmentStmt", "whichStmt", "lvalueIDstmt", "lvalueArrStmt", 
    "Index", "moduleReuseStmt", "optional", "idList", "newX", "expression", "new4", "AorBExpr", "arithmeticExpr", "new6",
    "term", "new7", "factor", "PlusMinus", "MulDiv", "relationalOP", "logicalOP", "boolKey", "boolExpr", "new8", "relationalExpr",
    "declareStmt", "iterativeStmt", "whileCondition", "new10", "new9", "newY", "conditionalStatement", "caseStmt", "numericCases", 
    "numericCase", "new11", "Default"};

int parse_token_stream(char* filename) {
    
    Node ** token_stream;
    lookup_table *table;
    int tokens_parsed = lexical_analyzer(filename, &token_stream, &table);

    // printf("*******************Lexical Analyzer Output: **********************\n");
    int i;
    for(i=0; i<tokens_parsed; i++) {
        Node * n = token_stream[i];

        // if(n->tag==0) {
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
    
    return 1;
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


first_set compute_first_set(int nt) {
    if(all_first_sets[nt].first_set_token != NULL) {
        return all_first_sets[nt];
    }

    rules* temp = grammar[nt];
    first_set current_set = all_first_sets[nt];

    while(temp) {
    
        symbol* res = temp->rule;

        if((res[0].tag==0)) {

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
        
        else {

            int j;
            for(j=0; j<(temp->count_of_symbols); j++) {

                if(res[j].tag == 1) {
                    first_set new_fs = compute_first_set(res[j].sym.non_terminal);

                    if(current_set.first_set_token == NULL) {
                        current_set.first_set_token = (tokens *) malloc(sizeof(tokens) * new_fs.count);
                        current_set.count = new_fs.count;
                    }
                    else {
                        current_set.count += new_fs.count;
                        current_set.first_set_token = (tokens *) realloc(current_set.first_set_token, sizeof(tokens) * current_set.count);
                    }

                    int k, flag=0;
                    for(k = (current_set.count-new_fs.count); k < (current_set.count); k++) {
                        
                        tokens ctok = new_fs.first_set_token[k-(current_set.count-new_fs.count)];

                        if(ctok == E && j!=(temp->count_of_symbols-1)) {
                            current_set.count -= 1;
                            flag = 1;
                        }
                        else { 
                            current_set.first_set_token[k] = ctok;
                        }
                    }
                    
                    if(!flag)
                        break;
                }
                else {
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

        temp = temp->next;
    }

    return current_set;
}

int find_first_sets() {
    int i;
    for(i=0; i<NON_TERMINAL_SIZE; i++) {
        all_first_sets[i] = compute_first_set(i);
    }

    for(i=0; i<NON_TERMINAL_SIZE; i++) {
        int j;
        printf("%s --> ", non_terminals_string_map[i]);
        for(j=0; j<all_first_sets[i].count; j++) {
            printf("%s, ", token_string_map[all_first_sets[i].first_set_token[j]]);
        }
        printf("\n");
    }
    // printf("%d, %s\n", grammar[new11]->count_of_symbols, non_terminals_string_map[grammar[new11]->rule[1].sym.non_terminal]);

    return 1;
}


// int main_parser(char* filename) {
//     Node ** token_stream;
//     lookup_table *table;
//     parse_token_stream(filename, token_stream, table);
//     read_grammar("grammar.txt");
// }