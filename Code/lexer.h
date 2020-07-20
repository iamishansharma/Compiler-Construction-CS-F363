/*	

	lexer.h 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	SSarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/
 
#ifndef LEXER_H
#define LEXER_H

#include "lexerDef.h"

extern char buffer[10000];
extern int buflen;
//extern char keyword[31][35];
//extern char *KeywordTable[1009];

// Primary Functions Declarations - 

FILE* getStream(FILE *fp);
Node* getNextToken();
void removeComments(char *testcaseFile);
bool isKeyword(char value[30]);
char bgetc(int pointer);
char* bgets(int start ,int end);

// Supporting Functions Declarations - 

Token* newToken();
Node* newNode();
Head* newHead();
void ClearMem(char *c, int len);

#endif