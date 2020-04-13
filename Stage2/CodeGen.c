/*  

	CodeGen.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "CodeGen.h"

int LABEL = 1;
int TEMP_COUNT = 1;
int TEMP_LOCAL = 1;

char TEMP_BUF[5];
char LABEL_BUF[10];

char cgbuffer[100];c

void getTemporary()
{

}

void getLabel()
{

}

CodeBlock *createCodeBlock()
{
	return NULL;
}

void AddCodeLine(char *buffer, CodeBlock *cb)
{

}

void MergeCodeBlocks(CodeBlock *cb1, CodeBlock *cb2)
{

}

void PrintCodeBlock(CodeBlock *cb)
{

}

void PrintToFile(CodeBlock *cb, FILE *fp)
{

}

void codeGenIO(ParseTree *IO)
{

}

void CodeGenAssg(ParseTree *Ass)
{

}

void CodeGenSwitch(ParseTree *Swt)
{

}

void CodeGenExprRec(ParseTree *Expr)
{

}

void CodeGenExpr(ParseTree *Expr)
{

}

void CodeGenIter(ParseTree *Iter)
{

}

void CodeGenStmts(ParseTree *Stmt)
{

}

void CodeGenRec(ParseTree *head)
{

}

void AddTemporaries(SymbolTable *table, CodeBlock *cb)
{

}

void CallingCodeGen(ParseTree *head, SymbolTable *table, FILE *f)
{

}