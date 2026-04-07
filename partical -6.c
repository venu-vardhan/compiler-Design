#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 256
#define MAX_STACK_SIZE 256
#define MAX_OPERATORS 10

// Operator precedence relations
typedef enum {
    GREATER = '>',
    LESS = '<',
    EQUAL = '=',
    NONE = ' '
} Relation;

// Token types
typedef enum {
    TK_ID,      // identifier
    TK_PLUS,    // +
    TK_MINUS,   // -
    TK_MULT,    // *
    TK_DIV,     // /
    TK_MOD,     // %
    TK_POWER,   // ^
    TK_LPAREN,  // (
    TK_RPAREN,  // )
    TK_DOLLAR,  // $ (end of input)
    TK_ERROR    // error
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[50];
} Token;

// Stack entry
typedef struct {
    int isOperator;  // 1 if operator, 0 if operand
    Token token;
} StackEntry;

// Global variables
char input[MAX_INPUT_SIZE];
int pos = 0;
Token currentToken;
int error = 0;

// Operator precedence table
// Rows and Columns: +, -, *, /, %, ^, (, ), $
char precedenceTable[9][9] = {
    //  +    -    *    /    %    ^    (    )    $
    {  '>',  '>', '<',  '<', '<', '<', '<', '>', '>' },  // +
    {  '>',  '>', '<',  '<', '<', '<', '<', '>', '>' },  // -
    {  '>',  '>', '>',  '>', '>', '<', '<', '>', '>' },  // *
    {  '>',  '>', '>',  '>', '>', '<', '<', '>', '>' },  // /
    {  '>',  '>', '>',  '>', '>', '<', '<', '>', '>' },  // %
    {  '>',  '>', '>',  '>', '>', '>', '<', '>', '>' },  // ^ (right associative)
    {  '<',  '<', '<',  '<', '<', '<', '<', '=', ' ' },  // (
    {  '>',  '>', '>',  '>', '>', '>', ' ', '>', '>' },  // )
    {  '<',  '<', '<',  '<', '<', '<', '<', ' ', ' ' }    // $
};

// Function declarations
void initLexer(char *str);
void lexer();
void advance();
int getTokenIndex(Token t);
Token makeToken(TokenType type, char *value);
Relation getPrecedence(Token op1, Token op2);
int parseExpression(char *str);
void displayPrecedenceTable();
void displayGrammar();
void applyOperator(StackEntry *stack, int *top, Token op);

// Initialize lexer
void initLexer(char *str) {
    strcpy(input, str);
    pos = 0;
    error = 0;
}

// Make token
Token makeToken(TokenType type, char *value) {
    Token t;
    t.type = type;
    strcpy(t.value, value);
    return t;
}

// Get token type string
char* getTokenTypeString(TokenType type) {
    switch(type) {
        case TK_ID: return "id";
        case TK_PLUS: return "+";
        case TK_MINUS: return "-";
        case TK_MULT: return "*";
        case TK_DIV: return "/";
        case TK_MOD: return "%";
        case TK_POWER: return "^";
        case TK_LPAREN: return "(";
        case TK_RPAREN: return ")";
        case TK_DOLLAR: return "$";
        default: return "?";
    }
}

// Get token index for precedence table
int getTokenIndex(Token t) {
    switch(t.type) {
        case TK_PLUS: return 0;
        case TK_MINUS: return 1;
        case TK_MULT: return 2;
        case TK_DIV: return 3;
        case TK_MOD: return 4;
        case TK_POWER: return 5;
        case TK_LPAREN: return 6;
        case TK_RPAREN: return 7;
        case TK_DOLLAR: return 8;
        default: return -1;
    }
}

// Get next token
void lexer() {
    // Skip whitespace
    while (pos < strlen(input) && isspace(input[pos])) {
        pos++;
    }
    
    if (pos >= strlen(input)) {
        currentToken = makeToken(TK_DOLLAR, "$");
        return;
    }
    
    char ch = input[pos];
    
    // Identifiers and numbers
    if (isalpha(ch) || isdigit(ch) || ch == '_') {
        int start = pos;
        while (pos < strlen(input) && (isalnum(input[pos]) || input[pos] == '_')) {
            pos++;
        }
        char id[50];
        strncpy(id, &input[start], pos - start);
        id[pos - start] = '\0';
        currentToken = makeToken(TK_ID, id);
        return;
    }
    
    // Operators and delimiters
    currentToken.value[1] = '\0';
    
    switch (ch) {
        case '+':
            currentToken = makeToken(TK_PLUS, "+");
            pos++;
            break;
        case '-':
            currentToken = makeToken(TK_MINUS, "-");
            pos++;
            break;
        case '*':
            currentToken = makeToken(TK_MULT, "*");
            pos++;
            break;
        case '/':
            currentToken = makeToken(TK_DIV, "/");
            pos++;
            break;
        case '%':
            currentToken = makeToken(TK_MOD, "%");
            pos++;
            break;
        case '^':
            currentToken = makeToken(TK_POWER, "^");
            pos++;
            break;
        case '(':
            currentToken = makeToken(TK_LPAREN, "(");
            pos++;
            break;
        case ')':
            currentToken = makeToken(TK_RPAREN, ")");
            pos++;
            break;
        default:
            currentToken = makeToken(TK_ERROR, "?");
            pos++;
    }
}

// Check if token is operator
int isOperator(Token t) {
    int idx = getTokenIndex(t);
    return idx >= 0 && idx < 9;
}

// Check if token is operand
int isOperand(Token t) {
    return t.type == TK_ID;
}

// Get precedence relation between two operators
Relation getPrecedence(Token op1, Token op2) {
    int i = getTokenIndex(op1);
    int j = getTokenIndex(op2);
    
    if (i < 0 || j < 0) return NONE;
    
    return (Relation)precedenceTable[i][j];
}

// Apply operator and show reduction
void applyOperator(StackEntry *stack, int *top, Token op) {
    if (*top >= 2) {
        printf("    Reduce: %s %s %s\n", 
               stack[*top-2].token.value,
               op.value,
               stack[*top].token.value);
        (*top) -= 2;
    }
}

// Display precedence table
void displayPrecedenceTable() {
    printf("\n========== OPERATOR PRECEDENCE TABLE ==========\n");
    printf("Symbols: + - * / %% ^ ( ) $\n");
    printf("<  : Lower precedence (reduce first)\n");
    printf(">  : Higher precedence (shift)\n");
    printf("=  : Same precedence (reduce)\n\n");
    
    char *ops[] = {"+", "-", "*", "/", "%", "^", "(", ")", "$"};
    
    printf("      |   +  |  -   |  *   |  /   |  %%   |  ^   |  (   |  )   |  $\n");
    printf("------+------+------+------+------+------+------+------+------+-----\n");
    
    for (int i = 0; i < 9; i++) {
        printf("  %2s  |", ops[i]);
        for (int j = 0; j < 9; j++) {
            printf("  %c  |", precedenceTable[i][j]);
        }
        printf("\n");
    }
    printf("===============================================\n\n");
}

// Display grammar
void displayGrammar() {
    printf("\n========== GRAMMAR ==========\n");
    printf("E -> E op E | id\n");
    printf("where op ∈ {+, -, *, /, %, ^}\n");
    printf("=============================\n\n");
}

// Operator precedence parsing algorithm
int parseExpression(char *str) {
    initLexer(str);
    lexer();
    
    StackEntry stack[MAX_STACK_SIZE];
    int top = -1;
    int step = 1;
    
    printf("\n========== OPERATOR PRECEDENCE PARSING ==========\n");
    printf("Input: %s\n\n", str);
    
    // Push $ to stack
    stack[++top].isOperator = 1;
    stack[top].token = makeToken(TK_DOLLAR, "$");
    
    printf("Step %d: Push $ to stack\n", step++);
    printf("  Stack: $\n\n");
    
    while (1) {
        Token lookahead = currentToken;
        
        // Need an operand first
        if (!isOperand(lookahead)) {
            if (lookahead.type == TK_DOLLAR && top > 0 && !stack[top].isOperator) {
                // Check if stack has single expression
                int exprCount = 0;
                for (int i = 0; i <= top; i++) {
                    if (!stack[i].isOperator) exprCount++;
                }
                if (exprCount == 1) {
                    printf("\n✓ PARSING SUCCESSFUL\n");
                    printf("==================================================\n\n");
                    return 1;
                }
            }
            printf("  ERROR: Expected operand\n");
            printf("\n✗ PARSING FAILED\n");
            printf("==================================================\n\n");
            return 0;
        }
        
        // Push operand
        stack[++top].isOperator = 0;
        stack[top].token = lookahead;
        printf("Step %d: Push operand '%s'\n", step++, lookahead.value);
        printf("  Stack: ");
        for (int i = 0; i <= top; i++) {
            printf("%s ", stack[i].token.value);
        }
        printf("\n\n");
        
        lexer();  // Get next token (operator)
        lookahead = currentToken;
        
        // Now we need an operator or $
        while (isOperator(lookahead)) {
            // Find the last operator on stack (before operands)
            int lastOpIdx = -1;
            for (int i = top; i >= 0; i--) {
                if (stack[i].isOperator) {
                    lastOpIdx = i;
                    break;
                }
            }
            
            if (lastOpIdx < 0) {
                printf("Step %d: Push operator '%s'\n", step++, lookahead.value);
                stack[++top].isOperator = 1;
                stack[top].token = lookahead;
                printf("  Stack: ");
                for (int i = 0; i <= top; i++) {
                    printf("%s ", stack[i].token.value);
                }
                printf("\n\n");
                
                lexer();
                lookahead = currentToken;
                break;  // Go back to get operand
            }
            
            Token lastOp = stack[lastOpIdx].token;
            Relation rel = getPrecedence(lastOp, lookahead);
            
            printf("Step %d: Compare '%s' and '%s'\n", step++, lastOp.value, lookahead.value);
            printf("  Relation: %c\n", rel);
            
            if (rel == GREATER || rel == EQUAL) {
                // Reduce
                printf("  Action: Reduce\n");
                
                if (top < 2) {
                    printf("  ERROR: Not enough operands for reduction\n");
                    printf("\n✗ PARSING FAILED\n");
                    printf("==================================================\n\n");
                    return 0;
                }
                
                // Show reduction
                printf("    Reduce: %s %s %s\n", 
                       stack[top-2].token.value,
                       lastOp.value,
                       stack[top].token.value);
                
                // Pop operand, operator, operand
                StackEntry op2 = stack[top--];
                StackEntry op = stack[top--];
                StackEntry op1 = stack[top--];
                
                // Push result (new operand)
                stack[++top].isOperator = 0;
                stack[top].token = makeToken(TK_ID, "expr");
                
                printf("  Stack: ");
                for (int i = 0; i <= top; i++) {
                    printf("%s ", stack[i].token.value);
                }
                printf("\n\n");
                // Loop back to check with same lookahead
                continue;
            } else if (rel == LESS) {
                // Shift
                printf("  Action: Shift\n");
                stack[++top].isOperator = 1;
                stack[top].token = lookahead;
                printf("  Stack: ");
                for (int i = 0; i <= top; i++) {
                    printf("%s ", stack[i].token.value);
                }
                printf("\n\n");
                
                lexer();
                lookahead = currentToken;
                break;  // Go back to get operand
            } else {
                // No relation
                if (lookahead.type == TK_DOLLAR && lastOp.type == TK_DOLLAR) {
                    // End of input reached successfully
                    printf("  Action: Accept (end of input)\n");
                    printf("\n✓ PARSING SUCCESSFUL\n");
                    printf("==================================================\n\n");
                    return 1;
                }
                printf("  ERROR: No precedence relation\n");
                printf("\n✗ PARSING FAILED\n");
                printf("==================================================\n\n");
                return 0;
            }
        }
        
        // Check if we're done
        if (lookahead.type == TK_DOLLAR) {
            // Stack should have $ and expr
            if (top == 1 && stack[0].token.type == TK_DOLLAR && !stack[1].isOperator) {
                printf("✓ PARSING SUCCESSFUL\n");
                printf("==================================================\n\n");
                return 1;
            } else {
                printf("Final state: Invalid\n");
                printf("✗ PARSING FAILED\n");
                printf("==================================================\n\n");
                return 0;
            }
        }
    }
    
    return 0;
}
int main() {
    printf("==================== OPERATOR PRECEDENCE PARSER ====================\n\n");
    
    displayGrammar();
    displayPrecedenceTable();
    
    printf("This parser uses operator precedence to parse arithmetic expressions.\n");
    printf("Supported operators:\n");
    printf("  + (addition)       - (subtraction)\n");
    printf("  * (multiplication) / (division)\n");
    printf("  %% (modulo)         ^ (exponentiation - right associative)\n");
    printf("Identifiers: letters, digits, underscore\n\n");
    printf("===================================================================\n");
    
    // Test cases
    char *testCases[] = {
        "id",                          // Valid: single identifier
        "id + id",                     // Valid: addition
        "id * id",                     // Valid: multiplication
        "id + id * id",                // Valid: precedence test
        "id * id + id",                // Valid: precedence test
        "id ^ id ^ id",                // Valid: right associative
        "id + id - id",                // Valid: left associative
        "id * id / id",                // Valid: left associative
        "id + id * id - id",           // Valid: complex expression
        "id + id +",                   // Invalid: missing operand
        "id + * id",                   // Invalid: missing operand
    };
    
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    int successCount = 0;
    
    printf("\n");
    for (int i = 0; i < numTests; i++) {
        if (parseExpression(testCases[i])) {
            successCount++;
        }
    }
    
    printf("===============================================\n");
    printf("SUMMARY: %d/%d tests passed\n", successCount, numTests);
    printf("===============================================\n");
    
    return 0;
}
