/*  

	TypeChecker.h
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#ifndef type_h
#define type_h

#include "ast.h"

// Checking Functions ->

void CheckArray(ParseTree *arrayid, int *errors);
void CheckExpRec(ParseTree *expr, int *errors);
void CheckExpCall(ParseTree *expr, int *errors);
void CheckSwitch(ParseTree *swt, int *errors);
void CheckIPL(SymbolEntry *mod, SymbolTable *table, ParseTree *IPL, int *errors);
void CheckOPL(SymbolEntry *mod, SymbolTable *table, ParseTree *OPL, int *errors);
void CheckIOStmt(ParseTree *IO, int *errors);
void CheckIterStmt(ParseTree *Iter, int *errors);
void CheckAssignStmt(ParseTree *Ass, int *errors);

// Main Functions -> 

void CallingTypeChecker(ParseTree *head, SymbolTable *table, int *errors);
void TypeChecker(ParseTree *head, SymbolTable *table, int *errors);

#endif