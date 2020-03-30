compileAll: driver.c lexer.c parser.c ast.c SymbolTable.c TypeChecker.c CodeGen.c
	gcc -o stage2exe driver.c lexer.c parser.c ast.c SymbolTable.c TypeChecker.c CodeGen.c

clean: 
	rm -r stage2exe