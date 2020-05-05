# Compiler-Project: CS-F363

### Group 13
 - Group Members:
	- 2017A7PS0096P - **Sahil Dubey**
	- 2017A7PS0105P - **Rohit Milind Rajhans**
	- 2017A7PS0109P - **Saujas Adarkar**

## Instructions to run
  1. run `make` to compile the code and generate executable
  2. run the file compiler as pass input test case and output filename as parameters</br>
	Example: `./compiler testcase.txt code.asm`
  3. To compile the `code.asm`: `nasm -f elf64 code.asm -o code.o && gcc -no-pie -o exe code.o -lc` or `make executable`
  4. To execute run: `./exe`

## Current Progress
  1. Lexer analyzes input stream and creates tokens
  2. Grammar is read from `grammar.txt`
  3. First and follow set are computed automatically from the grammar
  4. Parse Table generated based on the rules
  5. Parser generates a parse tree of the token stream with the help of parse table
  6. Error recovery has been implemented
  7. AST is generated from the parse tree and through the grammar
  8. Symbol table is populated with the help of AST
  9. Semantic checks have been applied and all the errors are reported
  10. Intermediate code is generated in the form tuples
  11. Assembly code is generated and stored is `code.asm`

