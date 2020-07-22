```diff
- # ERPLAG Compiler
```
This was my semester long project for Compiler Construction (CS F363) course at BITS Pilani, Spring 2020.

## ERPLAG (Toy Language) Details

ERPLAG is a toy language made for the course. Details of which can be looked at inside [Language Details](https://github.com/iamishansharma/Compiler-Construction-CS-F363/tree/master/Language%20Details) folder.

## Modules

### Lexer (lexer.c)

- This module reads the source code in HLL as a stream of charaters and converts sequence of characters to meaningful tokens. 
- The tokens are passed to the parser and contains information about the line of occurance, name of the token, token id etc.

### Parser (parser.c)

- Parser takes in the sequence of tokens and verifies the syntactical correctness of the source code by constructing the parse tree. 
- The Parser also has error recovery mechanism to parse the complete sequence of tokens even if a syntactical error exist.

### AST Construction (ast.c) 

1. Delete all the irrelevant tokens 
2. Changes the structure of <expressions> to infix notation (for proper checking and evaluation)
3. Removes chaining in tree
4. Removes empty non-terminals.
	
### Symbol Table and Scoping (SymbolTable.c) 	

- This module constructs the symbol-table for the corresponding AST. 
- The symbol table has a tree structure that depicts the scoping of the blocks of code. 
- Each node of the tree has a linked list of its locally defined variables. 
- It also reports the errors related to redundant declaration, no declaration of variables and modules.

### Type Checker and Semantic Analyser (TypeChecker.c)

- This module performs semantic checks on the AST for verifiying semantic correctness of the source code. 
- It also determines the correctness of the expressions.

### Code Generation (CodeGen.c)

- Generates the NASM-assembly code of the source code.

## Compatibility and Pre-requisites

- Unix (Linux / Mac)
- gcc 5.4.0 and up
- NASM version 2.12.01 and up

## Testcases

All the testcases are present inside [Testcases](https://github.com/iamishansharma/Compiler-Construction-CS-F363/tree/master/Testcases) folder.

- c1 - c6 and v1 - v11 pertain to Code Gen testcases specifically
- All other testcases can be used to check different translational phases of the compiler
- sampless.txt can be used to verify Symbol Table Creation / Visual Presentation

## Execution Instructions

- Download this repo and change directory to [Code](https://github.com/iamishansharma/Compiler-Construction-CS-F363/tree/master/Code) folder.
- Run `make`
- Executable `compiler` would be created.
- You can use `make clean` to delete the old executable.

### > If you don't want to run Code Gen

- Run `./compiler {path_to_testcase/*.txt} {parseTree_file_name.txt}`
- Eg. Run `./compiler ../Testcases/t1.txt parseTree.txt`

### > If you want to run Code Gen

- Run `./compiler {path_to_testcase/*.txt} {Assembly_file_name.asm}`
- Eg. Run `./compiler ../Testcases/c1.txt code.asm`

## Execution Instructions for Code Gen Assembly File

### For Linux

- `nasm -f elf64 -o code.o {Assembly_file_name}.asm`
- `gcc -no-pie code.o -o code`
- `./code`
