/*	parser.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "parser.h"

int no_nont=0; 	// no of non terminals
int no_t; 		// no of terminals
int no_rules=0; // total no of grammar rules

int stack[100];
int stack_max=99; //max value for indexing stack
int top=-1; // top pointer

Term t[110];

/* HARD CODE the terms here*/

/* **************************************************************************** */

/* START Supporting Functions for Primary Functions */

Grammar getGrammar(FILE *f)
{
	//return NULL;
}
void make_stack()
{
	for(int i=0; i<100; i++)
	{
		stack[i]=-1;
	}
}
void push(int ele)
{
	if(top==stack_max)
	{
		printf("Stack Ful! Cannot Push");
		exit(1);
	}
	else
	{
		top++;
		stack[top] = ele;
	}
}
int pop()
{
	if(top==-1)
	{
		printf("Stack Already Empty! Cannot Pop");
		exit(1);
		return -2;
	}
	else
	{
		int popping=stack[top];
		stack[top--]=-1;
		return popping;
	}
}

/* END Supporting Functions for Primary Functions */

/* **************************************************************************** */

/* START Primary Functions */

void ComputeFirstAndFollowSets(Grammar G, FirstAndFollow F)
{

}

void createParseTable(FirstAndFollow F, ParseTable T)
{
	//Initialising table

	for(int i=0; i<no_nont; i++)
	{
		for(int j=0; j<no_t; j++)
		{
			T.table[i][j]=-2;
		}
	}



}

void parseInputSourceCode(char *testcaseFile, ParseTable T)
{
	
}

void printParseTree(ParseTree PT, char *outfile)
{

}

/* END Primary Functions */

/* **************************************************************************** */