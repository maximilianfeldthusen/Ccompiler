## Documentation

### Tokenizer and Parser for Simple Assignments in C


Simple C program that implements a simple tokenizer and parser for basic assignment statements. The program is designed to read a string of code, tokenize it into meaningful components, and then parse those tokens to validate and interpret simple variable assignments. 

###   Tokenization: 
The process of breaking down a string of text into smaller, manageable pieces called tokens.
###   Parsing: 
The process of analyzing a sequence of tokens to determine its grammatical structure.
###   Data Structures: 
The use of structures and enumerations to represent tokens and their types.

### The program defines various token types, including integers, identifiers, and operators, and uses an array to store these tokens for further processing.

### The code is structured into several components:

###  Includes and Definitions: Necessary libraries and constants are defined.

###  Token Enumeration and Structure: An enumeration for token types and a structure to hold token data.

###   Tokenization Function:
A function that processes the input string and populates the token array.

###    Parsing Function:
A function that interprets the tokens and checks for syntactical correctness.

###   Main Function:
The entry point of the program that executes the tokenization and parsing.


## the Code

#### Tokenization: 
The tokenize function reads the input string character by character, identifying and categorizing tokens based on their type (integer, identifier, operator, etc.). It handles whitespace and stores valid tokens in an array.

#### Parsing:
The parse function iterates through the token array, checking for the correct sequence of tokens that form valid assignment statements. It validates the presence of identifiers, assignment operators, integers, and semicolons, providing error messages for any discrepancies.

#### Main Function: 
The main function serves as the entry point, where an example input string is defined, and the tokenization and parsing processes are executed.

### Limitations:

It only handles addition and does not support more complex expressions or operator precedence.
 The program does not store or evaluate the values of variables that are used in expressions etc.



![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
