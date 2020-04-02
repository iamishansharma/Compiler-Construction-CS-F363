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
	ConstructAST(head);
}

void ConstructAST(ParseTree *head)
{
	if(head->child != NULL)
	{
		ParseTree *child = head->child;

		while(child != NULL)
		{
			// Terminals 
			if(child->value >= NTER && child->child == NULL)
			{
				switch(child->value)
				{
					// Cases when unnecessary terminals are being removed

					case 57:  // DECLARE
					case 58:  // DEF 
					case 59:  // DRIVERDEF
					case 60:  // EPSILON
					case 61:  // RETURNS
					case 63:  // COMMA
					case 68:  // START
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
					case 107: // END
					case 108: // BC
					case 109: // WITH
					case 110: // PARAMETERS
					case 112: // DEFAULT
					case 113: // IN
					case 114: // RANGEOP

								removeNode(child);

							break;

					default: break;
				}
			}
			else
			{
				ConstructAST(child);

				// Remove Empty Terminals

				if(child->child == NULL)
					removeNode(child);

				// Removing all recursive non terminals
				switch(child->value)
				{
					// Cases for which nodes need to be lifted up

							 // moduleDeclations ??

					case 3:  // otherModules

								if(child->parent->value == 3) // DELETE THE RECURSIVE otherModules ONLY NOT FIRST PARENT otherModules

									liftUpNode(child);

								break;

					case 6:  // ret
					case 8:  // input_plist_again
					case 10: // output_plist_again
					case 13: // type
					case 15: // statements
							
								if(child->parent->value == 15) // DELETE THE RECURSIVE STATMENTS BUT NOT FIRST PARENT STATEMENTS

									liftUpNode(child);

								break;

					case 16: // statement 
					case 20: // whichId
					case 21: // simpleStmt
					case 23: // whichStmt
					case 28: // optional
					case 30: // idList_again
					case 32: // unary
					case 33: // unary_op
					case 52: // caseStmts_again

								liftUpNode(child);

							break;

					default: break;
				}

				// Applying magic on Expressions now: 

				// (This might trigger little plagirism) CHANGE LOGIC

				// prec2_op                prec1_op             logicalOp            relationalOp
				if(child->value == 45 || child->value == 46 || child->value == 47 || child->value == 48)
					liftUpNode(child);

				//                                          AND                             OR                   arithmeticOrBooleanExpr    arithmeticOrBooleanExpr_again  
				else if((child->child != NULL) && (child->child->value == 84 || child->child->value == 85) && (child->parent->value == 35 || child->parent->value == 36) && (child->right == NULL))
				{
					child->parent->value = child->child->value;
					child->parent->rule = child->child->rule;
					child->parent->n = child->child->n;
					child->child->n = NULL;
					removeNode(child->child);
					if(child->child->right == NULL)
						liftUpNode(child);
				}

				//                                         LT                               LE                             GT                         GE                           EQ                           NE                            anyTerm                     anyTerm_again
				else if((child->child != NULL) && (child->child->value == 86 || child->child->value == 87 || child->child->value == 88 || child->child->value == 89 || child->child->value == 90 || child->child->value == 91) && (child->parent->value == 37 || child->parent->value == 38) && (child->right == NULL))
				{
					child->parent->value = child->child->value;
					child->parent->rule = child->child->rule;
					child->parent->n = child->child->n;
					child->child->n = NULL;
					removeNode(child->child);
					if(child->child->right == NULL)
						liftUpNode(child);
				}

				//                                         MINUS                        PLUS                       arithmeticExpr               arithmeticExpr_again  
				else if((child->child != NULL) && (child->child->value == 79 || child->child->value == 81) && (child->parent->value == 39 || child->parent->value == 40) && (child->right == NULL))
				{
					child->parent->value = child->child->value;
					child->parent->rule = child->child->rule;
					child->parent->n = child->child->n;
					child->child->n = NULL;
					removeNode(child->child);
					if(child->child->right == NULL)
						liftUpNode(child);
				}

				//                                           MUL                        DIV                            term                         term_again
				else if((child->child != NULL) && (child->child->value == 92 || child->child->value == 93) && (child->parent->value == 41 || child->parent->value == 42) && (child->right == NULL))
				{
					child->parent->value = child->child->value;
					child->parent->rule = child->child->rule;
					child->parent->n = child->child->n;
					child->child->n = NULL;
					removeNode(child->child);
					if(child->child->right == NULL)
						liftUpNode(child);
				}

				// Eliminating the last arithmeticOrBooleanExpr recTerm arithmeticExpr term factor
				else if(child->value == 35 || child->value == 37 || child->value == 39 || child->value == 41 || child->value == 43)
					liftUpNode(child);

			}
			child = child->right;
		}
	}
}

void removeTerminals(ParseTree *head)
{
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
	
	// CASE WHEN THE CURRENT NODE IS THE ONLY CHILD OF ITS PARENT "OR" THE CURRENT NODE IS THE LEFTMOST CHILD OF ITS PARENT
	if(lefttemp == NULL)
	{
		if(righttemp == NULL)
		{
			parenttemp->child = childtemp;
			childtemp->parent = parenttemp;

			ParseTree *temp = childtemp;

			while(temp != NULL) // to change parent of lifted nodes
			{
				temp->parent = parenttemp;
				temp = temp->right;
			}
		}
		else
		{

			parenttemp->child = childtemp;
			childtemp->parent = parenttemp;

			righttemp->left = childtemp;

			if(childtemp != NULL)
				childtemp->right = righttemp;

			// Yahan parent same rahega for siblings
		}

		// free(current);
	}
	// CASE WHEN THE CURRENT NODE IS NOT THE LEFTMOST CHILD OF ITS PARENT
	else
	{
		// CASE WHEN THE CURRENT NODE->RIGHT = NULL
		if(righttemp == NULL)
		{

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

				while(temp!=NULL) // to change parent of lifted nodes
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
