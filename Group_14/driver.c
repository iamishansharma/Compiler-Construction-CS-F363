/*	driver.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "parser.h"
#include "lexer.h"
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>

int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);

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
		if(strcmp(n->t->token,"EOB")==0)
		{
			break;
		}
		if(strcmp(n->t->token,"Error"))
		{
			printf("     %d           %s           %s\n",n->t->lineno,n->t->value,n->t->token);
		}
		else
		{
			printf("     %d           %s           %s\n",n->t->lineno,n->t->value,n->t->token);
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

void calculateCPUtime(FILE *f4, ParseTable T, Grammar G, FILE *f2)
{
	clock_t start_time, end_time;
	double total_CPU_time, total_CPU_time_in_seconds;
	start_time = clock();

		parseInputSourceCode(f4,T,G,f2);

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

	FILE *f2=fopen(argv[2],"w"); // for printing parse tree

	FILE *f3=fopen("grammar.txt","r"); // for reading grammar file

	FILE *f1=fopen(argv[1],"a"); // appending $

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
		printf("\t1. Remove Comments is working.\n");
		printf("\t2. Lexer is working.\n");
		printf("\t3. ParseInputSourceCode is working.\n");
		printf("\t4. ParseTree isn't being printed correctly. Thats why skipping the call to printParseTree\n");
		printf("\t   We are instead printing whole information of parseInputSourceCode i.e. stack (left most term is \n");
		printf("\t   top of stack), input symbol, rule number in grammar.txt used, elements to push onto stack now \n");
		printf("\t   in the file given as ./stage1exe *.txt \"*.txt\" <- this file the i.e. second argument.\n\n");
		printf("Please select one of the following options -\n\n");
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
					//hashkeywords();
					printLexer(argv[1]);
					break;

			case 3: 
					fputc('$',f1);
					fclose(f1);
					FILE *f4=fopen(argv[1],"r"); // now reading that file
					//hashkeywords();
					G=getGrammar(f3);
					F=ComputeFirst(F);
					F=ComputeFollow(F);
					T=createParseTable(F,T,G);
					parseInputSourceCode(f4,T,G,f2);
					//printParseTree(f2);
					removedollar(argv[1]);
					fclose(f4);
					break;

			case 4: 
					fputc('$',f1);
					fclose(f1);
					FILE *f5=fopen(argv[1],"r"); // now reading that file
					//hashkeywords();
					G=getGrammar(f3);
					F=ComputeFirst(F);
					F=ComputeFollow(F);
					T=createParseTable(F,T,G);
					calculateCPUtime(f5,T,G,f2);
					//printParseTree(head,f2);
					removedollar(argv[1]);
					fclose(f5);
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
