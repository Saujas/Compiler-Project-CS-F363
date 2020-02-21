#ifndef PARSER_DEF
#define PARSER_DEF
#define NON_TERMINAL_SIZE 58

#include "lexer_def.h"

typedef enum{
    program, moduleDeclarations, moduleDeclaration, otherModules, driverModule, module, ret, input_plist,
    new1, output_plist, new2, dataType, dataType2, type, range, range2, moduleDef, statements, new3,
    statement, ioStmt, var, var2, whichID, simpleStmt, assignmentStmt, whichStmt, lvalueIDstmt, lvalueArrStmt, 
    Index, moduleReuseStmt, optional, idList, newX, expression, new4, AorBExpr, arithmeticExpr, new6,
    term, new7, factor, PlusMinus, MulDiv, relationalOP, logicalOP, boolKey, boolExpr, new8, relationalExpr,
    declareStmt, iterativeStmt, conditionalStatement, caseStmt, numericCases, 
    numericCase, new11, Default
} non_terminals;

typedef union {
    non_terminals non_terminal;
    tokens terminal;
} unit;

typedef struct {
    unit sym;
    int tag;
} symbol;

typedef struct grammar_rule {
    symbol* rule;
    int count_of_symbols;
    struct grammar_rule* next; 
} rules;

typedef struct {
    tokens* first_set_token;
    int count;
} first_set;

typedef struct {
    tokens* follow_set_token;
    int count;
} follow_set;

#endif