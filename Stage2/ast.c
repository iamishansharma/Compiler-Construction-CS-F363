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

	switch (head->value)
	{
		// These are cases for which no action to be taken

		case 1:
		case 2:
		case 3:
		.
		.
		.		: removePuncs(head);

					break;

		// Cases for which nodes need to be lifted up.

		case :
		case : 
		case : liftUpNode(head); 

				break;

		// Cases for which modification are needed. 

		case :
		case :
		case : removeNode(head, head->child);

				break;

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

}

void removePuncs(ParseTree *head)
{
	// Case 1: Current Node is leftmost child of its parent.
	if (head->parent->child == head)
	{
		head->parent->child = head->right;

		if (head->right!=NULL) // if current node has sibling
			head->right->left = NULL;

		free(head);
	}
	// Case 2: If Current Node is not the leftmost child of its parent.
	else
	{

		head->left->right = head->right;

		if(head->right!=NULL)
				head->right->left = head->left;
		free(head);
	}
}

void liftUpNode(ParseTree *current)
{

}

void removeNode(ParseTree *head, ParseTree *child)
{
	
}