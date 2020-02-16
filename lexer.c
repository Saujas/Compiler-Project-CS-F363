#include "lexer.h"

#define MAX_BUFFER_LENGTH 200
#define MAX_ID_LENGTH 20

char buffer[MAX_BUFFER_LENGTH];
char id[MAX_ID_LENGTH];
char number[]
int state = 0;

static int line_number = 1;
static int pointer = 0;
static int id_length = 0;

FILE* open_file(char* filename) {
    FILE* fp = fopen(filename, "r");

    if( fp == NULL) {
        printf("Error in opening file\n");
        exit(0);
    }

    return fp;
}

int string_flush(char *str) {
    for(int i = 0; i<sizeof(str); i++) {
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

Node get_token(char* fp) {

    char token[MAX_TOKEN_SIZE];
    char value[MAX_TOKEN_SIZE];
    string_flush(token);
    string_flush(value);
    char ch;

    while(!feof(fp) ) {
        if (sizeof(buffer)==pointer) {
            if(!buffer_read(fp)) {
                printf("Error in reading file\n");
                exit(0);
            }
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
                Node n;
                strcpy(n.token, "PLUS");
                strcpy(n.lexeme, "+");
                n.line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 2:
                Node n;
                strcpy(n.token, "MINUS");
                strcpy(n.lexeme, "-");
                n.line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;
            
            case 3:
                Node n;
                strcpy(n.token, "DIV");
                strcpy(n.lexeme, "/");
                n.line_no = line_number;
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
                Node n;
                strcpy(n.token, "MUL");
                strcpy(n.lexeme, "*");
                n.line_no = line_number;
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
                Node n;
                strcpy(n.token, "EQ");
                strcpy(n.lexeme, "==");
                n.line_no = line_number;
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
                Node n;
                strcpy(n.token, "ASSIGNOP");
                strcpy(n.lexeme, ":=");
                n.line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 15:
                Node n;
                strcpy(n.token, "COLON");
                strcpy(n.lexeme, ":");
                n.line_no = line_number;
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
                Node n;
                strcpy(n.token, "NE");
                strcpy(n.lexeme, "!=");
                n.line_no = line_number;
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
                Node n;
                strcpy(n.token, "RANGEOP");
                strcpy(n.lexeme, "..");
                n.line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 20:
                Node n;
                strcpy(n.token, "SEMICOL");
                strcpy(n.lexeme, ";");
                n.line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;
            
            case 21:
                Node n;
                strcpy(n.token, "COMMA");
                strcpy(n.lexeme, ",");
                n.line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 22:
                Node n;
                strcpy(n.token, "SQBO");
                strcpy(n.lexeme, "[");
                n.line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 23:
                Node n;
                strcpy(n.token, "SQBC");
                strcpy(n.lexeme, "]");
                n.line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 24:
                Node n;
                strcpy(n.token, "BO");
                strcpy(n.lexeme, "(");
                n.line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 25:
                Node n;
                strcpy(n.token, "BC");
                strcpy(n.lexeme, ")");
                n.line_no = line_number;
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
                    break;
                }

            case 29:
                if(id_length<=MAX_ID_LENGTH) {
                    id_length = 0;
                    Node n;
                    strcpy(n.token, "get_keyword_or_id");
                    strcpy(n.lexeme, "id_or_keyword_value");
                    n.line_no = line_number;
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
                if((ch>='0')&&(ch<='9')) {
                    state = 32;
                    pointer++;
                    break;
                }

            case 33:

            case 34:

            case 35:

            case 36:

            case 37:

            case 38:

            case 39:

            case 40:

            case 41:

            case 42:
            
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
                Node n;
                strcpy(n.token, "GT");
                strcpy(n.lexeme, ">");
                n.line_no = line_number;
                state = 0;
                return n;
                break;

            case 45:
                Node n;
                strcpy(n.token, "GE");
                strcpy(n.lexeme, ">=");
                n.line_no = line_number;
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
                Node n;
                strcpy(n.token, "LT");
                strcpy(n.lexeme, "<");
                n.line_no = line_number;
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
                Node n;
                strcpy(n.token, "LE");
                strcpy(n.lexeme, "<=");
                n.line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 51:

            case 52:

            case 53:
                Node n;
                strcpy(n.token, "ENDDRIVERDEF");
                strcpy(n.lexeme, ">>>");
                n.line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 54:
                Node n;
                strcpy(n.token, "ENDDEF");
                strcpy(n.lexeme, ">>");
                n.line_no = line_number;
                state = 0;
                return n;
                break;

            case 55:
                Node n;
                strcpy(n.token, "DRIVERDEF");
                strcpy(n.lexeme, "<<<");
                n.line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 56:
                Node n;
                strcpy(n.token, "DEF");
                strcpy(n.lexeme, "<<");
                n.line_no = line_number;
                state = 0;
                return n;
                break;

        }
    }
    
}

int lexical_analyzer(char* filename) {

    FILE* fp = open_file(filename);

    if(!buffer_read(fp)) {
        printf("Error in reading file\n");
        exit(0);
    }

    get_token(fp); //put in while until EOF
}


