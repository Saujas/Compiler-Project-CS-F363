#include "type_extractor.h"
#include "semantic_analyzer.h"
#include "symbol_table.h"

char* tc_string_map[AST_LABEL_NUMBER] = {
    "AST_PROGRAM", "MODULE_DECLARATIONS", "MODULE_DECLARATION", "OTHER_MODULES", "AST_DRIVER", "AST_MODULE", "INPUT_PLIST", "NEW1",
    "OUTPUT_PLIST", "NEW2", "DATA_TYPE", "DATA_TYPE2", "RANGE", "RANGE2", "STATEMENTS", "VAR", "ASSIGNMENT_STMT", 
    "LVALUE_ARR_STMT", "MODULE_REUSE_STMT", "ID_LIST", "NEWX", "EXPRESSION", "NEW6", "NEW7", "NEW8", "RELATIONAL_EXPR", 
    "DECLARE_STMT", "AST_FOR", "AST_WHILE", "CONDITIONAL_STMT", "CASE_STMT_T", "CASE_STMT_F", "NUMERIC_CASES", "NUMERIC_CASE", "IO_READ", "IO_WRITE", "AST_DEFAULT"
};

char * tc_non_terminals_string_map[NON_TERMINAL_SIZE] = {"program", "moduleDeclarations", "moduleDeclaration", "otherModules", "driverModule", "module", "ret", "input_plist",
    "new1", "output_plist", "new2", "dataType", "dataType2", "type", "range", "range2", "moduleDef", "statements", "new3",
    "statement", "ioStmt", "var", "var2", "whichID", "simpleStmt", "assignmentStmt", "whichStmt", "lvalueIDstmt", "lvalueArrStmt", 
    "Index", "moduleReuseStmt", "optional", "idList", "newX", "expression", "new4", "AorBExpr", "arithmeticExpr", "new6",
    "term", "new7", "factor", "PlusMinus", "MulDiv", "relationalOP", "logicalOP", "boolKey", "boolExpr", "new8", "relationalExpr",
    "declareStmt", "iterativeStmt", "conditionalStatement", "caseStmt", "numericCases", 
    "numericCase", "new11", "Default"};


int get_id_type(AST node) {
    Symbol_Node* st = node->symbol_table_node;

    // printf("%s\n", node->leaf_token->lexeme);

    if(st == NULL) {
        // variable not declared
        return -1;
    }
    
    if(st->datatype == 3) {
        return st->array_datatype;
    }

    return st->datatype;
}

// 0: INT, 1: REAL, 2: BOOLEAN, -1: ERROR
int extract_type(AST node,ErrorList* err) {
    
    if(node == NULL) {
        return -1;
    }

    int error = 0;

    if(node->tag == 1) {

        if(node->label == EXPRESSION || node->label == RELATIONAL_EXPR ||
        node->label == NEW8 || node->label == NEW7 || node->label == NEW6 || node->label == VAR) {
            return extract_type(node->child, err);
        }

        // INVALID NON TERMINAL WITHIN AN EXPRESSION
        else return -1;
    }

    // if a terminal is encountered,
    // it will either be an operator or a literal

    char* name = node->leaf_token->lexeme;
    tokens token = node->leaf_token->token;

    if(token == PLUS || token == MINUS) {
        AST n1 = node->next;
        AST n2 = node->next->next;

        int t1 = extract_type(n1, err), t2 = extract_type(n2, err);

        if(n2 == NULL) {
            if(t1 == 2) {
                error = 1;
            }
            else
                return t1;
        }

        if(t1 != t2 || t1 == 2 || t2 == 2) {
            error = 1;
        }
        else
            return t1;
    }

    if(token == MUL || token == DIV) {
        
        AST n1 = node->next;
        AST n2 = node->next->next;

        int t1 = extract_type(n1, err), t2 = extract_type(n2, err);
        
        if(t1 != t2 || t1 == 2 || t2 == 2) {
            error = 1;
        }

        else return t1;
    }

    if(token == GT || token == LT || token == GE || token == LE ||
        token == EQ || token == NE) {
        
        AST n1 = node->next;
        AST n2 = node->next->next;

        int t1 = extract_type(n1, err), t2 = extract_type(n2, err);
        
        if(t1 != t2 || t1 == 2 || t2 == 2 || t1 == -1 || t2 == -1) {
            error = 1;
        }

        else return 2;
    }

    if(token == AND || token == OR) {
        AST n1 = node->next;

        AST n2 = node->next->next;

        int t1 = extract_type(n1, err), t2 = extract_type(n2, err);

        if( !(t1 == 2 && t2 == 2)) {
            error = 1;
        }

        else return 2;
    }

    if(error) {
        //printf("Line: %d - Invalid types in expression\n", node->leaf_token->line_no);
       /* char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: INVALID TYPES IN EXPRESSION");
            add_sem_error(err,str,node->leaf_token->line_no);*/
        return -1;
    }

    // if it is a literal
    if(token == ID) {
        if(node->symbol_table_node && node->symbol_table_node->datatype == 3) {
            AST temp1 = node->next;
            if(!temp1)
                return -1;
            if(temp1->symbol_table_node && temp1->symbol_table_node->datatype != 0) {
                //printf("Line: %d - Invalid type of array index\n", node->leaf_token->line_no);
               /* char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: INVALID TYPE OF ARRAY INDEX");
            add_sem_error(err,str,node->leaf_token->line_no);*/
                return -1;
            }
            else if(temp1->leaf_token && temp1->leaf_token->token == NUM) {
                if(!check_bound(temp1, node)) {
                    //printf("Line: %d - Out of bound array index\n", node->leaf_token->line_no);
                    /*char* str = (char*)malloc(sizeof(str)*ERROR_STRING_SIZE);
            strcpy(str,"ERROR: ARRAY INDEX OUT OF BOUNDS");
            add_sem_error(err,str,node->leaf_token->line_no);*/
                    return -1;
                }
            }
        }
        int type = get_id_type(node);
        
        return type;
    }
    else {
        if(token == NUM) {
            return 0;
        }
        else if(token == RNUM)
            return 1;
        else if(token == TRUE || token == FALSE)
            return 2;
    }

    return -1;
}