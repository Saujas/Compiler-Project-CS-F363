// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include "lexer.h"

/* Constants used throughout the FILE 
*/
#define MAX_BUFFER_LENGTH 2000
#define MAX_ID_LENGTH 20
#define MAX_LEX_ERROR_SIZE 100
#define MAX_RNUM_LENGTH 3 + DBL_MANT_DIG - DBL_MIN_EXP

/* Certain arrays to store buffer, lexeme in case of an ID token, a NUM or an RNUM, and the set of characters causing a lexical error
*/
char buffer[MAX_BUFFER_LENGTH];
char id[MAX_ID_LENGTH];
char number[MAX_RNUM_LENGTH];
char error[MAX_LEX_ERROR_SIZE];

/* Global variables used in lexer
*/
int state = 0;
static int line_number = 1;
static int pointer = 0;
static int id_length = 0;
static int number_index = 0;

/* Token to string map indexed by enums defined in lexer_def.h
   Used in printing lexemes quickly
*/
char * token_string_map_copy[TOKEN_NUMBERS] = {"INTEGER", "REAL", "BOOLEAN", "OF", "ARRAY", "START",
            "END", "DECLARE", "MODULE", "DRIVER", "PROGRAM", "GET_VALUE", "PRINT",
            "USE", "WITH", "PARAMETERS", "TRUE", "FALSE", "TAKES", "INPUT", "RETURNS",
            "AND", "OR", "FOR", "IN", "SWITCH", "CASE", "BREAK", "DEFAULT", "WHILE", "PLUS", 
            "MINUS", "MUL", "DIV", "LT", "LE", "GE", "GT", "EQ", "NE", "DEF", "DRIVERDEF",
            "ENDDEF", "DRIVERENDDEF", "COLON", "RANGEOP", "SEMICOL", "COMMA", "ASSIGNOP", 
            "SQBO", "SQBC", "BO", "BC", "COMMENTMARK", "NUM", "RNUM", "ID", "ERROR", "E", "$"
};

/* For opening a file and returning the corresponding file pointer
*/
FILE* open_file(char* filename) {
    FILE* fp = fopen(filename, "r");

    if( fp == NULL) {
        printf("Error in opening file\n");
        exit(0);
    }

    return fp;
}

/* Function for clearing a string passed to it
   Useful for clearing the input buffer, error array, number array and id array
*/
int string_flush(char *str) {
    int i;
    int len = strlen(str);
    for(i = 0; i<len; i++) {
        str[i] = '\0';
    }
    return 1;
}

/* The function for reading from the file into the buffer defined at the top, with a max of 
   MAX_BUFFER_LENGTH characters
*/
int get_stream(FILE* fp, int offset) {
    if(fp == NULL) {
        printf("Invalid file pointer\n");
        exit(0);
    }

    string_flush(buffer);
    fseek(fp, offset, SEEK_CUR);

    int char_read = fread(buffer, (size_t)sizeof(char), (size_t)(sizeof(buffer)), fp);

    // printf("Number of characters read are: %d\n", char_read);
    // printf("%s\n", buffer);
    // printf("%ld\n", strlen(buffer));
    
    return char_read;
}

/* Allocating memory for a token node and returning the pointer
*/
Node* create_node() {
    Node* n = (Node*) malloc(sizeof(Node));
    n->tag = 0;
    return n;

}

/* Adding a character to the error array
*/
int add_error(char ch) {
    error[strlen(error)] = ch;
    return strlen(error);
}

/* This function calculates which state in the DFA to proceed based on switch-case statements.
   The while loop runs until a matching correct token is found, after which this function returns a pointer to a node
   containing the token found, and other details according to the definition in lexer_def.h
   If an error is encountered, it returns a pointer to a node which contains the lexeme which caused the error
*/
Node* get_next_token(FILE* fp, lookup_table table) {

    char ch;
    Node* n;
    Value v;

    while(1) {
        /* This if statement is to check whether the buffer has been read, and whether to read the rest of the file
        */
        if (sizeof(buffer)==pointer+5 && ((fgetc(fp))!=EOF)) {
            if(!get_stream(fp, -6)) {
                printf("Error in reading file\n");
                exit(0);
            }
            // printf("\n\nBuffer: %s\n\n", buffer);
            pointer = 0;
        }
        
        ch = buffer[pointer];
        switch(state) {
            //The start state corresponds to state 0
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
                    add_error(ch);
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
                    add_error(ch);
                    pointer++;
                    break;
                }
                else if  (ch=='.') {
                    state = 18;
                    add_error(ch); //The error array is updated on the possibility of encountering an error and flushed if token matches
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
                else if ((ch>='a')&&(ch<='z')||(ch>='A')&&(ch<='Z')) { //For checking if id or keyword
                    state = 28;
                    error[strlen(error)] = ch;
                    id[id_length] = ch;
                    pointer++;
                    break;
                }
                else if (ch==' ' || ch=='\t') { //Ignoring all white spaces and tabs
                    state = 30;
                    pointer++;
                    break;
                }
                else if (ch>='0' && ch<='9') { //For checking if digit
                    string_flush(number);
                    number_index = 0;
                    error[strlen(error)] = ch;
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
                    add_error(ch);
                    state = 51;
                    break;
                }
                
            case 1:
                n = create_node(); //An example of a final state where a token is found and its node pointer is returned 
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
                add_error(ch);

            case 5:
                n = create_node();
                n->token = MUL;
                strcpy(n->lexeme, "*");
                n->line_no = line_number;
                state = 0;
                return n;
                break;

            case 6:
                if(ch=='*') { //For removing comments in user source code, states 6,7,8,9 are used
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
                add_error(ch);

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
                add_error(ch);

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
                add_error(ch);

            case 9:
                state = 0;
                pointer++;
                break;

            case 10:
                line_number++; //Increments line number even though inside comments
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
                    string_flush(error);
                    break;
                }
                else {
                    state = 51; //Example of error being encountered on which the state is changed to 51
                    pointer--;
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
                    string_flush(error);
                    break;
                }
                else {
                    state = 51;
                    pointer--;
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
                    string_flush(error);
                    break;
                }
                else {
                    state = 51;
                    pointer--;
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

                if(id_length<MAX_ID_LENGTH) { //Checking if id length is less than 20
                    id[id_length] = ch; 
                }

                if(((ch>='a')&&(ch<='z'))||((ch>='A')&&(ch<='Z'))||((ch>='0')&&(ch<='9'))||(ch=='_')) {
                    state = 28;
                    pointer++;
                    error[strlen(error)] = ch;
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

                    /*The lexeme is searched for in the lookup table, to check if it's a keyword or not.
                    Further details in lookup.c
                    */
                    List tmp = search(id, table);
                    
                    if(tmp == NULL) {
                        n->token = ID; //Returning an ID token
                        strcpy(n->lexeme, id);
                    }
                    else {
                        n->token = tmp->token; //Returning a keyword token found in the lookup table
                        strcpy(n->lexeme, tmp->lexeme);
                    }

                    n->line_no = line_number;
                    state = 0;
                    string_flush(error);
                    return n;
                    break;
                }
                else {
                    id_length = 0;
                    string_flush(id); //Error on encountering is length > 20
                    pointer--;
                    state = 51;
                    break;
                }

            case 30:
                if((ch==' ') || (ch=='\t')) {
                    state = 30; //Ignoring tabs and spaces
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
                if((ch>='0')&&(ch<='9')) { //For identifying a NUM or RNUM
                    state = 32;
                    number_index++;
                    number[number_index] = ch;
                    error[strlen(error)] = ch;
                    pointer++;
                    break;
                }
                else if(ch=='.') {
                    state = 34;
                    number_index++;
                    number[number_index] = ch;
                    error[strlen(error)] = ch;
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
                string_flush(error);
                return n;
                break;                

            case 34:
                if((ch>='0')&&(ch<='9')) { //Checking RNUM
                    state = 36;
                    number_index++;
                    number[number_index] = ch;
                    error[strlen(error)] = ch;
                    pointer++;
                    break;
                }
                else if(ch=='.') {
                    number[number_index] = '\0';
                    n  = create_node();
                    n->token = NUM;
                    strcpy(n->lexeme, number);
                    n->line_no = line_number;
                    n->tag = 1;
                    v.num = atoi(number);
                    n->val = v;
                    pointer--;
                    string_flush(error);
                    state = 0;
                    return n;
                    break;
                }
                else {
                    state = 35;
                    break;
                }

            case 35:
                number[number_index] = '\0'; //Error state. Eg- 120.
                // n  = create_node();
                // n->token = NUM;
                // strcpy(n->lexeme, number);
                // n->line_no = line_number;
                // n->tag = 1;
                // v.num = atoi(number);
                // n->val = v;
                state = 51;
                pointer--;
                // return n;
                break;                            

            case 36:
                if((ch>='0')&&(ch<='9')) { //Checking for mantissa-exopnent form
                    state = 36;
                    number_index++;
                    number[number_index] = ch;
                    error[strlen(error)] = ch;
                    pointer++;
                    break;
                }
                else if((ch=='E')||(ch=='e')) {
                    state = 37;
                    number_index++;
                    number[number_index] = ch;
                    error[strlen(error)] = ch;
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
                    error[strlen(error)] = ch;
                    number[number_index] = ch;
                    break;
                }
                else {
                    state = 38;
                    break;
                }

            case 38: 
                number[number_index] = '\0'; //Error state - Eg: 180.ea
                // n  = create_node();
                // n->token = RNUM;
                // strcpy(n->lexeme, number);
                // n->line_no = line_number;
                // n->tag = 2;
                // v.rnum = atof(number);
                // n->val = v;
                // state = 0;
                pointer--;
                state = 51;
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
                number[number_index] = '\0'; //Error state - Eg: 120.E+a
                // number_index--;
                // number[number_index] = '\0';
                // n  = create_node();
                // n->token = RNUM;
                // strcpy(n->lexeme, number);
                // n->line_no = line_number;
                // n->tag = 2;
                // v.rnum = atof(number);
                // n->val = v;
                // state = 0;
                // pointer--;
                pointer--;
                state = 51;
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
                string_flush(error);
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
                n = create_node(); //This is the error state which returns an error token which returns the lexeme stored in array error
                n->token = ERROR;
                strcpy(n->lexeme, error);
                string_flush(error);
                // printf("Lexical error on line number: %s\n ", n->lexeme);
                n->line_no = line_number;
                state = 0;
                pointer++;
                return n;
                break;

            case 52: //State on encountering EOF character, which terminates the function
                return NULL;
                break;

            case 53:
                n = create_node();
                n->token = DRIVERENDDEF;
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

/*  The main function of the lexer which calls get_next_token for every token until EOF
    It stores every received correct node pointer in a token stream.
    It also prints lexer output, which includes correct lexemes with line numbers, as well as lexical errors
*/
int lexical_analyzer(char* filename, Node*** token_stream, lookup_table ** table, int check) {

    FILE* fp = open_file(filename);
    state = 0;
    line_number = 1;
    pointer = 0;
    id_length = 0;
    number_index = 0;

    if(!get_stream(fp, 0)) {
        printf("Error in reading file\n");
        exit(0);
    }

    *table = (lookup_table *)malloc(sizeof(lookup_table));
    **table = initialize_lookup_table(SLOT_SIZE);

    *token_stream = (Node **) malloc(sizeof(Node *) * INITIAL_TOKENS_IN_INPUT);
    int c_size = 0, c_max = INITIAL_TOKENS_IN_INPUT;

    Node* n;
    string_flush(error);

    while(1) {
        n = get_next_token(fp, **table);
        if(n==NULL) {
            break;
        }

        else {
            if(c_size == c_max) { //Reallocating token stream size
                *token_stream = (Node **) realloc(*token_stream, sizeof(Node *) * c_max * 2);
                c_max *= 2;
            }

            (*token_stream)[c_size] = n;
            c_size++;
        }

        if(check) {
            if(n->token==ERROR) { //Printing lexical error with reason
                if(strlen(n->lexeme)>20)
                    printf("Error on line number %d: %s (Length of identifier cannot exceed 20)\n", n->line_no, n->lexeme);
                else
                    printf("Error on line number %d: %s\n", n->line_no, n->lexeme);
         
            }
            else if(n->tag==0) { //Printing correct lexemes other than numbers
                printf("Line number: %d\t", n->line_no);
                printf("Lexeme: %s\t", n->lexeme);
                printf("Token: %s\t\n", token_string_map_copy[n->token]);
            }
            else if(n->tag==1){ //Printing NUM values
                printf("Line number: %d\t", n->line_no);
                printf("Value: %d\t", n->val.num);
                printf("Token: %s\t\n", token_string_map_copy[n->token]);
            }
            else { //Printing RNUM values
                printf("Line number: %d\t", n->line_no);
                printf("Value: %f\t", n->val.rnum);
                printf("Token: %s\t\n", token_string_map_copy[n->token]);
            }
        }

    }
    fclose(fp);
    *token_stream = (Node **) realloc(*token_stream, sizeof(Node *) * c_size);
    return c_size;
}

/* Function for printing the original user source code with comments removed.
   Line numbers are maintained
*/
int print_without_comments(char* filename) {
    FILE* fp = open_file(filename);
    
    char ch, ch1;
    int flag = 0;
    int flag2 = 0;
    int line = 1;

    while((ch = fgetc(fp))!=EOF) {
        if(!flag2) {
            printf("%d.\t", line);
            flag2 = 1;
        }
        if(ch=='\n') {
            printf("%c", ch);
            line++;
            printf("%d.\t", line);
            continue;
        }
        else if(flag==0 && ch=='*') {
            ch1 = ch;
            ch = fgetc(fp);
            if(ch==EOF) {
                printf("%c", ch1);
                break;
            }
            else if(ch=='*') {
                flag = 1;
                continue;
            }
            else if(ch=='\n') {
                printf("%c", ch1);
                printf("%c", ch);
                line++;
                printf("%d.\t", line);
                continue;
            }
            else {
                printf("%c", ch1);
                continue;
            }
            
        }
        else if(flag==1 && ch=='*') {
            ch = fgetc(fp);
            if(ch==EOF) {
                break;
            }
            else if(ch=='*') {
                flag = 0;
                continue;
            }
            else if(ch=='\n') {
                printf("%c", ch);
                line++;
                printf("%d.\t", line);
                continue;
            }

        }
        if(!flag)
            printf("%c", ch);
    }

    fclose(fp);
    return 1;
}