/*	parser.h 

	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/ 

#ifndef PARSER_H
#define PARSER_H

#include "parserDef.h"

// Primary Functions Declarations - 

void ComputeFirstAndFollowSets(Grammar G, FirstAndFollow F);
void createParseTable(FirstAndFollow F, ParseTable T);
void parseInputSourceCode(char *testcaseFile, ParseTable T);
void printParseTree(ParseTree PT, char *outfile);

// Supporting Functions Declarations - 

Grammar getGrammar(FILE *f);

#endif