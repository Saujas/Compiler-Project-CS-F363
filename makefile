exe: driver.o parser.o lexer.o lookup_table.o stack.o tree.o
	gcc -o exe driver.o parser.o lexer.o lookup_table.o stack.o tree.o

parser.o: parser.h parser_def.h lexer.h lexer_def.h lookup_table.h stack.h
	gcc -c -g parser.c

lexer.o: lexer.h lexer_def.h lookup_table.h
	gcc -c -g lexer.c

lookup_table.o: lookup_table.h
	gcc -c -g lookup_table.c

stack.o: stack.h parser_def.h
	gcc -c -g stack.c

tree.o: tree.h lexer_def.h parser_def.h
	gcc -c -g tree.c

driver.o: lexer.h lookup_table.h lexer_def.h
	gcc -c -g driver.c

clean:
	rm *.o

run:
	./exe $(filename)