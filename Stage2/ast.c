/*  ast.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "ast.h"

void ConstructAST(ParseTree *head) 
// Recursively call this function to traverse this whole tree
{
	
	if (head == NULL)
		return;

	switch(head->value)
	{
		// These are cases for which no action to be taken

		/* */
		
					break;

		// Cases for which punctuations/unnecesary terminals are being removed

		case 58-1:  // DECLARE
		case 97-1:  // MODULE
		case 98-1:  // SEMICOL
		case 60-1:  // DRIVERDEF
		case 99-1:  // DRIVER
		case 100-1: // PROGRAM
		case 101-1: // DRIVERENDDEF
		case 59-1:  // DEF
		case 102-1: // ENDDEF
		case 103-1: // TAKES
		case 104-1: // INPUT
		case 75-1:  // SQBO
		case 105-1: // SQBC
		case 62-1:  // RETURNS
		case 106-1: // COLON
		case 64-1:  // COMMA
		case 107-1: // OF
		case 115-1: // RANGEOP
		case 81-1:  // BO
		case 109-1: // BC
		case 70-1:  // GET_VALUE
		case 71-1:  // PRINT
		case 74-1:  // USE
		case 110-1: // WITH
		case 111-1: // PARAMETERS
		case 113-1: // DEFAULT

					removeTerminals(head);

					break;

		// Cases for which nodes need to be lifted up.

		/*case :
		case : 
		case : liftUpNode(head); 

				break;

		// Cases for which modification are needed. 

		case :
		case :
		case : removeNode(head, head->child);

				break;*/

		default: break;

	}
	
	if(head != NULL)
	{
		ConstructAST(head->child);
		ConstructAST(head->right);
	}
}

void printAST(ParseTree *head)
{
	// Copy from Parse Tree and change accordingly.
}

void removeTerminals(ParseTree *current)
{
	if(current->left == NULL)
	{   
		ParseTree *righttemp = current->right;

		current->parent->child = righttemp;

		if(righttemp != NULL)
			righttemp->left = NULL;

		free(current);
	}
	else
	{   
		ParseTree *lefttemp = current->left;
		ParseTree *righttemp = current->right;

		lefttemp->right = righttemp;

		if(righttemp != NULL)
			righttemp->left = lefttemp;

		free(current);
	}
}

ParseTree* liftUpNode(ParseTree *head)
{
	
}

ParseTree* removeNode(ParseTree *head, ParseTree *child)
{
	
}