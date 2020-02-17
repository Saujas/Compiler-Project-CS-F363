exe: driver.o lexer.o lookup_table.o
	gcc -o exe driver.o lexer.o lookup_table.o

lexer.o: lexer.h lexer_def.h lookup_table.h
	gcc -c -g lexer.c

lookup_table.o: lookup_table.h
	gcc -c -g lookup_table.c

driver.o: lexer.h lookup_table.h lexer_def.h
	gcc -c -g driver.c

clean:
	rm *.o

run:
	./exe $(filename)