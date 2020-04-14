/*	

	driver.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

// Stage 1 header files ->

#include "parser.h"
#include "lexer.h"
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>

// Stage 2 header files ->

#include "ast.h"
#include "SymbolTable.h"
#include "TypeChecker.h"
#include "CodeGen.h"

int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);

ParseTree *temphead;
ParseTree *temphead2;

void printLexer(char *filename)
{
	FILE *f=fopen(filename,"r");
	f=getStream(f);
	
	printf("\n");

	printf("\nLine Number      Lexeme               Token\n\n");
	Node *n=(Node*)malloc(sizeof(Node));
	do
	{
		n=getNextToken();
		if(strcmp(n->t->token,"EOB")==0)
		{
			break;
		}
		if(strcmp(n->t->token,"Error"))
		{
			printf("     %-12d %-20s %-20s\n",n->t->lineno,n->t->value,n->t->token);
		}
		else
		{
			printf("     %-12d %-20s %-20s\n",n->t->lineno,n->t->value,n->t->token);
		}
	}while(buffer[fwd]!='\0');
}

void removedollar(char *filename)
{
	//printf("Comes here");
	FILE *f=fopen(filename,"a");
	int charsToDelete = 1;
	fseeko(f,-charsToDelete,SEEK_END);
	int position = ftello(f);
	ftruncate(fileno(f), position);
	fclose(f);
}

void calculateCPUtime(FILE *f4, ParseTable T, Grammar G)
{
	clock_t start_time, end_time;
	double total_CPU_time, total_CPU_time_in_seconds;
	start_time = clock();

		//parseInputSourceCode(f4,T,G);

	end_time = clock();
	total_CPU_time = (double)(end_time - start_time);
	total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;

	printf("\n\n\tTotal CPU time is: %lf\n",total_CPU_time);
	printf("\tTotal CPU time in seconds is: %lfs\n",total_CPU_time_in_seconds);
	printf("\tTotal CPU time in miliseconds is: %lfms\n",total_CPU_time_in_seconds*1000);
}

int main(int argc, char *argv[])
{
	Grammar G;
	FirstAndFollow F;
	ParseTable T;

	FILE *f3=fopen("grammar.txt","r"); // for reading grammar file

	FILE *f1=fopen(argv[1],"a"); // appending $

	FILE *f9;

	FILE *codegen = fopen(argv[2],"w");

	FILE *f4=fopen(argv[1],"r"); // now reading that file

	int ParseTreeCount[1]={0};

	int ASTCount[1]={0};

	float comper;

	char scope[100];

	int option=-1;

	SymbolTable *Table;

	int scopeError = 0;

	int typeErrors = 0;

	int sizePT = 0;

	int sizeAST = 0;

	int udvflag = 0;

	if(argc!=3)
	{
		printf("Too few/many arguments, exiting! Please enter in format as ./compiler *.txt {<- test case file} *.txt {<- file to print AST/ParseTree} *.asm {<- machine code file}");
		exit(1);
	}

	do
	{
		printf("\n\n************************* %sERPLAG Compiler Stage2%s ***************************\n",BOLDYELLOW,RESET);
		printf("%sBatch 14:%s | Ishan Sharma 2016B2A70773P | Sarthak Sahu 2015B5A70749P   |\n",BOLDRED,RESET);
		printf("\t  | Anirudh Garg 2017A7PS0142P | Sanjeev Singla 2017A7PS0152P |\n");
		printf("****************************************************************************\n");
		printf("%sStatus:%s  \n",BOLDRED,RESET);
		printf("\t%s1. AST is being generated as required\n",BOLDGREEN);
		printf("\t2. Symbol Table is being populated as required.%s\n",RESET);
		printf("\t3. Type Checking and Semantic Check are working as required. \n");
		printf("\t4. Code Gen?\n\n");
		printf("Please select one of the following options (Please use only 1 option in one run of code) ->\n\n");
		printf("\t0. Exit the program.\n");
		printf("\t1. Display token list on console.\n");
		printf("\t2. Parse the input file.\n");
		printf("\t3. Create Abstract Syntax Tree and print it in on console.\n");
		printf("\t4. Display the sizes and compression percentage for Parse Tree and AST.\n");
		printf("\t5. Create and display the Symbol Table.\n");
		printf("\t6. Parse the file for type checking and semantic analysis. (Displays errors {if any}).\n");
		printf("\t6. Print activation record details on console.\n");
		printf("\t7. Print Static and Dynamic Arrays.\n");
		printf("\t8. Parse the file for type checking and semantic analysis. (Displays errors {if any}).\n");
		printf("\t9. Generate Assembly Code.\n\n");
		printf("Enter your option here: ");
		scanf("%d",&option);


		if(option == 0)
		{
			printf("\n***********************************************\n");
			printf("%s* Exiting, Thank you for using the compiler! *\n%s",BOLDWHITE,RESET);
			printf("***********************************************\n");
			exit(0);
			break;
		}

		else if(option == 1)
		{
			printLexer(argv[1]);
			exit(0);
			break;
		}

		else if(option == 2)
		{

			fputc('$',f1);
			fclose(f1);
			G=getGrammar(f3);
			F=ComputeFirst(F,G);
			F=ComputeFollow(F,G);
			T=createParseTable(F,T,G);
			printf("\n%sRunning Status: %s\n",BOLDRED,RESET);
			parseInputSourceCode(f4,T,G,f9);
			temphead=returnhead();
			countNodes(temphead, ParseTreeCount);
			//printParseTree(f2);

			removedollar(argv[1]);
			fclose(f4);
			exit(0);
			break;
		}
		else if(option == 3)
		{
			fputc('$',f1);
			fclose(f1);
			G=getGrammar(f3);
			F=ComputeFirst(F,G);
			F=ComputeFollow(F,G);
			T=createParseTable(F,T,G);
			printf("\n%sRunning Status: %s\n",BOLDRED,RESET);
			parseInputSourceCode(f4,T,G,f9);
			temphead=returnhead();
			countNodes(temphead, ParseTreeCount);
			//printParseTree(f2);

			printf("\n\nTraversal used: PreOrder - Parent -> LeftMost Child -> All other right children");

			// Making and printing AST here:

			callingAST(temphead);

			countNodes(temphead, ASTCount);

			printf("\n**************************************************   %sAbstract Syntax Tree%s   **************************************************\n", BOLDRED, RESET);
			printf("------------------------------------------------------------------------------------------------------------------------------\n");
			printf("Lexeme \t           LineNo   NodeToken \t      ValueIfNum    Parent \t\tisLeaf \t    NodeSymbol\n");
			printf("------------------------------------------------------------------------------------------------------------------------------\n");

			printParseTree(); // Printing AST here. */

			printf("*********************************************************************************************************************************\n");

			removedollar(argv[1]);
			fclose(f4);
			exit(0);
			break;
		}
		else if(option == 4)
		{
			fputc('$',f1);
			fclose(f1);
			G=getGrammar(f3);
			F=ComputeFirst(F,G);
			F=ComputeFollow(F,G);
			T=createParseTable(F,T,G);
			printf("\n%sRunning Status: %s\n",BOLDRED,RESET);
			parseInputSourceCode(f4,T,G,f9);
			temphead=returnhead();
			countNodes(temphead, ParseTreeCount);
			//printParseTree(f2);

			sizePT = sizeof(temphead);

			// Making and printing AST here:

			callingAST(temphead);
			countNodes(temphead, ASTCount);
			//printParseTree(f2);

			// Printing the compression percentage: 

			sizeAST = sizeof(temphead);

			printf("\n\n****************************************************************************");
			printf("\n\tNo of Parse Tree Nodes: %d || Size of ParseTree: %d bytes\n",ParseTreeCount[0], ParseTreeCount[0]*sizePT);
			printf("\tNo of AST Nodes: %d || Size of AST: %d bytes\n", ASTCount[0], ASTCount[0]*sizeAST);
			comper = (((float)ParseTreeCount[0] - (float)ASTCount[0]) / (float)ParseTreeCount[0])*100;
			printf("%s\tCompression Percentage:%s %0.2f %s",BOLDCYAN,RESET,comper,"%");
			printf("\n****************************************************************************");

			removedollar(argv[1]);
			fclose(f4);
			exit(0);
			break;
		}
		else if(option == 5)
		{
			fputc('$',f1);
			fclose(f1);
			G=getGrammar(f3);
			F=ComputeFirst(F,G);
			F=ComputeFollow(F,G);
			T=createParseTable(F,T,G);
			printf("\n%sRunning Status: %s\n",BOLDRED,RESET);
			parseInputSourceCode(f4,T,G,f9);
			temphead=returnhead();
			countNodes(temphead, ParseTreeCount);
			//printParseTree(f2);
			//fprintf(f2,"\n\n*************************************************************************************** \n\n");
			//fprintf(f2, "\nAST: \n\n");

			// Making and printing AST here:

			callingAST(temphead);
			countNodes(temphead, ASTCount);

			//printParseTree(f2);

			// Symbol Table: 

			//printf("\n\n%sErrors During SymbolTable Creation (if any):%s ",BOLDCYAN,RESET);

			Table = CallingSymbolTable(temphead, &scopeError, &udvflag);

			//if(scopeError == 0)
				//printf("%s\t2. Symbol Table built successfully.%s\n", BOLDWHITE, RESET);

			printf("\n******************************************************   %sSYMBOL TABLE%s   *****************************************************************************\n", BOLDRED, RESET);
			printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
			printf("IDENTIFIER \t     SCOPE \t     LINENUMB   WIDTH  isARRAY \tSTATIC/DYN     ARRAYRANGE     TYPE            OFFSET   NESTING   SCOPEPARENT\n");
			printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");

			printSymbolTable(Table);

			printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
			printf("Declaration Errors (if any) have been displayed just above symbol table, scroll up to see them.\n\n");

			removedollar(argv[1]);
			fclose(f4);
			exit(0);
			break;
		}
		else if(option == 6)
		{
			fputc('$',f1);
			fclose(f1);
			G=getGrammar(f3);
			F=ComputeFirst(F,G);
			F=ComputeFollow(F,G);
			T=createParseTable(F,T,G);
			printf("\n%sRunning Status: %s\n",BOLDRED,RESET);
			parseInputSourceCode(f4,T,G,f9);
			temphead=returnhead();
			countNodes(temphead, ParseTreeCount);
			//printParseTree(f2);
			//fprintf(f2,"\n\n*************************************************************************************** \n\n");
			//fprintf(f2, "\nAST: \n\n");

			// Making and printing AST here:

			callingAST(temphead);
			countNodes(temphead, ASTCount);

			//printParseTree(f2);

			// Symbol Table: 

			//printf("\n\n%sErrors During SymbolTable Creation (if any):%s ",BOLDCYAN,RESET);

			Table = CallingSymbolTable(temphead, &scopeError, &udvflag);

			//if(scopeError == 0)
				//printf("%s\t2. Symbol Table built successfully.%s\n", BOLDWHITE, RESET);

			printf("\n***** %sACTIVATION RECORDS TABLE%s *****\n", BOLDRED, RESET);
			printf("------------------------------------\n");
			printf("SCOPENAME \t     TOTALWIDTH \n");
			printf("------------------------------------\n");

			printActiveRecords(Table);

			printf("------------------------------------\n");

			removedollar(argv[1]);
			fclose(f4);
			exit(0);
			break;
		}
		else if(option == 7)
		{
			fputc('$',f1);
			fclose(f1);
			G=getGrammar(f3);
			F=ComputeFirst(F,G);
			F=ComputeFollow(F,G);
			T=createParseTable(F,T,G);
			printf("\n%sRunning Status: %s\n",BOLDRED,RESET);
			parseInputSourceCode(f4,T,G,f9);
			temphead=returnhead();
			countNodes(temphead, ParseTreeCount);
			//printParseTree(f2);
			//fprintf(f2,"\n\n*************************************************************************************** \n\n");
			//fprintf(f2, "\nAST: \n\n");

			// Making and printing AST here:

			callingAST(temphead);
			countNodes(temphead, ASTCount);

			//printParseTree(f2);

			// Symbol Table: 

			//printf("\n\n%sErrors During SymbolTable Creation (if any):%s ",BOLDCYAN,RESET);

			Table = CallingSymbolTable(temphead, &scopeError, &udvflag);

			//if(scopeError == 0)
				//printf("%s\t2. Symbol Table built successfully.%s\n", BOLDWHITE, RESET);

			printf("\n*************************************************   %sARRAY TABLE%s   *************************************************\n", BOLDRED, RESET);
			printf("-------------------------------------------------------------------------------------------------------------------\n");
			printf("SCOPE \t\t   LINENO \t IDENTIFIER  \t     STATIC/DYN  ARRAYRANGE            TYPE       SCOPEPARENT\n");
			printf("-------------------------------------------------------------------------------------------------------------------\n");

			printSymbolTableArray(Table);

			printf("-------------------------------------------------------------------------------------------------------------------\n");
			printf("Declaration Errors (if any) have been displayed just above symbol table, scroll up to see them.\n\n");

			removedollar(argv[1]);
			fclose(f4);
			exit(0);
			break;
		}
		else if(option == 8)
		{
			clock_t start_time, end_time;
			double total_CPU_time, total_CPU_time_in_seconds;
			start_time = clock();

				fputc('$',f1);
				fclose(f1);
				G=getGrammar(f3);
				F=ComputeFirst(F,G);
				F=ComputeFollow(F,G);
				T=createParseTable(F,T,G);
				printf("\n%sRunning Status: %s\n",BOLDRED,RESET);
				parseInputSourceCode(f4,T,G,f9);
				temphead=returnhead();
				countNodes(temphead, ParseTreeCount);

				// Making and printing AST here:

				callingAST(temphead);
				countNodes(temphead, ASTCount);

				// Symbol Table: 

				printf("\n\n%sErrors During TypeChecking and Semantic Analysis (if any):%s ",BOLDCYAN,RESET);

				Table = CallingSymbolTable(temphead, &scopeError, &udvflag);

				// Type Checking:

				CallingTypeChecker(temphead, Table, &typeErrors, &udvflag);

				/*else
				{
					printf("\n\t%sPlease rectify the above declaration errors during SymbolTable creation before \n\tproceeding forward with semantic analysis as it may contain undeclared variables.%s\n",BOLDRED,RESET);

					removedollar(argv[1]);
					fclose(f4);
					exit(0);
					break;
				}*/

				if(typeErrors == 0)
					printf("%s\t2. No errors found during Type Checking and Semantic Analysis.%s\n\n", BOLDWHITE, RESET);

			end_time = clock();
			total_CPU_time = (double)(end_time - start_time);
			total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;

			printf("\n\n**********************************************************");
			printf("\n    Total CPU time is: %lf\n",total_CPU_time);
			printf("    Total CPU time in seconds is: %lfs\n",total_CPU_time_in_seconds);
			printf("    Total CPU time in miliseconds is: %lfms\n",total_CPU_time_in_seconds*1000);
			printf("**********************************************************\n\n");

			removedollar(argv[1]);
			fclose(f4);
			exit(0);
			break;
		}
		else if(option == 9)
		{

			fputc('$',f1);
			fclose(f1);
			G=getGrammar(f3);
			F=ComputeFirst(F,G);
			F=ComputeFollow(F,G);
			T=createParseTable(F,T,G);
			printf("\n%sRunning Status: %s\n",BOLDRED,RESET);
			parseInputSourceCode(f4,T,G,f9);
			temphead=returnhead();
			countNodes(temphead, ParseTreeCount);
			//printParseTree(f2);
			//fprintf(f2,"\n\n*************************************************************************************** \n\n");
			//fprintf(f2, "\nAST: \n\n");

			// Making and printing AST here:

			callingAST(temphead);
			countNodes(temphead, ASTCount);
			//printParseTree(f2);

			// Symbol Table: 

			printf("\n\n%sErrors During SymbolTable Creation (if any):%s ",BOLDCYAN,RESET);

			Table = CallingSymbolTable(temphead, &scopeError, &udvflag);

			if(scopeError == 0)
				printf("%s\t2. Symbol Table built successfully.%s\n", BOLDWHITE, RESET);

			/*printf("\n**********************************   %sSYMBOL TABLE%s   ******************************************\n", BOLDRED, RESET);
			printf("----------------------------------------------------------------------------------------------\n");
			printf("IDENTIFIER \t USAGE \t\t TYPE \t     LINE NO. \t SCOPE \t     NESTING   WIDTH   OFFSET\n");
			printf("----------------------------------------------------------------------------------------------\n");

			printSymbolTable(Table);

			printf("**********************************************************************************************\n");
			*/

			// Type Checking:

			printf("\n%sType Checking Analysis:%s \n",BOLDCYAN,RESET);

			if(scopeError == 0)
				CallingTypeChecker(temphead, Table, &typeErrors, &udvflag);
			else
			{
				printf("\n\t%sPlease rectify the declaration errors during SymbolTable creation before \n\tproceeding forward with semantic analysis as it may contain undeclared variables.%s\n",BOLDRED,RESET);

				removedollar(argv[1]);
				fclose(f4);
				exit(0);
				break;
			}

			if(typeErrors == 0)
				printf("\n%s\t3. No errors found during Type Checking and Semantic Analysis.%s\n", BOLDWHITE, RESET);

			// Call CodeGen here

			if(typeErrors!=0)
			{
				printf("\n\t%sPlease rectify the semantic errors before proceeding forward \n\twith code gen as it may show errorneous behaviour.%s\n",BOLDRED,RESET);

				removedollar(argv[1]);
				fclose(f4);
				exit(0);
				break;
			}
			else
				CallingCodeGen(temphead, Table, codegen);

			removedollar(argv[1]);
			fclose(f4);
			exit(0);
			break;
		}
		else
		{
			printf("\nWrong option, try again!\n");
			exit(0);
			break;
		}

	}while(option!=0);

	return 0;
}