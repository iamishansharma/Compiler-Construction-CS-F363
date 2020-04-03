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

/***************************************/

/* GROUND LEVEL FUNCTIONS */

TokenHash* CreateTable();
TNode* CreateNode(char *inname, char *type, char *function, char *ifnumvalue);
FNode *CreateFNode(char *functionname, char *input_parameters,char *output_parameters);
int hash(char *key);

/* GROUND LEVEL FUNCTIONS END*/

/***************************************/

/* FIRST LEVEL (FOR FUNCTIONS) Functions */

int HashInsertFunc(char *key, char* input_parameters, char* output_parameters);
int GetFuncHashValue(char* functionname);
void FuncDisplay();
void GetFuncInputType(char* functionname);
void GetFuncOutputType(char* functionname);
char *GetFunctionInputType(char* functionname);
char *GetFunctionInputType(char* functionname);
int CheckFuncPresent(char* functionname);
FNode *DirectFunctionPointer(char* functionname);

/* FIRST LEVEL (FOR FUNCTIONS) Functions END*/

/***************************************/

/* SECOND LEVEL (FOR TOKENS) Functions */

int HashInsert(char* key,char* type,char* functionname,char* ifnumvalue);
int CheckSymbolPresent(char* key,char* functionname);
int GetOffset(char* key,char* functionname);
char *GetType(char* key,char* functionname);
void AutomateOffset(char* functionname);
TNode *GetDirectPointer(char* key,char* functionname);

/* SECOND LEVEL (FOR TOKENS) Functions END*/

/***************************************/

/* MAIN Functions */ 

void populateSymbolTable(FILE *semantic, ParseTree *head,char *scope);
void displaySymbolTable();

/* MAIN Functions END */ 

/***************************************/
#endif