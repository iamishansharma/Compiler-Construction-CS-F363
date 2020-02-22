/*	parser.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "parser.h"
#include "hash.h"

char *TermTable[1007];

int no_nont=100; 	// no of non terminals
int no_t=59; 		// no of terminals - 55 in LangSepc + <<< + >>> + epsilon as "esp" + "$" = 59
int no_rules=100; 	// total no of grammar rules

int stack[100];
int stack_max=99; 	//max value for indexing stack
int top=-1; 		// top pointer

/* **************************************************************************** */


/* **************************************************************************** */

/* START Supporting Functions for Primary Functions */

Grammar getGrammar(FILE *f)
{
	Grammar G;

	char string[100];

	FILE *f2=fopen("checkgrammar.txt","w");

	if(f==NULL)
	{
		printf("Cannot open grammar read file!");
		exit(1);
	}

	int rule_no=0;

	while(!feof(f))
	{
		fgets(string,100,f);
		int j=0;
		int k=0;
		char word[15][30];
		for(int i=0; i<=strlen(string); i++)
		{
			if(string[i]==' ' || string[i]=='\0')
			{
				word[j][k]='\0';
				j++;
				k=0;
			}
			else
			{
				word[j][k]=string[i];
				k++;
			}
		}

		char toinsert[30];

		int g=0;

		for(g=0; g<j; g++)
		{
			for(int z=0; z<30; z++)
			{
				toinsert[z]='\0';
			}

			int x=0;

			do
			{
				if(word[g][x]=='\n')
				{
					x++;
				}
				else
				{
					toinsert[x]=word[g][x];
					x++;
				}

			}while(word[g][x]!='\0');

			fprintf(f2,"%s",toinsert);

			int hashVal=insert(toinsert,TermTable);
			//fprintf(f2,"%d ",hashVal);
			//G.gnum[rule_no][g]=hashVal;
		}

		//fprintf(f2,"\n");

		//G.gnum[rule_no][g]=-1;
		//rule_no++;
	}
	fclose(f);
	fclose(f2);
	return G;
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
		printf("Stack Full! Cannot Push");
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

bool isinFIRST(FirstAndFollow F,int nonterminal, int terminal)
{
	int flag=0;
	int i=0;
	do
	{
		if(F.first[nonterminal][i]==terminal)
		{
			flag=1;
		}
		i++;

	}while(F.first[nonterminal][i]!=-1);

	if(flag==1)
		return true;
	else
		return false;
}

bool epsinFIRST(FirstAndFollow F,int nonterminal)
{
	int flag=0;
	int i=0;
	do
	{
		if(F.first[nonterminal][i]==/*value of "eps"*/111)
		{
			flag=1;
		}
		i++;

	}while(F.first[nonterminal][i]!=-1);

	if(flag==1)
		return true;
	else
		return false;
}

/* END Supporting Functions for Primary Functions */

/* **************************************************************************** */

/* START Primary Functions */

FirstAndFollow ComputeFirstAndFollowSets(Grammar G, FirstAndFollow F)
{
	return F;
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

	/*
		Parse Table - 

		Non terminals x Terminals 

							$ INTEGER REAL BOOLEAN ... AND SO ON
		<program>
		<moduleDeclations>

		etc 

		1. do this for very terminal- 

			if $ is in FIRST(program) - 

				put value of table[0][0]=rule_no; //Rule number of <program>

			//start of terminals is at index 53
		
		2. if eps is in FIRST(program) - 

			put rule_no //Rule Number of program in 
			every terminal that is in FOLLOW(program)
	*/

	for(int nt=0; nt<no_nont; nt++)
	{
		for(int ter=53; ter<112; ter++)
		{
			if(isinFIRST(F,nt,ter))
			{
				T.table[nt][ter-53]=nt; // rule value is same as nt value;
			}
			if(epsinFIRST(F,nt))
			{
				int i=0;
				do
				{
					T.table[nt][F.follow[nt][i]]=nt;
					i++;

				}while(F.follow[nt][i]!=-1);
			}
		}
	}
}

void parseInputSourceCode(char *testcaseFile, ParseTable T)
{
	
}

void printParseTree(ParseTree PT, char *outfile)
{
	FILE *f=fopen(outfile,"w");

	if(f==NULL)
	{
		printf("Cannot open Parse Tree print file!");
		exit(1);
	}
}

/* END Primary Functions */

/* **************************************************************************** */