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

#include "lexerDef.h"

// Primary Functions Declarations - 

FILE* getStream(FILE *fp);
Node* getNextToken();
void removeComments(char *testcaseFile, char *cleanFile);
bool isKeyword(char value[30]);

// Supporting Functions Declarations - 

Token* newToken();
Node* newNode();
Head* newHead();
void ClearMem(char *c, int len);

#endif