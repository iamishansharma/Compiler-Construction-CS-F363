/*  

	TypeChecker.c
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

	Type Checking and Semantics Analyser Rules ->

	Errors template: printf("\n%sError:%s The switch statement identifier %s at line no %d cannot be of type real.\n", BOLDRED, RESET, switchID->n->t->value, switchID->n->t->lineno);

	IDENTIFIER SEMANTICS ->
	
	DONE	1. An identifier cannot be declared multiple times in the same scope. 

	DONE	2. An identifier must be declared before its use. 				

	DONE	3. An identifier used beyond its scope must be viewed as undefined. 	

	FUNCTIONS SEMANTICS -> 

		1. The types and the number of parameters returned by a function must 
			be the same as that of the parameters used in invoking the function.

		2. The parameters being returned by a function must be assigned a value. 
			If a parameter does not get a value assigned within the function definition, 
			it should be reported as an error.

		3. The function that does not return any value, must be invoked appropriately.

		4. Function input parameters passed while invoking it should be of the 
			same type as those used in the function definition.

		5. Function overloading is not allowed.

		6. A function declaration for a function being used (say F1) by another 
			(say F2) must precede the definition of the function using it(i.e. F2), 
			only if the function definition of F1 does not precede the definition of F2.

		7. If the function definition of F1 precedes function definition of 
			F2(the one which uses F1), then the function declaration of F1 is 
			redundant and is not valid.

		8. The function cannot be invoked recursively.

	SWITCH SEMANTICS ->

	DONE	1. A switch statement with an integer typed identifier associated with it, 
			can have case statement with case keyword followed by an integer only 
			and the case statements must be followed by a default statement. 

	DONE	2. A switch statement with an identifier of type real is not valid and an error 
			should be reported.

	DONE	3. A switch statement with a boolean type identifier can have the case statements 
			with labels true and false only. The switch statement then should not have a 
			default statement.

	ITERATIVE SEMANTICS ->
	
	DONE	1. 'FOR' statement must not redefine the variable that participates in the 
				iterating over the range and iterating variable should be integer type.

		2. WHILE expression must be of boolean type

	EXPRESSION SEMANTICS -> 

		1. is integer, if both expressions are of type integer and the operator is arithmetic operator.

		2. is real, if both the expressions are of type real and the operator is arithmetic operator.

		3. is boolean, if both expressions are of type integer and the operator is a relational operator.

		4. is boolean, if both expressions are of type real and the operator is relational.

		5. is boolean, if both expressions are of type boolean and the operator is logical.

	ARRAY SEMANTICS ->

		FOR STATICS ARRAYS: 

			1. A[3] whenever used should be in bounds on the indices.

			2. The operations +, -, *, / and all relational and 
				logic operators cannot be applied on array variables.

			3. The assignment operator applied to two array variables of 
				the same type is valid. For example, if A and B are the 
				array variables of type array[12..20] of real, then A:= B; 
				is a valid statement. This applies to dynamic arrays of 
				type array[a..b] of real as well.

			4. Consider array elements with index represented by integer identifier say A[k]. 
				Here type checking of variable k is done at compile time. 

					If the type of k is integer, then it is valid else it is reported as an error. 

					Also, the type checking of A[13], for type of index (NUM), is done at compile time.

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
	ParseTree *switchID = swt->child->right;

	if(strcmp(switchID->entry->type,"INTEGER") == 0)
	{
		ParseTree *temp = switchID;

		int found = 0;

		while(temp != NULL)
		{
			if(strcmp(terms[temp->value],"default") == 0)
			{
				found = 1;
				break;
			}
			temp = temp->right;
		}

		ParseTree *caseStmt = swt->child->right->right;
		ParseTree *temp2 = caseStmt->child;

		while(temp2 != NULL)
		{
			if(strcmp(terms[temp2->value],"value") == 0)
			{
				if(strcmp(temp2->child->entry->type,"INTEGER") != 0)
				{
					printf("\n\t%sError:%s 'switch' with integer identifier cannot have non-integer '%s' case value. Error at line no %d", BOLDRED, RESET, temp2->child->n->t->value, temp2->child->n->t->lineno);
					*errors = *errors +1;
				}
			}
			temp2 = temp2->right;
		}

		if(!found)
		{
			printf("\n\t%sError:%s 'default' case statement missing for 'switch' with integer identifier starting at line no: %d\n", BOLDRED, RESET, switchID->n->t->lineno);
			*errors = *errors +1;
		}
	}
	else if(strcmp(switchID->entry->type,"BOOLEAN") == 0)
	{

		ParseTree *caseStmt = swt->child->right->right;
		ParseTree *temp2 = caseStmt->child;

		while(temp2 != NULL)
		{
			if(strcmp(terms[temp2->value],"value") == 0)
			{
				if(strcmp(temp2->child->entry->type,"BOOLEAN") != 0)
				{
					printf("\n\t%sError:%s 'switch' with boolean identifier cannot have non-boolean '%s' case value, error at line no %d", BOLDRED, RESET, temp2->child->n->t->value, temp2->child->n->t->lineno);
					*errors = *errors +1;
				}
			}
			temp2 = temp2->right;
		}

		ParseTree *temp = switchID;

		int found = 0;

		while(temp != NULL)
		{
			if(strcmp(terms[temp->value],"default") == 0)
			{
				printf("\n\t%sError:%s 'switch' from line no: %d with 'boolean' identifier cannot have 'default' case.", BOLDRED, RESET, switchID->n->t->lineno);
				*errors = *errors +1;
			}
			temp = temp->right;
		}
	}
	else
	{
		printf("\n\t%sError:%s The switch statement identifier %s at line no: %d cannot be of type 'real'.\n", BOLDRED, RESET, switchID->n->t->value, switchID->n->t->lineno);
		*errors = *errors +1;
	}
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
	if(strcmp(terms[Iter->child->value],"FOR") == 0)
	{
		ParseTree *iterID = Iter->child->right;

		if(strcmp(iterID->entry->type,"INTEGER") != 0)
		{
			printf("\n\t%sError:%s In 'for' construct the iterating variable '%s' cannot be non-integer at line no: %d\n", BOLDRED, RESET, iterID->n->t->value, iterID->n->t->lineno);
			*errors = *errors +1;
		}

		ParseTree *st = Iter->child->right->right->right;

		ParseTree *temp2 = st->child;

		while(temp2 != NULL)
		{
			if(strcmp(terms[temp2->value],"declareStmt") == 0)
			{
				ParseTree *idl = temp2->child->child;
				while(idl != NULL)
				{
					if(strcmp(idl->n->t->value,iterID->n->t->value) == 0)
					{
						printf("\n\t%sError:%s Iterating variable '%s' cannot be declared inside the 'for' loop, error at line no: %d\n", BOLDRED, RESET, iterID->n->t->value, idl->n->t->lineno);
						*errors = *errors +1;
					}
					idl = idl->right;
				}
			}
			temp2 = temp2->right;
		}
	}
	else if(strcmp(terms[Iter->child->value],"WHILE") == 0)
	{

	}
}

void CheckAssignStmt(ParseTree *Ass, int *errors)
{

}

void CheckVariableinST(ParseTree *Var, int *errors)
{
	
}

void CheckFunctioninST(ParseTree *Func, int *errors)
{

}
void AssignType(ParseTree *head)
{
	if(head == NULL)
		return;

	if(strcmp(terms[head->value],"NUM") == 0)
	{
		SymbolEntry *newEntry = (SymbolEntry *)malloc(sizeof(SymbolEntry));
		strcpy(newEntry->name,head->n->t->value);
		strcpy(newEntry->type,"INTEGER");
		newEntry->offset = -1;
		newEntry->width = -1;
		head->entry = newEntry;
	}
	else if(strcmp(terms[head->value],"RNUM") == 0)
	{
		SymbolEntry *newEntry = (SymbolEntry *)malloc(sizeof(SymbolEntry));
		strcpy(newEntry->name,head->n->t->value);
		strcpy(newEntry->type,"REAL");
		newEntry->offset = -1;
		newEntry->width = -1;
		head->entry = newEntry;
	}
	else if(strcmp(terms[head->value],"TRUE") == 0)
	{
		SymbolEntry *newEntry = (SymbolEntry *)malloc(sizeof(SymbolEntry));
		strcpy(newEntry->name,head->n->t->value);
		strcpy(newEntry->type,"BOOLEAN");
		newEntry->offset = -1;
		newEntry->width = -1;
		head->entry = newEntry;
	}
	else if(strcmp(terms[head->value],"FALSE") == 0)
	{
		SymbolEntry *newEntry = (SymbolEntry *)malloc(sizeof(SymbolEntry));
		strcpy(newEntry->name,head->n->t->value);
		strcpy(newEntry->type,"BOOLEAN");
		newEntry->offset = -1;
		newEntry->width = -1;
		head->entry = newEntry;
	}

	AssignType(head->child);
	AssignType(head->right);
}

/* Auxilary Functions END */

/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* MAIN Functions */

void CallingTypeChecker(ParseTree *head, SymbolTable *table, int *errors)
{
	// At this point we don't need to check if any variable is undeclared because that is already handled during SymbolTable

	AssignType(head);
	TypeChecker(head, table, errors);
}

void TypeChecker(ParseTree *head, SymbolTable *table, int *errors)
{
	if(head == NULL)
		return;

	if(strcmp(terms[head->value],"expression") == 0) // Expression Checker
	{
		CheckExpCall(head, errors);
	}
	else if(strcmp(terms[head->value],"conditionalStmt") == 0) // SWITCH 
	{
		CheckSwitch(head, errors);
	}
	else if(strcmp(terms[head->value],"moduleReuseStmt") == 0) // Function Call
	{
		CheckFunctioninST(head, errors);
	}
	else if(strcmp(terms[head->value],"ioStmt") == 0) // IOStmt
	{
		CheckIOStmt(head, errors);
	}
	else if(strcmp(terms[head->value],"iterativeStmt") == 0) // FOR and WHILE
	{
		CheckIterStmt(head, errors);
	}
	else if(strcmp(terms[head->value],"assignmentStmt") == 0) // ASSIGN
	{
		CheckAssignStmt(head, errors);
	}

	TypeChecker(head->child, table, errors);
	TypeChecker(head->right, table, errors);
}

/* MAIN Functions END */

/********************************************************************************************************************************/
/********************************************************************************************************************************/
