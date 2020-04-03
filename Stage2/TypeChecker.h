/*  TypeChecker.h
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#ifndef type_h
#define type_h

#include "ast.h"

// Primary Functions Declarations - 

int TypeChecker(FILE *fp, ParseTree *head, char *scope);

#endif