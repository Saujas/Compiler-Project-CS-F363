stage1exe: driver.o parser.o lexer.o lookup_table.o stack.o tree.o ast.o makefile
	gcc -o stage1exe driver.o parser.o lexer.o lookup_table.o stack.o tree.o ast.o

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

driver.o: lexer.h lookup_table.h lexer_def.h driver.c
	gcc -c -g driver.c

clean:
	rm *.o && rm stage1exe

run:
	./stage1exe $(input_file) $(output_file)