/*  

	CodeGen.h
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#ifndef CODEGEN_H
#define CODEGEN_H

#include "SymbolTableDef.h"
#include "ast.h"

struct codeline
{
	char line[400];
	struct codeline *next;
};

typedef struct codeline CodeLine;

struct codeblock
{
	CodeLine *upar;
	CodeLine *niche;
};

typedef struct codeblock CodeBlock;

// Functions - 

void getTemp();
void getL();
CodeBlock *cCB();
void ACLine(char *buffer, CodeBlock *cb);
void MCB(CodeBlock *cb1, CodeBlock *cb2);
void codeGenIO(ParseTree *IO, CodeBlock *main);
void CodeGenAssg(ParseTree *Ass, CodeBlock *main);
void CodeGenSwitch(ParseTree *Swt, CodeBlock *main);
void CodeGenSwitchRec(ParseTree *head, CodeBlock *main);
void CodeGenExprRec(ParseTree *Expr, CodeBlock *main);
void CodeGenExpr(ParseTree *Expr, CodeBlock *main);
void CodeGenIter(ParseTree *Iter, CodeBlock *main);
void CodeGenRec(ParseTree *head, CodeBlock *main);
void AddTemporaries(SymbolTable *table, CodeBlock *cb);
void PTF(CodeBlock *cb, FILE *f);
void CallingCodeGen(ParseTree *head, SymbolTable *table, FILE *f);

#endif