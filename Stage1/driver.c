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

void printLexer(FILE *f)
{
	f=getStream(f);
	
	printf("\n");

	Node *n=(Node*)malloc(sizeof(Node));
	do
	{
		n=getNextToken();
		if(strcmp(n->t->token,"Error"))
		{
			printf("%s %s %d\n",n->t->token,n->t->value,n->t->lineno);
		}
	}while(buffer[fwd]!='\0');
}

int main(int argc, char *argv[])
{
	FILE *f1=fopen(argv[1],"r");
	FILE *f2=fopen(argv[2],"r");

	int option=-1;

	if(argc!=3)
	{
		printf("Too few arguments, exiting!");
		exit(1);
	}

	do
	{
		printf("\n\n********* ErPlag Compiler Stage1 *********\n");
		printf("Please select one of the following options - \n");
		printf("0. Exit the program.\n");
		printf("1. Remove Comments and display on console.\n");
		printf("2. Display token list on console.\n");
		printf("3. Parse the input file and write the Parse Tree into a file.\n");
		printf("4. Print the total time taken by Option3.\n");
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
					printLexer(f1);
					break;

			case 3: 
					// parser & lexer call
					getGrammar(f1);
					break;

			case 4: 
					/*clock_t start_time, end_time;
					double total_CPU_time, total_CPU_time_in_seconds;
					start_time = clock();
						// parser & lexer call
					end_time = clock();
					total_CPU_time = (double)(end_time - start_time);
					total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;
					printf("Total CPU time is: %lf",total_CPU_time);
					printf("Total CPU time in seconds is: %lf",total_CPU_time_in_seconds);*/
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
