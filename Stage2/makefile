compileAll: driver.c lexer.c parser.c ast.c SymbolTable.c TypeChecker.c CodeGen.c
	gcc -o compiler driver.c lexer.c parser.c ast.c SymbolTable.c TypeChecker.c CodeGen.c

clean: 
	rm -r compiler