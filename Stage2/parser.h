/*	parser.h 

	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/ 

#ifndef PARSER_H
#define PARSER_H

#include "parserDef.h"

// Primary Functions Declarations - 

FirstAndFollow ComputeFirst(FirstAndFollow F, Grammar G);
FirstAndFollow ComputeFollow(FirstAndFollow F, Grammar G);
ParseTable createParseTable(FirstAndFollow F, ParseTable T, Grammar G);
void parseInputSourceCode(FILE *f, ParseTable T, Grammar G);
void printParseTree(FILE *f);
void printFF(FirstAndFollow F);
ParseTree* searchposition(ParseTree *head, int stacktop);

// Supporting Functions Declarations - 

void printParseTreeToFile(ParseTree *trav, FILE *f);
Grammar getGrammar(FILE *f);
ParseTree* returnhead();
void printTable(ParseTable T);
int compareTerm(char *tocomp);
void make_stack();
void push(int ele);
int pop();
void insert_in_tree(ParseTree *x,int rule,Grammar G,Node *n);

#endif