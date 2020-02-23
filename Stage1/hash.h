/*	driver.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#ifndef HASH_H
#define HASH_H

#define MOD 1999

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parserDef.h"
#include "lexerDef.h"

int hash(char *str);
int search(char *str,char **Hashtable);
int insert(char *str,char **Hashtable);
void printTerms();
bool isnont(int hashVal);
/*int hashcallparser(char *tosearch, Term T,int sizeofT);
int hashcalllexer(char *tosearch, char **Keywords,int sizeofK);*/

struct term
{
	char termname[30];
	bool nont;
	int hashValue;
};

typedef struct term Term;

Term t[115];
extern int no_terms;
extern int no_terminals;
extern int no_nonterminals;

#endif