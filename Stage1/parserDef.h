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
	Node* n;
	int rule_no;
	struct parsetree *child;
	struct parsetree *parent;
	struct parsetree *left;
	struct parsetree *right;
	int isleaf;
	int visited;

};

typedef struct parsetree ParseTree;

struct fandf
{
	int first[101][15];
	int follow[101][15];
	// 53 non terminals hence 53 x 20;
};

typedef struct fandf FirstAndFollow;

struct grammar
{
	int gnum[100][30];
};

typedef struct grammar Grammar;

struct parsetable
{
	int table[100][100];
	// Non terminals x terminals (excluding epsilon);
}; 

typedef struct parsetable ParseTable;

#endif