/*  SymbolTable.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "SymbolTable.h"

struct hash_table *create_table()
{
	struct hash_table *node = (struct hash_table *)malloc(sizeof(struct hash_table));
	return node;
}

struct tokNode *create_node(char* key, char* type, char* functionname, char* ifnumvalue)
{
	struct tokNode *node = (struct tokNode *)malloc(sizeof(struct tokNode));
	strcpy(node->tokname,key);
	strcpy(node->ifnumvalue,ifnumvalue);
	strcpy(node->scope,functionname);
	strcpy(node->type,type);
	node->offset = 0;
	node->width = 0;
	node->next = NULL;
	return node;
}

struct funcNode *create_func_node(char *lexeme, char *input_parameters, char *output_parameters)
{
   struct funcNode *node = (struct funcNode *)malloc(sizeof(struct funcNode));
   strcpy(node->fname,lexeme);
   strcpy(node->input,input_parameters);
   strcpy(node->output,output_parameters);
   return node;
}

int hash(char *key)
{
	int value = 0;
	int i;

	for (i = 0; i < strlen(key); i++)
		 value += (int)key[i];

	return (value % SIZE);
}