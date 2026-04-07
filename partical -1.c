#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Token Types
typedef enum {
    // Keywords
    KW_IF, KW_ELSE, KW_WHILE, KW_FOR, KW_INT, KW_FLOAT, KW_CHAR, KW_RETURN, 
    KW_VOID, KW_MAIN, KW_DOUBLE, KW_STRING,
    
    // Operators
    OP_PLUS, OP_MINUS, OP_MULT, OP_DIV, OP_MOD,
    OP_ASSIGN, OP_EQ, OP_NE, OP_LT, OP_LE, OP_GT, OP_GE,
    OP_AND, OP_OR, OP_NOT, OP_INC, OP_DEC,
    OP_BITAND, OP_BITOR, OP_XOR, OP_COMPL,
    
    // Delimiters
    LPAREN, RPAREN, LBRACE, RBRACE, LBRACKET, RBRACKET,
    SEMICOLON, COMMA, DOT, COLON, ARROW,
    
    // Literals
    NUMBER, FLOAT_NUM, STRING, CHAR_CONST,
    
    // Identifiers
    IDENTIFIER,
    
    // Special
    NEWLINE,
    END_OF_FILE,
    UNKNOWN
} TokenType;

// Token Structure
typedef struct {
    TokenType type;
    char value[256];
    int line;
    int column;
} Token;

// Global variables
char input[1024];
int pos = 0;
int line = 1;
int column = 1;
int length = 0;

// Function declarations
Token getNextToken();
void displayToken(Token token);
char peek();
char peekNext();
char advance();
void skipWhitespace();
void skipComments();
int isKeyword(char *str, TokenType *type);

// Initialize the lexer with input
void initLexer(char *source) {
    strcpy(input, source);
    length = strlen(input);
    pos = 0;
    line = 1;
    column = 1;
}

// Peek at current character without consuming
char peek() {
    if (pos < length) {
        return input[pos];
    }
    return '\0';
}

// Peek at next character without consuming
char peekNext() {
    if (pos + 1 < length) {
        return input[pos + 1];
    }
    return '\0';
}

// Advance to next character
char advance() {
    if (pos < length) {
        char ch = input[pos];
        pos++;
        if (ch == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        return ch;
    }
    return '\0';
}

// Skip whitespace
void skipWhitespace() {
    while (isspace(peek())) {
        advance();
    }
}

// Skip comments
void skipComments() {
    if (peek() == '/' && peekNext() == '/') {
        // Single-line comment
        advance();
        advance();
        while (peek() != '\n' && peek() != '\0') {
            advance();
        }
    } else if (peek() == '/' && peekNext() == '*') {
        // Multi-line comment
        advance();
        advance();
        while (peek() != '\0') {
            if (peek() == '*' && peekNext() == '/') {
                advance();
                advance();
                break;
            }
            advance();
        }
    }
}

// Check if string is a keyword
int isKeyword(char *str, TokenType *type) {
    if (strcmp(str, "if") == 0) { *type = KW_IF; return 1; }
    if (strcmp(str, "else") == 0) { *type = KW_ELSE; return 1; }
    if (strcmp(str, "while") == 0) { *type = KW_WHILE; return 1; }
    if (strcmp(str, "for") == 0) { *type = KW_FOR; return 1; }
    if (strcmp(str, "int") == 0) { *type = KW_INT; return 1; }
    if (strcmp(str, "float") == 0) { *type = KW_FLOAT; return 1; }
    if (strcmp(str, "double") == 0) { *type = KW_DOUBLE; return 1; }
    if (strcmp(str, "char") == 0) { *type = KW_CHAR; return 1; }
    if (strcmp(str, "string") == 0) { *type = KW_STRING; return 1; }
    if (strcmp(str, "return") == 0) { *type = KW_RETURN; return 1; }
    if (strcmp(str, "void") == 0) { *type = KW_VOID; return 1; }
    if (strcmp(str, "main") == 0) { *type = KW_MAIN; return 1; }
    return 0;
}

// Get next token from input
Token getNextToken() {
    Token token;
    token.line = line;
    token.column = column;
    
    // Skip whitespace and comments
    while (1) {
        skipWhitespace();
        if (peek() == '/' && (peekNext() == '/' || peekNext() == '*')) {
            skipComments();
        } else {
            break;
        }
    }
    
    char ch = peek();
    int start_col = column;
    
    // Handle identifiers and keywords
    if (isalpha(ch) || ch == '_') {
        int i = 0;
        while (isalnum(peek()) || peek() == '_') {
            token.value[i++] = advance();
        }
        token.value[i] = '\0';
        
        if (isKeyword(token.value, &token.type) == 0) {
            token.type = IDENTIFIER;
        }
        return token;
    }
    
    // Handle numbers
    if (isdigit(ch)) {
        int i = 0;
        int is_float = 0;
        while (isdigit(peek()) || peek() == '.') {
            if (peek() == '.') {
                is_float = 1;
            }
            token.value[i++] = advance();
        }
        token.value[i] = '\0';
        token.type = is_float ? FLOAT_NUM : NUMBER;
        return token;
    }
    
    // Handle strings
    if (ch == '"') {
        int i = 0;
        advance(); // consume opening quote
        while (peek() != '"' && peek() != '\0') {
            if (peek() == '\\') {
                token.value[i++] = advance();
            }
            token.value[i++] = advance();
        }
        token.value[i] = '\0';
        if (peek() == '"') {
            advance(); // consume closing quote
        }
        token.type = STRING;
        return token;
    }
    
    // Handle character literals
    if (ch == '\'') {
        int i = 0;
        advance(); // consume opening quote
        while (peek() != '\'' && peek() != '\0') {
            token.value[i++] = advance();
        }
        token.value[i] = '\0';
        if (peek() == '\'') {
            advance(); // consume closing quote
        }
        token.type = CHAR_CONST;
        return token;
    }
    
    // Handle operators and delimiters
    advance();
    
    // Two-character operators
    if (ch == '+' && peek() == '+') { advance(); token.type = OP_INC; strcpy(token.value, "++"); return token; }
    if (ch == '-' && peek() == '-') { advance(); token.type = OP_DEC; strcpy(token.value, "--"); return token; }
    if (ch == '-' && peek() == '>') { advance(); token.type = ARROW; strcpy(token.value, "->"); return token; }
    if (ch == '=' && peek() == '=') { advance(); token.type = OP_EQ; strcpy(token.value, "=="); return token; }
    if (ch == '!' && peek() == '=') { advance(); token.type = OP_NE; strcpy(token.value, "!="); return token; }
    if (ch == '<' && peek() == '=') { advance(); token.type = OP_LE; strcpy(token.value, "<="); return token; }
    if (ch == '>' && peek() == '=') { advance(); token.type = OP_GE; strcpy(token.value, ">="); return token; }
    if (ch == '&' && peek() == '&') { advance(); token.type = OP_AND; strcpy(token.value, "&&"); return token; }
    if (ch == '|' && peek() == '|') { advance(); token.type = OP_OR; strcpy(token.value, "||"); return token; }
    
    // Single-character operators and delimiters
    switch (ch) {
        case '+': token.type = OP_PLUS; strcpy(token.value, "+"); break;
        case '-': token.type = OP_MINUS; strcpy(token.value, "-"); break;
        case '*': token.type = OP_MULT; strcpy(token.value, "*"); break;
        case '/': token.type = OP_DIV; strcpy(token.value, "/"); break;
        case '%': token.type = OP_MOD; strcpy(token.value, "%"); break;
        case '=': token.type = OP_ASSIGN; strcpy(token.value, "="); break;
        case '<': token.type = OP_LT; strcpy(token.value, "<"); break;
        case '>': token.type = OP_GT; strcpy(token.value, ">"); break;
        case '!': token.type = OP_NOT; strcpy(token.value, "!"); break;
        case '&': token.type = OP_BITAND; strcpy(token.value, "&"); break;
        case '|': token.type = OP_BITOR; strcpy(token.value, "|"); break;
        case '^': token.type = OP_XOR; strcpy(token.value, "^"); break;
        case '~': token.type = OP_COMPL; strcpy(token.value, "~"); break;
        case '(': token.type = LPAREN; strcpy(token.value, "("); break;
        case ')': token.type = RPAREN; strcpy(token.value, ")"); break;
        case '{': token.type = LBRACE; strcpy(token.value, "{"); break;
        case '}': token.type = RBRACE; strcpy(token.value, "}"); break;
        case '[': token.type = LBRACKET; strcpy(token.value, "["); break;
        case ']': token.type = RBRACKET; strcpy(token.value, "]"); break;
        case ';': token.type = SEMICOLON; strcpy(token.value, ";"); break;
        case ',': token.type = COMMA; strcpy(token.value, ","); break;
        case '.': token.type = DOT; strcpy(token.value, "."); break;
        case ':': token.type = COLON; strcpy(token.value, ":"); break;
        case '\n': token.type = NEWLINE; strcpy(token.value, "\\n"); break;
        case '\0': token.type = END_OF_FILE; strcpy(token.value, "EOF"); break;
        default: token.type = UNKNOWN; strcpy(token.value, "?"); break;
    }
    
    return token;
}

// Display token information
void displayToken(Token token) {
    char *token_names[] = {
        // Keywords
        "KW_IF", "KW_ELSE", "KW_WHILE", "KW_FOR", "KW_INT", "KW_FLOAT", "KW_CHAR", 
        "KW_RETURN", "KW_VOID", "KW_MAIN", "KW_DOUBLE", "KW_STRING",
        
        // Operators
        "OP_PLUS", "OP_MINUS", "OP_MULT", "OP_DIV", "OP_MOD",
        "OP_ASSIGN", "OP_EQ", "OP_NE", "OP_LT", "OP_LE", "OP_GT", "OP_GE",
        "OP_AND", "OP_OR", "OP_NOT", "OP_INC", "OP_DEC",
        "OP_BITAND", "OP_BITOR", "OP_XOR", "OP_COMPL",
        
        // Delimiters
        "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET",
        "SEMICOLON", "COMMA", "DOT", "COLON", "ARROW",
        
        // Literals
        "NUMBER", "FLOAT_NUM", "STRING", "CHAR_CONST",
        
        // Identifiers
        "IDENTIFIER",
        
        // Special
        "NEWLINE", "END_OF_FILE", "UNKNOWN"
    };
    
    printf("Line: %2d | Column: %2d | Token: %-12s | Value: '%s'\n", 
           token.line, token.column, token_names[token.type], token.value);
}

// Main function for testing
int main() {
    printf("========== LEXICAL ANALYZER TEST ==========\n\n");
    
    // Sample C code
    char code[] = "int main() {\n"
                  "    int x = 10;\n"
                  "    float y = 3.14;\n"
                  "    char ch = 'a';\n"
                  "    if (x > 5) {\n"
                  "        y = y + x;\n"
                  "    }\n"
                  "    return 0;\n"
                  "}\n";
    
    printf("Source Code:\n");
    printf("-------------------\n");
    printf("%s\n", code);
    printf("-------------------\n\n");
    
    printf("Tokens Generated:\n");
    printf("-------------------\n");
    
    initLexer(code);
    Token token;
    
    while (1) {
        token = getNextToken();
        
        if (token.type == NEWLINE) {
            printf("(newline)\n");
        } else if (token.type != END_OF_FILE) {
            displayToken(token);
        }
        
        if (token.type == END_OF_FILE) {
            displayToken(token);
            break;
        }
    }
    
    printf("-------------------\n\n");
    printf("Lexical Analysis Complete!\n");
    
    return 0;
}
