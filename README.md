## Documentation

### Overview:
The program reads a string containing multiple assignment statements, tokenizes the input into meaningful tokens (identifiers, numbers, operators, etc.), and then parses these tokens to verify the syntax of simple assignment statements with optional addition operations.

---

### Breakdown:

#### 1. **Includes and Macros:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 64
```
- Includes standard libraries for input/output, memory, string manipulation, and character classification functions.
- Defines maximum number of tokens (`MAX_TOKENS`) and maximum length of each token (`MAX_TOKEN_LENGTH`).

---

#### 2. **Token Types Enumeration:**
```c
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
```
- Defines different kinds of tokens the tokenizer can identify:
  - `TOKEN_INT`: Numeric literals.
  - `TOKEN_ID`: Identifiers (variable names).
  - `TOKEN_SEMICOLON`: The `;` character.
  - `TOKEN_ASSIGN`: The `=` character.
  - `TOKEN_PLUS`: The `+` character.
  - `TOKEN_MINUS`: The `-` character (not used in parsing here but defined).
  - `TOKEN_END`: End of input token.
  - `TOKEN_INVALID`: For invalid tokens (not used explicitly here).

---

#### 3. **Token Structure:**
```c
typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;
```
- Each token contains:
  - Its type.
  - Its string value (e.g., `"x"`, `"5"`, `"+"`).

---

#### 4. **Global Token Array and Counter:**
```c
Token tokens[MAX_TOKENS];
int token_count = 0;
```
- Stores tokens after tokenization.
- Keeps track of how many tokens are stored.

---

#### 5. **Tokenization Function (`tokenize`):**
```c
void tokenize(const char *input) {
    const char *p = input;
    while (*p) {
        while (isspace(*p)) p++;  // Skip whitespace

        // Handle numbers
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
        }
        // Handle identifiers
        else if (isalpha(*p)) {
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
        }
        // Handle specific single-character tokens
        else if (*p == ';') {
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
        }
        // Handle invalid characters
        else {
            printf("Error: Invalid character '%c'\n", *p);
            exit(1);
        }
    }

    // Append end token to mark the end of input
    Token token;
    token.type = TOKEN_END;
    tokens[token_count++] = token;
}
```
- Reads the input string character by character.
- Skips whitespace.
- Recognizes numbers, identifiers, and specific symbols, creating tokens accordingly.
- On encountering an invalid character, prints an error and exits.
- Appends a special `TOKEN_END` to mark input termination.

---

#### 6. **Parsing Function (`parse`):**
```c
void parse() {
    int i = 0;
    while (i < token_count) {
        Token token = tokens[i];

        // Parse assignment: ID '=' expression ';'
        if (token.type == TOKEN_ID) {
            printf("Found identifier: %s
", token.value);
            i++;
            // Expect '=' after ID
            if (i >= token_count || tokens[i].type != TOKEN_ASSIGN) {
                printf("Error: Expected '=' after identifier '%s'\n", token.value);
                exit(1);
            }
            i++; // move past '='

            // Expect a value (ID or INT)
            if (i >= token_count || (tokens[i].type != TOKEN_INT && tokens[i].type != TOKEN_ID)) {
                printf("Error: Expected integer or identifier after '='\n");
                exit(1);
            }
            printf("Assigned value %s to %s
", tokens[i].value, tokens[i - 2].value);
            int lhs_index = i - 2; // index of the variable being assigned
            int rhs_index = i;     // index of the value assigned
            i++; // move past the value token

            // Optional '+' expression
            if (i < token_count && tokens[i].type == TOKEN_PLUS) {
                i++; // move past '+'
                if (i >= token_count || (tokens[i].type != TOKEN_INT && tokens[i].type != TOKEN_ID)) {
                    printf("Error: Expected integer or identifier after '+'\n");
                    exit(1);
                }
                printf("Expression: %s + %s
", tokens[rhs_index].value, tokens[i].value);
                i++; // move past second operand
            }

            // Expect semicolon to end statement
            if (i >= token_count || tokens[i].type != TOKEN_SEMICOLON) {
                printf("Error: Expected ';' after statement
");
                exit(1);
            }
            printf("Statement terminated with ';'\n");
            i++; // move past ';'
        }
        // End of tokens
        else if (token.type == TOKEN_END) {
            break;
        } else {
            printf("Error: Unexpected token '%s'\n", token.value);
            exit(1);
        }
    }
}
```
- Iterates through tokens.
- Looks for assignment statements of the form: `ID = (ID | INT) [+ (ID | INT)] ;`.
- Checks for correct syntax, printing relevant messages.
- Handles optional addition operation.
- Terminates parsing at `TOKEN_END` or on errors.

---

#### 7. **Main Function:**
```c
int main() {
    const char *input = "x = 5; y = 10; z = x + y;";  // Example input
    tokenize(input);
    parse();

    return 0;
}
```
- Defines an example input string with multiple assignment statements.
- Calls `tokenize` to break input into tokens.
- Calls `parse` to analyze the tokens and validate syntax.

---

### Summary:
- **Tokenization** converts a string into a sequence of tokens.
- **Parsing** checks if tokens conform to a simple assignment syntax, handling optional addition.
- The program outputs information about the tokens it finds and reports syntax errors if encountered.

---

Let me know if you'd like further details or modifications!

