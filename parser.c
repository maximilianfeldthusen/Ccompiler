
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 64

typedef enum {
    TOKEN_INT,
    TOKEN_ID,
    TOKEN_SEMICOLON,
    TOKEN_ASSIGN,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_END,
    TOKEN_INVALID
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

Token tokens[MAX_TOKENS];
int token_count = 0;

// Function to tokenize input
void tokenize(const char *input) {
    const char *p = input;
    while (*p) {
        while (isspace(*p)) p++;  // Skip whitespace

        if (isdigit(*p)) {
            Token token;
            token.type = TOKEN_INT;
            int i = 0;
            while (isdigit(*p) && i < MAX_TOKEN_LENGTH - 1) {
                token.value[i++] = *p++;
            }
            token.value[i] = '\0';
            if (token_count < MAX_TOKENS) {
                tokens[token_count++] = token;
            }
        } else if (isalpha(*p)) {
            Token token;
            token.type = TOKEN_ID;
            int i = 0;
            while (isalnum(*p) && i < MAX_TOKEN_LENGTH - 1) {
                token.value[i++] = *p++;
            }
            token.value[i] = '\0';
            if (token_count < MAX_TOKENS) {
                tokens[token_count++] = token;
            }
        } else if (*p == ';') {
            Token token;
            token.type = TOKEN_SEMICOLON;
            token.value[0] = ';';
            token.value[1] = '\0';
            if (token_count < MAX_TOKENS) {
                tokens[token_count++] = token;
            }
            p++;
        } else if (*p == '=') {
            Token token;
            token.type = TOKEN_ASSIGN;
            token.value[0] = '=';
            token.value[1] = '\0';
            if (token_count < MAX_TOKENS) {
                tokens[token_count++] = token;
            }
            p++;
        } else if (*p == '+') {
            Token token;
            token.type = TOKEN_PLUS;
            token.value[0] = '+';
            token.value[1] = '\0';
            if (token_count < MAX_TOKENS) {
                tokens[token_count++] = token;
            }
            p++;
        } else if (*p == '-') {
            Token token;
            token.type = TOKEN_MINUS;
            token.value[0] = '-';
            token.value[1] = '\0';
            if (token_count < MAX_TOKENS) {
                tokens[token_count++] = token;
            }
            p++;
        } else {
            printf("Error: Invalid character '%c'\n", *p);
            exit(1);
        }
    }

    // Append end token
    Token token;
    token.type = TOKEN_END;
    tokens[token_count++] = token;
}

// Function to parse the tokens
void parse() {
    int i = 0;
    while (i < token_count) {
        Token token = tokens[i];

        // Parse assignment statement: ID '=' expression ';'
        if (token.type == TOKEN_ID) {
            printf("Found identifier: %s
", token.value);
            i++;
            if (i >= token_count || tokens[i].type != TOKEN_ASSIGN) {
                printf("Error: Expected '=' after identifier '%s'\n", token.value);
                exit(1);
            }
            i++; // move past '='

            // Parse expression (either ID or INT)
            if (i >= token_count || (tokens[i].type != TOKEN_INT && tokens[i].type != TOKEN_ID)) {
                printf("Error: Expected integer or identifier after '='\n");
                exit(1);
            }
            printf("Assigned value %s to %s
", tokens[i].value, tokens[i - 2].value);
            int lhs_index = i - 2; // index of the variable being assigned
            int rhs_index = i; // index of the value assigned
            i++; // move past the value token

            // Check for optional '+' expression
            if (i < token_count && tokens[i].type == TOKEN_PLUS) {
                i++; // move past '+'
                if (i >= token_count || (tokens[i].type != TOKEN_INT && tokens[i].type != TOKEN_ID)) {
                    printf("Error: Expected integer or identifier after '+'\n");
                    exit(1);
                }
                printf("Expression: %s + %s
", tokens[rhs_index].value, tokens[i].value);
                i++; // move past the second operand
            }

            // Expect semicolon
            if (i >= token_count || tokens[i].type != TOKEN_SEMICOLON) {
                printf("Error: Expected ';' after statement
");
                exit(1);
            }
            printf("Statement terminated with ';'\n");
            i++; // move past ';'
        } else if (token.type == TOKEN_END) {
            break;
        } else {
            printf("Error: Unexpected token '%s'\n", token.value);
            exit(1);
        }
    }
}

int main() {
    const char *input = "x = 5; y = 10; z = x + y;";  // Example input
    tokenize(input);
    parse();

    return 0;
}

