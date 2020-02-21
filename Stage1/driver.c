/*	driver.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "parser.h"

void printLexer(FILE *f)
{
	f=getStream(f);
	Node *n=(Node*)malloc(sizeof(Node));
	for(int i=0; i<=91; i++)
	{
		n=getNextToken();
		if(strcmp(n->t->token,"Error"))
		{
			printf("%s %s %d\n",n->t->token,n->t->value,n->t->lineno);
		}
	}
}

int main(int argc, char *argv[])
{
	FILE *f=fopen(argv[1],"r");

	printLexer(f);

	return 0;
}
