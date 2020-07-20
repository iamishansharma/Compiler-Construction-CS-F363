/*	

	lexerDef.h 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

/* START COLOR DEFINE */

#ifndef RESET
#define RESET   "\033[0m"
#endif

#ifndef BOLDBLACK
#define BOLDBLACK   "\033[0m\033[30m"      /* Bold Black */
#endif

#ifndef BOLDRED
#define BOLDRED     "\033[0m\033[31m"      /* Bold Red */
#endif

#ifndef BOLDGREEN
#define BOLDGREEN   "\033[0m\033[32m"      /* Bold Green */
#endif

#ifndef BOLDYELLOW
#define BOLDYELLOW  "\033[0m\033[33m"      /* Bold Yellow */
#endif

#ifndef BOLDBLUE
#define BOLDBLUE    "\033[0m\033[34m"      /* Bold Blue */
#endif

#ifndef BOLDMAGENTA
#define BOLDMAGENTA "\033[0m\033[35m"      /* Bold Magenta */
#endif

#ifndef BOLDCYAN
#define BOLDCYAN    "\033[0;36m"      /* Bold Cyan */
#endif

#ifndef BOLDWHITE
#define BOLDWHITE   "\033[0m\033[37m"      /* Bold White */
#endif

/* END COLOR DEFINE */

#ifndef LEXER_DEF_H
#define LEXER_DEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern int state;
extern int line;
extern int begin;
extern int fwd;
extern int fwd2;
extern int keyno;
extern int tokno;

struct token
{
	char token[40];
	char value[40]; // create union 
	int lineno;
};

typedef struct token Token;

struct node
{
	Token *t;
};

typedef struct node Node;

struct head
{
	Node *hd;
};

typedef struct head Head;

#endif