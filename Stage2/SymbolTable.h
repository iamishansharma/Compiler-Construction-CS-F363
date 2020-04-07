/*  

	SymbolTable.h 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#ifndef ST_H
#define ST_H

#include "SymbolTableDef.h"

// Functions Declatations -> 

/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* Auxilary Functions */

SymbolTable *ScopeEntry(SymbolTable *parent, char *st);
SymbolEntry *FindEntryEverywhere(char *id, SymbolTable *scope, int line, int isFunc, int *errors);
int FindEntryInScope(char *id, SymbolTable *scope);
void AddEntry(char *id, int usage, char *type, int isArray, Index *startindex, Index *endindex, int line, SymbolTable *scope, int *errors);


/* Auxilary Functions END */

/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* MAIN Functions */ 

void printSymbolTable(SymbolTable *head);
SymbolTable *CallingSymbolTable(ParseTree *head, int *errors);
void ConstructSymbolTable(ParseTree *head, SymbolTable *scope, int *errors);

/* MAIN Functions END */ 

/********************************************************************************************************************************/
/********************************************************************************************************************************/
#endif