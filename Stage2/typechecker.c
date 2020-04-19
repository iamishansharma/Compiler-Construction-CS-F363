/*  

	TypeChecker.c
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

	Type Checking and Semantics Analyser Rules ->

	IO SEMANTICS -> 

	DONE	1. Get_Value ID should be declared previously. 

	DONE	2. Print mei ID shoudl be declared, array out of bounds bhi check karo. 

	IDENTIFIER SEMANTICS ->
	
	DONE	1. An identifier cannot be declared multiple times in the same scope. 

	DONE	2. An identifier must be declared before its use. 				

	DONE	3. An identifier used beyond its scope must be viewed as undefined. 	

	FUNCTIONS SEMANTICS -> 

	DONE	1. The types and the number of parameters returned by a function must 
			be the same as that of the parameters used in invoking the function.

	DONE	2. The parameters being returned by a function must be assigned a value. 
			If a parameter does not get a value assigned within the function definition, 
			it should be reported as an error.

	DONE	3. The function that does not return any value, must be invoked appropriately.

	DONE	4. Function input parameters passed while invoking it should be of the 
				same type as those used in the function definition.

	DONE	5. Function overloading is not allowed.

	DONE	6. A function declaration for a function being used (say F1) by another 
				(say F2) must precede the definition of the function using it(i.e. F2), 
				only if the function definition of F1 does not precede the definition of F2.

				moduleReuseStmt mei jo ID hai, uski entry check karenge ->

				if usage 6 hua toh theek.

				else usage 6 nahi hai, 

						usage == 5: toh function define hi nahi kiya 
						usage == 2: toh is function ka line no, moduleReuseStmt se kam hona chahiye


	DONE		7. If the function definition of F1 precedes function definition of 
				F2(the one which uses F1), then the function declaration of F1 is 
				redundant and is not valid.

	DONE	8. The function cannot be invoked recursively.

	DONE 	9. All Output Parameters were assigned inside function. 

	SWITCH SEMANTICS ->

	DONE	1. A switch statement with an integer typed identifier associated with it, 
			can have case statement with case keyword followed by an integer only 
			and the case statements must be followed by a default statement. 

	DONE	2. A switch statement with an identifier of type real is not valid and an error 
			should be reported.

	DONE	3. A switch statement with a boolean type identifier can have the case statements 
			with labels true and false only. The switch statement then should not have a 
			default statement.

			default ke line no galat hai.

	ITERATIVE SEMANTICS ->
	
	DONE	1. 'FOR' statement must not redefine the variable that participates in the 
				iterating over the range and iterating variable should be integer type.

	DONE	2. WHILE expression must be of boolean type

	DONE	3. WHILE expr any of the IDs in expression must be assigned a value.

	EXPRESSION SEMANTICS -> 

	DONE	1. is integer, if both expressions are of type integer and the operator is arithmetic operator.

	DONE	2. is real, if both the expressions are of type real and the operator is arithmetic operator.

	DONE	3. is boolean, if both expressions are of type integer and the operator is a relational operator.

	DONE	4. is boolean, if both expressions are of type real and the operator is relational.

	DONE	5. is boolean, if both expressions are of type boolean and the operator is logical.

	ARRAY SEMANTICS ->

	FOR STATICS ARRAYS:

	see if it can be done in TypeChecker.c 

	DONE	1. A[3] whenever used should be in bounds on the indices.

	DONE	2. The operations +, -, *, / and all relational and 
			logic operators cannot be applied on array variables.

	DONE	3. The assignment operator applied to two array variables of 
			the same type is valid. For example, if A and B are the 
			array variables of type array[12..20] of real, then A:= B; 
			is a valid statement. This applies to dynamic arrays of 
			type array[a..b] of real as well.

	DONE	4. Consider array elements with index represented by integer identifier say A[k]. 
			Here type checking of variable k is done at compile time. 

	DYNAMIC REMAINING		If the type of k is integer, then it is valid else it is reported as an error. 

				Also, the type checking of A[13], for type of index (NUM), is done at compile time.

			5. Dynamic array type checking

*/

#include "TypeChecker.h"
#include "ast.h"
#include "SymbolTable.h"

int asscidwhile = 0; // used to count assigned no of id's in while expression
int flagudvexp = 0;
int flagass = 0;
int defaultbool = 0;
int defaultint = 0;

/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* Auxilary Functions */

void isIDEntryNULLExp(ParseTree *root, int *errors)
{
	if(strcmp(terms[root->value],"var_id_num") == 0)
	{
		if(root->child->entry->udv == 1)
		{
			//printf("%s\tLine No: %d %s(Error)%s The identifier '%s' should be declared before its use.\n", BOLDWHITE, root->child->n->t->lineno,BOLDRED, RESET, root->child->n->t->value);
			*errors = *errors + 1;
			flagudvexp = 1;
		}
	}

	else if(strcmp(terms[root->value], "AND") == 0 || strcmp(terms[root->value], "OR") == 0)
	{
		isIDEntryNULLExp(root->child, errors);
		isIDEntryNULLExp(root->child->right, errors);
	}
	else if(strcmp(terms[root->value], "LE") == 0 || strcmp(terms[root->value], "LT") == 0 || strcmp(terms[root->value], "GE") == 0 || strcmp(terms[root->value], "GT") == 0 || strcmp(terms[root->value], "NE") == 0 || strcmp(terms[root->value], "EQ") == 0)
	{
		isIDEntryNULLExp(root->child, errors);
		isIDEntryNULLExp(root->child->right, errors);
	}
	else if(strcmp(terms[root->value], "PLUS") == 0 || strcmp(terms[root->value], "MINUS") == 0 || strcmp(terms[root->value], "MUL") == 0 || strcmp(terms[root->value], "DIV") == 0)
	{
		isIDEntryNULLExp(root->child, errors);
		isIDEntryNULLExp(root->child->right, errors);
	}
}

void CheckExpRec(ParseTree *root, int *errors, int *udvflag)
{
	//printf("\nExpr: %s | Value: %s\n", terms[root->value], root->n->t->value);

	if(root->child != NULL && strcmp(terms[root->child->value],"ID") == 0) // IF ID or not
	{
		if(root->child->entry->udv == 1)
		{
			/* printf("%s\tLine No: %d %s(Error)%s The identifier '%s' should be declared before its use.\n", BOLDWHITE, root->child->n->t->lineno,BOLDRED, RESET, root->child->n->t->value);
			*errors = *errors + 1; */
			goto arraycheckskip;
		}

		if(root->child->right != NULL) // if ID has index? 
		{
			ParseTree *index = root->child->right->child;

			//printf("\nID: %s\n",terms[index->value]);

			if(index->entry->udv == 1)
			{
				//printf("%s\tLine No: %d %s(Error)%s The identifier '%s' should be declared before its use.\n", BOLDWHITE, index->n->t->lineno,BOLDRED, RESET, index->n->t->value);
				*errors = *errors + 1;
				goto indexskip;
			}

			if(root->child->entry->isArray == 0)
			{
				printf("\t%sLine No: %d%s (Error) %sNon Array Variable '%s' cannot have index.\n", BOLDWHITE, root->child->n->t->lineno, BOLDRED,RESET, root->child->n->t->value);
				*errors = *errors + 1;
				goto indexskip;
			}

			if(strcmp(index->entry->type,"INTEGER") != 0) // IF Array Index is integer or not
			{
				printf("\t%sLine No: %d%s (Error) %sArray '%s' cannot have non-integer type of index '%s'.\n", BOLDWHITE, root->child->n->t->lineno, BOLDRED,RESET,root->child->n->t->value, index->n->t->value);
				*errors = *errors + 1;
			}
			else
			{
				if(root->child->entry->startindex->isDynamic == 0 && root->child->entry->endindex->isDynamic == 0)
				{
					if(strcmp(terms[index->value],"NUM") == 0)
					{
						if((atoi(index->n->t->value) <= root->child->entry->endindex->ifnumvalue) && (atoi(index->n->t->value) >= root->child->entry->startindex->ifnumvalue))
						{}
						else
						{
							printf("\t%sLine No: %d%s (Error) %sArray '%s' index '%s' is out of bounds.\n", BOLDWHITE, root->child->n->t->lineno, BOLDRED,RESET,root->child->n->t->value, index->n->t->value);
							*errors = *errors + 1;
						}
					}
					else
					{
						//Dynamic index but static array
					}
				}
				else
				{
					// Dynamic Array, index may / may not be static
				}				
			}

			indexskip: ;
		}
		else
		{
			if(root->child->entry->isArray == 1 && (strcmp(terms[root->parent->value],"expression") != 0))
			{
				printf("\t%sLine No: %d%s (Error) %sComplete Array '%s' cannot be used in any arithematic/relational/logical expression.\n", BOLDWHITE, root->child->n->t->lineno, BOLDRED,RESET, root->child->n->t->value);
				*errors = *errors + 1;
			}
		}

		arraycheckskip: ;
	}

	if(strcmp(terms[root->value],"FALSE") == 0 || strcmp(terms[root->value],"TRUE") == 0)
	{
		strcpy(root->type, root->entry->type);
	}

	if(strcmp(terms[root->value],"var_id_num") == 0)
	{
		if(root->child->entry->udv == 1)
		{
			//printf("%s\tLine No: %d %s(Error)%s The identifier '%s' should be declared before its use.\n", BOLDWHITE, root->child->n->t->lineno,BOLDRED, RESET, root->child->n->t->value);
			*errors = *errors + 1;
			strcpy(root->type, "UDV");
			flagass = 1;
		}
		else
			strcpy(root->type, root->child->entry->type);
	}

	else if(strcmp(terms[root->value], "AND") == 0 || strcmp(terms[root->value], "OR") == 0)
	{
		CheckExpRec(root->child, errors, udvflag);
		CheckExpRec(root->child->right, errors, udvflag);

		if((strcmp(root->child->type,"ERROR") == 0) || (strcmp(root->child->right->type,"ERROR") == 0))
		{
			strcpy(root->type, "ERROR");
			goto skiplop;
		}

		if((strcmp(root->child->type,"BOOLEAN") == 0) && (strcmp(root->child->right->type,"BOOLEAN") == 0))
			strcpy(root->type, "BOOLEAN");
		else 
		{
			if((strcmp(root->child->type,"UDV") == 0) || (strcmp(root->child->right->type,"UDV") == 0))
			{
				printf("\t%sLine No: %d%s (Error) %sLeft Term and Right Term type mismatch in expression for '%s' (Due to undeclared variable).\n", BOLDWHITE, root->child->n->t->lineno, BOLDRED, RESET, root->n->t->value);
				*errors = *errors + 1;
				strcpy(root->type, "ERROR");
			}
			else
			{	
				printf("\t%sLine No: %d%s (Error) %sLeft Term and Right Term type mismatch in expression for '%s'.\n", BOLDWHITE, root->child->n->t->lineno, BOLDRED, RESET, root->n->t->value);
				*errors = *errors + 1;
				strcpy(root->type, "ERROR");
			}
		}

		skiplop: ;
	}
	else if(strcmp(terms[root->value], "LE") == 0 || strcmp(terms[root->value], "LT") == 0 || strcmp(terms[root->value], "GE") == 0 || strcmp(terms[root->value], "GT") == 0 || strcmp(terms[root->value], "NE") == 0 || strcmp(terms[root->value], "EQ") == 0)
	{
		CheckExpRec(root->child, errors, udvflag);
		CheckExpRec(root->child->right, errors, udvflag);
		
		if((strcmp(root->child->type,"ERROR") == 0) || (strcmp(root->child->right->type,"ERROR") == 0))
		{
			strcpy(root->type, "ERROR");
			goto rop;
		}

		if((strcmp(root->child->type,"INTEGER") == 0) && (strcmp(root->child->right->type,"INTEGER") == 0))
			strcpy(root->type, "BOOLEAN");
		else if((strcmp(root->child->type,"REAL") == 0) && (strcmp(root->child->right->type,"REAL") == 0))
			strcpy(root->type, "BOOLEAN");
		else
		{
			if((strcmp(root->child->type,"UDV") == 0) || (strcmp(root->child->right->type,"UDV") == 0))
			{
				printf("\t%sLine No: %d%s (Error) %sLeft Term and Right Term type mismatch in expression for '%s' (Due to undeclared variable).\n", BOLDWHITE, root->child->n->t->lineno, BOLDRED, RESET, root->n->t->value);
				*errors = *errors + 1;
				strcpy(root->type, "ERROR");
			}
			else
			{	
				printf("\t%sLine No: %d%s (Error) %sLeft Term and Right Term type mismatch in expression for '%s'.\n", BOLDWHITE, root->child->n->t->lineno, BOLDRED, RESET, root->n->t->value);
				*errors = *errors + 1;
				strcpy(root->type, "ERROR");
			}
		}

		rop: ;
	}
	else if(strcmp(terms[root->value], "PLUS") == 0 || strcmp(terms[root->value], "MINUS") == 0 || strcmp(terms[root->value], "MUL") == 0 || strcmp(terms[root->value], "DIV") == 0)
	{
		CheckExpRec(root->child, errors, udvflag);
		CheckExpRec(root->child->right, errors, udvflag);

		if((strcmp(root->child->type,"ERROR") == 0) || (strcmp(root->child->right->type,"ERROR") == 0))
		{
			strcpy(root->type, "ERROR");
			goto skiparop;
		}

		if((strcmp(root->child->type,"INTEGER") == 0) && (strcmp(root->child->right->type,"INTEGER") == 0))
			strcpy(root->type, "INTEGER");
		else if((strcmp(root->child->type,"REAL") == 0) && (strcmp(root->child->right->type,"REAL") == 0))
			strcpy(root->type, "REAL");
		else
		{
			if((strcmp(root->child->type,"UDV") == 0) || (strcmp(root->child->right->type,"UDV") == 0))
			{
				printf("\t%sLine No: %d%s (Error) %sLeft Term and Right Term type mismatch in expression for '%s' (Due to undeclared variable).\n", BOLDWHITE, root->child->n->t->lineno, BOLDRED, RESET, root->n->t->value);
				*errors = *errors + 1;
				strcpy(root->type, "ERROR");
			}
			else
			{	
				printf("\t%sLine No: %d%s (Error) %sLeft Term and Right Term type mismatch in expression for '%s'.\n", BOLDWHITE, root->child->n->t->lineno, BOLDRED, RESET, root->n->t->value);
				*errors = *errors + 1;
				strcpy(root->type, "ERROR");
			}
		}

		skiparop: ;
	}
}

void CheckSwitch(ParseTree *swt, int *errors, int *udvflag)
{
	ParseTree *switchID = swt->child->right;

	if(switchID->entry->udv == 1)
	{
		//printf("%s\tLine No: %d %s(Error)%s The identifier '%s' should be declared before its use.\n", BOLDWHITE, switchID->n->t->lineno,BOLDRED, RESET, switchID->n->t->value);
		*errors = *errors + 1;
		goto swtskip;
	}

	if(strcmp(switchID->entry->type,"INTEGER") == 0)
	{
		ParseTree *temp = switchID;

		int found = 0;
		defaultint = 0;

		while(temp != NULL)
		{
			if(strcmp(terms[temp->value],"default") == 0)
			{
				found = 1;
				break;
			}
			//defaultint = temp->n->t->lineno;
			//printf("\nTerms: %s\n", terms[temp->value]);
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
					printf("\t%sLine No: %d%s (Error) %s'switch' with integer identifier cannot have non-integer '%s' case value.\n", BOLDWHITE, temp2->child->n->t->lineno,BOLDRED, RESET, temp2->child->n->t->value);
					*errors = *errors +1;
				}
			}
			temp2 = temp2->right;
		}

		if(!found)
		{
			printf("\t%sLine No: %d%s (Error) %s'default' case statement missing for 'switch' with integer identifier.\n", BOLDWHITE, switchID->n->t->lineno,BOLDRED, RESET);
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
					printf("\t%sLine No: %d%s (Error) %s'switch' with boolean identifier cannot have non-boolean '%s' case value.\n", BOLDWHITE, temp2->child->n->t->lineno, BOLDRED, RESET, temp2->child->n->t->value);
					*errors = *errors +1;
				}
			}
			temp2 = temp2->right;
		}

		ParseTree *temp = switchID;

		int found = 0;
		defaultbool = 0;

		while(temp != NULL)
		{
			if(strcmp(terms[temp->value],"default") == 0)
			{
				printf("\t%sLine No: %d%s (Error) %s'switch' with 'boolean' identifier cannot have 'default' case.\n", BOLDWHITE, temp->n->t->lineno,BOLDRED, RESET);
				*errors = *errors +1;
			}
			temp = temp->right;
		}
	}
	else
	{
		printf("\t%sLine No: %d%s (Error) %sThe switch statement identifier %s cannot be of type 'real'.\n", BOLDWHITE, switchID->n->t->lineno,BOLDRED, RESET, switchID->n->t->value);
		*errors = *errors +1;
	}

	swtskip:
			return;
}

void CheckIterStmt(ParseTree *Iter, int *errors, int *udvflag)
{
	if(strcmp(terms[Iter->child->value],"FOR") == 0)
	{
		ParseTree *iterID = Iter->child->right;

		if(iterID->entry->udv == 1)
		{
			//printf("%s\tLine No: %d %s(Error)%s The identifier '%s' should be declared before its use.\n", BOLDWHITE, iterID->n->t->lineno,BOLDRED, RESET, iterID->n->t->value);
			*errors = *errors + 1;
			goto forskip;
		}

		if(strcmp(iterID->entry->type,"INTEGER") != 0)
		{
			printf("\t%sLine No: %d%s (Error) %sIn 'for' construct the iterating variable '%s' cannot be non-integer.\n", BOLDWHITE, iterID->n->t->lineno, BOLDRED, RESET, iterID->n->t->value);
			*errors = *errors +1;
		}

		int lowval = atoi(Iter->child->right->right->child->n->t->value);
		int highval = atoi(Iter->child->right->right->child->right->n->t->value);

		if(highval < lowval)
		{
			printf("\t%sLine No: %d%s (Error) %sIn 'for' construct the end value '%d' cannot be smaller than start value '%d' \n", BOLDWHITE, iterID->n->t->lineno, BOLDRED, RESET, highval, lowval);
			*errors = *errors +1;
		}

		ParseTree *forexp = Iter->child->right->right->right;

		CheckFORID(iterID, forexp, errors, udvflag);

		forskip:
				return;
	}
	else if(strcmp(terms[Iter->child->value],"WHILE") == 0)
	{
		ParseTree *whileexp = Iter->child->right;

		isIDEntryNULLExp(whileexp, errors);

		if(flagudvexp)
			goto whileskip;

		CheckExpRec(whileexp, errors, udvflag);

		if(strcmp(whileexp->type,"BOOLEAN") != 0)
		{
			printf("\t%sLine No: %d%s (Error) %s'while' control expression cannot be of non-boolean type.\n", BOLDWHITE,Iter->child->n->t->lineno,BOLDRED, RESET);
			*errors = *errors +1;
		}

		CheckWhileID(Iter->child->scope->name, Iter->child, errors, udvflag);

		asscidwhile = 0;

		CheckWhileAssExpRec(whileexp, errors, udvflag);

		if(asscidwhile == 0)
		{
			printf("\t%sLine No: %d%s (Error) %s In 'while' control expression atleast one ID should be assigned a value inside while scope.\n", BOLDWHITE, whileexp->child->n->t->lineno,BOLDRED, RESET);
			*errors = *errors +1;
		}

		whileskip:
				return;
	}
}

void CheckFORID(ParseTree *iterID, ParseTree *func, int *errors, int *udvflag)
{
	if(func == NULL)
		return;

	if((strcmp(terms[func->value],"ID")==0) && (strcmp(terms[func->parent->value],"assignmentStmt")==0) && (strcmp(func->n->t->value,iterID->n->t->value)==0))
	{
		//printf("\nCame here for Ass: %s | Line No: %d\n", func->n->t->value, func->n->t->lineno);
		//func->entry->isAss = 1;
		printf("\t%sLine No: %d%s (Error) %s'for' control variable '%s' cannot be assigned a value inside the for loop.\n", BOLDWHITE, func->n->t->lineno,BOLDRED, RESET, iterID->n->t->value);
		*errors = *errors +1;
	}
	
	else if((strcmp(terms[func->value],"ID")==0) && (strcmp(terms[func->parent->value],"ioStmt")==0) && (strcmp(func->n->t->value,iterID->n->t->value)==0))
	{
		//printf("\nCame here for GV: %s | Line No: %d\n", func->n->t->value, func->n->t->lineno);
		/*if(strcmp(terms[func->left->value],"GET_VALUE")==0)
			func->entry->isAss = 1;*/
		printf("\t%sLine No: %d%s (Error) %s'for' control variable '%s' cannot be assigned a value inside the for loop.\n", BOLDWHITE, func->n->t->lineno,BOLDRED, RESET, iterID->n->t->value);
		*errors = *errors +1;
	}
	else if((strcmp(terms[func->value],"ID")==0) && (strcmp(func->n->t->value,iterID->n->t->value)==0) && (strcmp(terms[func->parent->value],"idList")==0) && (strcmp(terms[func->parent->parent->value],"optional")==0))
	{
		//printf("\nCame here for RP: %s | Line No: %d\n", func->n->t->value, func->n->t->lineno);
		//func->entry->isAss = 1;
		printf("\t%sLine No: %d%s (Error) %s'for' control variable '%s' cannot be assigned a value inside the for loop.\n", BOLDWHITE, func->n->t->lineno,BOLDRED, RESET, iterID->n->t->value);
		*errors = *errors +1;
	}

	CheckFORID(iterID, func->child, errors, udvflag);
	CheckFORID(iterID, func->right, errors, udvflag);
}

void CheckWhileAssExpRec(ParseTree *root, int *errors, int *udvflag)
{
	if(root->child != NULL && strcmp(terms[root->child->value],"ID") == 0) // IF ID or not
	{
		if(root->child->entry->isAss == 1)
		{
			asscidwhile++;
		}
	}

	if(strcmp(terms[root->value],"var_id_num") == 0)
	{
		
	}

	else if(strcmp(terms[root->value], "AND") == 0 || strcmp(terms[root->value], "OR") == 0)
	{
		CheckWhileAssExpRec(root->child, errors, udvflag);
		CheckWhileAssExpRec(root->child->right, errors, udvflag);
	}
	else if(strcmp(terms[root->value], "LE") == 0 || strcmp(terms[root->value], "LT") == 0 || strcmp(terms[root->value], "GE") == 0 || strcmp(terms[root->value], "GT") == 0 || strcmp(terms[root->value], "NE") == 0 || strcmp(terms[root->value], "EQ") == 0)
	{
		CheckWhileAssExpRec(root->child, errors, udvflag);
		CheckWhileAssExpRec(root->child->right, errors, udvflag);
	}
	else if(strcmp(terms[root->value], "PLUS") == 0 || strcmp(terms[root->value], "MINUS") == 0 || strcmp(terms[root->value], "MUL") == 0 || strcmp(terms[root->value], "DIV") == 0)
	{
		CheckWhileAssExpRec(root->child, errors, udvflag);
		CheckWhileAssExpRec(root->child->right, errors, udvflag);
	}
}

void CheckWhileID(char *id, ParseTree *func, int *errors, int *udvflag)
{
	if(func == NULL)
		return;

	//printf("\nFunc: %s | Parent: %s | Lineno: %d | Scope: %s | FuncValue: %s\n", terms[func->value], terms[func->parent->value], func->n->t->lineno, func->scope->name, func->n->t->value);

	if((strcmp(terms[func->value],"ID")==0) && (strcmp(terms[func->parent->value],"assignmentStmt")==0))
	{
		//printf("\nCame here for Ass: %s | Line No: %d\n", func->n->t->value, func->n->t->lineno);
		func->entry->isAss = 1;
	}
	
	else if((strcmp(terms[func->value],"ID")==0) && (strcmp(terms[func->parent->value],"ioStmt")==0))
	{
		//printf("\nCame here for GV: %s | Line No: %d\n", func->n->t->value, func->n->t->lineno);
		if(strcmp(terms[func->left->value],"GET_VALUE")==0)
			func->entry->isAss = 1;
	}
	else if((strcmp(terms[func->value],"ID")==0) && (strcmp(terms[func->parent->value],"idList")==0) && (strcmp(terms[func->parent->parent->value],"optional")==0))
	{
		//printf("\nCame here for RP: %s | Line No: %d\n", func->n->t->value, func->n->t->lineno);
		func->entry->isAss = 1;
	}

	CheckWhileID(id, func->child, errors, udvflag);
	CheckWhileID(id, func->right, errors, udvflag);
}

void CheckAssignStmt(ParseTree *Ass, int *errors, int *udvflag)
{
	ParseTree *lhs = Ass->child;

	//printf("\nLHS: %s | LineNo: %d\n",lhs->n->t->value, lhs->n->t->lineno);

	ParseTree *IDARR = lhs->right;

	if(strcmp(terms[IDARR->value],"lvalueIDStmt") == 0)
	{
		if(lhs->entry->udv == 1)
		{
			//printf("%s\tLine No: %d %s(Error)%s The identifier '%s' should be declared before its use.\n", BOLDWHITE, lhs->n->t->lineno,BOLDRED, RESET, lhs->n->t->value);
			*errors = *errors + 1;
		}

		if(lhs->entry->isArray)
		{
			ParseTree *rhsID = IDARR->child->child->child;

			if(strcmp(terms[rhsID->value],"ID") == 0)
			{
				if(rhsID->entry->udv == 1)
					goto skipthis;

				if(rhsID->entry->isArray == 0)
				{
					printf("\t%sLine No: %d%s (Error) %sComplete Array '%s' cannot be assigned to non-array identifer '%s'.\n", BOLDWHITE, lhs->n->t->lineno, BOLDRED, RESET, lhs->n->t->value, rhsID->n->t->value);
					*errors = *errors +1;
				}
				else
				{
					// No need to calculate expr type as only single ID is present.

					if(strcmp(rhsID->entry->type, lhs->entry->type) == 0)
					{
						if(rhsID->entry->startindex->isDynamic == 0 && rhsID->entry->startindex->isDynamic == 0 && lhs->entry->endindex->isDynamic == 0 && lhs->entry->endindex->isDynamic == 0)
						{
							// Both static arrays
							if((rhsID->entry->startindex->ifnumvalue == lhs->entry->startindex->ifnumvalue) && (rhsID->entry->endindex->ifnumvalue == lhs->entry->endindex->ifnumvalue))
							{
								// Do nothing.
							}
							else
							{
								printf("\t%sLine No: %d%s (Error) %sLHS Array '%s' start/end indices does not match the start/end indices of RHS Array '%s'.\n", BOLDWHITE, lhs->n->t->lineno, BOLDRED, RESET, lhs->n->t->value, rhsID->n->t->value);
								*errors = *errors +1;
							}
						}
						else
						{
							// Something is dynamic, might / might not be error;
						}
					}
					else
					{
						printf("\t%sLine No: %d%s (Error) %sType of LHS Array '%s' does not match the type of RHS Array '%s'.\n", BOLDWHITE,lhs->n->t->lineno,BOLDRED, RESET, lhs->n->t->value, rhsID->n->t->value);
						*errors = *errors +1;
					}
				}
				skipthis: ;
			}
			else
			{
				printf("\t%sLine No: %d%s (Error) %sComplete Array '%s' cannot be assigned to an arithematic/relational/logical expression.\n", BOLDWHITE, lhs->n->t->lineno, BOLDRED, RESET, lhs->n->t->value);
				*errors = *errors +1;
			}
		}

		ParseTree *rhsexpr = Ass->child->right->child;

		if(strcmp(terms[rhsexpr->child->value],"unary") == 0)
		{
			ParseTree *ue = rhsexpr->child->child->right->child; // new_NT

			flagass = 0;

			CheckExpRec(ue, errors, udvflag);

			if(strcmp(lhs->entry->type, ue->type) != 0 && (lhs->entry->udv != 1) && (flagass == 0))
			{
				printf("\t%sLine No: %d%s (Error) %sAssignment Statement LHS type does not match with RHS type.\n", BOLDWHITE, lhs->n->t->lineno, BOLDRED, RESET);
				*errors = *errors +1;
			}
		}
		else
		{
			//printf("\nComes here for LHS: %s | RHS: %s | Lineno: %d\n" , lhs->n->t->value, terms[rhsexpr->child->value], lhs->n->t->lineno);

			flagass = 0;

			CheckExpRec(rhsexpr->child, errors, udvflag);

			if(strcmp(lhs->entry->type, rhsexpr->child->type) != 0 && (lhs->entry->udv != 1) && (flagass == 0))
			{
				printf("\t%sLine No: %d%s (Error) %sAssignment Statement LHS type does not match with RHS type.\n", BOLDWHITE, lhs->n->t->lineno, BOLDRED, RESET);
				*errors = *errors +1;
			}
		}
	}
	else
	{
		if(lhs->entry->udv == 1)
		{
			//printf("%s\tLine No: %d %s(Error)%s The identifier '%s' should be declared before its use.\n", BOLDWHITE, lhs->n->t->lineno,BOLDRED, RESET, lhs->n->t->value);
			*errors = *errors + 1;
			goto RHSCHECK2;
		}

		if(lhs->entry->isArray)
		{
			ParseTree *lhsindex = IDARR->child->child;

			if(strcmp(lhsindex->entry->type,"INTEGER") != 0 && lhsindex->entry->udv == 0) // IF Array Index is integer or not
			{
				printf("\t%sLine No: %d%s (Error) %sArray '%s' cannot have non-integer type of index '%s'.\n", BOLDWHITE, lhs->n->t->lineno,BOLDRED,RESET,lhs->n->t->value, lhsindex->n->t->value);
				*errors = *errors + 1;
			}
			else
			{
				if(lhs->entry->startindex->isDynamic == 0 && lhs->entry->endindex->isDynamic == 0)
				{
					if(strcmp(terms[lhsindex->value],"NUM") == 0)
					{
						if((atoi(lhsindex->n->t->value) <= lhs->entry->endindex->ifnumvalue) && (atoi(lhsindex->n->t->value) >= lhs->entry->startindex->ifnumvalue))
						{}
						else
						{
							printf("\t%sLine No: %d%s (Error) %sArray '%s' index '%s' is out of bounds.\n", BOLDWHITE, lhs->n->t->lineno,BOLDRED,RESET,lhs->n->t->value, lhsindex->n->t->value);
							*errors = *errors + 1;
						}
					}
					else
					{
						//Dynamic index but static array
					}
				}
				else
				{
					// Dynamic Array, index may / may not be static
				}				
			}
		}
		else
		{
			printf("\t%sLine No: %d%s (Error) %sNon Array Variable '%s' cannot have index.\n", BOLDWHITE, lhs->n->t->lineno, BOLDRED,RESET, lhs->n->t->value);
			*errors = *errors + 1;
		}

		ParseTree *rhsexpr = Ass->child->right->child->right;

		RHSCHECK2: // Now expression checking -> 

			if(strcmp(terms[rhsexpr->child->value],"unary") == 0)
			{
				ParseTree *ue = rhsexpr->child->child->right->child; // new_NT

				flagass = 0;

				CheckExpRec(ue, errors, udvflag);

				if(strcmp(lhs->entry->type, ue->type) != 0 && (flagass == 0))
				{
					printf("\t%sLine No: %d%s (Error) %sAssignment Statement LHS type does not match with RHS type.\n", BOLDWHITE, lhs->n->t->lineno, BOLDRED, RESET);
					*errors = *errors +1;
				}
			}
			else
			{
				//printf("\nComes here for LHS: %s | RHS: %s | Lineno: %d\n" , lhs->n->t->value, terms[rhsexpr->child->value], lhs->n->t->lineno);

				flagass = 0;

				CheckExpRec(rhsexpr->child, errors, udvflag);

				if(strcmp(lhs->entry->type, rhsexpr->child->type) != 0 && (flagass == 0))
				{
					printf("\t%sLine No: %d%s (Error) %sAssignment Statement LHS type does not match with RHS type.\n", BOLDWHITE, lhs->n->t->lineno, BOLDRED, RESET);
					*errors = *errors +1;
				}
			}
	}
}

void CheckIPL(SymbolTable *table, ParseTree *IPL, int *errors, int *udvflag)
{
	ParseTree *travPT = IPL->child;

	SymbolTable *inplist = table->child;

	SymbolEntry *travST = inplist->nodehead;

	while(travST != NULL)
	{
		if(travPT->entry->udv == 1)
		{
			//Error reporting here
			//printf("%s\tLine No: %d %s(Error)%s The identifier '%s' should be declared before its use.\n", BOLDWHITE, travPT->n->t->lineno,BOLDRED, RESET, travPT->n->t->value);
			*errors = *errors + 1;
			goto skip;
		}
		else
		{
			if((strcmp(travST->type, travPT->type) != 0) || (travST->isArray != travPT->entry->isArray))
			{
				printf("\t%sLine No: %d%s (Error) %sType of actual parameter '%s' does not match with formal parameter '%s' during function '%s' call.\n", BOLDWHITE, IPL->n->t->lineno, BOLDRED, RESET, travPT->n->t->value, travST->name, table->name);
				*errors = *errors + 1;
				goto skip1;
			}

			if(travST->isArray == travPT->entry->isArray && (travST->isArray == 1))
			{
				if(travST->startindex->isDynamic == 0 && travST->endindex->isDynamic == 0 && travPT->entry->startindex->isDynamic == 0 && travPT->entry->endindex->isDynamic == 0)
				{
					if((travST->startindex->ifnumvalue == travPT->entry->startindex->ifnumvalue) && (travST->endindex->ifnumvalue == travPT->entry->endindex->ifnumvalue))
					{}
					else
					{
						printf("\t%sLine No: %d%s (Error) %sType of actual parameter '%s' does not match with formal parameter '%s' during function '%s' call.\n", BOLDWHITE, IPL->n->t->lineno, BOLDRED, RESET, travPT->n->t->value, travST->name, table->name);
						*errors = *errors + 1;
					}
				}
			}

			skip1:;
		}

		skip:

			travPT = travPT->right;
			travST = travST->next;

			if((travPT == NULL && travST != NULL) || (travPT != NULL && travST == NULL))
			{
				printf("\t%sLine No: %d%s (Error) %sNumber of Input Parameters mismatch during function '%s' call.\n", BOLDWHITE, IPL->n->t->lineno, BOLDRED, RESET, table->name);
				*errors = *errors + 1;
				break;
			}
	}
}

void CheckOPL(SymbolTable *table, ParseTree *OPL, int *errors, int *udvflag)
{
	ParseTree *travPT = OPL->child;

	SymbolEntry *travST = table->nodehead;

	SymbolEntry *countOPL = table->nodehead;

	while(travST != NULL)
	{
		if(travST->usage == 4) // Output P List only
		{
			//printf("\nRET: %s | Op: %s\n", travST->name, travPT->n->t->value);
			if(travPT == NULL)
			{
				printf("\t%sLine No: %d%s (Error) %sNumber of Output Parameters mismatch during function '%s' call.\n", BOLDWHITE, OPL->n->t->lineno, BOLDRED, RESET, table->name);
				*errors = *errors + 1;
				break;
			}

			if(strcmp(travST->type, travPT->type) != 0)
			{
				printf("\t%sLine No: %d%s (Error) %sType of receiving parameter '%s' does not match with output parameter '%s' during function '%s' call.\n", BOLDWHITE, OPL->n->t->lineno, BOLDRED, RESET, travPT->n->t->value, travST->name, table->name);
				*errors = *errors + 1;
			}
			travPT = travPT->right;
		}
		travST = travST->next;

		if(travPT != NULL && travPT->entry->udv == 1)
		{
			//printf("%s\tLine No: %d %s(Error)%s The identifier '%s' should be declared before its use.\n", BOLDWHITE, travPT->n->t->lineno,BOLDRED, RESET, travPT->n->t->value);
			*errors = *errors + 1;

			travPT = travPT->right;
			travST = travST->next;
		}
	}

	if(travPT != NULL)
	{
		printf("\t%sLine No: %d%s (Error) %sNumber of Output Parameters mismatch during function '%s' call.\n", BOLDWHITE, OPL->n->t->lineno, BOLDRED, RESET, table->name);
		*errors = *errors + 1;
	}
}

SymbolTable *FindModule(char *id, SymbolTable *tables, int *udvflag)
{
	SymbolTable *temp = tables->child;

	while(temp != NULL)
	{
		if((strcmp(temp->name,id)==0))
		{
			return temp;
		}
		temp = temp->right;
	}
	return NULL;
}

void CheckFunctioninST(ParseTree *Func, int *errors, int *udvflag)
{
	ParseTree *op = Func->child;

	if(strcmp(terms[op->value],"optional") == 0)
	{
		ParseTree *MRSID = Func->child->right;

		if(MRSID->entry == NULL)
		{
			printf("%s\tLine No: %d %s(Error)%s The module '%s' should be declared or defined before its use.\n", BOLDWHITE, MRSID->n->t->lineno,BOLDRED, RESET, MRSID->n->t->value);
			*errors = *errors + 1;
			return;
		}
		
		// Recursion Check
		SymbolTable *tempsc = Func->scope;

		while(strcmp(tempsc->parent->name,"global") != 0)
			tempsc = tempsc->parent;
		
		if(strcmp(tempsc->name,MRSID->n->t->value)==0)
		{
			printf("\t%sLine No: %d%s (Error) %sRecursive call to function '%s' is not allowed inside function '%s'.\n", BOLDWHITE, MRSID->n->t->lineno,BOLDRED, RESET, MRSID->n->t->value, tempsc->name);
			*errors = *errors +1;
		}

		SymbolTable *func = FindModule(MRSID->n->t->value, MRSID->entry->scope, udvflag);

		CheckIPL(func, MRSID->right, errors, udvflag);

		int flagforOPL = 0;

		SymbolEntry *travST = func->nodehead;

		while(travST != NULL)
		{
			if(travST->usage == 4)
			{
				flagforOPL = 1;
				break; // ek bhi trigger hua toh break karo
			}
			travST = travST->next;
		}

		if(flagforOPL == 0)
		{
			printf("\t%sLine No: %d%s (Error) %sFor function '%s' call recieving parameters are specified but function has no returning parameters.\n", BOLDWHITE, MRSID->n->t->lineno, BOLDRED, RESET, func->name);
			*errors = *errors + 1;
		}
		else
			CheckOPL(func, op->child, errors, udvflag);

		if(MRSID->entry->mrsreq == -1 && MRSID->entry->usage == 6 && (MRSID->entry->deflno < MRSID->n->t->lineno))
		{
			printf("\t%sLine No: %d%s (Error) %sDeclaration of function '%s' is redundant hence not required.\n", BOLDWHITE, MRSID->entry->lineno, BOLDRED, RESET, MRSID->entry->name);
			*errors = *errors + 1;
		}

		if(MRSID->entry->usage == 2 && (MRSID->entry->deflno > MRSID->n->t->lineno))
		{
			printf("\t%sLine No: %d%s (Error) %sFunction '%s' should be declared at start, as it is being called before its defination.\n", BOLDWHITE, MRSID->n->t->lineno, BOLDRED, RESET, MRSID->entry->name);
			*errors = *errors + 1;
		}
	}
	else
	{
		ParseTree *MRSID = Func->child;

		if(MRSID->entry == NULL)
		{
			printf("%s\tLine No: %d %s(Error)%s The module '%s' should be declared or defined before its use.\n", BOLDWHITE, MRSID->n->t->lineno,BOLDRED, RESET, MRSID->n->t->value);
			*errors = *errors + 1;
			return;
		}

		// Recursion Check
		SymbolTable *tempsc = Func->scope;
		while(strcmp(tempsc->parent->name,"global") != 0)
			tempsc = tempsc->parent;
		if(strcmp(tempsc->name,MRSID->n->t->value)==0)
		{
			printf("\t%sLine No: %d%s (Error) %sRecursive call to function '%s' is not allowed inside function '%s'.\n", BOLDWHITE, MRSID->n->t->lineno, BOLDRED, RESET, MRSID->n->t->value, tempsc->name);
			*errors = *errors +1;
		}

		SymbolTable *func = FindModule(MRSID->n->t->value, MRSID->entry->scope, udvflag);

		CheckIPL(func, MRSID->right, errors, udvflag);

		SymbolEntry *travST = func->nodehead;

		while(travST != NULL)
		{
			if(travST->usage == 4)
			{
				printf("\t%sLine No: %d%s (Error) %sNo recieving parameters specified during function '%s' call.\n", BOLDWHITE, MRSID->n->t->lineno, BOLDRED, RESET, func->name);
				*errors = *errors + 1;
				break; // ek bhi trigger hua toh break karo
			}
			travST = travST->next;
		}

		if(MRSID->entry->mrsreq == -1 && MRSID->entry->usage == 6 && (MRSID->entry->deflno < MRSID->n->t->lineno))
		{
			printf("\t%sLine No: %d%s (Error) %sDeclaration of function '%s' is redundant hence not required.\n", BOLDWHITE, MRSID->entry->lineno, BOLDRED, RESET, MRSID->entry->name);
			*errors = *errors + 1;
		}

		if(MRSID->entry->usage == 2 && (MRSID->entry->deflno > MRSID->n->t->lineno))
		{
			printf("\t%sLine No: %d%s (Error) %sFunction '%s' is should be declared, as it is being called before its defination.\n", BOLDWHITE, MRSID->n->t->lineno, BOLDRED, RESET, MRSID->entry->name);
			*errors = *errors + 1;
		}
	}
}

void CheckOPLifAssigned(ParseTree *func, int *errors, int *udvflag)
{
	CheckOPLifAssignedRec(func->child->n->t->value, func, errors, udvflag);

	ParseTree *ret = func->child->right->right;

	if((strcmp(terms[ret->value],"ret")==0))
	{
		ParseTree *OPL = ret->child->child;

		while((OPL != NULL))
		{
			if((strcmp(terms[OPL->value],"ID") == 0))
			{
				if(OPL->entry->isAss == 0)
				{
					printf("\t%sLine No: %d%s (Error) %sOutput Parameter '%s' was not assigned anywhere inside function '%s'.\n", BOLDWHITE, OPL->n->t->lineno, BOLDRED, RESET, OPL->n->t->value, func->child->n->t->value);
					*errors = *errors + 1;
				}
			}
			OPL = OPL->right;
		}
	}
}

void CheckOPLifAssignedRec(char *id, ParseTree *func, int *errors, int *udvflag)
{
	if(func == NULL)
		return;

	if((strcmp(terms[func->value],"ID")==0) && func->entry->udv == 1)
	{
		/*printf("%s\tLine No: %d %s(Error)%s The identifier '%s' should be declared before its use.\n", BOLDWHITE, func->n->t->lineno,BOLDRED, RESET, func->n->t->value);
		*errors = *errors + 1;*/
		goto OPLskip;
	}

	if((strcmp(terms[func->value],"ID")==0) && (strcmp(terms[func->parent->value],"assignmentStmt")==0))
	{
		func->entry->isAss = 1;
	}
	
	else if((strcmp(terms[func->value],"ID")==0) && (strcmp(terms[func->parent->value],"ioStmt")==0))
	{
		if(strcmp(terms[func->left->value],"GET_VALUE")==0)
			func->entry->isAss = 1;
	}
	else if((strcmp(terms[func->value],"ID")==0) && (strcmp(terms[func->parent->value],"idList")==0) && (strcmp(terms[func->parent->parent->value],"optional")==0))
	{
		func->entry->isAss = 1;
	}

	OPLskip: ;

	CheckOPLifAssignedRec(id, func->child, errors, udvflag);
	CheckOPLifAssignedRec(id, func->right, errors, udvflag);
}

void AssignType(ParseTree *head, int *udvflag)
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
		strcpy(head->type, "INTEGER");
	}
	else if(strcmp(terms[head->value],"RNUM") == 0)
	{
		SymbolEntry *newEntry = (SymbolEntry *)malloc(sizeof(SymbolEntry));
		strcpy(newEntry->name,head->n->t->value);
		strcpy(newEntry->type,"REAL");
		newEntry->offset = -1;
		newEntry->width = -1;
		head->entry = newEntry;
		strcpy(head->type, "REAL");
	}
	else if(strcmp(terms[head->value],"TRUE") == 0)
	{
		SymbolEntry *newEntry = (SymbolEntry *)malloc(sizeof(SymbolEntry));
		strcpy(newEntry->name,head->n->t->value);
		strcpy(newEntry->type,"BOOLEAN");
		newEntry->offset = -1;
		newEntry->width = -1;
		head->entry = newEntry;
		strcpy(head->type, "BOOLEAN");
	}
	else if(strcmp(terms[head->value],"FALSE") == 0)
	{
		SymbolEntry *newEntry = (SymbolEntry *)malloc(sizeof(SymbolEntry));
		strcpy(newEntry->name,head->n->t->value);
		strcpy(newEntry->type,"BOOLEAN");
		newEntry->offset = -1;
		newEntry->width = -1;
		head->entry = newEntry;
		strcpy(head->type, "BOOLEAN");
	}

	AssignType(head->child, udvflag);
	AssignType(head->right, udvflag);
}

void CheckFuncDef(SymbolTable *table)
{
	SymbolEntry *templist = table->nodehead;

	while(templist != NULL)
	{
		if(templist->usage == 5)
		{
			printf("\t%sLine No: %d%s (Warning) %sFunction '%s' was declared but never defined and called in the program.\n", BOLDWHITE, templist->lineno, BOLDCYAN, RESET, templist->name);
		}
		templist = templist->next;
	}
}
void CheckIOStmt(ParseTree *IO, int *errors, int *udvflag)
{
	// get value 
	if(strcmp(terms[IO->child->value],"GET_VALUE") == 0)
	{
		// kuch karna hi nahi hai because variable undeclared pehli hi ho gaya hoga
	}
	else
	{
		if((strcmp(terms[IO->child->right->value],"FALSE")==0) || (strcmp(terms[IO->child->right->value],"TRUE")==0))
			goto skipIOFT;

		ParseTree *ID = IO->child->right->child;
		ParseTree *index = ID->right;

		if(ID->entry->udv == 1)
		{
			goto skipprint;
		}
		else
		{
			if(index == NULL)
			{
				// kuch karna hi nahi hai because variable undeclared pehli hi ho gaya hoga
			}
			else
			{
				if(ID->entry->isArray)
				{
					if(strcmp(terms[index->child->value],"ID") == 0)
					{
						//printf("\nID wale: %s LNO: %d\n", ID->n->t->value, ID->n->t->lineno);
						if(index->child->entry->udv == 1)
						{
							return;
						}
						else
						{
							if(strcmp(index->child->entry->type, "INTEGER") != 0)
							{
								printf("\t%sLine No: %d%s (Error) %sArray '%s' cannot have non-integer type of index '%s'.\n", BOLDWHITE, ID->n->t->lineno, BOLDRED,RESET, ID->n->t->value, index->child->n->t->value);
								*errors = *errors + 1;
							}
							else
							{
								// Dynamic Bound Checking
							}
						}
					}
					else
					{
						//printf("\nNON ID wale: %s LNO: %d\n", ID->n->t->value, ID->n->t->lineno);

						if(strcmp(index->child->entry->type,"INTEGER") != 0)
						{
							// Yahan aayegi hi nahi because parser se hi RNUM accepted nahi hai.
							printf("\t%sLine No: %d%s (Error) %sArray '%s' cannot have non-integer type of index '%s'.\n", BOLDWHITE, ID->n->t->lineno, BOLDRED,RESET, ID->n->t->value, index->child->n->t->value);
							*errors = *errors + 1;
						}
						else
						{
							// Static Bound Check for num;

							// Check for Static Array -> 

							int indexval = atoi(index->child->n->t->value);

							if(ID->entry->startindex->isDynamic == 0 && ID->entry->endindex->isDynamic == 0)
							{
								if(indexval >= ID->entry->startindex->ifnumvalue && indexval <= ID->entry->endindex->ifnumvalue)
								{}
								else
								{
									printf("\t%sLine No: %d%s (Error) %sArray '%s' index '%s' is out of bounds.\n", BOLDWHITE, ID->n->t->lineno, BOLDRED,RESET, ID->n->t->value, index->child->n->t->value);
									*errors = *errors + 1;
								}
							}
						}
					}
				}
				else
				{
					printf("\t%sLine No: %d%s (Error) %sNon Array Variable '%s' cannot index.\n", BOLDWHITE, ID->n->t->lineno, BOLDRED,RESET, ID->n->t->value);
					*errors = *errors + 1;
				}
			}
		}
		skipprint: ;

		skipIOFT: ;
	}
}
void CheckArrayDynamicType(ParseTree *head, int *errors, int *udvflag)
{
	if(head == NULL)
		return;

	if(head->parent != NULL)
	{
		if(strcmp(terms[head->parent->value],"index") == 0)
		{
			if(head->parent->parent != NULL)
			{
				if(strcmp(terms[head->parent->parent->value],"range_arrays") == 0)
				{
					if(strcmp(terms[head->value],"ID") == 0 )
					{
						if(head->entry->udv == 1)
						{

						}
						else
						{
							if(strcmp(head->entry->type,"INTEGER") != 0)
							{
								printf("\t%sLine No: %d%s (Error) %sArray/s cannot have non-integer type of index '%s' at declaration.\n", BOLDWHITE, head->n->t->lineno, BOLDRED,RESET, head->n->t->value);
								*errors = *errors + 1;
							}
						}
					}
				}
			}
		}
	}

	CheckArrayDynamicType(head->child, errors, udvflag);
	CheckArrayDynamicType(head->right, errors, udvflag);
}

void CheckStaticArrayDecIndex(ParseTree *head, int *errors)
{
	if(head == NULL)
		return;

	if(strcmp(terms[head->value],"ID") == 0)
	{
		if(head->entry->isArray)
		{
			if(strcmp(terms[head->parent->value],"input_plist") == 0)
			{	
				//printf("\nHenlo 1 Lno: %d\n" , head->n->t->lineno);
				if(head->entry->startindex->isDynamic == 0 && head->entry->startindex->isDynamic == 0)
				{
					if(head->entry->startindex->ifnumvalue > head->entry->endindex->ifnumvalue)
					{
						printf("\t%sLine No: %d%s (Error) %sArray '%s' cannot have higher index '%d' less than lower index '%d'.\n", BOLDWHITE, head->n->t->lineno, BOLDRED,RESET, head->n->t->value, head->entry->endindex->ifnumvalue, head->entry->startindex->ifnumvalue);
						*errors = *errors + 1;
					}
				}
			}
			else if(strcmp(terms[head->parent->value],"idList") == 0 && strcmp(terms[head->parent->parent->value],"declareStmt") == 0)
			{
				//printf("\nHenlo 2 Lno: %d\n", head->n->t->lineno);
				if(head->entry->startindex->isDynamic == 0 && head->entry->startindex->isDynamic == 0)
				{
					if(head->entry->startindex->ifnumvalue > head->entry->endindex->ifnumvalue)
					{
						printf("\t%sLine No: %d%s (Error) %sArray '%s' cannot have higher index '%d' less than lower index '%d'.\n", BOLDWHITE, head->n->t->lineno, BOLDRED,RESET, head->n->t->value, head->entry->endindex->ifnumvalue, head->entry->startindex->ifnumvalue);
						*errors = *errors + 1;
					}
				}
			}
		}
	}

	CheckStaticArrayDecIndex(head->child, errors);
	CheckStaticArrayDecIndex(head->right, errors);
}

/* Auxilary Functions END */

/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* MAIN Functions */

void CallingTypeChecker(ParseTree *head, SymbolTable *table, int *errors, int *udvflag)
{
	AssignType(head, udvflag);
	TypeChecker(head, table, errors, udvflag);
	CheckArrayDynamicType(head, errors, udvflag);
	CheckFuncDef(table);
	CheckStaticArrayDecIndex(head, errors);
}

void TypeChecker(ParseTree *head, SymbolTable *table, int *errors, int *udvflag)
{
	if(head == NULL)
		return;

	if(strcmp(terms[head->value],"expression") == 0) // Expression Checker
	{
		//CheckExpCall(head, errors); // Is this really required ? Na bitsh.
	}
	else if(strcmp(terms[head->value],"conditionalStmt") == 0) // SWITCH 
	{
		CheckSwitch(head, errors, udvflag); // DONE
	}
	else if(strcmp(terms[head->value],"moduleReuseStmt") == 0) // Function Call
	{
		CheckFunctioninST(head, errors, udvflag);
	}
	else if(strcmp(terms[head->value],"ioStmt") == 0) // IOStmt
	{
		CheckIOStmt(head, errors, udvflag);
	}
	else if(strcmp(terms[head->value],"iterativeStmt") == 0) // FOR and WHILE
	{
		CheckIterStmt(head, errors, udvflag);
	}
	else if(strcmp(terms[head->value],"assignmentStmt") == 0) // ASSIGN
	{
		CheckAssignStmt(head, errors, udvflag);
		//printf("\nEnding Assignment\n");
	}
	else if(strcmp(terms[head->value],"module") == 0 && head->child->right->right != NULL)
	{
		CheckOPLifAssigned(head, errors, udvflag);
	}

	TypeChecker(head->child, table, errors, udvflag);
	TypeChecker(head->right, table, errors, udvflag);
}

/* MAIN Functions END */

/********************************************************************************************************************************/
/********************************************************************************************************************************/
