compiler: driver.o parser.o lexer.o lookup_table.o stack.o tree.o ast.o symbol_table.o type_extractor.o semantic_analyzer.o intermediate_code.o code_gen.o makefile
	gcc -o compiler driver.o parser.o lexer.o lookup_table.o stack.o tree.o ast.o symbol_table.o type_extractor.o semantic_analyzer.o intermediate_code.o code_gen.o

parser.o: parser.h parser_def.h lexer.h lexer_def.h lookup_table.h stack.h parser.c
	gcc -c -g parser.c

lexer.o: lexer.h lexer_def.h lookup_table.h lexer.c
	gcc -c -g lexer.c

lookup_table.o: lookup_table.h lookup_table.c
	gcc -c -g lookup_table.c

stack.o: stack.h parser_def.h stack.c
	gcc -c -g stack.c

tree.o: tree.h lexer_def.h parser_def.h tree.c
	gcc -c -g tree.c

ast.o: ast.h ast_def.h tree.h parser_def.h lexer_def.h ast.c
	gcc -c -g ast.c

symbol_table.o: symbol_table.h symbol_table_def.h ast_def.h label.h symbol_table.c
	gcc -c -g symbol_table.c

type_extractor.o: type_extractor.h symbol_table_def.h ast_def.h label.h type_extractor.c
	gcc -c -g type_extractor.c

semantic_analyzer.o: semantic_analyzer.h type_extractor.h symbol_table_def.h ast_def.h label.h semantic_analyzer.c
	gcc -c -g semantic_analyzer.c

intermediate_code.o: intermediate_code_def.h intermediate_code.h symbol_table_def.h lexer_def.h ast_def.h parser_def.h intermediate_code.c
	gcc -c -g intermediate_code.c

code_gen.o: code_gen.h intermediate_code_def.h symbol_table_def.h ast_def.h code_gen.c
	gcc -c -g code_gen.c

driver.o: lexer.h lookup_table.h lexer_def.h ast.h symbol_table.h intermediate_code.h code_gen.h driver.c
	gcc -c -g driver.c

clean:
	rm *.o && rm compiler && rm exe

run:
	./compiler $(input_file) $(output_file)

executable:
	nasm -f elf64 code.asm -o code.o && gcc -no-pie -o exe code.o -lc
