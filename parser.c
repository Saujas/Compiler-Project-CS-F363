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
            printf("%s --> ", non_terminals_string_map[i]);
            symbol* symbols = temp->rule;
            int j;
            for(j=0; j<(temp->count_of_symbols); j++) {
                symbol res = symbols[j];
                if(res.tag == 0) {
                    printf("%s ", token_string_map[res.sym.terminal]);
                }
                else {
                    printf("%s ", non_terminals_string_map[res.sym.non_terminal]);
                }
            }
            printf("\n");
            temp = temp->next;
        }

        printf("\n");
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


// int main_parser(char* filename) {
//     Node ** token_stream;
//     lookup_table *table;
//     parse_token_stream(filename, token_stream, table);
//     read_grammar("grammar.txt");
// }