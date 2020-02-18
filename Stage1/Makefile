compileAll: driver.o lexer.o parser.o
	gcc -o stage1 driver.o lexer.o parser.o

driver.o: driver.c parser.h
	gcc -c driver.c 

parser.o: parser.c parser.h
	gcc -c parser.c

lexer.o: lexer.c lexer.h
	gcc -c lexer.c

clean: 
	rm -r *.o stage1