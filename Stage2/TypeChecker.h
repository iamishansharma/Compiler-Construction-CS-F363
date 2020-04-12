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

void CheckExpRec(ParseTree *expr, int *errors);
void CheckSwitch(ParseTree *swt, int *errors);
void CheckIPL(SymbolTable *table, ParseTree *IPL, int *errors);
void CheckOPL(SymbolTable *table, ParseTree *OPL, int *errors);
void CheckIOStmt(ParseTree *IO, int *errors);
void CheckIterStmt(ParseTree *Iter, int *errors);
void CheckWhileAssExpRec(ParseTree *root, int *errors);
void CheckFORID(ParseTree *iterID, ParseTree *func, int *errors);
void CheckWhileID(char *id, ParseTree *func, int *errors);
void CheckAssignStmt(ParseTree *Ass, int *errors);
void CheckFunctioninST(ParseTree *Func, int *errors);
SymbolTable *FindModule(char *id, SymbolTable *tables);
void CheckOPLifAssigned(ParseTree *func, int *errors);
void CheckOPLifAssignedRec(char *id, ParseTree *func, int *errors);
void AssignType(ParseTree *head);

// Main Functions -> 

void CallingTypeChecker(ParseTree *head, SymbolTable *table, int *errors);
void TypeChecker(ParseTree *head, SymbolTable *table, int *errors);

#endif