// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#ifndef PARSER_DEF
#define PARSER_DEF
#define NON_TERMINAL_SIZE 59

#include "lexer_def.h"

// Enums of all non-terminals are stored here
typedef enum{
    program, moduleDeclarations, moduleDeclaration, otherModules, driverModule, module, ret, input_plist,
    new1, output_plist, new2, dataType, dataType2, type, range, range2, moduleDef, statements, new3,
    statement, ioStmt, var, var2, whichID, simpleStmt, assignmentStmt, whichStmt, lvalueIDstmt, lvalueArrStmt, 
    Index, moduleReuseStmt, optional, idList, newX, expression, new4, AorBExpr, arithmeticExpr, new6,
    term, new7, factor, PlusMinus, MulDiv, relationalOP, logicalOP, boolKey, boolExpr, new8, relationalExpr,
    declareStmt, iterativeStmt, conditionalStatement, caseStmt, numericCases, 
    numericCase, new11, Default, NT_value
} non_terminals;

// A unit is a union of a non-teminal enum or a token enum
typedef union {
    non_terminals non_terminal;
    tokens terminal;
} unit;

// A symbol structure consisting of a union unit and a tag to identify the union
typedef struct {
    unit sym;
    int tag;
} symbol;

// A rule is an array of symbols corresponding to a single production of a non-terminal, a count of symbols,
// and a pointer to the next production of the same non-terminal
typedef struct grammar_rule {
    symbol* rule;
    int count_of_symbols;
    struct grammar_rule* next; 
    int rule_num;//new additions
} rules;

// Structure for first set containing an array of token enums and a count
typedef struct {
    tokens* first_set_token;
    int count;
} first_set;

// Structure for follow set containing an array of token enums and a count
typedef struct {
    tokens* follow_set_token;
    int count;
} follow_set;

#endif