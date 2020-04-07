/*  

	TypeChecker.c
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

	Type Checking Semantics ->
	
	1.
*/

#include "TypeChecker.h"
#include "ast.h"
#include "SymbolTableDef.h"
#include "SymbolTable.h"

/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* Auxilary Functions */

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

void CheckIOStmt(ParseTree *IO, int *errors)
{

}

void CheckIterStmt(ParseTree *Iter, int *errors)
{

}

void CheckAssignStmt(ParseTree *Ass, int *errors)
{

}

int CheckVariableinST(ParseTree *Var, int *errors)
{
	int found = 0; 
	// 0 - not found
	// 1 - found as variable
	return 0;
}

int CheckFunctioninST(ParseTree *Func, int *errors)
{
	return 0;
}

/* Auxilary Functions END */

/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* MAIN Functions */

void CallingTypeChecker(ParseTree *head, SymbolTable *table, int *errors)
{
	TypeChecker(head, table, errors);
}

void TypeChecker(ParseTree *head, SymbolTable *table, int *errors)
{
	if(head == NULL)
		return;

	if(strcmp(terms[head->value],"ID") == 0)
	{
		//printf("\n ID: %s | IDParent: %s | Scope: %s | ParentScope: %s", head->entry->name, terms[head->parent->value], head->entry->scope->name, head->entry->scope->parent->name);
	}

	TypeChecker(head->child, table, errors);
	TypeChecker(head->right, table, errors);
}

/* MAIN Functions END */

/********************************************************************************************************************************/
/********************************************************************************************************************************/
