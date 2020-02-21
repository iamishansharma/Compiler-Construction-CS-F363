/*	parserDef.h 

	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/ 

#ifndef PARSER_DEF_H
#define PARSER_DEF_H

#include "lexer.h"

struct parsetree
{				
	Node* token;
	struct parsetree *child;
	struct parsetree *parent;
	struct parsetree *left;
	struct parsetree *right;
	int ifleaf;

};

typedef struct parsetree ParseTree;

struct fandf
{
	int first[55][20];
	int follow[55][20];	
};

typedef struct fandf FirstAndFollow;

struct grammar
{
	int gnum[55][20];
};

typedef struct grammar Grammar;

struct term
{
	char termname[15];
	bool nont_t;
};

typedef struct term Term;

struct parsetable
{
	int table[110][110];
}; 

typedef struct parsetable ParseTable;

#endif