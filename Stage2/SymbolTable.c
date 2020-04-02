/*  SymbolTable.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "SymbolTable.h"

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