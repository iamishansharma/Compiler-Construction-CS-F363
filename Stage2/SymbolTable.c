/*  

	SymbolTable.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "ast.h"
#include "SymbolTable.h"

/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* Auxilary Functions */

SymbolTable *ScopeEntry(SymbolTable *table, char *scopename)
{
	SymbolTable *newTable = (SymbolTable *)malloc(sizeof(SymbolTable));

	newTable->parent = NULL;
	newTable->child = NULL;
	newTable->right = NULL;
	newTable->left = NULL;
	newTable->nodehead = NULL;

	strcpy(newTable->name, scopename);

	// Insert scope in tree

	if(table != NULL)
	{
		if(table->child == NULL)
			table->child = newTable;
		else
		{
			SymbolTable *sib = table->child;

			while(sib->right != NULL)
				sib = sib->right;

			sib->right = newTable;
			newTable->left = sib;
		}
		newTable->parent = table;
	}

	return newTable;

}

SymbolEntry *FindEntry(char *id, SymbolTable *scope, int line, int isFunc, int *errors)
{
	SymbolEntry *FoundEntry = NULL;
	return FoundEntry;
}

void AddEntry(char *id, int usage, char *type, int isArray, Index *startindex, Index *endindex, int line, SymbolTable *scope, int *errors)
{
	// Search the current identifier in the scopes

		// If found, error do 

		// Else ghusao 
}

SymbolTable *GetScope(SymbolTable *current)
{
	SymbolTable *FoundScope = NULL;
	return FoundScope;
}

/* Auxilary Functions END */

/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* MAIN Functions */ 

SymbolTable *CallingSymbolTable(ParseTree *head, int *errors)
{
	SymbolTable *table;
	table = ScopeEntry(NULL, "program");
	ConstructSymbolTable(head, table, errors);
	return table;
}

void ConstructSymbolTable(ParseTree *head, SymbolTable *scope, int *errors)
{
	if(head == NULL)
		return;

	SymbolTable *newScope;
	SymbolEntry *newEntry;

	//head->scope = scope;

	ConstructSymbolTable(head->child, scope, errors);

	// ID
	if(strcmp(terms[(head->value)],"ID") == 0)
	{
		if((strcmp(terms[(head->parent->value)],"idList") == 0) && (strcmp(terms[(head->parent->value)],"declareStmt") == 0))
		{
			ParseTree *datatype = head->parent->right->child;

			if(strcmp(terms[(datatype->value)],"ARRAY") == 0)
			{
				ParseTree *index1 = head->parent->right->child->child->child->child;
				ParseTree *index2 = head->parent->right->child->child->child->right->child;
				ParseTree *datatypearray = head->parent->right->child->right;

				Index *i1 = (Index *)malloc(sizeof(Index));
				Index *i2 = (Index *)malloc(sizeof(Index));

				i1->isused = 1;
				i2->isused = 1;

				if(strcmp(terms[index1->value],"ID") == 0)
				{
					strcpy(i1->id,index1->n->t->value);
					i1->ifnumvalue = -1;
					i1->isDynamic = 1;
				}
				else // INDEX1 is num
				{
					int value = atoi(index1->n->t->value);
					strcpy(i1->id,"NUM");
					i1->ifnumvalue = value;
					i1->isDynamic = 0;
				}

				if(strcmp(terms[index2->value],"ID") == 0)
				{
					strcpy(i2->id,index2->n->t->value);
					i2->ifnumvalue = -1;
					i2->isDynamic = 1;
				}
				else // INDEX2 is num
				{
					int value = atoi(index2->n->t->value);
					strcpy(i2->id,"NUM");
					i2->ifnumvalue = value;
					i2->isDynamic = 0;
				}

				//             ID name   Usage: Variable  Datatype  isArray
				AddEntry(head->n->t->value, 1, terms[datatype->value], 1, i1, i2, head->n->t->lineno, scope, errors);

			}
			else // Non array INTEGER | REAL | BOOLEAN 
			{	
				Index *i1 = (Index *)malloc(sizeof(Index));
				Index *i2 = (Index *)malloc(sizeof(Index));

				i1->isused = 0;
				i2->isused = 0;

				//              ID name  Usage: Variable  Datatype  Not array 
				AddEntry(head->n->t->value, 1, terms[datatype->value], 0, i1, i2, head->n->t->lineno, scope, errors);
			}
		}
		else if(strcmp(terms[(head->parent->value)],"input_plist") == 0)
		{

		}
		else if(strcmp(terms[(head->parent->value)],"output_plist") == 0)
		{

		}
		else if(strcmp(terms[(head->parent->value)],"module") == 0)
		{

		}
		else if(strcmp(terms[(head->parent->value)],"moduleDeclarations") == 0)
		{

		}
		else
		{
			// moduleReuseStmt
		}
		// some condition
	}
	else
	{
		// Statements 

		// caseStmts

		// module 

		// driverModule

		// iterativeStmt
	}
	ConstructSymbolTable(head->right, scope, errors);
}

void printSymbolTable(SymbolTable *head)
{

}

/* MAIN Functions END */ 

/********************************************************************************************************************************/
/********************************************************************************************************************************/