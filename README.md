# Ccompiler
Simple C Compiler in C

This example includes a lexer and parser with fundamental syntax checking. Keep in mind that this is a very simplified version and does not encompass the entire C language or its complexities.

Explanation

1. Tokenization: The `tokenize` function scans the input string and breaks it down into tokens. It identifies integers, identifiers, and a few operators/symbols.

2. Parsing: The `parse` function checks whether the tokens form valid statements. It ensures that each identifier is followed by an assignment operator and an integer, and it checks for a semicolon at the end.

3. Error Handling: The compiler looks for various syntax errors, such as missing assignments, invalid characters, and missing semicolons.

Limitations
- This example does not implement a complete C-like language; many features (such as function definitions, control structures, and more complex expressions) are left out.
- There are no semantic checks (like type checking).
- The code does not generate machine code; it merely interprets the statements.
- This serves only as a starting point for a more advanced compiler.

