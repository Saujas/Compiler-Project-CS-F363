#include "lexer.h"

#define MAX_BUFFER_LENGTH 200
#define MAX_ID_LENGTH 20
#define MAX_RNUM_LENGTH 3 + DBL_MANT_DIG - DBL_MIN_EXP

char buffer[MAX_BUFFER_LENGTH];
char id[MAX_ID_LENGTH];
char number[MAX_RNUM_LENGTH];

int state = 0;

static int line_number = 1;
static int pointer = 0;
static int id_length = 0;
static int number_index = 0;

// char * token_string_map[TOKEN_NUMBERS] = {"INTEGER", "REAL", "BOOLEAN", "OF", "ARRAY", "START",
//             "END", "DECLARE", "MODULE", "DRIVER", "PROGRAM", "GET_VALUE", "PRINT",
//             "USE", "WITH", "PARAMETERS", "TRUE", "FALSE", "TAKES", "INPUT", "RETURNS",
//             "AND", "OR", "FOR", "IN", "SWITCH", "CASE", "BREAK", "DEFAULT", "WHILE", "PLUS", 
//             "MINUS", "MUL", "DIV", "LT", "LE", "GE", "GT", "EQ", "NE", "DEF", "DRIVERDEF",
//             "ENDDEF", "ENDDRIVERDEF", "COLON", "RANGEOP", "SEMICOL", "COMMA", "ASSIGNOP", 
//             "SQBO", "SQBC", "BO", "BC", "COMMENTMARK", "NUM", "RNUM", "ID", "ERROR"
// };

FILE* open_file(char* filename) {
    FILE* fp = fopen(filename, "r");

    if( fp == NULL) {
        printf("Error in opening file\n");
        exit(0);
    }

    return fp;
}

int string_flush(char *str) {
    int i;
    int len = strlen(str);
    for(i = 0; i<len; i++) {
        str[i] = '\0';
    }
    return 1;
}

int buffer_read(FILE* fp) {
    if(fp == NULL) {
        printf("Invalid file pointer\n");
        exit(0);
    }

    string_flush(buffer);

    int char_read = fread(buffer, (size_t)sizeof(char), (size_t)(sizeof(buffer)), fp);

    printf("Number of characters read are: %d\n", char_read);
    
    return char_read;
}

Node* create_node() {
    Node* n = (Node*) malloc(sizeof(Node));
    n->tag = 0;
    return n;

}

Node* get_token(FILE* fp, lookup_table table) {

    char ch;
    Node* n;
    Value v;

    while(1) {

        if (sizeof(buffer)==pointer) {
            if(!buffer_read(fp)) {
                printf("Error in reading file\n");
                exit(0);
            }
            // printf("\n\nBuffer: %s\n\n", buffer);
            pointer = 0;
        }
        
        ch = buffer[pointer];
        switch(state) {
            case 0: 
                if (ch=='>') {
                    state = 43;
                    pointer++;
                    break;
                }
                else if  (ch=='<') {
                    state = 47;
                    pointer++;
                    break;
                }
                else if  (ch=='+') {
                    state = 1;
                    break;
                }
                else if  (ch=='-') {
                    state = 2;
                    break;
                }
                else if  (ch=='/') {
                    state = 3;
                    break;
                }
                else if  (ch=='*') {
                    state = 4;
                    pointer++;
                    break;
                }
                else if  (ch=='=') {
                    state = 11;
                    pointer++;
                    break;
                }
                else if  (ch==':') {
                    state = 13;
                    pointer++;
                    break;
                }
                else if  (ch=='!') {
                    state = 16;
                    pointer++;
                    break;
                }
                else if  (ch=='.') {
                    state = 18;
                    pointer++;
                    break;
                }
                else if  (ch==';') {
                    state = 20;
                    break;
                }
                else if  (ch==',') {
                    state = 21;
                    break;
                }
                else if  (ch=='[') {
                    state = 22;
                    break;
                }
                else if  (ch==']') {
                    state = 23;
                    break;
                }
                else if  (ch=='(') {
                    state = 24;
                    break;
                }
                else if  (ch==')') {
                    state = 25;
                    break;
                }
                else if (ch=='\n') {
                    state = 26;
                    pointer++;
                    break;
                }
                else if ((ch>='a')&&(ch<='z')||(ch>='A')&&(ch<='Z')) {
                    state = 28;
                    id[id_length] = ch;
                    pointer++;
                    break;
                }
                else if (ch==' ' || ch=='\t') {
                    state = 30;
                    pointer++;
                    break;
                }
                else if (ch>='0' && ch<='9') {
                    string_flush(number);
                    number_index = 0;
                    number[number_index] = ch;
                    state = 32;
                    pointer++;
                    break;
                }
                else if(ch=='\0') {
                    state = 52;
                    break;
                }
                else {
                    state = 51;
                    break;
                }
            case 1:
                n = create_node();
                n->token = PLUS;
                strcpy(n->lexeme, "+");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 2:
                n = create_node();
                n->token = MINUS;
                strcpy(n->lexeme, "-");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;
            
            case 3:
                n = create_node();
                n->token = DIV;
                strcpy(n->lexeme, "/");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 4:
                if(ch=='*') {
                    state = 6;
                    pointer++;
                    break;
                }
                else {
                    state = 5;
                    break;
                }

            case 5:
                n = create_node();
                n->token = MUL;
                strcpy(n->lexeme, "*");
                n->line_no = line_number;
                state = 0;
                return n;
                break;

            case 6:
                if(ch=='*') {
                    state = 7;
                    pointer++;
                    break;
                }
                else if(ch=='\n') {
                    state = 10;
                    pointer++;
                    break;
                }
                else if(ch=='\0') {
                    state = 52;
                    break;
                }
                else {
                    state = 8;
                    pointer++;
                    break;
                }

            case 7:
                if(ch=='*') {
                    state = 9;
                    break;
                }
                else if(ch=='\n') {
                    state = 10;
                    pointer++;
                    break;
                }
                else if(ch=='\0') {
                    state = 52;
                    break;
                }
                else {
                    state = 8;
                    pointer++;
                    break;
                }

            case 8:
                if(ch=='*') {
                    state = 7;
                    pointer++;
                    break;
                }
                else if(ch=='\n') {
                    state = 10;
                    pointer++;
                    break;
                }
                else if(ch=='\0') {
                    state = 52;
                    break;
                }
                else {
                    state = 8;
                    pointer++;
                    break;
                }

            case 9:
                state = 0;
                pointer++;
                break;

            case 10:
                line_number++;
                if(ch=='*') {
                    state = 7;
                    pointer++;
                    break;
                }
                else if(ch=='\n') {
                    state = 10;
                    pointer++;
                    break;
                }
                else if(ch=='\0') {
                    state = 52;
                    break;
                }
                else {
                    state = 8;
                    pointer++;
                    break;
                }

            case 11:
                if(ch=='=') {
                    state = 12;
                    break;
                }
                else {
                    state = 51;
                    break;
                }

            case 12:
                n = create_node();
                n->token = EQ;
                strcpy(n->lexeme, "==");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 13:
                if(ch=='=') {
                    state = 14;
                    break;
                }
                else {
                    state = 15;
                    break;
                }

            case 14:
                n = create_node();
                n->token = ASSIGNOP;
                strcpy(n->lexeme, ":=");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 15:
                n = create_node();
                n->token = COLON;
                strcpy(n->lexeme, ":");
                n->line_no = line_number;
                state = 0;
                return n;
                break;

            case 16:
                if(ch=='=') {
                    state = 17;
                    break;
                }
                else {
                    state = 51;
                    break;
                }

            case 17:
                n = create_node();
                n->token = NE;
                strcpy(n->lexeme, "!=");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 18:
                if(ch=='.') {
                    state = 19;
                    break;
                }
                else {
                    state = 51;
                    break;
                }

            case 19:
                n = create_node();
                n->token = RANGEOP;
                strcpy(n->lexeme, "..");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 20:
                n = create_node();
                n->token = SEMICOL;
                strcpy(n->lexeme, ";");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;
            
            case 21:
                n = create_node();
                n->token = COMMA;
                strcpy(n->lexeme, ",");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 22:
                n = create_node();
                n->token = SQBO;
                strcpy(n->lexeme, "[");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 23:
                n = create_node();
                n->token = SQBC;
                strcpy(n->lexeme, "]");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 24:
                n = create_node();
                n->token = BO;
                strcpy(n->lexeme, "(");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 25:
                n = create_node();
                n->token = BC;
                strcpy(n->lexeme, ")");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 26:
                line_number++;
                if(ch=='\n') {
                    state = 26;
                    pointer++;
                    break;
                }
                else {
                    state = 27;
                    break;
                }

            case 27:
                state = 0;
                break;

            case 28:
                id_length++;

                if(id_length<MAX_ID_LENGTH) {
                    id[id_length] = ch; 
                }

                if(((ch>='a')&&(ch<='z'))||((ch>='A')&&(ch<='Z'))||((ch>='0')&&(ch<='9'))||(ch=='_')) {
                    state = 28;
                    pointer++;
                    break;
                }
                else {
                    state = 29;
                    id[id_length] = '\0';
                    break;
                }

            case 29:
                if(id_length<=MAX_ID_LENGTH) {
                    id_length = 0;
                    n = create_node();

                    List tmp = search(id, table);
                    
                    if(tmp == NULL) {
                        n->token = ID;
                        strcpy(n->lexeme, id);
                    }
                    else {
                        n->token = tmp->token;
                        strcpy(n->lexeme, tmp->lexeme);
                    }

                    n->line_no = line_number;
                    state = 0;
                    return n;
                    break;
                }
                else {
                    id_length = 0;
                    string_flush(id);
                    pointer--;
                    state = 51;
                    break;
                }

            case 30:
                if((ch==' ') || (ch=='\t')) {
                    state = 30;
                    pointer++;
                    break;
                }
                else {
                    state = 31;
                    break;
                }

            case 31:
                state = 0;
                break;

            case 32:
                // printf("%s\n", number);
                if((ch>='0')&&(ch<='9')) {
                    state = 32;
                    number_index++;
                    number[number_index] = ch;
                    pointer++;
                    break;
                }
                else if(ch=='.') {
                    state = 34;
                    number_index++;
                    number[number_index] = ch;
                    pointer++;
                    break;
                }
                else {
                    state = 33;
                    break;
                }

            case 33:
                n  = create_node();
                n->token = NUM;
                strcpy(n->lexeme, number);
                // printf("%s\n", number);
                n->line_no = line_number;
                n->tag = 1;
                v.num = atoi(number);
                n->val = v;
                state = 0;
                return n;
                break;                

            case 34:
                if((ch>='0')&&(ch<='9')) {
                    state = 36;
                    number_index++;
                    number[number_index] = ch;
                    pointer++;
                    break;
                }
                else {
                    state = 35;
                    break;
                }

            case 35:
                number[number_index] = '\0';
                n  = create_node();
                n->token = NUM;
                strcpy(n->lexeme, number);
                n->line_no = line_number;
                n->tag = 1;
                v.num = atoi(number);
                n->val = v;
                state = 0;
                pointer--;
                return n;
                break;                            

            case 36:
                if((ch>='0')&&(ch<='9')) {
                    state = 36;
                    number_index++;
                    number[number_index] = ch;
                    pointer++;
                    break;
                }
                else if((ch=='E')||(ch=='e')) {
                    state = 37;
                    number_index++;
                    number[number_index] = ch;
                    pointer++;
                    break;
                }
                else {
                    state = 42;
                    break;
                }

            case 37:
                if((ch>='0')&&(ch<='9')) {
                    state = 41;
                    pointer++;
                    number_index++;
                    number[number_index] = ch;
                    break;
                }
                else if((ch=='+')||(ch=='-')) {
                    state = 39;
                    pointer++;
                    number_index++;
                    number[number_index] = ch;
                    break;
                }
                else {
                    state = 38;
                    break;
                }

            case 38: 
                number[number_index] = '\0';
                n  = create_node();
                n->token = RNUM;
                strcpy(n->lexeme, number);
                n->line_no = line_number;
                n->tag = 2;
                v.rnum = atof(number);
                n->val = v;
                state = 0;
                pointer--;
                return n;
                break;

            case 39:
                if((ch>='0')&&(ch<='9')) {
                    state = 41;
                    pointer++;
                    number_index++;
                    number[number_index] = ch;
                    break;
                }
                else {
                    state = 40;
                    break;
                }

            case 40:
                number[number_index] = '\0';
                number_index--;
                number[number_index] = '\0';
                n  = create_node();
                n->token = RNUM;
                strcpy(n->lexeme, number);
                n->line_no = line_number;
                n->tag = 2;
                v.rnum = atof(number);
                n->val = v;
                state = 0;
                pointer--;
                pointer--;
                return n;
                break;

            case 41:
                if((ch>='0')&&(ch<='9')) {
                    state = 41;
                    pointer++;
                    number_index++;
                    number[number_index] = ch;
                    break;
                }
                else {
                    state = 42;
                    break;
                }

            case 42:
                n  = create_node();
                n->token = RNUM;
                strcpy(n->lexeme, number);
                n->line_no = line_number;
                n->tag = 2;
                v.rnum = atof(number);
                n->val = v;
                state = 0;
                return n;
                break;
            
            case 43: 
                if(ch=='>') {
                    state = 46;
                    pointer++;
                    break;
                }
                else if(ch=='=') {
                    state = 45;
                    break;
                }
                else {
                    state = 44;
                    break;
                }

            case 44:
                n = create_node();
                n->token = GT;
                strcpy(n->lexeme, ">");
                n->line_no = line_number;
                state = 0;
                return n;
                break;

            case 45:
                n = create_node();
                n->token = GE;
                strcpy(n->lexeme, ">=");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 46:
                if(ch=='>') {
                    state = 53;
                    break;
                }
                else {
                    state = 54;
                    break;
                }

            case 47:
                if(ch=='=') {
                    state = 50;
                    break;
                }
                else if(ch=='<') {
                    state = 49;
                    pointer++;
                    break;
                }
                else {
                    state = 48;
                    break;
                }

            case 48:
                n = create_node();
                n->token = LT;
                strcpy(n->lexeme, "<");
                n->line_no = line_number;
                state = 0;
                return n;
                break;

            case 49:
                if(ch=='<') {
                    state = 55;
                    break;
                }
                else {
                    state = 56;
                    break;
                }

            case 50:
                n = create_node();
                n->token = LE;
                strcpy(n->lexeme, "<=");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 51:
                n = create_node();
                n->token = ERROR;
                strcpy(n->lexeme, "Token not found");
                // printf("Lexical error on line number: %d\n ", line_number);
                n->line_no = line_number;
                state = 0;
                pointer++;
                break;

            case 52:
                return NULL;
                break;

            case 53:
                n = create_node();
                n->token = ENDDRIVERDEF;
                strcpy(n->lexeme, ">>>");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 54:
                n = create_node();
                n->token = ENDDEF;
                strcpy(n->lexeme, ">>");
                n->line_no = line_number;
                state = 0;
                return n;
                break;

            case 55:
                n = create_node();
                n->token = DRIVERDEF;
                strcpy(n->lexeme, "<<<");
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 56:
                n = create_node();
                n->token = DEF;
                strcpy(n->lexeme, "<<");
                n->line_no = line_number;
                state = 0;
                return n;
                break;

        }
    }
    
}

int lexical_analyzer(char* filename, Node*** token_stream, lookup_table ** table) {

    FILE* fp = open_file(filename);

    if(!buffer_read(fp)) {
        printf("Error in reading file\n");
        exit(0);
    }

    *table = (lookup_table *)malloc(sizeof(lookup_table));
    **table = initialize_lookup_table(SLOT_SIZE);

    *token_stream = (Node **) malloc(sizeof(Node *) * INITIAL_TOKENS_IN_INPUT);
    int c_size = 0, c_max = INITIAL_TOKENS_IN_INPUT;

    Node* n;

    while(1) {
        n = get_token(fp, **table);
        if(n==NULL)
            break;

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

        if(n==NULL || n->token == ERROR) {
            continue;
        }
        else {
            if(c_size == c_max) {
                *token_stream = (Node **) realloc(*token_stream, sizeof(Node *) * c_max * 2);
                c_max *= 2;
            }

            (*token_stream)[c_size] = n;
            c_size++;
        }
    }

    *token_stream = (Node **) realloc(*token_stream, sizeof(Node *) * c_size);
    return c_size;
}
