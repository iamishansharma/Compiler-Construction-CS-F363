/*  

	TypeChecker.c
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

	Type Checking Semantics ->
	
	1. Every variable should be in symbol table during use.
	2. Every module should have defination / declaration during use.
	3.
*/

#include "TypeChecker.h"
#include "ast.h"
#include "SymbolTableDef.h"
#include "SymbolTable.h"

void CheckArray(ParseTree *arrayid, int *errors)
{

}

void CheckExpRec(ParseTree *expr, int *errors)
{

}

void CheckExpCall(ParseTree *expr, int *errors)
{

}

void CheckSwitch(ParseTree *swt, int *errors)
{

}

void CheckIPL(SymbolEntry *mod, SymbolTable *table, ParseTree *IPL, int *errors)
{

}

void CheckOPL(SymbolEntry *mod, SymbolTable *table, ParseTree *OPL, int *errors)
{

}

void CallingTypeChecker(ParseTree *head, SymbolTable *table, int *errors)
{

}

void CheckIOStmt(ParseTree *IO, int *errors)
{

}

void CheckIterStmt(ParseTree *Iter, int *errors)
{

}

void CheckAssignStmt(ParseTree *Ass, int *errors)
{

}

void TypeChecker(ParseTree *head, SymbolTable *table, int *errors)
{

}