/*  ast.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "ast.h"

void callingAST(ParseTree *head)
{
	removeTerminals(head);
	ConstructAST(head);
}

void removeTerminals(ParseTree *head)
{
	if (head == NULL)
		return;

	switch(head->value)
	{
		// Cases when unnecessary terminals are being removed

		case 57:  // DECLARE
		case 58:  // DEF 
		case 59:  // DRIVERDEF
		case 60:  // EPSILON
		case 61:  // RETURNS
		case 63:  // COMMA
		case 73:  // USE
		case 74:  // SQBO
		case 78:  // ASSIGNOP
		case 80:  // BO
		case 95:  // $
		case 96:  // MODULE
		case 97:  // SEMICOL
		case 98:  // DRIVER
		case 99:  // PROGRAM
		case 100: // DRIVERENDDEF
		case 101: // ENDDEF
		case 102: // TAKES
		case 103: // INPUT
		case 104: // SQBC
		case 105: // COLON
		case 106: // OF
		case 108: // BC
		case 109: // WITH
		case 110: // PARAMETERS
		case 112: // DEFAULT
		case 113: // IN
		case 114: // RANGEOP

					removeNode(head);

				break;

		default: break;

	}
	
	if(head != NULL)
	{
		removeTerminals(head->child);
		removeTerminals(head->right);
	}
}

void ConstructAST(ParseTree *head)
// Recursively call this function to traverse this whole tree
{
	
	if (head == NULL)
		return;

	switch(head->value)
	{
		// Cases for which nodes need to be lifted up

		case 6:  // ret
		case 8:  // input_plist_again
		case 10: // output_plist_again
		case 13: // type
		case 15: // statements
				
					if(head->parent->value == 15) // DELETE THE RECURSIVE STATMENTS ONLY NOT FIRST PARENT STATEMENTS
						liftUpNode(head);

					break;

		case 16: // statement 
		case 19: // var_id_num
		case 20: // whichId
		case 23: // whichStmt
		case 28: // optional
		case 30: // idList_again
		case 36: // arithmeticOrBooleanExpr_again
		case 38: // recTerm_again
		case 40: // arithmeticExpr_again
		case 42: // term_again
		case 52: // caseStmts_again

					liftUpNode(head);

				break;

		// Cases for which modification are needed. 

		/*case :
		case :
		case : removeNode(head, head->child);

				break;

		default: break;*/

		
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

void removeNode(ParseTree *current)
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

void liftUpNode(ParseTree *current)
{
	ParseTree *parenttemp = current->parent;
	ParseTree *childtemp = current->child;
	ParseTree *righttemp = current->right;
	ParseTree *lefttemp = current->left;
	
	char parent[30];
	char child[30];
	char left[30];
	char right[30];

	if(current->value == 16)
	{
		if(parenttemp==NULL)
		{
			strcpy(parent,"NULL");
		}
		else
		{
			strcpy(parent,terms[parenttemp->value]);
		}
		if(childtemp==NULL)
		{
			strcpy(child,"NULL");
		}
		else
		{
			strcpy(child,terms[childtemp->value]);
		}
		if(righttemp==NULL)
		{
			strcpy(right,"NULL");
		}
		else
		{
			strcpy(right,terms[righttemp->value]);
		}
		if(lefttemp==NULL)
		{
			strcpy(left,"NULL");
		}
		else
		{
			strcpy(left,terms[lefttemp->value]);
		}
		printf("\nParent: %s | Current: %s | Child: %s | Right: %s | Left: %s \n",parent,terms[current->value],child,right,left);
	}
	
	// CASE WHEN THE CURRENT NODE IS THE ONLY CHILD OF ITS PARENT "OR" THE CURRENT NODE IS THE LEFTMOST CHILD OF ITS PARENT

	if(lefttemp == NULL)
	{
		if(righttemp == NULL)
		{
			if(current->value == 16)
				printf("\n\n Statement alone \n\n");

			parenttemp->child = childtemp;
			childtemp->parent = parenttemp;
		}
		else
		{
			if(current->value == 16)
				printf("\n\n Statement at start \n\n");

			parenttemp->child = childtemp;
			childtemp->parent = parenttemp;

			righttemp->left = childtemp;
		}

		// free(current);
	}
	// CASE WHEN THE CURRENT NODE IS NOT THE LEFTMOST CHILD OF ITS PARENT
	else
	{
		// CASE WHEN THE CURRENT NODE->RIGHT = NULL
		if(righttemp == NULL)
		{
			if(current->value == 16)
				printf("\n\n Statement right end \n\n");

			// CHILD OF CURRENT IS NULL
			if(childtemp==NULL)
			{
				lefttemp->right = NULL;
			}
			// HAS SOME CHILD
			else
			{
				

				lefttemp->right = childtemp;
				childtemp->left = lefttemp;

				ParseTree *temp = childtemp;

				while(temp!=NULL)
				{
					temp->parent = parenttemp;
					temp = temp->right;
				}
			}

			// free(current);
		}
		// CASE WHEN THE CURRENT NODE->RIGHT != NULL
		else
		{

			lefttemp->right = childtemp;
			childtemp->left = lefttemp;

			childtemp->right = righttemp;
			righttemp->left = childtemp;

			childtemp->parent = lefttemp->parent;

			// free(current);
		}
	}
}