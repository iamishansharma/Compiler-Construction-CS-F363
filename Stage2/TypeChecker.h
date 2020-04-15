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

void isIDEntryNULLExp(ParseTree *root, int *errors);
void CheckExpRec(ParseTree *expr, int *errors, int *udvflag);
void CheckSwitch(ParseTree *swt, int *errors, int *udvflag);
void CheckIPL(SymbolTable *table, ParseTree *IPL, int *errors, int *udvflag);
void CheckOPL(SymbolTable *table, ParseTree *OPL, int *errors, int *udvflag);
void CheckIterStmt(ParseTree *Iter, int *errors, int *udvflag);
void CheckWhileAssExpRec(ParseTree *root, int *errors, int *udvflag);
void CheckFORID(ParseTree *iterID, ParseTree *func, int *errors, int *udvflag);
void CheckWhileID(char *id, ParseTree *func, int *errors, int *udvflag);
void CheckAssignStmt(ParseTree *Ass, int *errors, int *udvflag);
void CheckIOStmt(ParseTree *IO, int *errors, int *udvflag);
void CheckFunctioninST(ParseTree *Func, int *errors, int *udvflag);
SymbolTable *FindModule(char *id, SymbolTable *tables, int *udvflag);
void CheckOPLifAssigned(ParseTree *func, int *errors, int *udvflag);
void CheckOPLifAssignedRec(char *id, ParseTree *func, int *errors, int *udvflag);
void AssignType(ParseTree *head, int *udvflag);

// Main Functions -> 

void CallingTypeChecker(ParseTree *head, SymbolTable *table, int *errors, int *udvflag);
void TypeChecker(ParseTree *head, SymbolTable *table, int *errors, int *udvflag);

#endif