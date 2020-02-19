#include "lexer.h"
#define NON_TERMINAL_SIZE 62
#define GRAMMAR_FILE "grammar.txt"
#define MAX_RULE_LENGTH 500

typedef enum{
    program, moduleDeclarations, moduleDeclaration, otherModules, driverModule, module, ret, input_plist,
    new1, output_plist, new2, dataType, dataType2, type, range, range2, moduleDef, statements, new3,
    statement, ioStmt, var, var2, whichID, simpleStmt, assignmentStmt, whichStmt, lvalueIDstmt, lvalueArrStmt, 
    Index, moduleReuseStmt, optional, idList, newX, expression, new4, AorBExpr, arithmeticExpr, new6,
    term, new7, factor, PlusMinus, MulDiv, relationalOP, logicalOP, boolKey, boolExpr, new8, relationalExpr,
    declareStmt, iterativeStmt, whileCondition, new10, new9, newY, conditionalStatement, caseStmt, numericCases, 
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

first_set all_first_sets[NON_TERMINAL_SIZE];

int parse_token_stream(char* filename);
int read_grammar(char* filename);
int addRule(rules** grammar, symbol* rule, symbol nt, int count_of_symbols);
int main_parser(char* filename);
symbol convert_to_symbol(char* str);
first_set compute_first_set(int nt);
int find_first_sets();