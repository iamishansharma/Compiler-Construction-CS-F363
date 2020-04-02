/*  ast.h 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "lexer.h"
#include "lexerDef.h"
#include "parser.h"
#include "parserDef.h"

/* Function definations */

void callingAST(ParseTree *head);
void removeTerminals(ParseTree *head);
void ConstructAST(ParseTree *head);
void ExpressionAST(ParseTree *head);
void printAST(ParseTree *head);
void liftUpNode(ParseTree *child);
void removeNode(ParseTree *head);