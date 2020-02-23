# Compiler-Project: CS-F363

### Group 13
 - Group Members:
	- 2017A7PS0096P - **Sahil Dubey**
	- 2017A7PS0105P - **Rohit Milind Rajhans**
	- 2017A7PS0109P - **Saujas Adarkar**

## Instructions to run
  1. run `make` to compile the code and generate executable
  2. run the file stage1exe as pass input test case and output filename as parameters
	Example: `./stage1exe test.txt parsetreeOutFile.txt`

## Current Progress
  1. Lexer analyzes input stream and creates tokens
  2. Grammar is read from `grammar.txt`
  3. First and follow set are computed automatically from the grammar
  4. Parse Table generated based on the rules
  5. Parser generates a parse tree of the token stream with the help of parse table
  6. Error recovery has been implemented

