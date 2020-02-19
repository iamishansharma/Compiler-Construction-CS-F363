/*	lexer.c
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "parser.h"

/* **************************************************************************** */

/* Global Variables */

int state=1;

int begin=0;
int fwd=0;
int fwd2=0;

int keyno=35;
int tokno=60;

char *keyword[35] =
{
	"integer",
	"real",
	"boolean",
	"of",
	"array",
	"start",
	"end",
	"declare",
	"module",
	"driver",
	"program",
	"get_value",
	"print",
	"use",
	"with",
	"parameters",
	"true",
	"false",
	"takes",
	"input",
	"returns",
	"AND",
	"OR",
	"for",
	"in",
	"switch",
	"case",
	"break",
	"default",
	"while"
};

char *tokens[60] = 
{
	"INTEGER",
	"REAL",
	"BOOLEAN",
	"OF",
	"ARRAY",
	"START",
	"END",
	"DECLARE",
	"MODULE",
	"DRIVER",
	"PROGRAM",
	"GET_VALUE",
	"PRINT",
	"USE",
	"WITH",
	"PARAMETERS",
	"TRUE",
	"FALSE",
	"TAKES",
	"INPUT",
	"RETURNS",
	"AND",
	"OR",
	"FOR",
	"IN",
	"SWITCH",
	"CASE",
	"BREAK",
	"DEFAULT",
	"WHILE",
	"PLUS",
	"MINUS",
	"MUL",
	"DIV",
	"LT",
	"LE",
	"GE",
	"GT",
	"EQ",
	"NE",
	"DEF",
	"ENDDEF",
	"COLON",
	"RANGEOP",
	"SEMICOL",
	"COMMA",
	"ASSIGNOP",
	"SQBO",
	"SQBC",
	"BO",
	"BC",
	"COMMENTMARK"
};

char buffer[4000];
int buflen;

/* **************************************************************************** */

/* START Supporting Functions for Primary Functions */

Token* newToken()
{
	Token *t=(Token*)malloc(sizeof(Token));
	return t;
}

Node* newNode()
{
	Node *n=(Node*)malloc(sizeof(Node));
	return n;
}

Head* newHead()
{
	Head *h=(Head*)malloc(sizeof(Head));
	return h;
}

void ClearMem(char *c,int len) // To Clear Char Arrays
{
	for(int i=0; i<len; i++)
	{
		c[i]='\0';
	}
}

Token getLexeme(int begin, int fwd)
{
	Token t;

	char valueinit[30];

	for(int i=begin; i<fwd; i++)
	{
		valueinit[i]=buffer[i];
		/* token and value differences */
	}
	begin=fwd+1;
	fwd=begin;
	return t;
}

/* END Supporting Functions for Primary Functions */

/* **************************************************************************** */

/* START Primary Functions */

FILE* getStream(FILE *fp)
{
	if(fp==NULL)
	{
		printf("Cannot Open File!");
		exit(0);
	}

	ClearMem(buffer,buflen);

	fread(buffer,buflen,1,fp);

	//printf("%s",buffer); //for debugging.

	return fp;
}

void removeComments(char *testcaseFile, char *cleanFile)
{
	FILE *f1 = fopen(testcaseFile, "r");
	if(f1==NULL)
	{
		printf("Error opening file for removing comments!");
		return;
	}

	FILE *f2 = fopen(cleanFile, "w");
	if(f2==NULL)
	{
		printf("Error opening file for removing comments!");
		return;
	}

	char c; // Reading Character my character

	while(!feof(f1))
	{
		c = fgetc(f1); // Gets initial character

		if(c=='*')
		{
			c=fgetc(f1);

			if(c=='*')
			{
				while(1)
				{
					c=fgetc(f1);
					if(c=='\n')
					{
						fputc(c,f2);
					}
					else
					{
						if(c=='*')
						{
							c=fgetc(f1);
							if(c=='*')
							{
								break;
							}
							else
							{
								continue;
							}
						}
						else
						{
							continue;
						}
					}
				}
			}
			c=fgetc(f1);
		}
		fputc(c,f2);
	}
	fclose(f1);
	fclose(f2);
}

Node* getNextToken()
{
	Node *newToken=newNode();
	ClearMem(newToken->t->token,30);
	ClearMem(newToken->t->value,30);
	newToken->t->lineno=0;

	char c;

	char tokeninit[30];
	char valueinit[30];

	while(1)
	{
		c=buffer1[fwd];
		switch(state)
		{
			case 1: 
					if(c=='\b' || c=='\t')
					{
						if((fwd-begin)!=0)
						{
							Token t;
							t=getLexeme(begin,fwd);
						}
						else
						{
							;
						}
						fwd++;
					}
					else if(c=='\n')
					{
						newToken->t->lineno++;
						if((fwd-begin)!=0)
						{
							Token t;
							t=getLexeme(begin,fwd);
						}
						else
						{
							;
						}
						fwd++;
					}
					break;
		}
	}
}

/* END Primary Functions */

/* **************************************************************************** */