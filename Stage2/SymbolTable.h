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

struct udv // undeclared variable structure
{
	char id[30];
	int lineno;
	char scopename[30];
	char scopeparentname[30];
	struct udv *next;
};

typedef struct udv UDV;
UDV *udvhead;

// Functions Declatations -> 

/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* Auxilary Functions */

SymbolTable *ScopeEntry(SymbolTable *parent, char *st, int line);
SymbolEntry *FindEntryEverywhere(char *id, SymbolTable *scope, int line, int isFunc, int *errors);
int FindEntryInScope(char *id, SymbolTable *scope);
void AddEntry(char *id, int usage, char *type, int isArray, Index *startindex, Index *endindex, int line, SymbolTable *scope, int *errors);
void ReassignMRS(ParseTree *head, SymbolTable *globaltable, int *errors);

/* Auxilary Functions END */

/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* MAIN Functions */ 

void printActiveRecords(SymbolTable *Table);
void printSymbolTable(SymbolTable *head);
void printSymbolTableArray(SymbolTable *table);
SymbolTable *CallingSymbolTable(ParseTree *head, int *errors, int *udvflag);
void ConstructSymbolTable(ParseTree *head, SymbolTable *scope, int *errors, int *udvflag);

/* MAIN Functions END */ 

/********************************************************************************************************************************/
/********************************************************************************************************************************/
#endif