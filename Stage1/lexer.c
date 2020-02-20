/*	lexer.c
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "lexer.h"

/* **************************************************************************** */

/* Global Variables */

int state=1;

int line=1;
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

/* no use 

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
}; */

char buffer[4000];
int buflen=4000;

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

bool isKeyword(char value[30])
{

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

	char ch;
	int tklen=0; // used here to read into token/value
	char tokeninit[30];
	char valueinit[30];

	while(1)
	{
		ch=buffer[fwd];
		switch(state)
		{
			case 1: /* This branch is for state 1 and all 
					its direct paths in our original DFA */
					
					 // change this 
					/*if(ch == '\r')
					{
						ch = buffer[++fwd];
						if(ch == '\n')
						{
							ch = buffer[++fwd];
						}
						line++;
						state = 1;
						break;
					}*/
					else if(ch=='\b'|| ch=='\t')
					{
						state = 1;
						ch = buffer[++fwd];
						break;
					}
					else if(((ch>='a') && (ch<='z')) || ((ch>='A') && (ch<='Z')))
					{
						valueinit[tklen++] = ch;
						ch=buffer[++fwd];
						state = 2;
					}
					else if((ch>='0') && (ch<='9'))
					{
						valueinit[tklen++] = ch;
						ch = buffer[++fwd];
						state = 3;
					}
					else if(ch=='+')
					{
						strcpy(newToken->t->token,"PLUS");
						strcpy(newToken->t->value,"+");
						newToken->t->lineno=line;
						fwd++;
						begin = fwd;
						state = 1;
						return newToken;
						break;
					}
					else if(ch=='-')
					{
						strcpy(newToken->t->token,"MINUS");
						strcpy(newToken->t->value,"-");
						newToken->t->lineno=line;
						fwd++;
						begin = fwd;
						state = 1;
						return newToken;
						break;
					}
					else if(ch=='*')
					{
						ch = buffer[++fwd];

						if(ch=='*')
						{
							while(1)
							{
								ch=buffer[++fwd];

								if(ch=='\n')
								{
									line++;
								}
								else
								{
									if(ch=='*')
									{
										ch=buffer[++fwd];
										if(ch=='*')
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
						else
						{
							strcpy(newToken->t->token,"MUL");
							strcpy(newToken->t->value,"*");
							newToken->t->lineno=line;
							begin = fwd;
							state = 1;
							return newToken;
							break;
						}
					}
					else if(ch=='/')
					{
						strcpy(newToken->t->token,"DIV");
						strcpy(newToken->t->value,"/");
						newToken->t->lineno=line;
						fwd++;
						begin = fwd;
						state = 1;
						return newToken;
						break;
					}
					else if(ch=='<')
					{
						ch = buffer[++fwd];

						if(ch=='=')
						{
							strcpy(newToken->t->token,"LE");
							strcpy(newToken->t->value,"<=");
							newToken->t->lineno=line;
							fwd++;
							begin = fwd;
							state = 1;
							return newToken;
							break;
						}
						else if(ch=='<')
						{
							ch = buffer[++fwd];

							if(ch=='<')
							{
								strcpy(newToken->t->token,"DRIVERDEF");
								strcpy(newToken->t->value,"<<<");
								newToken->t->lineno=line;
								fwd++;
								begin = fwd;
								state = 1;
								return newToken;
								break;
							}
							else
							{
								strcpy(newToken->t->token,"DEF");
								strcpy(newToken->t->value,"<<");
								newToken->t->lineno=line;
								begin = fwd;
								state = 1;
								return newToken;
								break;
							}
						}
						else
						{
							strcpy(newToken->t->token,"LT");
							strcpy(newToken->t->value,"<");
							newToken->t->lineno=line;
							begin = fwd;
							state = 1;
							return newToken;
							break;
						}
					}
					else if(ch=='>')
					{
						ch = buffer[++fwd];

						if(ch=='=')
						{
							strcpy(newToken->t->token,"GE");
							strcpy(newToken->t->value,">=");
							newToken->t->lineno=line;
							fwd++;
							begin = fwd;
							state = 1;
							return newToken;
							break;
						}
						else if(ch=='>')
						{
							ch = buffer[++fwd];

							if(ch=='>')
							{
								strcpy(newToken->t->token,"DRIVERENDDEF");
								strcpy(newToken->t->value,">>>");
								newToken->t->lineno=line;
								fwd++;
								begin = fwd;
								state = 1;
								return newToken;
								break;
							}
							else
							{
								strcpy(newToken->t->token,"ENDDEF");
								strcpy(newToken->t->value,">>");
								newToken->t->lineno=line;
								begin = fwd;
								state = 1;
								return newToken;
								break;
							}
						}
						else
						{
							strcpy(newToken->t->token,"GT");
							strcpy(newToken->t->value,">");
							newToken->t->lineno=line;
							begin = fwd;
							state = 1;
							return newToken;
							break;
						}
					}
					else if(ch=='=')
					{
						ch = buffer[++fwd];

						if(ch=='=')
						{
							strcpy(newToken->t->token,"EQ");
							strcpy(newToken->t->value,"==");
							newToken->t->lineno=line;
							fwd++;
							begin = fwd;
							state = 1;
							return newToken;
							break;
						}
					}
					else if(ch=='!')
					{
						ch = buffer[++fwd];

						if(ch=='=')
						{
							strcpy(newToken->t->token,"NE");
							strcpy(newToken->t->value,"!=");
							newToken->t->lineno=line;
							fwd++;
							begin = fwd;
							state = 1;
							return newToken;
							break;
						}
					}
					else if(ch==':')
					{
						ch = buffer[++fwd];

						if(ch=='=')
						{
							strcpy(newToken->t->token,"ASSIGNOP");
							strcpy(newToken->t->value,":=");
							newToken->t->lineno=line;
							fwd++;
							begin = fwd;
							state = 1;
							return newToken;
							break;
						}
						else
						{
							strcpy(newToken->t->token,"COLON");
							strcpy(newToken->t->value,":");
							newToken->t->lineno=line;
							begin = fwd;
							state = 1;
							return newToken;
							break;
						}
					}
					else if(ch=='.')
					{
						ch = buffer[++fwd];

						if(ch=='.')
						{
							strcpy(newToken->t->token,"RANGEOP");
							strcpy(newToken->t->value,"..");
							newToken->t->lineno=line;
							fwd++;
							begin = fwd;
							state = 1;
							return newToken;
							break;
						}
					}
					else if(ch==';')
					{
						strcpy(newToken->t->token,"SEMICOL");
						strcpy(newToken->t->value,";");
						newToken->t->lineno=line;
						fwd++;
						begin = fwd;
						state = 1;
						return newToken;
						break;
					}
					else if(ch==',')
					{
						strcpy(newToken->t->token,"COMMA");
						strcpy(newToken->t->value,",");
						newToken->t->lineno=line;
						fwd++;
						begin = fwd;
						state = 1;
						return newToken;
						break;
					}
					else if(ch=='[')
					{
						strcpy(newToken->t->token,"SQBO");
						strcpy(newToken->t->value,"[");
						newToken->t->lineno=line;
						fwd++;
						begin = fwd;
						state = 1;
						return newToken;
						break;
					}
					else if(ch==']')
					{
						strcpy(newToken->t->token,"SQBC");
						strcpy(newToken->t->value,"]");
						newToken->t->lineno=line;
						fwd++;
						begin = fwd;
						state = 1;
						return newToken;
						break;
					}
					else if(ch=='(')
					{
						strcpy(newToken->t->token,"BO");
						strcpy(newToken->t->value,"(");
						newToken->t->lineno=line;
						fwd++;
						begin = fwd;
						state = 1;
						return newToken;
						break;
					}
					else if(ch==')')
					{
						strcpy(newToken->t->token,"BC");
						strcpy(newToken->t->value,")");
						newToken->t->lineno=line;
						fwd++;
						begin = fwd;
						state = 1;
						return newToken;
						break;
					}
					else
					{
						strcpy(newToken->t->token,"Error");
						printf("Lexical Error: %s at line no: %d\n",valueinit,line);
						state = 1;
						fwd++;
						begin = fwd;
						return newToken;
					}
					break;

			case 2: /* This branch is for state 2 and state 3
					 in our original DFA */


					isKeyword(char value[30]);



					
					break;

			case 3: /* This branch is for state 4 to state10
					 in our original DFA */


					
					break;
		}
	}
}

/* END Primary Functions */

/* **************************************************************************** */