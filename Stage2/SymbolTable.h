/*  SymbolTable.h 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#ifndef ST_H
#define ST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 20
#define HASHSIZE 20
#define A assert(0);

struct funcNode
{
   char fname[30];
   char input[100];
   char output[100];
   struct funcNode* next;
};

typedef struct funcNode fnode;
typedef struct funcNode *fnext;

struct func_hash_table
{
	fnode *table[SIZE];
};

struct tokNode
{
   char tokname[30];
   char ifnumvalue[10];
   char scope[15];
   char type[15];
   int offset;
   int width;
   struct tokNode *next;
};

typedef struct tokNode pNode;
typedef struct tokNode *pNext;

struct hash_of_hash_tables
{
	struct hash_table *functable[HASHSIZE];
};

struct hash_table
{
	pNode *table[SIZE];
};

// Functions definations for SymbolTable.c

struct hash_table *create_table();
struct tokNode *create_node(char* key, char* type, char* functionname, char* ifnumvalue);
struct funcNode *create_func_node(char *lexeme, char *input_parameters, char *output_parameters);
int hash(char *key);

#endif