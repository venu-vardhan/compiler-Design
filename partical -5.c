#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 256

// Token types
typedef enum {
    TK_ID,      // identifier
    TK_PLUS,    // +
    TK_MINUS,   // -
    TK_MULT,    // *
    TK_DIV,     // /
    TK_LPAREN,  // (
    TK_RPAREN,  // )
    TK_DOLLAR,  // $ (end of input)
    TK_ERROR    // error
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[50];
    int line;
    int column;
} Token;

// Global variables
char input[MAX_INPUT_SIZE];
int pos = 0;
Token currentToken;
int error = 0;
int line = 1;
int column = 1;

// Function declarations
void lexer();
void advance();
void match(TokenType type);
void error_msg(char *message);
void parseExpression();
void parseTerm();
void parseFactor();
void displayParseTree(int depth, char *node);

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
        currentToken.line = line;
        currentToken.column = column;
        return;
    }
    
    char ch = input[pos];
    currentToken.line = line;
    currentToken.column = column;
    
    // Identifiers and keywords
    if (isalpha(ch) || ch == '_') {
        int start = pos;
        while (pos < strlen(input) && (isalnum(input[pos]) || input[pos] == '_')) {
            pos++;
        }
        strncpy(currentToken.value, &input[start], pos - start);
        currentToken.value[pos - start] = '\0';
        currentToken.type = TK_ID;
        column += pos - start;
        return;
    }
    
    // Numbers
    if (isdigit(ch)) {
        int start = pos;
        while (pos < strlen(input) && isdigit(input[pos])) {
            pos++;
        }
        strncpy(currentToken.value, &input[start], pos - start);
        currentToken.value[pos - start] = '\0';
        currentToken.type = TK_ID;  // Treat numbers as identifiers
        column += pos - start;
        return;
    }
    
    // Operators and delimiters
    currentToken.value[1] = '\0';
    
    switch (ch) {
        case '+':
            currentToken.type = TK_PLUS;
            strcpy(currentToken.value, "+");
            break;
        case '-':
            currentToken.type = TK_MINUS;
            strcpy(currentToken.value, "-");
            break;
        case '*':
            currentToken.type = TK_MULT;
            strcpy(currentToken.value, "*");
            break;
        case '/':
            currentToken.type = TK_DIV;
            strcpy(currentToken.value, "/");
            break;
        case '(':
            currentToken.type = TK_LPAREN;
            strcpy(currentToken.value, "(");
            break;
        case ')':
            currentToken.type = TK_RPAREN;
            strcpy(currentToken.value, ")");
            break;
        default:
            currentToken.type = TK_ERROR;
            strcpy(currentToken.value, "?");
    }
    
    pos++;
    column++;
}

// Advance to next token
void advance() {
    printf("    Match '%s'\n", currentToken.value);
    lexer();
    if (currentToken.type == TK_ERROR) {
        char msg[100];
        sprintf(msg, "Invalid character: %s", currentToken.value);
        error_msg(msg);
    }
}

// Match expected token
void match(TokenType type) {
    if (currentToken.type == type) {
        advance();
    } else {
        char msg[100];
        sprintf(msg, "Expected different token, got: %s", currentToken.value);
        error_msg(msg);
    }
}

// Error message
void error_msg(char *message) {
    printf("ERROR at Line %d, Column %d: %s\n", currentToken.line, currentToken.column, message);
    error = 1;
}

// Display parse tree node
void displayParseTree(int depth, char *node) {
    for (int i = 0; i < depth; i++) printf("  ");
    printf("|-- %s\n", node);
}

/*
   GRAMMAR:
   E  -> T E_Prime
   E' -> + T E' | - T E' | ε
   T  -> F T_Prime
   T' -> * F T' | / F T' | ε
   F  -> ( E ) | id
*/

// Parse Expression: E -> T E'
void parseExpression() {
    displayParseTree(1, "E");
    parseTerm();
    
    while (currentToken.type == TK_PLUS || currentToken.type == TK_MINUS) {
        if (currentToken.type == TK_PLUS) {
            displayParseTree(2, "+ T E'");
            match(TK_PLUS);
        } else {
            displayParseTree(2, "- T E'");
            match(TK_MINUS);
        }
        parseTerm();
    }
}

// Parse Term: T -> F T'
void parseTerm() {
    displayParseTree(2, "T");
    parseFactor();
    
    while (currentToken.type == TK_MULT || currentToken.type == TK_DIV) {
        if (currentToken.type == TK_MULT) {
            displayParseTree(3, "* F T'");
            match(TK_MULT);
        } else {
            displayParseTree(3, "/ F T'");
            match(TK_DIV);
        }
        parseFactor();
    }
}

// Parse Factor: F -> ( E ) | id
void parseFactor() {
    displayParseTree(3, "F");
    
    if (currentToken.type == TK_LPAREN) {
        displayParseTree(4, "( E )");
        match(TK_LPAREN);
        parseExpression();
        if (currentToken.type != TK_RPAREN) {
            error_msg("Expected ')'");
        } else {
            match(TK_RPAREN);
        }
    } else if (currentToken.type == TK_ID) {
        displayParseTree(4, currentToken.value);
        match(TK_ID);
    } else {
        error_msg("Expected identifier or '('");
    }
}

// Parse input and validate
int parse(char *str) {
    initLexer(str);
    lexer();
    
    printf("\n=========== RECURSIVE DESCENT PARSING ===========\n");
    printf("Input: %s\n\n", str);
    
    parseExpression();
    
    if (currentToken.type != TK_DOLLAR) {
        error_msg("Expected end of input");
    }
    
    printf("\n");
    if (error) {
        printf("✗ PARSING FAILED\n");
        printf("==================================================\n\n");
        return 0;
    } else {
        printf("✓ PARSING SUCCESSFUL\n");
        printf("==================================================\n\n");
        return 1;
    }
}

// Display grammar
void displayGrammar() {
    printf("\n========== GRAMMAR ==========\n");
    printf("E  -> T E'\n");
    printf("E' -> + T E' | - T E' | ε\n");
    printf("T  -> F T'\n");
    printf("T' -> * F T' | / F T' | ε\n");
    printf("F  -> ( E ) | id\n");
    printf("=============================\n\n");
}

// Main function
int main() {
    printf("==================== RECURSIVE DESCENT PARSER ====================\n\n");
    
    displayGrammar();
    
    printf("This parser recognizes arithmetic expressions with operators:\n");
    printf("  + (addition)  - (subtraction)\n");
    printf("  * (multiplication) / (division)\n");
    printf("Parentheses ( ) for grouping\n");
    printf("Identifiers: letters, digits, underscore\n\n");
    printf("===================================================================\n");
    
    // Test cases
    char *testCases[] = {
        "id",                          // Valid: single identifier
        "id + id",                     // Valid: addition
        "id * id",                     // Valid: multiplication
        "id + id * id",                // Valid: precedence test
        "( id + id ) * id",            // Valid: parentheses
        "id + id - id",                // Valid: multiple operations
        "( ( id ) )",                  // Valid: nested parentheses
        "id + id +",                   // Invalid: missing operand
        "id + * id",                   // Invalid: missing operand
        "( id + id",                   // Invalid: missing closing paren
        "id ) + id",                   // Invalid: extra closing paren
        "id + id * id / id - id",      // Valid: complex expression
    };
    
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    int successCount = 0;
    
    printf("\n");
    for (int i = 0; i < numTests; i++) {
        if (parse(testCases[i])) {
            successCount++;
        }
    }
    
    printf("\n===============================================\n");
    printf("SUMMARY: %d/%d tests passed\n", successCount, numTests);
    printf("===============================================\n");
    
    return 0;
}
