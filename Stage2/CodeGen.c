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

int labelno = 1;
int tempno = 1;
int templocal = 1;

char tempbuf[10];
char labelbuf[10];

char cgbuffer[100];

void getTemporary()
{
	sprintf(tempbuf,"ri%d", tempno);
	tempno++;
}

void getLabel()
{
	sprintf(labelbuf,"L%d",labelno);
	labelno++;
}

CodeBlock *createCodeBlock()
{
	CodeBlock *cb = (CodeBlock *)malloc(sizeof(CodeBlock));
	cb->top = cb->bot = NULL;
	return cb;
}

void AddCodeLine(char *line, CodeBlock *cb)
{
	// Add line at the bottom of CodeBlock
	
	CodeLine *newLine;
	newLine = (CodeLine *)malloc(sizeof(CodeLine));
	newLine->next = NULL;
	strcpy(newLine->line,line);

	if(cb->bot == NULL && cb->top == NULL)
		cb->top = cb->bot = newLine;
	else
	{
		cb->bot->next = newLine;
		cb->bot = newLine;
	}
}

void MergeCodeBlocks(CodeBlock *cb1, CodeBlock *cb2)
{
	// Merge cb1 and cb2, put cb1 on top, cb2 on Bottom

	if(cb1->top != NULL && cb1->bot != NULL)
	{
		cb1->bot->next = cb2->top;
		cb2->top = cb1->top;
	}
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