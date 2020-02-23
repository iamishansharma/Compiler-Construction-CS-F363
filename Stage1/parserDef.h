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
	int first[101][15];
	int follow[101][15];
	// 53 non terminals hence 53 x 20;
};

typedef struct fandf FirstAndFollow;

struct grammar
{
	int gnum[100][30];
};

typedef struct grammar Grammar; 

struct parsetable
{
	int table[53][57];
}; 

typedef struct parsetable ParseTable;

static char *terms[112] = 
{
	"program",
	"moduleDeclarations",
	"otherModules",
	"driverModule",
	"moduleDeclaration",
	"module",
	"moduleDef",
	"input_plist",
	"ret",
	"output_plist",
	"dataType",
	"input_plist_again",
	"type",
	"output_plist_again",
	"range",
	"statements",
	"statement",
	"ioStmt",
	"simpleStmt",
	"declareStmt",
	"conditionalStmt",
	"iterativeStmt",
	"var",
	"booleanConstants",
	"whichId",
	"assignmentStmt",
	"moduleReuseStmt",
	"whichStmt",
	"lvalueIDStmt",
	"lvalueARRStmt",
	"expression",
	"index",
	"optional",
	"idList",
	"idList_again",
	"arithmeticOrBooleanExpr",
	"unary",
	"arithmeticExpr",
	"recTerm",
	"arithmeticOrBooleanExpr_again",
	"logicalOp",
	"recTerm_again",
	"relationalOp",
	"term",
	"arithmeticExpr_again",
	"prec2_op",
	"factor",
	"term_again",
	"prec1_op",
	"caseStmts",
	"default",
	"value",
	"caseStmts_again",
	"$",
	"EPSILON",
	"DECLARE",
	"MODULE",
	"ID",
	"SEMICOL",
	"DRIVERDEF",
	"DRIVER",
	"PROGRAM",
	"DRIVERENDDEF",
	"DEF",
	"ENDDEF",
	"TAKES",
	"INPUT",
	"SQBO",
	"SQBC",
	"RETURNS",
	"COLON",
	"COMMA",
	"INTEGER",
	"REAL",
	"BOOLEAN",
	"ARRAY",
	"OF",
	"START",
	"END",
	"GET_VALUE",
	"BO",
	"BC",
	"PRINT",
	"ASSIGNOP",
	"NUM",
	"USE",
	"WITH",
	"PARAMETERS",
	"MINUS",
	"PLUS",
	"RNUM",
	"TRUE",
	"FALSE",
	"MUL",
	"DIV",
	"AND",
	"OR",
	"LT",
	"LE",
	"GT",
	"GE",
	"EQ",
	"NE",
	"CASE",
	"BREAK",
	"DEFAULT",
	"FOR",
	"IN",
	"WHILE",
	"RANGEOP",
	"SWITCH"
};

#endif