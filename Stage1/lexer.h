/*	lexer.h 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/ 

#ifndef LEXER_H
#define LEXER_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum 
{

	integer,
	real,
	boolean,
	of,
	array,
	start,
	end,
	declare,
	module,
	driver,
	program,
	get_value,
	print,
	use,
	with,
	parameters,
	true,
	false,
	takes,
	input,
	returns,
	AND,
	OR,
	for,
	in,
	switch,
	case,
	break,
	default,
	while

}Keyword;

typedef enum 
{

	INTEGER,
	REAL,
	BOOLEAN,
	OF,
	ARRAY,
	START,
	END,
	DECLARE,
	MODULE,
	DRIVER,
	PROGRAM,
	GET_VALUE,
	PRINT,
	USE,
	WITH,
	PARAMETERS,
	TRUE,
	FALSE,
	TAKES,
	INPUT,
	RETURNS,
	AND,
	OR,
	FOR,
	IN,
	SWITCH,
	CASE,
	BREAK,
	DEFAULT,
	WHILE,
	PLUS,
	MINUS,
	MUL,
	DIV,
	LT,
	LE,
	GE,
	GT,
	EQ,
	NE,
	DEF,
	ENDDEF,
	COLON,
	RANGEOP,
	SEMICOL,
	COMMA,
	ASSIGNOP,
	SQBO,
	SQBC,
	BO,
	BC,
	COMMENTMARK,
	DRIVERDEF,
	DRIVERENDDEF

}Token;

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
}

typedef struct head *Head;

// Functions Declarations - 

FILE *getStream(FILE *fp);
Node* getNextToken();
void removeComments(char *testcaseFile, char *cleanFile);

#endif




