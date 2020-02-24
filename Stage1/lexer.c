/*	lexer.c
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "lexer.h"
#include "hash.h"
#include <ctype.h>

/* **************************************************************************** */

/* Global Variables */

int state=1;

int line=1;
int begin=0;
int fwd=0;
int fwd2=0;

int keyno=35;
int tokno=60;

char *KeywordTable[1007];

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
	int flag=1;
	for(int i=0; i<29; i++)
	{
		flag=strcmp(value,keyword[i]);
		if(flag==0)
		{
			return true;
		}
	}
	return false;
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

void removeComments(char *testcaseFile)
{
	FILE *f1 = fopen(testcaseFile, "r");
	if(f1==NULL)
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
						printf("%c",c);
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
		if(!feof(f1))
			printf("%c",c);
	}
	fclose(f1);
}

Node* getNextToken()
{
	Node *newToken=(Node*)malloc(sizeof(Node));
	newToken->t=(Token *)malloc(sizeof(Token));
	ClearMem(newToken->t->token,30);
	ClearMem(newToken->t->value,30);
	newToken->t->lineno=0;

	char ch;
	int tklen=0; // used here to read into token/value
	
	char tokeninit[30];
	char valueinit[30];

	ClearMem(tokeninit,30);
	ClearMem(valueinit,30);

	while(1)
	{
		ch=buffer[fwd];
		switch(state)
		{
			case 1:  // This branch is for state 1 and all 
					//  its direct paths in our original DFA
					
					if(ch == '\n')
					{
						ch = buffer[++fwd];
						//printf("\n %c \n",ch);
						line++;
						state = 1;
						break;
					}
					else if(ch==' '|| ch=='\t')
					{
						//printf("Finds a space!\n");
						state = 1;
						ch = buffer[++fwd];
						break;
					}
					else if(((ch>='a') && (ch<='z')) || ((ch>='A') && (ch<='Z')))
					{
						valueinit[tklen++] = ch;
						state = 2;

					}
					else if((ch>='0') && (ch<='9'))
					{
						//printf("\n Comes here!\n ");
						valueinit[tklen++] = ch;
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
								ch = buffer[++fwd];
								//printf("\n %c \n",ch);
								if(ch=='\n')
								{
									line++;
								}
								else
								{
									if(ch=='*')
									{
										ch = buffer[++fwd];
										if(ch=='*')
										{
											//printf("Comes here!");
											fwd++;
											state=1;
											//printf("\n %c \n",buffer[fwd]);
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
							begin = fwd;
							fwd++;
							//printf("%c",buffer[fwd]);
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
						else
						{
							strcpy(newToken->t->token,"Error");
							//strcpy(newToken->t->value,ch);
							newToken->t->lineno=line;
							printf("Lexical Error: = at line no: %d\n",line);
							state = 1;
							begin = fwd;
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
						else
						{
							strcpy(newToken->t->token,"Error");
							//strcpy(newToken->t->value,ch);
							newToken->t->lineno=line;
							printf("Lexical Error: . at line no: %d\n",line);
							state = 1;
							begin = fwd;
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
						//printf("in here comma");
						strcpy(newToken->t->token,"COMMA");
						strcpy(newToken->t->value,",");
						newToken->t->lineno=line;
						fwd++;
						//printf(" %c \n",buffer[fwd]);
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
					else if(ch=='$')
					{
						strcpy(newToken->t->token,"DOLLAR");
						strcpy(newToken->t->value,"$");
						newToken->t->lineno=line;
						fwd++;
						begin = fwd;
						state = 1;
						return newToken;
						break;
					}
					else
					{
						if(ch!='\0')
						{
							//printf("\nyeh wala error %d\n",ch);
							strcpy(newToken->t->token,"Error");
							//strcpy(newToken->t->value,ch);
							newToken->t->lineno=line;
							printf("Lexical Error: %d at line no: %d\n",ch,line);
							state = 1;
							fwd++;
							begin = fwd;
							return newToken;
						}
						else
						{
							strcpy(newToken->t->token,"EOB");
							//strcpy(newToken->t->value,ch);
							newToken->t->lineno=line;
							//printf("Lexical Error: %d at line no: %d\n",ch,line);
							state = 1;
							return newToken;
							break;
						}
					}
					break;

			case 2: // This branch is for state 2 and state 3
					// in our original DFA 

					// Idenfier limit 20 characters including _

					//isKeyword(char value[30]);
					while(1)
					{
						ch = buffer[++fwd];
						if(((ch>='a') && (ch<='z')) || ((ch>='A') && (ch<='Z')) || ((ch>='0') && (ch<='9')) || (ch=='_'))
						{
							valueinit[tklen++] = ch;
							state = 2;
						}
						else
						{
							state = 1;
							break;
						}
					}

					bool isk=isKeyword(valueinit);

					//printf("Tklen for %s: %d\n",valueinit,tklen);

					if(isk)
					{
						char keyw[30];
						ClearMem(keyw,30);

						for (int i = 0; valueinit[i]!='\0'; i++) 
						{
						    if(valueinit[i] >= 'a' && valueinit[i] <= 'z') 
						    {
						    	keyw[i] = valueinit[i] - 32;
						    }
						    else if(valueinit[i]=='_')
						    	keyw[i] = '_';
						}	
						if(strcmp(valueinit,"AND")==0)
						{
							strcpy(newToken->t->token,"AND");
							strcpy(newToken->t->value,valueinit);
							newToken->t->lineno=line;
							state = 1;
							begin = fwd;
							return newToken;
							break;
						}
						else if(strcmp(valueinit,"OR")==0)
						{
							strcpy(newToken->t->token,"OR");
							strcpy(newToken->t->value,valueinit);
							newToken->t->lineno=line;
							state = 1;
							begin = fwd;
							return newToken;
							break;
						}
						else
						{
							strcpy(newToken->t->token,keyw);
							strcpy(newToken->t->value,valueinit);
							newToken->t->lineno=line;
							state = 1;
							begin = fwd;
							return newToken;
							break;
						}	
					}
					else
					{
						if(tklen>20)
						{
							strcpy(newToken->t->token,"Error");
							strcpy(newToken->t->value,valueinit);
							printf("Identifier size too large! -- ");
							newToken->t->lineno=line;
							printf("Lexical Error: %s at line no: %d\n",valueinit,line);
							state = 1;
							fwd++;
							begin = fwd;
							return newToken;
							break;
						}
						else
						{
							strcpy(newToken->t->token,"ID");
							strcpy(newToken->t->value,valueinit);
							newToken->t->lineno=line;
							return newToken;
							break;
						}
					}
					
					break;

			case 3: // This branch is for state 4 to state10
					// in our original DFA 
					while(1)
					{
						ch = buffer[++fwd];
						//printf("%c\n",ch);

						if((ch>='0') && (ch<='9'))
						{
							valueinit[tklen++] = ch;
							//printf("\n %s \n",valueinit);
							state = 3;
						}
						else if(ch=='.')
						{
							ch = buffer[++fwd];

							if(ch=='.')
							{
								fwd--;
								strcpy(newToken->t->token,"NUM");
								strcpy(newToken->t->value,valueinit);
								newToken->t->lineno=line;
								state = 1;
								return newToken;
								break;
							}
							else if((ch>='0') && (ch<='9'))
							{
								valueinit[tklen++] = '.';
								valueinit[tklen++] = ch;
								while(1)
								{
									ch = buffer[++fwd];
									if((ch>='0') && (ch<='9'))
									{
										valueinit[tklen++] = ch;
										//ch = buffer[++fwd];
										state = 3;
									}
									else if(ch=='E' || ch=='e')
									{
										valueinit[tklen++] = ch;
										ch = buffer[++fwd];
										if(ch=='+' || ch=='-')
										{
											valueinit[tklen++] = ch;
											ch = buffer[++fwd];
											if((ch>='0') && (ch<='9'))
											{
												valueinit[tklen++] = ch;
												while(1)
												{
													ch = buffer[++fwd];
													//printf("\n %c \n",buffer[fwd]);
													if((ch>='0') && (ch<='9'))
													{
														valueinit[tklen++] = ch;
														state = 3;
													}
													else
													{
														//printf("\n %c \n",buffer[fwd]);
														strcpy(newToken->t->token,"RNUM");
														strcpy(newToken->t->value,valueinit);
														newToken->t->lineno=line;
														state = 1;
														return newToken;
														break;
													}
												}
											}
											else
											{
												strcpy(newToken->t->token,"Error");
												strcpy(newToken->t->value,valueinit);
												newToken->t->lineno=line;
												printf("Lexical Error: %s at line no: %d\n",valueinit,line);
												state = 1;
												begin = fwd;
												return newToken;
												break;
											}

										}
										else if((ch>='0') && (ch<='9'))
										{
											valueinit[tklen++] = ch;
											while(1)
											{
												ch = buffer[++fwd];
												if((ch>='0') && (ch<='9'))
												{
													valueinit[tklen++] = ch;
													ch = buffer[++fwd];
													state = 3;
												}
												else if (((ch>='a') && (ch<='z')) || ((ch>='A') && (ch<='Z')))
												{
													strcpy(newToken->t->token,"Error");
													strcpy(newToken->t->value,valueinit);
													newToken->t->lineno=line;
													printf("Lexical Error: %s at line no: %d\n",valueinit,line);
													state = 1;
													fwd++;
													begin = fwd;
													return newToken;
													break;
												}
												else
												{
													state = 1;
													break;
												}
											}

										}
									}
									else if (((ch>='a') && (ch<='z')) || ((ch>='A') && (ch<='Z')))
									{
										//printf("\n %c \n",ch);
										strcpy(newToken->t->token,"Error");
										strcpy(newToken->t->value,valueinit);
										newToken->t->lineno=line;
										printf("Lexical Error: %s at line no: %d\n",valueinit,line);
										state = 1;
										fwd++;
										begin = fwd;
										return newToken;
										break;
									}
									else
									{
										strcpy(newToken->t->token,"RNUM");
										strcpy(newToken->t->value,valueinit);
										newToken->t->lineno=line;
										state = 1;
										
										begin = fwd;
										return newToken;
										break;
									}
								}
							}
							else
							{
								fwd--;
								valueinit[tklen++]=buffer[fwd];
								strcpy(newToken->t->token,"Error");
								strcpy(newToken->t->value,valueinit);
								newToken->t->lineno=line;
								printf("Lexical Error: %s at line no: %d\n",valueinit,line);
								state = 1;
								fwd++;
								begin = fwd;
								return newToken;
								break;
							}
						}

						else
						{
							//printf("\n %c \n",ch);
							//printf("\n %c \n",buffer[fwd]);
							//printf("%s",valueinit);
							strcpy(newToken->t->token,"NUM");
							strcpy(newToken->t->value,valueinit);
							newToken->t->lineno=line;
							state = 1;
							//printf("\n %c \n",buffer[fwd]);
							return newToken;
							break;
						}
					}
					
					break;

			default: 
					printf("No matching case!\n");
					return newToken;
					break;
		}
	}
}

/* END Primary Functions */

/* **************************************************************************** */