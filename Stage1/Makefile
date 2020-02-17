compileAll: driver.o lexer.o parser.o
	gcc -o stage1 driver.o lexer.o parser.o

driver.o: driver.c parser.h lexer.h
	gcc -c driver.c 

lexer.o: lexer.c lexer.h
	gcc -c lexer.c

parser.o: parser.c parser.h lexer.h
	gcc -c parser.c

clean: 
	rm -r *.o stage1