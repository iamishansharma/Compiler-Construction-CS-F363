/*	lexerDef.h 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#ifndef LEXER_DEF_H
#define LEXER_DEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int keyno;
extern int tokno;
extern char *keyword[35];
extern char *tokens[60];

struct token
{
	char token[30];
	char value[30];
	int lineno;
};

typedef struct token Token;

struct node
{
	Token *t;
};

typedef struct node Node;

struct head
{
	Node *hd;
};

typedef struct head Head;

#endif