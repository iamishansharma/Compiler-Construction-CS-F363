/*	parserDef.h 

	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/ 

#ifndef PARSER_DEF_H
#define PARSER_DEF_H

#include "lexer.h"

struct parsetree
{				
	Node* n;
	int rule_no;
	struct parsetree *child;
	struct parsetree *parent;
	struct parsetree *left;
	struct parsetree *right;
	int isleaf;
	int visited;

};

typedef struct parsetree ParseTree;

struct fandf
{
	int first[112][15];
	int follow[112][15];
	// 53 non terminals hence 53 x 20;
};

typedef struct fandf FirstAndFollow;

struct grammar
{
	int gnum[101][30];
};

typedef struct grammar Grammar; 

struct parsetable
{
	int table[53][58];
}; 

typedef struct parsetable ParseTable;

static char *terms[111] = 
{
	"program",
	"moduleDeclarations",
	"moduleDeclaration",
	"otherModules",
	"driverModule",
	"module",
	"ret",
	"input_plist",
	"input_plist_again",
	"output_plist",
	"output_plist_again",
	"dataType",
	"type",
	"moduleDef",
	"statements",
	"statement",
	"ioStmt",
	"var",
	"whichId",
	"simpleStmt",
	"assignmentStmt",
	"whichStmt",
	"lvalueIDStmt",
	"lvalueARRStmt",
	"index",
	"moduleReuseStmt",
	"optional",
	"idList",
	"idList_again",
	"expression",
	"unary",
	"arithmeticOrBooleanExpr",
	"arithmeticOrBooleanExpr_again",
	"recTerm",
	"recTerm_again",
	"arithmeticExpr",
	"arithmeticExpr_again",
	"term",
	"term_again",
	"factor",
	"booleanConstants",
	"prec2_op",
	"prec1_op",
	"logicalOp",
	"relationalOp",
	"declareStmt",
	"conditionalStmt",
	"caseStmts",
	"caseStmts_again",
	"value",
	"default",
	"iterativeStmt",
	"range",
	"DECLARE",
	"DEF",
	"DRIVERDEF",
	"EPSILON",
	"RETURNS",
	"ID",
	"COMMA",
	"INTEGER",
	"REAL",
	"BOOLEAN",
	"ARRAY",
	"START",
	"GET_VALUE",
	"PRINT",
	"SWITCH",
	"FOR",
	"USE",
	"SQBO",
	"WHILE",
	"RNUM",
	"NUM",
	"ASSIGNOP",
	"MINUS",
	"BO",
	"PLUS",
	"TRUE",
	"FALSE",
	"AND",
	"OR",
	"LT",
	"LE",
	"GT",
	"GE",
	"EQ",
	"NE",
	"MUL",
	"DIV",
	"CASE",
	"$",
	"MODULE",
	"SEMICOL",
	"DRIVER",
	"PROGRAM",
	"DRIVERENDDEF",
	"ENDDEF",
	"TAKES",
	"INPUT",
	"SQBC",
	"COLON",
	"OF",
	"END",
	"BC",
	"WITH",
	"PARAMETERS",
	"BREAK",
	"DEFAULT",	
	"IN",
	"RANGEOP"
};

#endif