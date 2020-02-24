/*	driver.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "parser.h"
#include "lexer.h"
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>

void printLexer(char *filename)
{
	FILE *f=fopen(filename,"r");
	f=getStream(f);
	
	printf("\n");

	printf("\nLine Number      Lexeme            Token\n\n");
	Node *n=(Node*)malloc(sizeof(Node));
	do
	{
		n=getNextToken();
		if(strcmp(n->t->value,"$")==0)
		{
			continue;
		}
		if(strcmp(n->t->token,"EOB")==0)
		{
			break;
		}
		if(strcmp(n->t->token,"Error"))
		{
			printf("     %d           %s           %s\n",n->t->lineno,n->t->value,n->t->token);
		}


	}while(buffer[fwd]!='\0');
}

/*void adddollar(FILE *f)
{
	FILE *f2=fopen("mainreadfile.txt","w");
	char ch;
	while(!feof(f))
	{
		ch=fgetc(f);
		fputc(ch,f2);
	}
	fputc('$',f2);
	fclose(f2);
}*/

int main(int argc, char *argv[])
{
	FILE *f1=fopen(argv[1],"r"); // appending $

	FILE *f2=fopen(argv[2],"r"); // for printing parse tree

	FILE *f3=fopen("grammar.txt","r"); // for reading grammar file

	//adddollar(f1);

	Grammar G;
	FirstAndFollow F;
	ParseTable T;
	//ParseTree *hd;

	int option=-1;

	if(argc!=3)
	{
		printf("Too few arguments, exiting! Please enter in format as ./stage1exe *.txt *.txt");
		exit(1);
	}

	do
	{
		printf("\n\n********* ERPlAG Compiler Stage1 *********\n\n");
		printf("Status:  \n");
		printf("\t1. Remove Comments is Working.\n");
		printf("\t2. Lexer is Working.\n");
		printf("\n\t3. CAUTION! ParseInputSourceCode is working only if you add a dollar at the end of every testfile\n");
		printf("\tAlthough we defined a function in driver.c (which is commented) to add dollar to end of the file\n");
		printf("\tbut it was giving error in different opearting systems and environments. Requsting you to manually add $.\n\n");
		printf("Please select one of the following options - \n");
		printf("0. Exit the program.\n");
		printf("1. Remove Comments and display on console.\n");
		printf("2. Display token list on console.\n");
		printf("3. Parse the input file and write the Parse Tree into a file.\n");
		printf("4. Print the total time taken for parsing the input file.\n");
		printf("5. Clear the Screen.\n\n");
		printf("Enter your option here: ");
		scanf("%d",&option);

		switch(option)
		{
			case 0: 
					break;

			case 1:

					printf("\n");
					removeComments(argv[1]);
					break;

			case 2: 

					printLexer(argv[1]);
					break;

			case 3: 
					G=getGrammar(f3);
					F=ComputeFirst(F);
					F=ComputeFollow(F);
					//printFF(F);
					T=createParseTable(F,T,G);
					//printTable(T);
					parseInputSourceCode(f1,T,G);
					//hd=returnhead();
					printParseTree(f2);

					break;

			case 4: 
					
					G=getGrammar(f3);
					F=ComputeFirst(F);
					F=ComputeFollow(F);
					//printFF(F);
					T=createParseTable(F,T,G);
					//printTable(T);
					
					clock_t start_time, end_time;
					double total_CPU_time, total_CPU_time_in_seconds;
					start_time = clock();

						parseInputSourceCode(f1,T,G);

					end_time = clock();
					total_CPU_time = (double)(end_time - start_time);
					total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;

					//hd=returnhead();
					//printParseTree(head,f2);

					printf("\nTotal CPU time is: %lf\n",total_CPU_time);
					printf("Total CPU time in seconds is: %lf\n",total_CPU_time_in_seconds);
					
					break;

			case 5:

					system("clear");
					break;

			default:

					printf("\nWrong option, try again!\n");
					break;
		}

	}while(option!=0);

	return 0;
}
