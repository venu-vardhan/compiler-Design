#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 256
#define MAX_INPUT_SIZE 256
#define NUM_STATES 13
#define NUM_SYMBOLS 7

// Token types
typedef enum {
    TK_ID,      // identifier
    TK_PLUS,    // +
    TK_MULT,    // *
    TK_LPAREN,  // (
    TK_RPAREN,  // )
    TK_DOLLAR,  // $ (end of input)
    TK_ERROR    // error
} TokenType;

// Grammar symbols (non-terminals and terminals)
typedef enum {
    // Non-terminals
    E = 0,      // Expression
    T = 1,      // Term
    F = 2,      // Factor
    // Terminals
    PLUS = 3,
    MULT = 4,
    LPAREN = 5,
    RPAREN = 6,
    ID = 7,
    DOLLAR = 8
} Symbol;

// Token structure
typedef struct {
    TokenType type;
    char value[50];
} Token;

// Stack entry (state and symbol)
typedef struct {
    int state;
    Symbol symbol;
    char value[50];
} StackEntry;

// Action types
typedef enum {
    ACTION_SHIFT = 1,
    ACTION_REDUCE = 2,
    ACTION_ACCEPT = 3,
    ACTION_ERROR = 0
} ActionType;

// LALR Action entry
typedef struct {
    ActionType type;
    int value;  // state for shift, rule number for reduce
} Action;

// LALR parsing table entries
// Action table: [state][symbol] -> action
Action actionTable[NUM_STATES][NUM_SYMBOLS];

// Goto table: [state][non-terminal] -> next state
int gotoTable[NUM_STATES][3];

// Grammar rules
typedef struct {
    Symbol lhs;      // Left-hand side
    Symbol rhs[3];   // Right-hand side (max 3 symbols)
    int rhsLen;      // Number of symbols on RHS
} Rule;

Rule rules[] = {
    {E, {E, PLUS, T}, 3},    // Rule 0: E -> E + T
    {E, {T}, 1},             // Rule 1: E -> T
    {T, {T, MULT, F}, 3},    // Rule 2: T -> T * F
    {T, {F}, 1},             // Rule 3: T -> F
    {F, {LPAREN, E, RPAREN}, 3},  // Rule 4: F -> ( E )
    {F, {ID}, 1}             // Rule 5: F -> id
};

int numRules = 6;

// Global variables
char input[MAX_INPUT_SIZE];
int pos = 0;
Token currentToken;
int error = 0;
int line = 1;
int column = 1;

// Function declarations
void initializeParseTables();
void initLexer(char *str);
void lexer();
int getSymbolIndex(Symbol s);
int parseWithLALR(char *str);
void displayParsingTables();
void displayGrammar();
char* symbolToString(Symbol s);

// Convert symbol to string
char* symbolToString(Symbol s) {
    switch(s) {
        case E: return "E";
        case T: return "T";
        case F: return "F";
        case PLUS: return "+";
        case MULT: return "*";
        case LPAREN: return "(";
        case RPAREN: return ")";
        case ID: return "id";
        case DOLLAR: return "$";
        default: return "?";
    }
}

// Get symbol index for tables
int getSymbolIndex(Symbol s) {
    switch(s) {
        case PLUS: return 0;
        case MULT: return 1;
        case LPAREN: return 2;
        case RPAREN: return 3;
        case ID: return 4;
        case DOLLAR: return 5;
        default: return -1;
    }
}

// Initialize LALR parsing tables
void initializeParseTables() {
    // Initialize action table with errors
    for (int i = 0; i < NUM_STATES; i++) {
        for (int j = 0; j < NUM_SYMBOLS; j++) {
            actionTable[i][j].type = ACTION_ERROR;
            actionTable[i][j].value = 0;
        }
    }
    
    // Initialize goto table with errors
    for (int i = 0; i < NUM_STATES; i++) {
        for (int j = 0; j < 3; j++) {
            gotoTable[i][j] = -1;
        }
    }
    
    // State 0
    actionTable[0][getSymbolIndex(ID)].type = ACTION_SHIFT;
    actionTable[0][getSymbolIndex(ID)].value = 5;
    actionTable[0][getSymbolIndex(LPAREN)].type = ACTION_SHIFT;
    actionTable[0][getSymbolIndex(LPAREN)].value = 4;
    gotoTable[0][0] = 1;  // E
    gotoTable[0][1] = 2;  // T
    gotoTable[0][2] = 3;  // F
    
    // State 1
    actionTable[1][getSymbolIndex(PLUS)].type = ACTION_SHIFT;
    actionTable[1][getSymbolIndex(PLUS)].value = 6;
    actionTable[1][getSymbolIndex(DOLLAR)].type = ACTION_ACCEPT;
    actionTable[1][getSymbolIndex(DOLLAR)].value = 0;
    
    // State 2
    actionTable[2][getSymbolIndex(PLUS)].type = ACTION_REDUCE;
    actionTable[2][getSymbolIndex(PLUS)].value = 1;
    actionTable[2][getSymbolIndex(MULT)].type = ACTION_SHIFT;
    actionTable[2][getSymbolIndex(MULT)].value = 7;
    actionTable[2][getSymbolIndex(RPAREN)].type = ACTION_REDUCE;
    actionTable[2][getSymbolIndex(RPAREN)].value = 1;
    actionTable[2][getSymbolIndex(DOLLAR)].type = ACTION_REDUCE;
    actionTable[2][getSymbolIndex(DOLLAR)].value = 1;
    
    // State 3
    actionTable[3][getSymbolIndex(PLUS)].type = ACTION_REDUCE;
    actionTable[3][getSymbolIndex(PLUS)].value = 3;
    actionTable[3][getSymbolIndex(MULT)].type = ACTION_REDUCE;
    actionTable[3][getSymbolIndex(MULT)].value = 3;
    actionTable[3][getSymbolIndex(RPAREN)].type = ACTION_REDUCE;
    actionTable[3][getSymbolIndex(RPAREN)].value = 3;
    actionTable[3][getSymbolIndex(DOLLAR)].type = ACTION_REDUCE;
    actionTable[3][getSymbolIndex(DOLLAR)].value = 3;
    
    // State 4
    actionTable[4][getSymbolIndex(ID)].type = ACTION_SHIFT;
    actionTable[4][getSymbolIndex(ID)].value = 5;
    actionTable[4][getSymbolIndex(LPAREN)].type = ACTION_SHIFT;
    actionTable[4][getSymbolIndex(LPAREN)].value = 4;
    gotoTable[4][0] = 8;  // E
    gotoTable[4][1] = 2;  // T
    gotoTable[4][2] = 3;  // F
    
    // State 5
    actionTable[5][getSymbolIndex(PLUS)].type = ACTION_REDUCE;
    actionTable[5][getSymbolIndex(PLUS)].value = 5;
    actionTable[5][getSymbolIndex(MULT)].type = ACTION_REDUCE;
    actionTable[5][getSymbolIndex(MULT)].value = 5;
    actionTable[5][getSymbolIndex(RPAREN)].type = ACTION_REDUCE;
    actionTable[5][getSymbolIndex(RPAREN)].value = 5;
    actionTable[5][getSymbolIndex(DOLLAR)].type = ACTION_REDUCE;
    actionTable[5][getSymbolIndex(DOLLAR)].value = 5;
    
    // State 6
    actionTable[6][getSymbolIndex(ID)].type = ACTION_SHIFT;
    actionTable[6][getSymbolIndex(ID)].value = 5;
    actionTable[6][getSymbolIndex(LPAREN)].type = ACTION_SHIFT;
    actionTable[6][getSymbolIndex(LPAREN)].value = 4;
    gotoTable[6][1] = 9;  // T
    gotoTable[6][2] = 3;  // F
    
    // State 7
    actionTable[7][getSymbolIndex(ID)].type = ACTION_SHIFT;
    actionTable[7][getSymbolIndex(ID)].value = 5;
    actionTable[7][getSymbolIndex(LPAREN)].type = ACTION_SHIFT;
    actionTable[7][getSymbolIndex(LPAREN)].value = 4;
    gotoTable[7][2] = 10; // F
    actionTable[8][getSymbolIndex(PLUS)].type = ACTION_SHIFT;
    actionTable[8][getSymbolIndex(PLUS)].value = 6;
    actionTable[8][getSymbolIndex(RPAREN)].type = ACTION_SHIFT;
    actionTable[8][getSymbolIndex(RPAREN)].value = 11;
    
    // State 9
    actionTable[9][getSymbolIndex(PLUS)].type = ACTION_REDUCE;
    actionTable[9][getSymbolIndex(PLUS)].value = 0;
    actionTable[9][getSymbolIndex(MULT)].type = ACTION_SHIFT;
    actionTable[9][getSymbolIndex(MULT)].value = 7;
    actionTable[9][getSymbolIndex(RPAREN)].type = ACTION_REDUCE;
    actionTable[9][getSymbolIndex(RPAREN)].value = 0;
    actionTable[9][getSymbolIndex(DOLLAR)].type = ACTION_REDUCE;
    actionTable[9][getSymbolIndex(DOLLAR)].value = 0;
    
    // State 10
    actionTable[10][getSymbolIndex(PLUS)].type = ACTION_REDUCE;
    actionTable[10][getSymbolIndex(PLUS)].value = 2;
    actionTable[10][getSymbolIndex(MULT)].type = ACTION_REDUCE;
    actionTable[10][getSymbolIndex(MULT)].value = 2;
    actionTable[10][getSymbolIndex(RPAREN)].type = ACTION_REDUCE;
    actionTable[10][getSymbolIndex(RPAREN)].value = 2;
    actionTable[10][getSymbolIndex(DOLLAR)].type = ACTION_REDUCE;
    actionTable[10][getSymbolIndex(DOLLAR)].value = 2;
    
    // State 11
    actionTable[11][getSymbolIndex(PLUS)].type = ACTION_REDUCE;
    actionTable[11][getSymbolIndex(PLUS)].value = 4;
    actionTable[11][getSymbolIndex(MULT)].type = ACTION_REDUCE;
    actionTable[11][getSymbolIndex(MULT)].value = 4;
    actionTable[11][getSymbolIndex(RPAREN)].type = ACTION_REDUCE;
    actionTable[11][getSymbolIndex(RPAREN)].value = 4;
    actionTable[11][getSymbolIndex(DOLLAR)].type = ACTION_REDUCE;
    actionTable[11][getSymbolIndex(DOLLAR)].value = 4;
    
    // State 12
    actionTable[12][getSymbolIndex(PLUS)].type = ACTION_REDUCE;
    actionTable[12][getSymbolIndex(PLUS)].value = 2;
    actionTable[12][getSymbolIndex(MULT)].type = ACTION_REDUCE;
    actionTable[12][getSymbolIndex(MULT)].value = 2;
    actionTable[12][getSymbolIndex(RPAREN)].type = ACTION_REDUCE;
    actionTable[12][getSymbolIndex(RPAREN)].value = 2;
    actionTable[12][getSymbolIndex(DOLLAR)].type = ACTION_REDUCE;
    actionTable[12][getSymbolIndex(DOLLAR)].value = 2;
}

// Initialize lexer
void initLexer(char *str) {
    strcpy(input, str);
    pos = 0;
    error = 0;
    line = 1;
    column = 1;
}

// Get next token
void lexer() {
    // Skip whitespace
    while (pos < strlen(input) && isspace(input[pos])) {
        if (input[pos] == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        pos++;
    }
    
    if (pos >= strlen(input)) {
        currentToken.type = TK_DOLLAR;
        strcpy(currentToken.value, "$");
        return;
    }
    
    char ch = input[pos];
    
    // Identifiers and numbers
    if (isalpha(ch) || ch == '_') {
        int start = pos;
        while (pos < strlen(input) && (isalnum(input[pos]) || input[pos] == '_')) {
            pos++;
        }
        strncpy(currentToken.value, &input[start], pos - start);
        currentToken.value[pos - start] = '\0';
        currentToken.type = TK_ID;
        return;
    }
    
    if (isdigit(ch)) {
        int start = pos;
        while (pos < strlen(input) && isdigit(input[pos])) {
            pos++;
        }
        strncpy(currentToken.value, &input[start], pos - start);
        currentToken.value[pos - start] = '\0';
        currentToken.type = TK_ID;
        return;
    }
    
    // Operators and delimiters
    switch (ch) {
        case '+':
            currentToken.type = TK_PLUS;
            strcpy(currentToken.value, "+");
            pos++;
            break;
        case '*':
            currentToken.type = TK_MULT;
            strcpy(currentToken.value, "*");
            pos++;
            break;
        case '(':
            currentToken.type = TK_LPAREN;
            strcpy(currentToken.value, "(");
            pos++;
            break;
        case ')':
            currentToken.type = TK_RPAREN;
            strcpy(currentToken.value, ")");
            pos++;
            break;
        default:
            currentToken.type = TK_ERROR;
            strcpy(currentToken.value, "?");
            pos++;
    }
    column++;
}

// Convert token type to symbol
Symbol tokenToSymbol(TokenType type) {
    switch(type) {
        case TK_PLUS: return PLUS;
        case TK_MULT: return MULT;
        case TK_LPAREN: return LPAREN;
        case TK_RPAREN: return RPAREN;
        case TK_ID: return ID;
        case TK_DOLLAR: return DOLLAR;
        default: return -1;
    }
}

// Display grammar
void displayGrammar() {
    printf("\n========== GRAMMAR ==========\n");
    printf("0. E -> E + T\n");
    printf("1. E -> T\n");
    printf("2. T -> T * F\n");
    printf("3. T -> F\n");
    printf("4. F -> ( E )\n");
    printf("5. F -> id\n");
    printf("=============================\n\n");
}

// Display parsing tables
void displayParsingTables() {
    printf("\n========== LALR PARSING TABLES ==========\n");
    printf("Action Table (Sample):\n");
    printf("State | +      | *      | (      | )      | id     | $\n");
    printf("------+--------+--------+--------+--------+--------+--------\n");
    printf("  0   | --     | --     | s4     | --     | s5     | --\n");
    printf("  1   | s6     | --     | --     | --     | --     | acc\n");
    printf("  2   | r1     | s7     | --     | r1     | --     | r1\n");
    printf("  3   | r3     | r3     | --     | r3     | --     | r3\n");
    printf("  4   | --     | --     | s4     | --     | s5     | --\n");
    printf("  5   | r5     | r5     | --     | r5     | --     | r5\n");
    printf("  6   | --     | --     | s4     | --     | s5     | --\n");
    printf("  7   | --     | --     | s4     | --     | s5     | --\n");
    printf("  8   | s6     | --     | --     | s11    | --     | --\n");
    printf("  9   | r0     | s7     | --     | r0     | --     | r0\n");
    printf(" 10   | r2     | r2     | --     | r2     | --     | r2\n");
    printf(" 11   | r4     | r4     | --     | r4     | --     | r4\n");
    printf(" 12   | r2     | r2     | --     | r2     | --     | r2\n");
    printf("\nNote: s# = shift to state #, r# = reduce by rule #, acc = accept\n");
    printf("=========================================\n\n");
}

// LALR Parsing
int parseWithLALR(char *str) {
    initLexer(str);
    lexer();
    
    printf("\n========== LALR PARSING ==========\n");
    printf("Input: %s\n\n", str);
    
    StackEntry stack[MAX_STACK_SIZE];
    int stackTop = 0;
    int step = 1;
    
    // Initialize stack with state 0
    stack[0].state = 0;
    stack[0].symbol = DOLLAR;
    strcpy(stack[0].value, "$");
    
    printf("Step %d: Initialize parser with state 0\n", step++);
    printf("  Stack: [0:$]\n\n");
    
    while (1) {
        int currentState = stack[stackTop].state;
        Symbol currentSymbol = tokenToSymbol(currentToken.type);
        int symIndex = getSymbolIndex(currentSymbol);
        
        if (symIndex < 0) {
            printf("  ERROR: Invalid symbol\n");
            printf("\n✗ PARSING FAILED\n");
            printf("==================================\n\n");
            return 0;
        }
        
        Action action = actionTable[currentState][symIndex];
        
        printf("Step %d: State %d, Token '%s'\n", step++, currentState, currentToken.value);
        
        if (action.type == ACTION_ERROR) {
            printf("  ACTION: Error - No action defined\n");
            printf("\n✗ PARSING FAILED\n");
            printf("==================================\n\n");
            return 0;
        } else if (action.type == ACTION_SHIFT) {
            printf("  ACTION: Shift to state %d\n", action.value);
            stackTop++;
            stack[stackTop].state = action.value;
            stack[stackTop].symbol = currentSymbol;
            strcpy(stack[stackTop].value, currentToken.value);
            
            printf("  Stack: ");
            for (int i = 0; i <= stackTop; i++) {
                printf("[%d:%s] ", stack[i].state, symbolToString(stack[i].symbol));
            }
            printf("\n\n");
            
            lexer();  // Get next token
        } else if (action.type == ACTION_REDUCE) {
            int ruleNum = action.value;
            Rule rule = rules[ruleNum];
            
            printf("  ACTION: Reduce by rule %d: %s ->", ruleNum, symbolToString(rule.lhs));
            for (int i = 0; i < rule.rhsLen; i++) {
                printf(" %s", symbolToString(rule.rhs[i]));
            }
            printf("\n");
            
            // Pop RHS symbols from stack (but keep the state before them)
            int popCount = rule.rhsLen;
            int prevState = (stackTop >= popCount) ? stack[stackTop - popCount].state : stack[0].state;
            
            stackTop -= popCount;
            
            // Get next state from goto table using non-terminal index
            int ntIndex = rule.lhs;  // E=0, T=1, F=2
            int nextState = gotoTable[prevState][ntIndex];
            
            if (nextState < 0) {
                printf("  ERROR: Invalid goto state from state %d, non-terminal %s\n", prevState, symbolToString(rule.lhs));
                printf("\n✗ PARSING FAILED\n");
                printf("==================================\n\n");
                return 0;
            }
            
            stackTop++;
            stack[stackTop].state = nextState;
            stack[stackTop].symbol = rule.lhs;
            strcpy(stack[stackTop].value, symbolToString(rule.lhs));
            
            printf("  Stack: ");
            for (int i = 0; i <= stackTop; i++) {
                printf("[%d:%s] ", stack[i].state, symbolToString(stack[i].symbol));
            }
            printf("\n\n");
        } else if (action.type == ACTION_ACCEPT) {
            printf("  ACTION: Accept\n");
            printf("\n✓ PARSING SUCCESSFUL\n");
            printf("==================================\n\n");
            return 1;
        }
    }
    
    return 0;
}

// Main function
int main() {
    printf("==================== LALR PARSER ====================\n\n");
    
    initializeParseTables();
    
    displayGrammar();
    displayParsingTables();
    
    printf("This parser uses LALR(1) parsing algorithm.\n");
    printf("Supported operators: + (addition), * (multiplication)\n");
    printf("Parentheses for grouping, identifiers for operands\n\n");
    printf("====================================================\n");
    
    // Test cases
    char *testCases[] = {
        "id",                  // Valid: single identifier
        "id + id",             // Valid: addition
        "id * id",             // Valid: multiplication
        "id + id * id",        // Valid: precedence (multiply first)
        "( id + id ) * id",    // Valid: parentheses
        "id * id + id",        // Valid: precedence (multiply first)
        "( ( id ) )",          // Valid: nested parentheses
        "id +",                // Invalid: missing operand
        "id + *",              // Invalid: missing operand
        "( id + id",           // Invalid: missing closing paren
    };
    
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    int successCount = 0;
    
    printf("\n");
    for (int i = 0; i < numTests; i++) {
        if (parseWithLALR(testCases[i])) {
            successCount++;
        }
    }
    
    printf("===============================================\n");
    printf("SUMMARY: %d/%d tests passed\n", successCount, numTests);
    printf("===============================================\n");
    
    return 0;
}
