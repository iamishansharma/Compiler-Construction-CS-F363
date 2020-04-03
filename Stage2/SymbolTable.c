/*  SymbolTable.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "SymbolTable.h"

/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* Global Variables */

int offseter = 0;
int sequencenumber = 1;
int offset = 0;
HashOfHash *ht;
FuncHash *functable;
int count, funcnum = 0;
char funcarr[100][100]; // Stores all the function names

/* Global Variables END */
 
/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* GROUND LEVEL FUNCTIONS */

TokenHash* CreateTable()
{
	TokenHash *node = (TokenHash *)malloc(sizeof(TokenHash));

	return node;
}

TNode* CreateNode(char *inname, char *type, char *function, char *ifnumvalue)
{
	TNode *node = (TNode *)malloc(sizeof(TNode));

	strcpy(node->name,inname);
	strcpy(node->ifnumvalue,ifnumvalue);
	strcpy(node->type,type);
	strcpy(node->scope,function);

	node->offset = 0;
	node->width = 0;
	node->next = NULL;

	return node;
}

FNode *CreateFNode(char *functionname, char *input_parameters,char *output_parameters)
{
   FNode *node = (FNode *)malloc(sizeof(FNode));

   strcpy(node->name,functionname);
   strcpy(node->input,input_parameters);
   strcpy(node->output,output_parameters);

   return node;
}

int hash(char *key)
{
	int value = 0;
	int i;

	for(i=0; i<strlen(key); i++)
		 value += (int)key[i];

	return (value % SIZE);
}

/* GROUND LEVEL FUNCTIONS END*/

/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* FIRST LEVEL (FOR FUNCTIONS) Functions */

int HashInsertFunc(char *key, char* inputplist, char* outputplist)
{
	return 0;
}

int GetFuncHashValue(char* functionname)
{
	return 0;
}

void FuncDisplay()
{
	
}

void GetFuncInputType(char* functionname)
{
	
}

void GetFuncOutputType(char* functionname)
{
	
}

char *GetFunctionInputType(char* functionname)
{
	return NULL;
}

char *GetFunctionOutputType(char* functionname)
{
	return NULL;
}

int CheckFuncPresent(char* functionname)
{
	return 0;
}

FNode *DirectFunctionPointer(char* functionname)
{
	return NULL;
}

/* FIRST LEVEL (FOR FUNCTIONS) Functions END*/

/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* SECOND LEVEL (FOR TOKENS) Functions */
int HashInsert(char* key,char* type,char* functionname,char* ifnumvalue)
{
	return 0;
}
int CheckSymbolPresent(char* key,char* functionname)
{
	return 0;
}
int GetOffset(char* key,char* functionname)
{
	return 0;
}
char *GetType(char* key,char* functionname)
{
	return NULL;
}
void AutomateOffset(char* functionname)
{
	
}
TNode *GetDirectPointer(char* key,char* functionname)
{
	return NULL;
}
/* SECOND LEVEL (FOR TOKENS Functions END*/

/********************************************************************************************************************************/
/********************************************************************************************************************************/

/* MAIN Functions */ 

void populateSymbolTable(FILE *semantic, ParseTree *head, char *scope)
{
	if(head == NULL)
		return;

	populateSymbolTable(semantic, head->child, scope);

	if(head->value==4) // driverModule
	{
		HashInsertFunc("driver","-", "-");
		strcpy(scope,"driver");
	}

	// Current Ndoe is an ID
	if(head->value == 62)
	{
		// declareStmts ke IDs ki Entry
		if((strcmp("idList",terms[head->parent->value])==0) && (strcmp("declareStmt",terms[head->parent->parent->value])==0))
		{
			ParseTree *idtemp = head;

			while(idtemp != NULL)
			{
				if(CheckSymbolPresent(idtemp->n->t->value, scope))
				{
					fprintf(semantic,"Error 1: Redeclaration of variable %s in the same scope at line no: %d\n",idtemp->n->t->value,idtemp->n->t->lineno);
				}
				else
				{
					if(strcmp("INTEGER",terms[head->parent->right->child->value])==0)
					{
						HashInsert(head->n->t->value,"INTEGER",scope,"-");
					}
					else if(strcmp("REAL",terms[head->parent->right->child->value])==0)
					{
						HashInsert(head->n->t->value,"REAL",scope,"-");
					}
					else if(strcmp("BOOLEAN",terms[head->parent->right->child->value])==0)
					{
						HashInsert(head->n->t->value,"BOOLEAN",scope,"-");
					}
					else if(strcmp("ARRAY",terms[head->parent->right->child->value])==0)
					{
						int flagIndex1=0; // Zero is static
						int flagIndex2=0; // One if dynamic

						ParseTree *index1 = head->parent->right->child->child->child->child;
						ParseTree *index2 = head->parent->right->child->child->child->right->child;

						if(strcmp("ID",terms[index1->value])==0)
							flagIndex1=1;
						else
							flagIndex1=0;

						if(strcmp("ID",terms[index2->value])==0)
							flagIndex1=1;
						else
							flagIndex1=0;

						// if array is static
						if((flagIndex1 == 0) && (flagIndex2 == 0))
						{
							int i1 = atoi(index1->n->t->value);
							int i2 = atoi(index2->n->t->value);

							int arrayrange = i2 - i1 + 1;

							char arrayrangestring[10];

							sprintf(arrayrangestring,"%d",arrayrange);

							char type[30];

							ParseTree *arraytype = head->parent->right->child->right;

							if(strcmp("INTEGER",terms[arraytype->value])==0)
							{
								strcat(type, "ARRAY(INTEGER, ");
								strcat(type, arrayrangestring);
								strcat(type, ")");
								HashInsert(head->n->t->value,type,scope,"-");
							}
							else if(strcmp("REAL",terms[arraytype->value])==0)
							{
								strcat(type, "ARRAY(REAL, ");
								strcat(type, arrayrangestring);
								strcat(type, ")");
								HashInsert(head->n->t->value,type,scope,"-");
							}
							else if(strcmp("BOOLEAN",terms[arraytype->value])==0)
							{
								strcat(type, "ARRAY(BOOLEAN, ");
								strcat(type, arrayrangestring);
								strcat(type, ")");
								HashInsert(head->n->t->value,type,scope,"-");
							}
						}
						// if array is dynamic
						else
						{

						}
					}
				}
				idtemp = idtemp->right;
			}

		}

		// inputplist

		// outputplist

		// moduleReuseStmt

		// expression Type Checker 
	}
	populateSymbolTable(semantic, head->right, scope);
}
void displaySymbolTable()
{
	
}

/* MAIN Functions END */ 

/********************************************************************************************************************************/
/********************************************************************************************************************************/