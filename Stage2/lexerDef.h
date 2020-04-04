/*	

	lexerDef.h 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#ifndef LEXER_DEF_H
#define LEXER_DEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern int state;
extern int line;
extern int begin;
extern int fwd;
extern int fwd2;
extern int keyno;
extern int tokno;

struct token
{
	char token[40];
	char value[40]; // create union 
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