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
	char line[100];
	struct codeline *next;
};

typedef struct codeline CodeLine;

struct codeblock
{
	CodeLine *top;
	CodeLine *bot;
};

typedef struct codeblock CodeBlock;

// Functions - 

void getTemporary();
void getLabel();
CodeBlock *createCodeBlock();
void AddCodeLine(char *buffer, CodeBlock *cb);
void MergeCodeBlocks(CodeBlock *cb1, CodeBlock *cb2);
void codeGenIO(ParseTree *IO);
void CodeGenAssg(ParseTree *Ass);
void CodeGenSwitch(ParseTree *Swt);
void CodeGenExprRec(ParseTree *Expr);
void CodeGenExpr(ParseTree *Expr);
void CodeGenIter(ParseTree *Iter);
void CodeGenStmts(ParseTree *Stmt);
void CodeGenRec(ParseTree *head);
void AddTemporaries(SymbolTable *table, CodeBlock *cb);
void CallingCodeGen(ParseTree *head, SymbolTable *table, FILE *f);

#endif