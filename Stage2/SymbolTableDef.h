/*  SymbolTableDef.h 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#ifndef ST_DEFH
#define ST_DEFH

#include "ast.h"

#define SIZE 20
#define HASHSIZE 20

struct FuncNode
{
	char name[30];
	char input[100];
	char output[100];
	struct FuncNode *next;
};

typedef struct FuncNode FNode;

struct FuncHashTable
{
	struct FuncNode *table[SIZE];
};

typedef struct FuncHashTable FuncHash;

struct TokenNode
{
	char name[30];
	char ifnumvalue[30];
	char scope[15];
	char type[15];
	int offset;
	int width;
	struct TokenNode *next;
};

typedef struct TokenNode TNode;

struct hash_of_hash_tables
{
	struct hash_table *functable[HASHSIZE];
};

typedef struct hash_of_hash_tables HashOfHash;

struct hash_table
{
	TNode *table[SIZE];
};

typedef struct hash_table TokenHash;

#endif