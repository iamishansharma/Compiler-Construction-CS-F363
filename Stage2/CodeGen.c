/*  

	CodeGen.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

	To Do: 

		Unary minus wala negation

		While

		Switch

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

void getTemp()
{
	sprintf(tempbuf,"ri%d", tempno);
	tempno++;
}

void getL()
{
	sprintf(labelbuf,"l%d",labelno);
	labelno++;
}

CodeBlock *cCB()
{
	CodeBlock *cb = (CodeBlock *)malloc(sizeof(CodeBlock));
	cb->upar = NULL;
	cb->niche = NULL;
	return cb;
}

void ACLine(char *line, CodeBlock *cb)
{
	// Add line at the bottom of CodeBlock

	CodeLine *newLine;
	newLine = (CodeLine *)malloc(sizeof(CodeLine));
	newLine->next = NULL;
	strcpy(newLine->line,line);

	if(cb->niche == NULL && cb->upar == NULL)
		cb->upar = cb->niche = newLine;
	else
	{
		cb->niche->next = newLine;
		cb->niche = newLine;
	}
}

void MCB(CodeBlock *cb1, CodeBlock *cb2)
{
	// Merge cb1 and cb2, put cb1 on upar, cb2 on Bottom

	if(cb1->upar == NULL)
	{
		if(cb2->upar == NULL)
		{}
		else
		{
			cb1->upar = cb2->upar;
			cb1->niche = cb2->niche;
		}
	}
	else
	{
		if(cb2->upar == NULL)
		{}
		else
		{
			cb1->niche->next = cb2->upar;
			cb1->niche = cb2->niche;
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
			getTemp();
		}
		else
			getTemp();
		

		strcpy(temp->temporary,tempbuf);

		if(temp->isArray)
		{
			if(temp->startindex->isDynamic == 0 && temp->endindex->isDynamic == 0)
			{
				int range = temp->endindex->ifnumvalue - temp->startindex->ifnumvalue + 1;
				sprintf(cgbuffer,"\t%s: \tresd %d ; ID: %s | Line No: %d",temp->temporary,range,temp->name,temp->lineno);
			}
			else
				daflag = 1;
		}
		else
			sprintf(cgbuffer,"\t%s: \tresd %d ; ID: %s | Line No: %d",temp->temporary,1,temp->name,temp->lineno);

		ACLine(cgbuffer,cb);
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
		ACLine(getvbuf,main);

		if(id->entry->isArray)
		{
			if(strcmp(id->entry->type,"INTEGER") == 0 || strcmp(id->entry->type,"REAL") == 0)
			{
				int start = id->entry->startindex->ifnumvalue;
				int end = id->entry->endindex->ifnumvalue;
				int tot = end - start + 1;

				getL();
				char arlp[20];
				strcpy(arlp,labelbuf);

				ACLine("\t\tpush rbp",main);
				ACLine("\t\tmov rdi, in_format_int_a ; printing array integer format",main); 
				ACLine("\t\tmov rax, 0",main);
				memset(cgbuffer,0,100);
				sprintf(cgbuffer,"\t\tmov rsi, dword %d", tot);
				ACLine(cgbuffer,main);
				memset(cgbuffer,0,100);
				sprintf(cgbuffer,"\t\tmov rdx, dword %d", start);
				ACLine(cgbuffer,main);
				memset(cgbuffer,0,100);
				sprintf(cgbuffer,"\t\tmov rcx, dword %d", end);
				ACLine(cgbuffer,main);
				ACLine("\t\tcall printf",main);
				ACLine("\t\tpop rbp",main);

				// for loop for array here -> 
				ACLine("\t\tpush rbp",main);
				memset(cgbuffer,0,100);
				sprintf(cgbuffer,"\t\tmov r14, dword 0");
				ACLine(cgbuffer,main);
				memset(cgbuffer,0,100);
				sprintf(cgbuffer,"\t%s: ", arlp);
				ACLine(cgbuffer,main);
				ACLine("\t\tmov rdi, in_format",main);
				ACLine("\t\tmov rax, 0",main);
				sprintf(cgbuffer,"\t\tlea rsi, [%s + 4*r14]",id->entry->temporary);
				ACLine(cgbuffer,main);
				ACLine("\t\tcall scanf",main);
				ACLine("\t\tinc r14",main);
				memset(cgbuffer,0,100);
				sprintf(cgbuffer,"\t\tcmp r14, %d",tot);
				ACLine(cgbuffer,main);
				memset(cgbuffer,0,100);
				sprintf(cgbuffer,"\t\tjne %s", arlp);
				ACLine(cgbuffer,main);
				ACLine("\t\tpop rbp\n",main);
			}
			else
			{
				int start = id->entry->startindex->ifnumvalue;
				int end = id->entry->endindex->ifnumvalue;
				int tot = end - start + 1;

				ACLine("\t\tpush rbp",main);
				ACLine("\t\tmov rdi, in_format_boolean_a ; printing array integer format",main); 
				ACLine("\t\tmov rax, 0",main);
				memset(cgbuffer,0,100);
				sprintf(cgbuffer,"\t\tmov rsi, dword %d", tot);
				ACLine(cgbuffer,main);
				memset(cgbuffer,0,100);
				sprintf(cgbuffer,"\t\tmov rdx, dword %d", start);
				ACLine(cgbuffer,main);
				memset(cgbuffer,0,100);
				sprintf(cgbuffer,"\t\tmov rcx, dword %d", end);
				ACLine(cgbuffer,main);
				ACLine("\t\tcall printf",main);
				ACLine("\t\tpop rbp",main);

				getL();
				char arlp[20];
				strcpy(arlp,labelbuf);

				// for loop for array here -> 
				ACLine("\t\tpush rbp",main);
				memset(cgbuffer,0,100);
				sprintf(cgbuffer,"\t\tmov r14, dword 0");
				ACLine(cgbuffer,main);
				memset(cgbuffer,0,100);
				sprintf(cgbuffer,"\t%s: ", arlp);
				ACLine(cgbuffer,main);
				ACLine("\t\tmov rdi, in_format",main);
				ACLine("\t\tmov rax, 0",main);
				sprintf(cgbuffer,"\t\tlea rsi, [%s + 4*r14]",id->entry->temporary);
				ACLine(cgbuffer,main);
				ACLine("\t\tcall scanf",main);
				ACLine("\t\tinc r14",main);
				memset(cgbuffer,0,100);
				sprintf(cgbuffer,"\t\tcmp r14, %d",tot);
				ACLine(cgbuffer,main);
				memset(cgbuffer,0,100);
				sprintf(cgbuffer,"\t\tjne %s", arlp);
				ACLine(cgbuffer,main);
				ACLine("\t\tpop rbp\n",main);
			}
		}
		else
		{
			if(strcmp(id->entry->type,"INTEGER") == 0)
			{
				ACLine("\t\tpush rbp",main);
				ACLine("\t\tmov rdi, in_format_int ; printing integer format",main); 

				ACLine("\t\tmov rax, 0",main);
				ACLine("\t\tcall printf",main);
				ACLine("\t\tpop rbp",main);

				ACLine("\t\tpush rbp",main);
				//ACLine("\t\tpush rax",main);
				ACLine("\t\tmov rdi, in_format",main);
				ACLine("\t\tmov rax, 0",main);

				sprintf(cgbuffer,"\t\tmov rsi, %s",id->entry->temporary);
				ACLine(cgbuffer,main);
				ACLine("\t\tcall scanf",main);
				//ACLine("\t\tpop rax",main);
				ACLine("\t\tpop rbp\n",main);
			}
			else if(strcmp(id->entry->type,"REAL") == 0)
			{
				// Not working because float registers nahi hai.
				ACLine("\t\tpush rbp",main);
				ACLine("\t\tmov rdi, in_format_real ; printing real format",main);
				ACLine("\t\tmov rax, 0",main);
				ACLine("\t\tcall printf",main);
				ACLine("\t\tpop rbp",main);

				ACLine("\t\tpush rbp",main);
				ACLine("\t\tmov rdi, in_format",main);
				ACLine("\t\tmov rax, 0",main);

				sprintf(cgbuffer,"\t\tmov rsi, %s",id->entry->temporary);
				ACLine(cgbuffer,main);
				ACLine("\t\tcall scanf",main);
				ACLine("\t\tpop rbp\n",main);
			}
			else if(strcmp(id->entry->type,"BOOLEAN") == 0)
			{
				ACLine("\t\tpush rbp",main);
				ACLine("\t\tmov rdi, in_format_boolean ; printing boolean format",main);
				ACLine("\t\tmov rax, 0",main);
				ACLine("\t\tcall printf",main);
				ACLine("\t\tpop rbp",main);

				ACLine("\t\tpush rbp",main);
				ACLine("\t\tmov rdi, in_format",main);
				ACLine("\t\tmov rax, 0",main);

				sprintf(cgbuffer,"\t\tmov rsi, %s",id->entry->temporary);
				ACLine(cgbuffer,main);
				ACLine("\t\tcall scanf",main);
				ACLine("\t\tpop rbp\n",main);
			}
		}
	}
	else // print
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
			ACLine(pbuf,main);

			ACLine("\t\tpush rbp",main);
			ACLine("\t\tmov rdi, out_format_m",main);
			ACLine("\t\tmov rax, 0",main);
			ACLine("\t\tcall printf",main);
			ACLine("\t\tpop rbp\n",main);

			ACLine("\t\tmov rax,1",main);
			ACLine("\t\tmov rdi,1",main);
			sprintf(cgbuffer,"\t\tmov rsi, %s", fort);
			ACLine(cgbuffer,main);
			ACLine("\t\tmov rdx, 13",main);
			ACLine("\t\tsyscall\n",main);
		}	
		else
		{
			ParseTree *id = tfvar->child;

			if(strcmp(terms[id->value],"ID") == 0)
			{
				if(id->entry->isArray)
				{
					if(id->right == NULL) // full array
					{
						//printf("\nFull array\n");
						if(strcmp(id->entry->type,"INTEGER") == 0)
						{
							int tot = id->entry->endindex->ifnumvalue - id->entry->startindex->ifnumvalue + 1;

							char pbuf[100];
							sprintf(pbuf,"\t\t; Printing INTEGER ARRAY ID: %s",id->n->t->value);
							ACLine(pbuf,main);
							ACLine("\t\tpush rbp",main);
							ACLine("\t\tmov rdi, out_format_ma",main);
							ACLine("\t\tmov rax, 0",main);
							ACLine("\t\tcall printf",main);
							ACLine("\t\tpop rbp\n",main);

							getL();
							char arlp[20];
							strcpy(arlp,labelbuf);
							
							ACLine("\t\tpush rbp",main);
							memset(cgbuffer,0,100);
							sprintf(cgbuffer,"\t\tmov r13, dword 0");
							ACLine(cgbuffer,main);
							memset(cgbuffer,0,100);
							sprintf(cgbuffer,"\t%s: ", arlp);
							ACLine(cgbuffer,main);
							ACLine("\t\tmov rdi, out_format",main);
							ACLine("\t\tmov rax, 0",main);
							sprintf(cgbuffer,"\t\tmov rsi, [%s + 4*r13]", id->entry->temporary);
							ACLine(cgbuffer,main);
							ACLine("\t\tcall printf",main);
							ACLine("\t\tinc r13",main);
							memset(cgbuffer,0,100);
							sprintf(cgbuffer,"\t\tcmp r13, %d",tot);
							ACLine(cgbuffer,main);
							memset(cgbuffer,0,100);
							sprintf(cgbuffer,"\t\tjne %s", arlp);
							ACLine(cgbuffer,main);
							ACLine("\t\tpop rbp\n",main);
						}
						else if(strcmp(id->entry->type,"BOOLEAN") == 0)
						{
							int tot = id->entry->endindex->ifnumvalue - id->entry->startindex->ifnumvalue + 1;

							char pbuf[100];
							sprintf(pbuf,"\t\t; Printing BOOLEAN ARRAY ID: %s",id->n->t->value);
							ACLine(pbuf,main);
							ACLine("\t\tpush rbp",main);
							ACLine("\t\tmov rdi, out_format_ma",main);
							ACLine("\t\tmov rax, 0",main);
							ACLine("\t\tcall printf",main);
							ACLine("\t\tpop rbp\n",main);

							getL();
							char arlp[20];
							strcpy(arlp,labelbuf);

							ACLine("\t\tpush rbp",main);
							memset(cgbuffer,0,100);
							sprintf(cgbuffer,"\t\tmov r12, dword 0");
							ACLine(cgbuffer,main);

							memset(cgbuffer,0,100);
							sprintf(cgbuffer,"\t%s: ", arlp);
							ACLine(cgbuffer,main);

							memset(cgbuffer,0,100);
							sprintf(cgbuffer,"\t\tcmp [%s + 4*r12], dword 1",id->entry->temporary);
							ACLine(cgbuffer,main);

							getL();
							char truelabel[20];
							strcpy(truelabel,labelbuf);

							getL();
							char falselabel[20];
							strcpy(falselabel,labelbuf);

							memset(cgbuffer,0,100);
							sprintf(cgbuffer,"\t\tje %s", truelabel);
							ACLine(cgbuffer,main);

							// FALSE
							ACLine("\t\tmov rdi, falseout",main);
							ACLine("\t\tmov rax, 0",main);
							memset(cgbuffer,0,100);
							sprintf(cgbuffer,"\t\tjmp %s", falselabel);
							ACLine(cgbuffer,main);
							
							// TRUE
							memset(cgbuffer,0,100);
							sprintf(cgbuffer,"\t%s: mov rdi, trueout", truelabel);
							ACLine(cgbuffer,main);
							ACLine("\t\tmov rax, 0",main);
							memset(cgbuffer,0,100);
							ACLine(cgbuffer,main);
							memset(cgbuffer,0,100);
							sprintf(cgbuffer,"\t%s: ", falselabel);
							ACLine(cgbuffer,main);
							ACLine("\t\tcall printf",main);
							ACLine("\t\tinc r12",main);
							memset(cgbuffer,0,100);
							sprintf(cgbuffer,"\t\tcmp r12, %d",tot);
							ACLine(cgbuffer,main);
							memset(cgbuffer,0,100);
							sprintf(cgbuffer,"\t\tjne %s", arlp);
							ACLine(cgbuffer,main);
							ACLine("\t\tpop rbp\n",main);
						}
					}
					else // index wala
					{
						ParseTree *index = id->right->child;

						if(strcmp(terms[index->value],"ID") == 0)
						{
							// Dynamic Index
							if(strcmp(id->entry->type,"INTEGER") == 0)
							{
								//printf("\nYahan aaya\n");
								char pbuf[100];
								sprintf(pbuf,"\t\t; Printing INTEGER ARRAY (Dynamic Indexed) ID: %s",id->n->t->value);
								ACLine(pbuf,main);
								ACLine("\t\tpush rbp",main);
								ACLine("\t\tmov rdi, out_format_m",main);
								ACLine("\t\tmov rax, 0",main);
								ACLine("\t\tcall printf",main);
								ACLine("\t\tpop rbp\n",main);

								ACLine("\t\tpush rbp",main);
								ACLine("\t\tmov rdi, out_format",main);
								ACLine("\t\tmov rax, 0",main);

								getL();
								char iofb[20];
								strcpy(iofb,labelbuf);

								getL();
								char doa[20];
								strcpy(doa,labelbuf);

								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tmov r11d, [%s]", index->entry->temporary);
								ACLine(cgbuffer,main);

								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tcmp r11d, %d", id->entry->startindex->ifnumvalue);
								ACLine(cgbuffer,main);

								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tjnge %s", iofb);
								ACLine(cgbuffer,main);

								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tcmp r11d, %d", id->entry->endindex->ifnumvalue);
								ACLine(cgbuffer,main);
								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tjle %s", doa);
								ACLine(cgbuffer,main);

								ACLine("\n\t; array index out of bounds error", main);
								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t%s: ", iofb);
								ACLine(cgbuffer,main);
								ACLine("\t\tpush rbp",main);
								ACLine("\t\tmov rdi, array_iofb",main);
								ACLine("\t\tmov rax, 0",main);
								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tmov rsi, dword %d", id->n->t->lineno);
								ACLine(cgbuffer,main);
								ACLine("\t\tcall printf",main);
								ACLine("\t\tpop rbp\n",main);
								ACLine("\t\tjmp exit",main);

								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t%s: sub r11d, %d", doa, id->entry->startindex->ifnumvalue);
								ACLine(cgbuffer,main);

								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tmov rsi, [%s + 4*r11d]", id->entry->temporary);
								ACLine(cgbuffer,main);
								ACLine("\t\tcall printf",main);
								ACLine("\t\tpop rbp\n",main);
							}
							else if(strcmp(id->entry->type,"BOOLEAN") == 0)
							{
								char pbuf[100];
								sprintf(pbuf,"\t\t; Printing BOOLEAN ARRAY (Dynamic Indexed) ID: %s",id->n->t->value);
								ACLine(pbuf,main);
								ACLine("\t\tpush rbp",main);
								ACLine("\t\tmov rdi, out_format_m",main);
								ACLine("\t\tmov rax, 0",main);
								ACLine("\t\tcall printf",main);
								ACLine("\t\tpop rbp\n",main);

								ACLine("\t\tpush rbp",main);
								ACLine("\t\tmov rdi, out_format",main);
								ACLine("\t\tmov rax, 0",main);

								getL();
								char iofb[20];
								strcpy(iofb,labelbuf);

								getL();
								char doa[20];
								strcpy(doa,labelbuf);

								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tmov r10d, [%s]", index->entry->temporary);
								ACLine(cgbuffer,main);

								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tcmp r10d, %d", id->entry->startindex->ifnumvalue);
								ACLine(cgbuffer,main);

								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tjnge %s", iofb);
								ACLine(cgbuffer,main);

								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tcmp r10d, %d", id->entry->endindex->ifnumvalue);
								ACLine(cgbuffer,main);
								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tjle %s", doa);
								ACLine(cgbuffer,main);

								ACLine("\n\t; array index out of bounds error", main);
								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t%s: ", iofb);
								ACLine(cgbuffer,main);
								ACLine("\t\tpush rbp",main);
								ACLine("\t\tmov rdi, array_iofb",main);
								ACLine("\t\tmov rax, 0",main);
								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tmov rsi, dword %d", id->n->t->lineno);
								ACLine(cgbuffer,main);
								ACLine("\t\tcall printf",main);
								ACLine("\t\tpop rbp\n",main);
								ACLine("\t\tjmp exit",main);

								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t%s: sub r10d, %d", doa, id->entry->startindex->ifnumvalue);
								ACLine(cgbuffer,main);

								ACLine("\t\tpush rbp",main);
								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tcmp [%s + 4*r10d], dword 1",id->entry->temporary);
								ACLine(cgbuffer,main);

								getL();
								char truelabel[20];
								strcpy(truelabel,labelbuf);

								getL();
								char falselabel[20];
								strcpy(falselabel,labelbuf);

								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tje %s", truelabel);
								ACLine(cgbuffer,main);

								// FALSE
								ACLine("\t\tmov rdi, falseout",main);
								ACLine("\t\tmov rax, 0",main);
								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tjmp %s", falselabel);
								ACLine(cgbuffer,main);
								
								// TRUE
								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t%s: mov rdi, trueout", truelabel);
								ACLine(cgbuffer,main);
								ACLine("\t\tmov rax, 0",main);
								memset(cgbuffer,0,100);
								ACLine(cgbuffer,main);

								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t%s: ", falselabel);
								ACLine(cgbuffer,main);
								ACLine("\t\tcall printf",main);
								ACLine("\t\tpop rbp\n",main);
							}
						}
						else // NUM ID
						{
							int indexval = atoi(index->n->t->value) - id->entry->startindex->ifnumvalue;

							if(strcmp(id->entry->type,"INTEGER") == 0)
							{
								char pbuf[100];
								sprintf(pbuf,"\t\t; Printing INTEGER ARRAY (Static Indexed) ID: %s",id->n->t->value);
								ACLine(pbuf,main);
								ACLine("\t\tpush rbp",main);
								ACLine("\t\tmov rdi, out_format_m",main);
								ACLine("\t\tmov rax, 0",main);
								ACLine("\t\tcall printf",main);
								ACLine("\t\tpop rbp\n",main);
								ACLine("\t\tpush rbp",main);
								ACLine("\t\tmov rdi, out_format",main);
								ACLine("\t\tmov rax, 0",main);
								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tmov r11, dword %d", indexval);
								ACLine(cgbuffer,main);
								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tmov rsi, [%s + 4*r11]", id->entry->temporary);
								ACLine(cgbuffer,main);
								ACLine("\t\tcall printf",main);
								ACLine("\t\tpop rbp\n",main);
							}
							else if(strcmp(id->entry->type,"BOOLEAN") == 0)
							{
								char pbuf[100];
								sprintf(pbuf,"\t\t; Printing BOOLEAN ARRAY (Static Indexed) ID: %s",id->n->t->value);
								ACLine(pbuf,main);
								ACLine("\t\tpush rbp",main);
								ACLine("\t\tmov rdi, out_format_m",main);
								ACLine("\t\tmov rax, 0",main);
								ACLine("\t\tcall printf",main);
								ACLine("\t\tpop rbp\n",main);

								ACLine("\t\tpush rbp",main);
								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tmov r10, dword %d",indexval);
								ACLine(cgbuffer,main);
								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tcmp [%s + 4*r10], dword 1",id->entry->temporary);
								ACLine(cgbuffer,main);

								getL();
								char truelabel[20];
								strcpy(truelabel,labelbuf);

								getL();
								char falselabel[20];
								strcpy(falselabel,labelbuf);

								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tje %s", truelabel);
								ACLine(cgbuffer,main);

								// FALSE
								ACLine("\t\tmov rdi, falseout",main);
								ACLine("\t\tmov rax, 0",main);
								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t\tjmp %s", falselabel);
								ACLine(cgbuffer,main);
								
								// TRUE
								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t%s: mov rdi, trueout", truelabel);
								ACLine(cgbuffer,main);
								ACLine("\t\tmov rax, 0",main);
								memset(cgbuffer,0,100);
								ACLine(cgbuffer,main);

								memset(cgbuffer,0,100);
								sprintf(cgbuffer,"\t%s: ", falselabel);
								ACLine(cgbuffer,main);
								ACLine("\t\tcall printf",main);
								ACLine("\t\tpop rbp\n",main);
							}
						}
					}
				}
				else
				{
					if(strcmp(id->entry->type,"INTEGER") == 0 || strcmp(id->entry->type,"REAL") == 0)
					{
						char pbuf[100];
						sprintf(pbuf,"\t\t; Printing INTEGER ID: %s",id->n->t->value);
						ACLine(pbuf,main);
						ACLine("\t\tpush rbp",main);
						ACLine("\t\tmov rdi, out_format_m",main);
						ACLine("\t\tmov rax, 0",main);
						ACLine("\t\tcall printf",main);
						ACLine("\t\tpop rbp\n",main);
						ACLine("\t\tpush rbp",main);
						ACLine("\t\tmov rdi, out_format",main);
						ACLine("\t\tmov rax, 0",main);
						sprintf(cgbuffer,"\t\tmov rsi, [%s]", id->entry->temporary);
						ACLine(cgbuffer,main);
						ACLine("\t\tcall printf",main);
						ACLine("\t\tpop rbp\n",main);
					}
					else
					{
						char pbuf[100];
						sprintf(pbuf,"\t\t; Printing BOOLEAN ID: %s",id->n->t->value);
						ACLine(pbuf,main);
						ACLine("\t\tpush rbp",main);
						ACLine("\t\tmov rdi, out_format_m",main);
						ACLine("\t\tmov rax, 0",main);
						ACLine("\t\tcall printf",main);
						ACLine("\t\tpop rbp\n",main);

						ACLine("\t\tpush rbp",main);

						memset(cgbuffer,0,100);
						sprintf(cgbuffer,"\t\tcmp [%s], dword 1",id->entry->temporary);
						ACLine(cgbuffer,main);

						getL();
						char truelabel[20];
						strcpy(truelabel,labelbuf);

						getL();
						char falselabel[20];
						strcpy(falselabel,labelbuf);

						memset(cgbuffer,0,100);
						sprintf(cgbuffer,"\t\tje %s", truelabel);
						ACLine(cgbuffer,main);

						// FALSE
						ACLine("\t\tmov rdi, falseout",main);
						ACLine("\t\tmov rax, 0",main);
						memset(cgbuffer,0,100);
						sprintf(cgbuffer,"\t\tjmp %s", falselabel);
						ACLine(cgbuffer,main);
						
						// TRUE
						memset(cgbuffer,0,100);
						sprintf(cgbuffer,"\t%s: mov rdi, trueout", truelabel);
						ACLine(cgbuffer,main);
						ACLine("\t\tmov rax, 0",main);
						memset(cgbuffer,0,100);
						ACLine(cgbuffer,main);

						memset(cgbuffer,0,100);
						sprintf(cgbuffer,"\t%s: ", falselabel);
						ACLine(cgbuffer,main);
						ACLine("\t\tcall printf",main);
						ACLine("\t\tpop rbp\n",main);
					}
				}
			}
			else if(strcmp(terms[id->value],"RNUM") == 0)
			{
				//sprintf(cgbuffer,"\t\tmov rsi, dword %s", id->n->t->value);
				//ACLine(cgbuffer,main);
			}
			else if(strcmp(terms[id->value],"NUM") == 0)
			{
				//sprintf(cgbuffer,"\t\tmov rsi, dword %s", id->n->t->value);
				//ACLine(cgbuffer,main);
			}
		}
	}
}

void CodeGenAssg(ParseTree *Ass, CodeBlock *main)
{
	memset(cgbuffer,0,100); // to clear memory
	sprintf(cgbuffer,"\t; Assignment Statement for '%s' at LineNo: %d", Ass->child->n->t->value, Ass->child->n->t->lineno);
	ACLine(cgbuffer,main);

	if(strcmp(terms[Ass->child->right->value],"lvalueIDStmt") == 0)
	{
		if(Ass->child->entry->isArray)
		{
			// Complete array assignment
			ParseTree *lhs = Ass->child;
			ParseTree *rhs = Ass->child->right->child->child->child;

			memset(cgbuffer,0,100); // to clear memory
			sprintf(cgbuffer,"\t; Full Array '%s' with '%s' at LineNo: %d", lhs->n->t->value, rhs->n->t->value, lhs->n->t->lineno);
			ACLine(cgbuffer,main);

			int lowval = lhs->entry->startindex->ifnumvalue;
			int highval = lhs->entry->endindex->ifnumvalue;

			ACLine("\t\tpush rbp",main);

			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t\tmov r15, dword 0");
			ACLine(cgbuffer,main);

			getL();
			char forloop[20];
			strcpy(forloop,labelbuf);
			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t\t%s: ",forloop);
			ACLine(cgbuffer,main);

			memset(cgbuffer,0,100); // to clear memory
			sprintf(cgbuffer,"\t\tmov eax, [%s + 4*r15]", rhs->entry->temporary);
			ACLine(cgbuffer,main);

			memset(cgbuffer,0,100); // to clear memory
			sprintf(cgbuffer,"\t\tmov [%s + 4*r15], eax", lhs->entry->temporary);
			ACLine(cgbuffer,main);

			ACLine("\t\tinc r15",main);
			sprintf(cgbuffer,"\t\tcmp r15, %d", highval+1);
			ACLine(cgbuffer,main);
			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t\tjne %s\n",forloop);
			ACLine(cgbuffer,main);
			ACLine("\t\tpop rbp",main);
		}
		else
		{
			ParseTree *expr = Ass->child->right->child;

				CodeGenExpr(expr, main);

			memset(cgbuffer,0,100); // to clear memory
			sprintf(cgbuffer,"\t\tmov eax, [%s]", expr->child->temporary);
			ACLine(cgbuffer,main);

			memset(cgbuffer,0,100); // to clear memory
			sprintf(cgbuffer,"\t\tmov [%s], eax\n", Ass->child->entry->temporary);
			ACLine(cgbuffer,main);
		}
	}
	else
	{
		// Array index wala case 

		ParseTree *expr = Ass->child->right->child->right;
		ParseTree *indexID = Ass->child->right->child->child;

		CodeGenExpr(expr, main);

		if(strcmp(terms[indexID->value],"ID") == 0)
		{
			ACLine("\t\tpush rbp",main);

			getL();
			char iofb[20];
			strcpy(iofb,labelbuf);

			getL();
			char doa[20];
			strcpy(doa,labelbuf);

			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t\tmov r13d, [%s]", indexID->entry->temporary);
			ACLine(cgbuffer,main);

			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t\tcmp r13d, %d", Ass->child->entry->startindex->ifnumvalue);
			ACLine(cgbuffer,main);

			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t\tjnge %s", iofb);
			ACLine(cgbuffer,main);

			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t\tcmp r13d, %d", Ass->child->entry->endindex->ifnumvalue);
			ACLine(cgbuffer,main);
			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t\tjle %s", doa);
			ACLine(cgbuffer,main);

			ACLine("\n\t; array index out of bounds error", main);
			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t%s: ", iofb);
			ACLine(cgbuffer,main);
			ACLine("\t\tpush rbp",main);
			ACLine("\t\tmov rdi, array_iofb",main);
			ACLine("\t\tmov rax, 0",main);
			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t\tmov rsi, dword %d", Ass->child->n->t->lineno);
			ACLine(cgbuffer,main);
			ACLine("\t\tcall printf",main);
			ACLine("\t\tpop rbp\n",main);
			ACLine("\t\tjmp exit",main);

			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t%s: sub r13d, %d", doa, Ass->child->entry->startindex->ifnumvalue);
			ACLine(cgbuffer,main);

			memset(cgbuffer,0,100); // to clear memory
			sprintf(cgbuffer,"\t\tmov eax, [%s]", expr->child->temporary);
			ACLine(cgbuffer,main);

			memset(cgbuffer,0,100); // to clear memory
			sprintf(cgbuffer,"\t\tmov [%s + 4*r13d], eax", Ass->child->entry->temporary);
			ACLine(cgbuffer,main);
			ACLine("\t\tpop rbp\n",main);
		}
		else
		{
			int indexval = atoi(indexID->n->t->value) - Ass->child->entry->startindex->ifnumvalue;

			ACLine("\t\tpush rbp",main);
			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t\tmov r9d, %d", indexval);
			ACLine(cgbuffer,main);

			memset(cgbuffer,0,100); // to clear memory
			sprintf(cgbuffer,"\t\tmov eax, [%s]", expr->child->temporary);
			ACLine(cgbuffer,main);

			memset(cgbuffer,0,100); // to clear memory
			sprintf(cgbuffer,"\t\tmov [%s + 4*r9d], eax", Ass->child->entry->temporary);
			ACLine(cgbuffer,main);
			ACLine("\t\tpop rbp\n",main);
		}
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
				// Indexed hi hoga, warna recurse possible nahi hai
				getTemp();
				strcpy(expr->temporary, tempbuf);
				memset(cgbuffer,0,100);
				sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
				ACLine(cgbuffer,bss);

				if(strcmp(terms[ID->right->child->value],"ID") == 0)
				{
					ParseTree *indexid = ID->right->child;

					ACLine("\t\tpush rbp",main);

					getL();
					char iofb[20];
					strcpy(iofb,labelbuf);

					getL();
					char doa[20];
					strcpy(doa,labelbuf);

					memset(cgbuffer,0,100);
					sprintf(cgbuffer,"\t\tmov r13d, [%s]", indexid->entry->temporary);
					ACLine(cgbuffer,main);

					memset(cgbuffer,0,100);
					sprintf(cgbuffer,"\t\tcmp r13d, %d", ID->entry->startindex->ifnumvalue);
					ACLine(cgbuffer,main);

					memset(cgbuffer,0,100);
					sprintf(cgbuffer,"\t\tjnge %s", iofb);
					ACLine(cgbuffer,main);

					memset(cgbuffer,0,100);
					sprintf(cgbuffer,"\t\tcmp r13d, %d", ID->entry->endindex->ifnumvalue);
					ACLine(cgbuffer,main);
					memset(cgbuffer,0,100);
					sprintf(cgbuffer,"\t\tjle %s", doa);
					ACLine(cgbuffer,main);

					ACLine("\n\t; array index out of bounds error", main);
					memset(cgbuffer,0,100);
					sprintf(cgbuffer,"\t%s: ", iofb);
					ACLine(cgbuffer,main);
					ACLine("\t\tpush rbp",main);
					ACLine("\t\tmov rdi, array_iofb",main);
					ACLine("\t\tmov rax, 0",main);
					memset(cgbuffer,0,100);
					sprintf(cgbuffer,"\t\tmov rsi, dword %d", ID->n->t->lineno);
					ACLine(cgbuffer,main);
					ACLine("\t\tcall printf",main);
					ACLine("\t\tpop rbp\n",main);
					ACLine("\t\tjmp exit",main);

					memset(cgbuffer,0,100);
					sprintf(cgbuffer,"\t%s: sub r13d, %d", doa, ID->entry->startindex->ifnumvalue);
					ACLine(cgbuffer,main);
					memset(cgbuffer,0,100); // to clear memory
					sprintf(cgbuffer,"\t\tmov eax, [%s + 4*r13d]\n", ID->entry->temporary);
					ACLine(cgbuffer,main);
					memset(cgbuffer,0,100); // to clear memory
					sprintf(cgbuffer,"\t\tmov [%s], eax", expr->temporary);
					ACLine(cgbuffer,main);
					ACLine("\t\tpop rbp\n",main);
				}
				else
				{
					int indexval = atoi(ID->right->child->n->t->value) - ID->entry->startindex->ifnumvalue;

					ACLine("\t\tpush rbp",main);
					memset(cgbuffer,0,100);
					sprintf(cgbuffer,"\t\tmov r9, %d", indexval);
					ACLine(cgbuffer,main);
					memset(cgbuffer,0,100); // to clear memory
					sprintf(cgbuffer,"\t\tmov eax, [%s + 4*r9]\n", ID->entry->temporary);
					ACLine(cgbuffer,main);
					memset(cgbuffer,0,100); // to clear memory
					sprintf(cgbuffer,"\t\tmov [%s], eax", expr->temporary);
					ACLine(cgbuffer,main);
					ACLine("\t\tpop rbp\n",main);
				}
			}
			else
			{
				strcpy(expr->temporary, ID->entry->temporary);
			}
		}
		else if(strcmp(terms[ID->value],"RNUM")==0)
		{
			getTemp();
			strcpy(expr->temporary, tempbuf);
			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
			ACLine(cgbuffer,bss);

			memset(cgbuffer, 0, 100);
			sprintf(cgbuffer, "\t\tmov [%s], dword %s\n", expr->temporary, ID->n->t->value);

			ACLine(cgbuffer, main);
		}
		else if(strcmp(terms[ID->value],"NUM")==0)
		{
			getTemp();
			strcpy(expr->temporary, tempbuf);
			memset(cgbuffer,0,100);
			sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
			ACLine(cgbuffer,bss);

			memset(cgbuffer, 0, 100);
			sprintf(cgbuffer, "\t\tmov [%s], dword %s\n", expr->temporary, ID->n->t->value);

			ACLine(cgbuffer, main);
		}
	}
	else if(strcmp(terms[expr->value],"FALSE") == 0)
	{
		getTemp();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		ACLine(cgbuffer,bss);

		ACLine("\t; FALSE specific",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		ACLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"TRUE") == 0)
	{
		getTemp();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		ACLine(cgbuffer,bss);

		ACLine("\t; TRUE specific",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 1", expr->temporary);
		ACLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"PLUS") == 0)
	{
		//printf("\nTerm: %s\n",terms[expr->value]);

		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		ACLine("\t\t; Addition",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		ACLine(cgbuffer, main);

		ACLine("\t\tadd eax, ebx", main);

		getTemp();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		ACLine(cgbuffer,bss);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], eax\n", expr->temporary);
		ACLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"MINUS") == 0)
	{
		//printf("\nTerm: %s\n",terms[expr->value]);

		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		ACLine("\t\t; Subtraction",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		ACLine(cgbuffer, main);

		ACLine("\t\tsub eax, ebx", main);

		getTemp();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		ACLine(cgbuffer,bss);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], eax\n", expr->temporary);
		ACLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"MUL") == 0)
	{
		//printf("\nTerm: %s\n",terms[expr->value]);

		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		ACLine("\t\t; Multiplication",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		ACLine(cgbuffer, main);

		ACLine("\t\timul ebx", main);

		getTemp();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		ACLine(cgbuffer,bss);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], eax\n", expr->temporary);
		ACLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"DIV") == 0)
	{
		//printf("\nTerm: %s\n",terms[expr->value]);

		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		ACLine("\t\t; Division",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		ACLine(cgbuffer, main);

		ACLine("\t\tidiv ebx", main);

		getTemp();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		ACLine(cgbuffer,bss);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], eax\n", expr->temporary);
		ACLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"LE") == 0)
	{
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		ACLine("\t\t; Less Than Equal To",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		ACLine(cgbuffer, main);

		ACLine("\t\tcmp eax, ebx", main);

		getL();
		char truelabel[20];
		strcpy(truelabel,labelbuf);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjle %s", truelabel);
		ACLine(cgbuffer, main);

		getTemp();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		ACLine(cgbuffer,bss);

		// False
		ACLine("\t; FALSE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		ACLine(cgbuffer, main);
		getL();
		char falselabel[20];
		strcpy(falselabel,labelbuf);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjmp %s", falselabel);
		ACLine(cgbuffer, main);

		// True
		ACLine("\t; TRUE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 1", truelabel, expr->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s:", falselabel);
		ACLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"LT") == 0)
	{
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		ACLine("\t\t; Less Than",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		ACLine(cgbuffer, main);

		ACLine("\t\tcmp eax, ebx", main);

		getL();
		char truelabel[20];
		strcpy(truelabel,labelbuf);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjl %s", truelabel);
		ACLine(cgbuffer, main);

		getTemp();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		ACLine(cgbuffer,bss);

		// False
		ACLine("\t; FALSE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		ACLine(cgbuffer, main);
		getL();
		char falselabel[20];
		strcpy(falselabel,labelbuf);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjmp %s", falselabel);
		ACLine(cgbuffer, main);

		// True
		ACLine("\t; TRUE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 1", truelabel, expr->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s:", falselabel);
		ACLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"GE") == 0)
	{
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		ACLine("\t\t; Greater Than Equal To",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		ACLine(cgbuffer, main);

		ACLine("\t\tcmp eax, ebx", main);

		getL();
		char truelabel[20];
		strcpy(truelabel,labelbuf);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjge %s", truelabel);
		ACLine(cgbuffer, main);

		getTemp();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		ACLine(cgbuffer,bss);

		// False
		ACLine("\t; FALSE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		ACLine(cgbuffer, main);
		getL();
		char falselabel[20];
		strcpy(falselabel,labelbuf);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjmp %s", falselabel);
		ACLine(cgbuffer, main);

		// True
		ACLine("\t; TRUE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 1", truelabel, expr->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s:", falselabel);
		ACLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"GT") == 0)
	{
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		ACLine("\t\t; Greater Than",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		ACLine(cgbuffer, main);

		ACLine("\t\tcmp eax, ebx", main);

		getL();
		char truelabel[20];
		strcpy(truelabel,labelbuf);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjg %s", truelabel);
		ACLine(cgbuffer, main);

		getTemp();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		ACLine(cgbuffer,bss);

		// False
		ACLine("\t; FALSE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		ACLine(cgbuffer, main);
		getL();
		char falselabel[20];
		strcpy(falselabel,labelbuf);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjmp %s", falselabel);
		ACLine(cgbuffer, main);

		// True
		ACLine("\t; TRUE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 1", truelabel, expr->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s:", falselabel);
		ACLine(cgbuffer, main);
	}
	else if(strcmp(terms[expr->value],"NE") == 0)
	{
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		ACLine("\t\t; Not Equal To",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		ACLine(cgbuffer, main);

		ACLine("\t\tcmp eax, ebx", main);

		getL();
		char truelabel[20];
		strcpy(truelabel,labelbuf);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjne %s", truelabel);
		ACLine(cgbuffer, main);

		getTemp();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		ACLine(cgbuffer,bss);

		// False
		ACLine("\t; FALSE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		ACLine(cgbuffer, main);
		getL();
		char falselabel[20];
		strcpy(falselabel,labelbuf);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjmp %s", falselabel);
		ACLine(cgbuffer, main);

		// True
		ACLine("\t; TRUE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 1", truelabel, expr->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s:", falselabel);
		ACLine(cgbuffer, main);

	}
	else if(strcmp(terms[expr->value],"EQ") == 0)
	{
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		ACLine("\t\t; Equal To",main);

		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov eax, [%s]", expr->child->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		ACLine(cgbuffer, main);

		ACLine("\t\tcmp eax, ebx", main);

		getL();
		char truelabel[20];
		strcpy(truelabel,labelbuf);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tje %s", truelabel);
		ACLine(cgbuffer, main);

		getTemp();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		ACLine(cgbuffer,bss);

		// False
		ACLine("\t; FALSE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		ACLine(cgbuffer, main);
		getL();
		char falselabel[20];
		strcpy(falselabel,labelbuf);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tjmp %s", falselabel);
		ACLine(cgbuffer, main);

		// True
		ACLine("\t; TRUE RELOP",main);
		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 1", truelabel, expr->temporary);
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t%s:", falselabel);
		ACLine(cgbuffer, main);

	}
	else if(strcmp(terms[expr->value],"AND") == 0)
	{	
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		ACLine("\t\t; AND",main);

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
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		ACLine(cgbuffer, main);

		getL();
		char lsetfalse[20];
		strcpy(lsetfalse,labelbuf);

		getL();
		char ljumptrue[20];
		strcpy(ljumptrue,labelbuf);

		getTemp();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		ACLine(cgbuffer,bss);

		ACLine("\t; if left == 0, goto lsetfalse", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tcmp eax, dword 0");
		ACLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tje %s", lsetfalse);
		ACLine(cgbuffer, main);

		ACLine("\t; if right == 0, goto lsetfalse", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tcmp ebx, dword 0");
		ACLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tje %s", lsetfalse);
		ACLine(cgbuffer, main);

		ACLine("\t; 11 case, set parent = True", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 1", expr->temporary);
		ACLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tjmp %s", ljumptrue);
		ACLine(cgbuffer, main);

		ACLine("\t; 00/01/10 case, set Parent = False", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 0", lsetfalse, expr->temporary);
		ACLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t%s:", ljumptrue);
		ACLine(cgbuffer, main);

	}
	else if(strcmp(terms[expr->value],"OR") == 0)
	{
		CodeGenExprRec(expr->child, main);
		CodeGenExprRec(expr->child->right, main);

		ACLine("\t\t; OR",main);

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
		ACLine(cgbuffer, main);

		memset(cgbuffer, 0, 100);
		sprintf(cgbuffer, "\t\tmov ebx, [%s]", expr->child->right->temporary);
		ACLine(cgbuffer, main);

		getL();
		char lsettrue[20];
		strcpy(lsettrue,labelbuf);

		getL();
		char ljumpfalse[20];
		strcpy(ljumpfalse,labelbuf);

		getTemp();
		strcpy(expr->temporary, tempbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t%s: \tresd %d", expr->temporary,1);
		ACLine(cgbuffer,bss);

		ACLine("\t; if left == 1, goto lsettrue", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tcmp eax, dword 1");
		ACLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tje %s", lsettrue);
		ACLine(cgbuffer, main);

		ACLine("\t; if right == 1, goto lsettrue", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tcmp ebx, dword 0");
		ACLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tje %s", lsettrue);
		ACLine(cgbuffer, main);

		ACLine("\t; 00 case, set parent = false", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tmov [%s], dword 0", expr->temporary);
		ACLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t\tjmp %s", ljumpfalse);
		ACLine(cgbuffer, main);

		ACLine("\t; 11/01/10 case, set Parent = true", main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t%s: mov [%s], dword 1", lsettrue, expr->temporary);
		ACLine(cgbuffer, main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer, "\t%s:", ljumpfalse);
		ACLine(cgbuffer, main);
	
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
	if(strcmp(terms[Iter->child->value],"FOR") == 0)
	{
		ParseTree *ID = Iter->child->right;
		ParseTree *low = Iter->child->right->right->child;
		ParseTree *high = Iter->child->right->right->child->right;
		int lowval = atoi(Iter->child->right->right->child->n->t->value);
		int highval = atoi(Iter->child->right->right->child->right->n->t->value);
		ParseTree *Stmt = Iter->child->right->right->right;

		char getvbuf[100];
		sprintf(getvbuf,"\t\t; FOR iterative stmt ID: %s", ID->n->t->value);
		ACLine(getvbuf,main);

		//ACLine("\t\tpush rbp",main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t\tmov r15, dword %d", lowval);
		ACLine(cgbuffer,main);

		getL();
		char forloop[20];
		strcpy(forloop,labelbuf);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t\t%s: ",forloop);
		ACLine(cgbuffer,main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t\tmov [%s], r15d", ID->entry->temporary);
		ACLine(cgbuffer,main);

		CodeGenRec(Stmt, main);

		ACLine("\t\tinc r15",main);
		sprintf(cgbuffer,"\t\tcmp r15, %d", highval+1);
		ACLine(cgbuffer,main);
		memset(cgbuffer,0,100);
		sprintf(cgbuffer,"\t\tjne %s\n",forloop);
		ACLine(cgbuffer,main);
		//ACLine("\t\tpop rbp\n",main);
	}
	else
	{
		// WHILE
	}
}

void CodeGenStmts(ParseTree *Stmt, CodeBlock *main)
{

}

void CodeGenRec(ParseTree *head, CodeBlock *main)
{
	if(head == NULL)
		return;

	if(strcmp(terms[head->value],"conditionalStmt") == 0 && head->isCG == 0)
	{
		head->isCG = 1;
		CodeGenSwitch(head, main);
	}
	else if(strcmp(terms[head->value],"ioStmt") == 0 && head->isCG == 0)
	{
		head->isCG = 1;
		codeGenIO(head, main);
	}
	else if(strcmp(terms[head->value],"iterativeStmt") == 0 && head->isCG == 0)
	{
		head->isCG = 1;
		CodeGenIter(head, main);
	}
	else if(strcmp(terms[head->value],"assignmentStmt") == 0 && head->isCG == 0)
	{
		head->isCG = 1;
		CodeGenAssg(head, main);
	}

	CodeGenRec(head->child, main);
	CodeGenRec(head->right, main);
}

void PTF(CodeBlock *cb, FILE *f)
{
	CodeLine *temp = cb->upar;

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

		main = cCB();
		bss = cCB();

		ACLine("section .bss\n", bss);

		AssignTemporaries(table->child, bss);

		if(daflag == 1)
		{
			printf("\n%sCode Gen (Error):%s Such Source Code hasn't been implemented in our project. Please use testcases only with static arrays and driver module.\n\n",BOLDRED,RESET);
			return;
		}

		ACLine("\nextern printf, scanf\n", main);
		ACLine("global main \n", main);

		// .data section strings ->

		//******************************************************************************************\\
			
			ACLine("\nsection .data\n", main);
			ACLine("\tin_format:            db \"%d\", 0", main);
			ACLine("\tin_format_int:        db \"Input: Enter an integer value -> \", 10, 0", main);
			ACLine("\tin_format_int_a:      db \"Input: Enter %d array elements of integer type for range %d to %d -> \", 10, 0", main);
			ACLine("\tin_format_real:       db \"Input: Enter a real value -> \", 10, 0", main);
			ACLine("\tin_format_real_a:     db \"Input: Enter %d array elements of real type for range %d to %d -> \", 10, 0", main);
			ACLine("\tin_format_boolean:    db \"Input: Enter a boolean value (0 or 1) -> \", 10, 0", main);
			ACLine("\tin_format_boolean_a:  db \"Input: Enter %d array elements of boolean type (0 or 1) for range %d to %d -> \", 10, 0", main);
			ACLine("\tout_format_m:         db \"Output: \", 10, 0", main);
			ACLine("\tout_format_ma:        db \"Output Array: \", 10, 0", main);
			ACLine("\tout_format:           db \"%d\", 10, 0", main);
			ACLine("\ttrueout:              db \"True\", 10, 0", main);
			ACLine("\tfalseout:             db \"False\", 10, 0\n", main);
			ACLine("\tarray_iofb:           db \"(RUN TIME ERROR): Array index is out of bounds at line no %d\", 10, 0\n", main);

		//******************************************************************************************\\

		ACLine("section .text", main);
		ACLine("\nmain:", main);

		// Recursing the AST for statements -> 

		//******************************************

			CodeGenRec(head, main);

		//******************************************

		// Exiting Code -> 

		ACLine("\n\t;exit code", main);
		ACLine("\texit: mov eax, 1", main);
		ACLine("\t\tmov ebx, 0", main);
		ACLine("\t\tint 80h\n", main);

		MCB(main,bss);

		PTF(main,f);

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