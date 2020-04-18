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
int tempfloatno = 0;

char tempbuf[10];
char labelbuf[10];

char cgbuffer[100];

int daflag = 0;

CodeBlock *bss;

void getTemporary()
{
	sprintf(tempbuf,"ri%d", tempno);
	tempno++;
}

void getTemporaryFloat()
{
	sprintf(tempbuf,"xmm%d", tempfloatno);
	tempfloatno++;
}

void getLabel()
{
	sprintf(labelbuf,"l%d",labelno);
	labelno++;
}

CodeBlock *createCodeBlock()
{
	CodeBlock *cb = (CodeBlock *)malloc(sizeof(CodeBlock));
	cb->top = NULL;
	cb->bot = NULL;
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
		if(strcmp(temp->type,"REAL") == 0)
		{
			getTemporary();
		}
		else
			getTemporary();
		

		strcpy(temp->temporary,tempbuf);

		if(temp->isArray)
		{
			if(temp->startindex->isDynamic == 0 && temp->endindex->isDynamic == 0)
			{
				int range = temp->endindex->ifnumvalue - temp->startindex->ifnumvalue + 1;
				sprintf(cgbuffer,"\t%s: \tresd %d ; ID: %s | Line No:%d",temp->temporary,range,temp->name,temp->lineno);
			}
			else
				daflag = 1;
		}
		else
			sprintf(cgbuffer,"\t%s: \tresd %d ; ID: %s | Line No: %d",temp->temporary,1,temp->name,temp->lineno);

		AddCodeLine(cgbuffer,cb);
		temp = temp->next;
	}

	AssignTemporaries(table->child, cb);
	AssignTemporaries(table->right, cb);
}

void codeGenIO(ParseTree *IO, CodeBlock *main)
{
	if(strcmp(terms[IO->child->value],"GET_VALUE") == 0)
	{
		ParseTree *id = IO->child->right;

		char getvbuf[100];
		sprintf(getvbuf,"\t\t; Getting A Value In ID: %s",id->n->t->value);
		AddCodeLine(getvbuf,main);

		if(id->entry->isArray)
		{
			int start = id->entry->startindex->ifnumvalue;
			int end = id->entry->endindex->ifnumvalue;
			int tot = end - start + 1;

			// Handle Arrays
		}
		else
		{
			if(strcmp(id->entry->type,"INTEGER") == 0)
			{
				AddCodeLine("\t\tpush rbp",main);
				AddCodeLine("\t\tmov rdi, in_format_int ; printing integer format",main); 

				AddCodeLine("\t\tmov rax, 0",main);
				AddCodeLine("\t\tcall printf",main);
				AddCodeLine("\t\tpop rbp",main);

				AddCodeLine("\t\tpush rbp",main);
				AddCodeLine("\t\tmov rdi, in_format",main);
				AddCodeLine("\t\tmov rax, 0",main);

				sprintf(cgbuffer,"\t\tmov rsi, %s",id->entry->temporary);
				AddCodeLine(cgbuffer,main);
				AddCodeLine("\t\tcall scanf",main);
				AddCodeLine("\t\tpop rbp\n",main);
			}
			else if(strcmp(id->entry->type,"REAL") == 0)
			{
				// Not working because float registers nahi hai.
				AddCodeLine("\t\tpush rbp",main);
				AddCodeLine("\t\tmov rdi, in_format_real ; printing real format",main);
				AddCodeLine("\t\tmov rax, 0",main);
				AddCodeLine("\t\tcall printf",main);
				AddCodeLine("\t\tpop rbp",main);

				AddCodeLine("\t\tpush rbp",main);
				AddCodeLine("\t\tmov rdi, in_format",main);
				AddCodeLine("\t\tmov rax, 0",main);

				sprintf(cgbuffer,"\t\tmov rsi, %s",id->entry->temporary);
				AddCodeLine(cgbuffer,main);
				AddCodeLine("\t\tcall scanf",main);
				AddCodeLine("\t\tpop rbp\n",main);
			}
			else if(strcmp(id->entry->type,"BOOLEAN") == 0)
			{
				AddCodeLine("\t\tpush rbp",main);
				AddCodeLine("\t\tmov rdi, in_format_boolean ; printing boolean format",main);
				AddCodeLine("\t\tmov rax, 0",main);
				AddCodeLine("\t\tcall printf",main);
				AddCodeLine("\t\tpop rbp",main);

				AddCodeLine("\t\tpush rbp",main);
				AddCodeLine("\t\tmov rdi, in_format",main);
				AddCodeLine("\t\tmov rax, 0",main);

				sprintf(cgbuffer,"\t\tmov rsi, %s",id->entry->temporary);
				AddCodeLine(cgbuffer,main);
				AddCodeLine("\t\tcall scanf",main);
				AddCodeLine("\t\tpop rbp\n",main);
			}
		}
	}
	else
	{
		ParseTree *tfvar = IO->child->right;

		if(strcmp(terms[tfvar->value],"FALSE") == 0 || strcmp(terms[tfvar->value],"TRUE") == 0)
		{
			char fort[10];

			if(strcmp(terms[tfvar->value],"FALSE") == 0)
				strcpy(fort,"falseout");
			else
				strcpy(fort,"trueout");

			char pbuf[100];
			sprintf(pbuf,"\t\t; Printing %s", tfvar->n->t->value);
			AddCodeLine(pbuf,main);

			AddCodeLine("\t\tmov rax,1",main);
			AddCodeLine("\t\tmov rdi,1",main);
			sprintf(cgbuffer,"\t\tmov rsi, %s", fort);
			AddCodeLine(cgbuffer,main);
			AddCodeLine("\t\tmov rdx, 13",main);
			AddCodeLine("\t\tsyscall\n",main);
		}	
		else
		{
			ParseTree *id = tfvar->child;

			if(strcmp(terms[id->value],"ID") == 0)
			{
				if(id->entry->isArray)
				{
					// Handle Arrays

						// Indexed
						// Whole
				}
				else
				{
					if(strcmp(id->entry->type,"INTEGER") == 0 || strcmp(id->entry->type,"REAL") == 0)
					{
						char pbuf[100];
						sprintf(pbuf,"\t\t; Printing INTEGER ID: %s",id->n->t->value);
						AddCodeLine(pbuf,main);
						AddCodeLine("\t\tpush rbp",main);
						AddCodeLine("\t\tmov rdi, out_format",main);
						AddCodeLine("\t\tmov rax, 0",main);
						sprintf(cgbuffer,"\t\tmov rsi, [%s]", id->entry->temporary);
						AddCodeLine(cgbuffer,main);
					}
					else
					{
						char pbuf[100];
						sprintf(pbuf,"\t\t; Printing BOOLEAN ID: %s",id->n->t->value);
						AddCodeLine(pbuf,main);
						AddCodeLine("\t\tpush rbp",main);

						memset(cgbuffer,0,100);
						sprintf(cgbuffer,"\t\tcmp [%s], dword 1",id->entry->temporary);
						AddCodeLine(cgbuffer,main);

						getLabel();
						char truelabel[20];
						strcpy(truelabel,labelbuf);

						getLabel();
						char falselabel[20];
						strcpy(falselabel,labelbuf);

						memset(cgbuffer,0,100);
						sprintf(cgbuffer,"\t\tje %s", truelabel);
						AddCodeLine(cgbuffer,main);

						// FALSE
						AddCodeLine("\t\tmov rdi, falseout",main);
						AddCodeLine("\t\tmov rax, 0",main);
						memset(cgbuffer,0,100);
						sprintf(cgbuffer,"\t\tjmp %s", falselabel);
						AddCodeLine(cgbuffer,main);
						
						// TRUE
						memset(cgbuffer,0,100);
						sprintf(cgbuffer,"\t%s: mov rdi, trueout", truelabel);
						AddCodeLine(cgbuffer,main);
						AddCodeLine("\t\tmov rax, 0",main);
						memset(cgbuffer,0,100);
						AddCodeLine(cgbuffer,main);

						memset(cgbuffer,0,100);
						sprintf(cgbuffer,"\t%s: ", falselabel);
						AddCodeLine(cgbuffer,main);
					}
				}
			}
			else if(strcmp(terms[id->value],"RNUM") == 0)
			{
				//sprintf(cgbuffer,"\t\tmov rsi, dword %s", id->n->t->value);
				//AddCodeLine(cgbuffer,main);
			}
			else if(strcmp(terms[id->value],"NUM") == 0)
			{
				//sprintf(cgbuffer,"\t\tmov rsi, dword %s", id->n->t->value);
				//AddCodeLine(cgbuffer,main);
			}

			AddCodeLine("\t\tcall printf",main);
			AddCodeLine("\t\tpop rbp\n",main);
		}
	}
}

void CodeGenAssg(ParseTree *Ass, CodeBlock *main)
{
	memset(cgbuffer,0,100); // to clear memory
	sprintf(cgbuffer,"\t; Assignment Statement for '%s' at LineNo: %d", Ass->child->n->t->value, Ass->child->n->t->lineno);
	AddCodeLine(cgbuffer,main);

	if(strcmp(terms[Ass->child->right->value],"lvalueIDStmt") == 0)
	{
		if(Ass->child->entry->isArray)
		{
			// Complete array assignment
		}
		else
		{
			ParseTree *expr = Ass->child->right->child;

				CodeGenExpr(expr, main);

				// Return the temporary (set as global)

			memset(cgbuffer,0,100); // to clear memory
			sprintf(cgbuffer,"\t\tmov eax, [%s]", expr->child->temporary);
			AddCodeLine(cgbuffer,main);

			memset(cgbuffer,0,100); // to clear memory
			sprintf(cgbuffer,"\t\tmov [%s], eax\n", Ass->child->entry->temporary);
			AddCodeLine(cgbuffer,main);
		}
	}
	else
	{
		// Array index wala case 

		ParseTree *expr = Ass->child->right->child->right;
		ParseTree *indexID = Ass->child->right->child->child;
	}
}

void CodeGenSwitch(ParseTree *Swt, CodeBlock *main)
{

}

void CodeGenExprRec(ParseTree *expr, CodeBlock *main)
{

	if(strcmp(terms[expr->value],"var_id_num") == 0)
	{
		ParseTree *ID = expr->child;

		if(strcmp(terms[ID->value],"ID")==0)
		{
			if(ID->entry->isArray)
			{
				// Indexed
				// Non Indexed
			}
			else
			{
				strcpy(expr->temporary, ID->entry->temporary);
			}
		}
		else if(strcmp(terms[ID->value],"RNUM")==0)
		{
			getTemporary();
			strcpy(expr->temporary, tempbuf);
			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
			AddCodeLine(cgbuffer,bss);

			memset(cgbuffer, 0, 100);
			sprintf(cgbuffer, "\t\tmov [%s], dword %s\n", expr->temporary, ID->n->t->value);

			AddCodeLine(cgbuffer, main);
		}
		else if(strcmp(terms[ID->value],"NUM")==0)
		{
			getTemporary();
			strcpy(expr->temporary, tempbuf);
			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
			AddCodeLine(cgbuffer,bss);

			memset(cgbuffer, 0, 100);
			sprintf(cgbuffer, "\t\tmov [%s], dword %s\n", expr->temporary, ID->n->t->value);

			AddCodeLine(cgbuffer, main);
		}
	}
	else if(strcmp(terms[expr->value],"FALSE") == 0)
	{
		getTemporary();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		AddCodeLine(cgbuffer,bss);

		AddCodeLine("\t; FALSE specific",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		AddCodeLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"TRUE") == 0)
	{
		getTemporary();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		AddCodeLine(cgbuffer,bss);

		AddCodeLine("\t; FALSE specific",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 1", expr->temporary);
		AddCodeLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"PLUS") == 0)
	{
		//printf("\nTerm: %s\n",terms[expr->value]);

		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		AddCodeLine("\t\t; Addition",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t\tadd eax, ebx", main);

		getTemporary();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		AddCodeLine(cgbuffer,bss);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], eax\n", expr->temporary);
		AddCodeLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"MINUS") == 0)
	{
		//printf("\nTerm: %s\n",terms[expr->value]);

		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		AddCodeLine("\t\t; Subtraction",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t\tsub eax, ebx", main);

		getTemporary();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		AddCodeLine(cgbuffer,bss);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], eax\n", expr->temporary);
		AddCodeLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"MUL") == 0)
	{
		//printf("\nTerm: %s\n",terms[expr->value]);

		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		AddCodeLine("\t\t; Multiplication",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t\timul ebx", main);

		getTemporary();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		AddCodeLine(cgbuffer,bss);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], eax\n", expr->temporary);
		AddCodeLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"DIV") == 0)
	{
		//printf("\nTerm: %s\n",terms[expr->value]);

		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		AddCodeLine("\t\t; Division",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t\tidiv ebx", main);

		getTemporary();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		AddCodeLine(cgbuffer,bss);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], eax\n", expr->temporary);
		AddCodeLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"LE") == 0)
	{
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		AddCodeLine("\t\t; Less Than Equal To",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t\tcmp eax, ebx", main);

		getLabel();
		char truelabel[20];
		strcpy(truelabel,labelbuf);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjle %s", truelabel);
		AddCodeLine(cgbuffer, main);

		getTemporary();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		AddCodeLine(cgbuffer,bss);

		// False
		AddCodeLine("\t; FALSE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		AddCodeLine(cgbuffer, main);
		getLabel();
		char falselabel[20];
		strcpy(falselabel,labelbuf);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjmp %s", falselabel);
		AddCodeLine(cgbuffer, main);

		// True
		AddCodeLine("\t; TRUE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 1", truelabel, expr->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s:", falselabel);
		AddCodeLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"LT") == 0)
	{
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		AddCodeLine("\t\t; Less Than",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t\tcmp eax, ebx", main);

		getLabel();
		char truelabel[20];
		strcpy(truelabel,labelbuf);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjl %s", truelabel);
		AddCodeLine(cgbuffer, main);

		getTemporary();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		AddCodeLine(cgbuffer,bss);

		// False
		AddCodeLine("\t; FALSE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		AddCodeLine(cgbuffer, main);
		getLabel();
		char falselabel[20];
		strcpy(falselabel,labelbuf);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjmp %s", falselabel);
		AddCodeLine(cgbuffer, main);

		// True
		AddCodeLine("\t; TRUE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 1", truelabel, expr->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s:", falselabel);
		AddCodeLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"GE") == 0)
	{
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		AddCodeLine("\t\t; Greater Than Equal To",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t\tcmp eax, ebx", main);

		getLabel();
		char truelabel[20];
		strcpy(truelabel,labelbuf);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjge %s", truelabel);
		AddCodeLine(cgbuffer, main);

		getTemporary();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		AddCodeLine(cgbuffer,bss);

		// False
		AddCodeLine("\t; FALSE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		AddCodeLine(cgbuffer, main);
		getLabel();
		char falselabel[20];
		strcpy(falselabel,labelbuf);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjmp %s", falselabel);
		AddCodeLine(cgbuffer, main);

		// True
		AddCodeLine("\t; TRUE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 1", truelabel, expr->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s:", falselabel);
		AddCodeLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"GT") == 0)
	{
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		AddCodeLine("\t\t; Greater Than",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t\tcmp eax, ebx", main);

		getLabel();
		char truelabel[20];
		strcpy(truelabel,labelbuf);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjg %s", truelabel);
		AddCodeLine(cgbuffer, main);

		getTemporary();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		AddCodeLine(cgbuffer,bss);

		// False
		AddCodeLine("\t; FALSE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		AddCodeLine(cgbuffer, main);
		getLabel();
		char falselabel[20];
		strcpy(falselabel,labelbuf);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjmp %s", falselabel);
		AddCodeLine(cgbuffer, main);

		// True
		AddCodeLine("\t; TRUE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 1", truelabel, expr->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s:", falselabel);
		AddCodeLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"NE") == 0)
	{
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		AddCodeLine("\t\t; Not Equal To",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t\tcmp eax, ebx", main);

		getLabel();
		char truelabel[20];
		strcpy(truelabel,labelbuf);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjne %s", truelabel);
		AddCodeLine(cgbuffer, main);

		getTemporary();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		AddCodeLine(cgbuffer,bss);

		// False
		AddCodeLine("\t; FALSE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		AddCodeLine(cgbuffer, main);
		getLabel();
		char falselabel[20];
		strcpy(falselabel,labelbuf);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjmp %s", falselabel);
		AddCodeLine(cgbuffer, main);

		// True
		AddCodeLine("\t; TRUE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 1", truelabel, expr->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s:", falselabel);
		AddCodeLine(cgbuffer, main);

	}
	else if(strcmp(terms[expr->value],"EQ") == 0)
	{
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		AddCodeLine("\t\t; Equal To",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t\tcmp eax, ebx", main);

		getLabel();
		char truelabel[20];
		strcpy(truelabel,labelbuf);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tje %s", truelabel);
		AddCodeLine(cgbuffer, main);

		getTemporary();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		AddCodeLine(cgbuffer,bss);

		// False
		AddCodeLine("\t; FALSE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		AddCodeLine(cgbuffer, main);
		getLabel();
		char falselabel[20];
		strcpy(falselabel,labelbuf);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjmp %s", falselabel);
		AddCodeLine(cgbuffer, main);

		// True
		AddCodeLine("\t; TRUE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 1", truelabel, expr->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s:", falselabel);
		AddCodeLine(cgbuffer, main);

	}
	else if(strcmp(terms[expr->value],"AND") == 0)
	{	
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		AddCodeLine("\t\t; AND",main);

		// Short Circuit logic -> 

		/*
			for a AND b -

			if a == 0 then goto lsetfalse
			if b == 0 then goto lsetfalse
			set parent true here

			lsetfalse: set parent false here
		*/

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		AddCodeLine(cgbuffer, main);

		getLabel();
		char lsetfalse[20];
		strcpy(lsetfalse,labelbuf);

		getLabel();
		char ljumptrue[20];
		strcpy(ljumptrue,labelbuf);

		getTemporary();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		AddCodeLine(cgbuffer,bss);

		AddCodeLine("\t; if left == 0, goto lsetfalse", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tcmp eax, dword 0");
		AddCodeLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tje %s", lsetfalse);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t; if right == 0, goto lsetfalse", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tcmp ebx, dword 0");
		AddCodeLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tje %s", lsetfalse);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t; 11 case, set parent = True", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 1", expr->temporary);
		AddCodeLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tjmp %s", ljumptrue);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t; 00/01/10 case, set Parent = False", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 0", lsetfalse, expr->temporary);
		AddCodeLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t%s:", ljumptrue);
		AddCodeLine(cgbuffer, main);

	}
	else if(strcmp(terms[expr->value],"OR") == 0)
	{
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		AddCodeLine("\t\t; OR",main);

		// Short Circuit logic -> 

		/*
			for a OR b -

			if a == 1 then goto lsettrue
			if b == 1 then goto lsettrue
			set parent false here

			lsettrue: set parent true here	
		*/

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		AddCodeLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		AddCodeLine(cgbuffer, main);

		getLabel();
		char lsettrue[20];
		strcpy(lsettrue,labelbuf);

		getLabel();
		char ljumpfalse[20];
		strcpy(ljumpfalse,labelbuf);

		getTemporary();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		AddCodeLine(cgbuffer,bss);

		AddCodeLine("\t; if left == 1, goto lsettrue", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tcmp eax, dword 1");
		AddCodeLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tje %s", lsettrue);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t; if right == 1, goto lsettrue", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tcmp ebx, dword 0");
		AddCodeLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tje %s", lsettrue);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t; 00 case, set parent = false", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		AddCodeLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tjmp %s", ljumpfalse);
		AddCodeLine(cgbuffer, main);

		AddCodeLine("\t; 11/01/10 case, set Parent = true", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 1", lsettrue, expr->temporary);
		AddCodeLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t%s:", ljumpfalse);
		AddCodeLine(cgbuffer, main);
	
	}
}

void CodeGenExpr(ParseTree *expr, CodeBlock *main)
{

	if(strcmp(terms[expr->child->value],"unary") == 0)
	{
		ParseTree *unaryexpr = expr->child->child->right->child;	

		if(strcmp(terms[expr->child->child->value],"MINUS") == 0)
		{
			// Negate the CodeGEnExprRec

			//CodeGenExprRec(unaryexpr, main);
		}
		else
		{
			//CodeGenExprRec(unaryexpr, main);
		}
	}
	else
	{
		CodeGenExprRec(expr->child, main);
	}
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
		CodeGenSwitch(head, main);
	}
	else if(strcmp(terms[head->value],"ioStmt") == 0)
	{
		codeGenIO(head, main);
	}
	else if(strcmp(terms[head->value],"iterativeStmt") == 0)
	{
		CodeGenIter(head, main);
	}
	else if(strcmp(terms[head->value],"assignmentStmt") == 0)
	{
		CodeGenAssg(head, main);
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
		CodeBlock *main;

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
		AddCodeLine("global main \n", main);

		// .data section strings ->

		//******************************************************************************************\\
			
			AddCodeLine("\nsection .data\n", main);
			AddCodeLine("\tin_format:            db \"%d\", 0", main);
			AddCodeLine("\tin_format_int:        db \"Input: Enter an integer value -> \", 10, 0", main);
			AddCodeLine("\tin_format_real:       db \"Input: Enter a real value -> \", 10, 0", main);
			AddCodeLine("\tin_format_boolean:    db \"Input: Enter a boolean value -> \", 10, 0", main);
			AddCodeLine("\tout_format:           db \"Output: %d\", 10, 0", main);
			AddCodeLine("\ttrueout:              db \"Output: True\", 10, 0", main);
			AddCodeLine("\tfalseout:             db \"Output: False\", 10, 0\n", main);

		//******************************************************************************************\\

		AddCodeLine("section .text", main);
		AddCodeLine("\nmain:", main);

		// Recursing the AST for statements -> 

		//******************************************

			CodeGenRec(head, main);

		//******************************************

		// Exiting Code -> 

		AddCodeLine("\n\t;exit code", main);
		AddCodeLine("\texit: mov eax, 1", main);
		AddCodeLine("\t\tmov ebx, 0", main);
		AddCodeLine("\t\tint 80h\n", main);

		MergeCodeBlocks(main,bss);

		PrintToFile(main,f);

		printf("\n%sPlease use the following instructions to assemble, link and execute the \"code.asm\" file - %s\n", BOLDCYAN, RESET);
		printf("\n\tnasm -f elf64 -o code.o code.asm\n");
		printf("\tgcc -no-pie code.o -o code\n");
		printf("\t./code");

		printf("\n\n%sAssembly Code Generated Succesfully............%s\n\n", BOLDWHITE, RESET);
	}
	else
	{
		printf("\n%sCode Gen (Error):%s Such Source Code hasn't been implemented in our project. Please use testcases with driver module only with static arrays.\n\n",BOLDRED,RESET);
	}
}