#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100
#define MAX_RULES 20
#define MAX_RULE_LENGTH 10
#define MAX_INPUT_SIZE 100

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

// Token structure
typedef struct {
    TokenType type;
    char value[20];
} Token;

// Grammar symbols
typedef enum {
    E, E_PRIME, T, T_PRIME, F,  // Non-terminals
    PLUS, MULT, LPAREN, RPAREN, ID, DOLLAR, EPSILON  // Terminals
} Symbol;

// Parsing action
typedef enum {
    SHIFT, REDUCE, ACCEPT, ERROR_ACTION
} ActionType;

// Parsing table entry
typedef struct {
    ActionType action;
    int data;  // For reduce: rule number; For shift: next state
} ParseAction;

// Stack entry
typedef struct {
    Symbol symbol;
    char value[20];
} StackEntry;

// Global variables
Token tokens[MAX_INPUT_SIZE];
int tokenCount = 0;
int currentToken = 0;
StackEntry stack[MAX_STACK_SIZE];
int stackTop = -1;

// Grammar rules (RHS only, LHS not included)
char grammar[MAX_RULES][MAX_RULE_LENGTH][20] = {
    {"T", "E'"},                 // Rule 0: E -> T E'
    {"PLUS", "T", "E'"},         // Rule 1: E' -> + T E'
    {"EPSILON"},                 // Rule 2: E' -> epsilon
    {"F", "T'"},                 // Rule 3: T -> F T'
    {"MULT", "F", "T'"},         // Rule 4: T' -> * F T'
    {"EPSILON"},                 // Rule 5: T' -> epsilon
    {"LPAREN", "E", "RPAREN"},   // Rule 6: F -> ( E )
    {"ID"}                       // Rule 7: F -> id
};

int grammarLen[MAX_RULES] = {2, 3, 1, 2, 3, 1, 3, 1};

// LHS of each grammar rule
Symbol grammarLHS[MAX_RULES] = {E, E_PRIME, E_PRIME, T, T_PRIME, T_PRIME, F, F};

// Parsing table (LL(1) table)
// Rows: Non-terminals (E, E', T, T', F)
// Columns: Terminals (id, +, *, (, ), $)
int parseTable[5][6] = {
    //  id  +   *   (   )   $
    {   0,  -1, -1, 0,  -1, -1 },  // E
    {   -1, 1,  -1, -1, 2,  2  },  // E'
    {   3,  -1, -1, 3,  -1, -1 },  // T
    {   -1, 5,  4,  -1, 5,  5  },  // T'
    {   7,  -1, -1, 6,  -1, -1 }   // F
};

// Function declarations
void tokenize(char *input);
Token getNextToken(char *str, int *pos);
Token makeToken(TokenType type, char *value);
int symbolToIndex(Symbol s);
Symbol stringToSymbol(char *str);
void pushStack(Symbol symbol, char *value);
StackEntry popStack();
StackEntry peekStack();
int parseString(char *input);
void displayParsingTable();
void displayGrammar();
void displayTokens();

// Convert symbol to string
char* symbolToString(Symbol s) {
    switch(s) {
        case E: return "E";
        case E_PRIME: return "E'";
        case T: return "T";
        case T_PRIME: return "T'";
        case F: return "F";
        case PLUS: return "+";
        case MULT: return "*";
        case LPAREN: return "(";
        case RPAREN: return ")";
        case ID: return "id";
        case DOLLAR: return "$";
        case EPSILON: return "ε";
        default: return "?";
    }
}

// Convert string to symbol
Symbol stringToSymbol(char *str) {
    if (strcmp(str, "E") == 0) return E;
    if (strcmp(str, "E'") == 0) return E_PRIME;
    if (strcmp(str, "T") == 0) return T;
    if (strcmp(str, "T'") == 0) return T_PRIME;
    if (strcmp(str, "F") == 0) return F;
    if (strcmp(str, "+") == 0) return PLUS;
    if (strcmp(str, "*") == 0) return MULT;
    if (strcmp(str, "(") == 0) return LPAREN;
    if (strcmp(str, ")") == 0) return RPAREN;
    if (strcmp(str, "id") == 0) return ID;
    if (strcmp(str, "$") == 0) return DOLLAR;
    if (strcmp(str, "epsilon") == 0) return EPSILON;
    return -1;
}

// Get non-terminal index for parsing table
int getNTIndex(Symbol s) {
    switch(s) {
        case E: return 0;
        case E_PRIME: return 1;
        case T: return 2;
        case T_PRIME: return 3;
        case F: return 4;
        default: return -1;
    }
}

// Get terminal index for parsing table
int getTerminalIndex(Token t) {
    switch(t.type) {
        case TK_ID: return 0;
        case TK_PLUS: return 1;
        case TK_MULT: return 2;
        case TK_LPAREN: return 3;
        case TK_RPAREN: return 4;
        case TK_DOLLAR: return 5;
        default: return -1;
    }
}

// Make a token
Token makeToken(TokenType type, char *value) {
    Token t;
    t.type = type;
    strcpy(t.value, value);
    return t;
}

// Tokenize input string
void tokenize(char *input) {
    tokenCount = 0;
    int pos = 0;
    
    while (input[pos] != '\0') {
        if (isspace(input[pos])) {
            pos++;
            continue;
        }
        
        if (isalpha(input[pos]) || input[pos] == '_') {
            // Identifier
            int start = pos;
            while (isalnum(input[pos]) || input[pos] == '_') {
                pos++;
            }
            char id[20];
            strncpy(id, &input[start], pos - start);
            id[pos - start] = '\0';
            tokens[tokenCount++] = makeToken(TK_ID, id);
        } else if (input[pos] == '+') {
            tokens[tokenCount++] = makeToken(TK_PLUS, "+");
            pos++;
        } else if (input[pos] == '*') {
            tokens[tokenCount++] = makeToken(TK_MULT, "*");
            pos++;
        } else if (input[pos] == '(') {
            tokens[tokenCount++] = makeToken(TK_LPAREN, "(");
            pos++;
        } else if (input[pos] == ')') {
            tokens[tokenCount++] = makeToken(TK_RPAREN, ")");
            pos++;
        } else {
            tokens[tokenCount++] = makeToken(TK_ERROR, "?");
            pos++;
        }
    }
    
    // Add end-of-input marker
    tokens[tokenCount++] = makeToken(TK_DOLLAR, "$");
}

// Push to stack
void pushStack(Symbol symbol, char *value) {
    if (stackTop < MAX_STACK_SIZE - 1) {
        stackTop++;
        stack[stackTop].symbol = symbol;
        strcpy(stack[stackTop].value, value);
    }
}

// Pop from stack
StackEntry popStack() {
    if (stackTop >= 0) {
        return stack[stackTop--];
    }
    StackEntry e;
    e.symbol = -1;
    return e;
}

// Peek stack
StackEntry peekStack() {
    if (stackTop >= 0) {
        return stack[stackTop];
    }
    StackEntry e;
    e.symbol = -1;
    return e;
}

// Display tokens
void displayTokens() {
    printf("TOKENS:\n");
    for (int i = 0; i < tokenCount; i++) {
        printf("%d. Type: %-8s Value: %s\n", i, 
            (tokens[i].type == TK_ID ? "ID" :
             tokens[i].type == TK_PLUS ? "+" :
             tokens[i].type == TK_MULT ? "*" :
             tokens[i].type == TK_LPAREN ? "(" :
             tokens[i].type == TK_RPAREN ? ")" :
             tokens[i].type == TK_DOLLAR ? "$" : "ERROR"), 
            tokens[i].value);
    }
    printf("\n");
}

// Display grammar
void displayGrammar() {
    printf("\n========== GRAMMAR ==========\n");
    printf("0. E  -> T E'\n");
    printf("1. E' -> + T E'\n");
    printf("2. E' -> ε\n");
    printf("3. T  -> F T'\n");
    printf("4. T' -> * F T'\n");
    printf("5. T' -> ε\n");
    printf("6. F  -> ( E )\n");
    printf("7. F  -> id\n");
    printf("============================\n\n");
}

// Display parsing table
void displayParsingTable() {
    printf("\n========== LL(1) PARSING TABLE ==========\n");
    printf("         |   id  |   +   |   *   |   (   |   )   |   $\n");
    printf("---------+-------+-------+-------+-------+-------+-----\n");
    printf("   E     |   0   |  ERR  |  ERR  |   0   |  ERR  | ERR\n");
    printf("   E'    |  ERR  |   1   |  ERR  |  ERR  |   2   |  2\n");
    printf("   T     |   3   |  ERR  |  ERR  |   3   |  ERR  | ERR\n");
    printf("   T'    |  ERR  |   5   |   4   |  ERR  |   5   |  5\n");
    printf("   F     |   7   |  ERR  |  ERR  |   6   |  ERR  | ERR\n");
    printf("========================================\n\n");
}

// LL(1) Predictive Parsing
int parseString(char *input) {
    tokenize(input);
    
    printf("============ PARSING PROCESS ============\n\n");
    displayTokens();
    
    // Initialize
    stackTop = -1;
    currentToken = 0;
    pushStack(DOLLAR, "$");
    pushStack(E, "E");
    
    int step = 1;
    
    while (1) {
        StackEntry top = peekStack();
        Token current = tokens[currentToken];
        
        printf("Step %d:\n", step++);
        printf("  Stack Top: %s\n", symbolToString(top.symbol));
        printf("  Current Token: %s (%s)\n", current.value, 
               current.type == TK_ID ? "id" : symbolToString(top.symbol));
        
        // If stack top is terminal
        if (top.symbol == PLUS || top.symbol == MULT || 
            top.symbol == LPAREN || top.symbol == RPAREN || 
            top.symbol == ID || top.symbol == DOLLAR) {
            
            if (top.symbol == current.type || 
                (top.symbol == ID && current.type == TK_ID) ||
                (top.symbol == PLUS && current.type == TK_PLUS) ||
                (top.symbol == MULT && current.type == TK_MULT) ||
                (top.symbol == LPAREN && current.type == TK_LPAREN) ||
                (top.symbol == RPAREN && current.type == TK_RPAREN) ||
                (top.symbol == DOLLAR && current.type == TK_DOLLAR)) {
                
                printf("  ACTION: Match '%s'\n", symbolToString(top.symbol));
                popStack();
                
                if (top.symbol == DOLLAR && current.type == TK_DOLLAR) {
                    printf("\n✓ String is ACCEPTED\n");
                    printf("==========================================\n\n");
                    return 1;
                }
                currentToken++;
            } else {
                printf("  ACTION: ERROR - Token mismatch\n");
                printf("\n✗ String is REJECTED\n");
                printf("==========================================\n\n");
                return 0;
            }
        } else {
            // Non-terminal on stack
            int ntIndex = getNTIndex(top.symbol);
            int termIndex = getTerminalIndex(current);
            
            if (ntIndex == -1 || termIndex == -1 || 
                parseTable[ntIndex][termIndex] == -1) {
                printf("  ACTION: ERROR - No entry in parsing table\n");
                printf("\n✗ String is REJECTED\n");
                printf("==========================================\n\n");
                return 0;
            }
            
            int ruleNum = parseTable[ntIndex][termIndex];
            printf("  ACTION: Reduce using rule %d: %s -> ", ruleNum, 
                   symbolToString(grammarLHS[ruleNum]));
            
            // Display rule
            for (int i = 0; i < grammarLen[ruleNum]; i++) {
                Symbol sym = stringToSymbol(grammar[ruleNum][i]);
                if (i > 0) printf(" ");
                if (sym == EPSILON) {
                    printf("ε");
                } else {
                    printf("%s", symbolToString(sym));
                }
            }
            printf("\n");
            
            popStack();
            
            // Push rule symbols (in reverse order)
            for (int i = grammarLen[ruleNum] - 1; i >= 0; i--) {
                Symbol sym = stringToSymbol(grammar[ruleNum][i]);
                if (sym != EPSILON) {
                    pushStack(sym, grammar[ruleNum][i]);
                }
            }
        }
        printf("\n");
    }
    
    return 0;
}

// Main function
int main() {
    printf("\n========== LL(1) PREDICTIVE PARSER ==========\n");
    printf("Grammar for Expression Parsing\n\n");
    
    displayGrammar();
    displayParsingTable();
    
    // Test cases
    char *testCases[] = {
        "id",
        "id + id",
        "id * id",
        "id + id * id",
        "( id + id ) * id",
        "id +",          // Invalid
        "id + *",        // Invalid
        "( id + id",     // Invalid
    };
    
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTests; i++) {
        printf("\n========== TEST CASE %d ==========\n", i + 1);
        printf("Input: %s\n", testCases[i]);
        parseString(testCases[i]);
    }
    
    return 0;
}
