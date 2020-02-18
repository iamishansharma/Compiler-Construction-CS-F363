/*	lexer.c
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "parser.h"

/* ******************************************************* */

/* Global Variables */

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

char buffer[4000]; // DOUBT is twin buffer necessary ?
int buflen=4000;

/* ******************************************************* */

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

/* END Supporting Functions for Primary Functions */

/* ******************************************************* */

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
				/*while((c=fgetc(f1))!='*' && (c=fgetc(f1))!='*')
				{
					continue; // NOT WORKING, EXTRA *
				}
				c = fgetc(f1); // Gets the character after the last *
				*/
				
				c=fgetc(f1);

				while(c!='*')
				{
					if(c=='\n')
					{
						fputc(c,f2);
					}
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
				/* NOT WORKING FOR MULTIPLY */
			}
			c=fgetc(f1);
			c=fgetc(f1);
		}
		fputc(c,f2);
	}
	fclose(f1);
	fclose(f2);
}

Node* getNextToken()
{
	return NULL;
}

/* END Primary Functions */

/* ******************************************************* */