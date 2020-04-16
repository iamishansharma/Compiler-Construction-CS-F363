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

int daflag = 0;

void getTemporary()
{
	sprintf(tempbuf,"ri%d", tempno);
	tempno++;
}

void getLabel()
{
	sprintf(labelbuf,"label%d",labelno);
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
		//printf("\nBot Line: %s\n",cb->bot->line);
		cb->bot->next = newLine;
		//printf("\nNew Bot Line: %s\n", cb->bot->next->line);
		cb->bot = newLine;
	}
}

void MergeCodeBlocks(CodeBlock *cb1, CodeBlock *cb2)
{
	// Merge cb1 and cb2, put cb1 on top, cb2 on Bottom

	if(cb1->top == NULL)
	{
		if(cb2->top == NULL)
		{}
		else
		{
			cb1->top = cb2->top;
			cb1->bot = cb2->bot;
		}
	}
	else
	{
		if(cb2->top == NULL)
		{}
		else
		{
			cb1->bot->next = cb2->top;
			cb1->bot = cb2->bot;
		}
	}
}

void AssignTemporaries(SymbolTable *table, CodeBlock *cb)
{
	if(table == NULL)
		return;

	SymbolEntry *temp = table->nodehead;

	while(temp != NULL)
	{
		getTemporary();

		strcpy(temp->temporary,tempbuf);

		if(temp->isArray)
		{
			if(temp->startindex->isDynamic == 0 && temp->endindex->isDynamic == 0)
			{
				int range = temp->endindex->ifnumvalue - temp->startindex->ifnumvalue + 1;
				sprintf(cgbuffer,"\t%s: resd %d",temp->temporary,range);
			}
			else
				daflag = 1;
		}
		else
			sprintf(cgbuffer,"\t%s: resd %d",temp->temporary,1);

		AddCodeLine(cgbuffer,cb);
		temp = temp->next;
	}

	AssignTemporaries(table->child, cb);
	AssignTemporaries(table->right, cb);
}

void codeGenIO(ParseTree *IO, CodeBlock *main)
{

}

void CodeGenAssg(ParseTree *Ass, CodeBlock *main)
{

}

void CodeGenSwitch(ParseTree *Swt, CodeBlock *main)
{

}

void CodeGenExprRec(ParseTree *Expr, CodeBlock *main)
{

}

void CodeGenExpr(ParseTree *Expr, CodeBlock *main)
{

}

void CodeGenIter(ParseTree *Iter, CodeBlock *main)
{

}

void CodeGenStmts(ParseTree *Stmt, CodeBlock *main)
{

}

void CodeGenRec(ParseTree *head, CodeBlock *main)
{
	if(head == NULL)
		return;

	if(strcmp(terms[head->value],"conditionalStmt") == 0)
	{

	}
	else if(strcmp(terms[head->value],"ioStmt") == 0)
	{

	}
	else if(strcmp(terms[head->value],"iterativeStmt") == 0)
	{

	}
	else if(strcmp(terms[head->value],"assignmentStmt") == 0)
	{

	}

	CodeGenRec(head->child, main);
	CodeGenRec(head->right, main);
}

void PrintToFile(CodeBlock *cb, FILE *f)
{
	CodeLine *temp = cb->top;

	while(temp != NULL)
	{
		fprintf(f,"%s\n",temp->line);
		temp = temp->next;
	}
}

void CallingCodeGen(ParseTree *head, SymbolTable *table, FILE *f)
{
	if(strcmp(terms[head->child->value], "driverModule") == 0 && head->child->right == NULL)
	{
		CodeBlock *main, *bss;

		main = createCodeBlock();
		bss = createCodeBlock();

		AddCodeLine("section .bss\n", bss);

		AssignTemporaries(table->child, bss);

		if(daflag == 1)
		{
			printf("\n%sCode Gen (Error):%s Such Source Code hasn't been implemented in our project. Please use testcases only with static arrays and driver module.\n\n",BOLDRED,RESET);
			return;
		}

		AddCodeLine("\nextern printf, scanf\n", main);
		AddCodeLine("global mainseg \n", main);

		MergeCodeBlocks(main,bss);

		AddCodeLine("\nsection .data\n", main);
		AddCodeLine("\tin_format:    db \"%d\", 0", main);
		AddCodeLine("\tout_format:   db \"%d\", 10, 0\n", main);

		AddCodeLine("section .text", main);
		AddCodeLine("\nmainseg:", main);

		//CodeGenRec(head->child->child,main);

		// Exiting Code -> 

		AddCodeLine("\n\t;exit code\n", main);
		AddCodeLine("\tmov eax, 1", main);
		AddCodeLine("\tmov ebx, 0", main);
		AddCodeLine("\tint 80h", main);

		PrintToFile(main,f);

		printf("\n%sPlease use the following instructions to assemble, link and execute the \"code.asm file\" - %s\n", BOLDCYAN, RESET);
		printf("\n\tnasm -f elf64 -o code.o code.asm\n");
		printf("\tld code.o -o code\n");
		printf("\t./code\n\n");
	}
	else
	{
		printf("\n%sCode Gen (Error):%s Such Source Code hasn't been implemented in our project. Please use testcases with driver module only with static arrays.\n\n",BOLDRED,RESET);
	}
}