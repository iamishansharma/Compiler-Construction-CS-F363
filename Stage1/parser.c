/*  parser.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "parser.h"
#include "hash.h"

char *TermTable[MOD];

int no_rules=0;     // total no of grammar rules populated in getGrammar()

int stack[100];
int stack_max=99;   //max value for indexing stack
int top=-1;         // top pointer

/* **************************************************************************** */


/* **************************************************************************** */

/* START Supporting Functions for Primary Functions */

Grammar getGrammar(FILE *f)
{
	Grammar G;

	char string[100];

	FILE *f2=fopen("checkgrammar.txt","w");

	if(f==NULL)
	{
		printf("Cannot open grammar read file!");
		exit(1);
	}

	while(!feof(f))
	{
		fgets(string,100,f);

		int j=0;
		int k=0;

		char word[15][30];

		for(int i=0; i<=strlen(string); i++)
		{
			if(string[i]==' ' || string[i]=='\0')
			{
				word[j][k]='\0';
				j++;
				k=0;
			}
			else
			{
				word[j][k]=string[i];
				k++;
			}
		}

		char toinsert[30];

		int g=0;

		for(g=0; g<j; g++)
		{
			for(int z=0; z<30; z++)
			{
				toinsert[z]='\0';
			}

			int x=0;

			do
			{
				if(word[g][x]==13 || word[g][x]==10)
				{
					//fprintf(f2,"\n \n %d \n \n",word[g][x]);
					x++;
				}
				else
				{
					toinsert[x]=word[g][x];
					x++;
				}

			}while(word[g][x]!='\0');

			int hashVal=insert(toinsert,TermTable);

			if(no_rules==90 && g==1)
			{
				G.gnum[no_rules][g]=1301; //switch wala BT
			}
			else
				G.gnum[no_rules][g]=hashVal;

			fprintf(f2,"%d ",G.gnum[no_rules][g]);
		}

		G.gnum[no_rules][g]=-1;
		fprintf(f2,"%d",G.gnum[no_rules][g]);
		fprintf(f2,"\n");
		no_rules++;
	}
	fclose(f);
	fclose(f2);
	printTerms();
	return G;
}

bool isinFIRST(FirstAndFollow F,int nonterminal, int terminal)
{
	int flag=0;
	int i=0;
	do
	{
		if(F.first[nonterminal][i]==terminal)
		{
			flag=1;
		}
		i++;

	}while(F.first[nonterminal][i]!=-1);

	if(flag==1)
		return true;
	else
		return false;
}

bool epsinFIRST(FirstAndFollow F,int nonterminal)
{
	int flag=0;
	int i=0;
	do
	{
		if(F.first[nonterminal][i]==1529)
		{
			flag=1;
		}
		i++;

	}while(F.first[nonterminal][i]!=-1);

	if(flag==1)
		return true;
	else
		return false;
}

void make_stack()
{
	for(int i=0; i<100; i++)
	{
		stack[i]=-1;
	}
}
void push(int ele)
{
	if(top==stack_max)
	{
		printf("Stack Full! Cannot Push");
		exit(1);
	}
	else
	{
		top++;
		stack[top] = ele;
	}
}
int pop()
{
	if(top==-1)
	{
		printf("Stack Already Empty! Cannot Pop");
		exit(1);
		return -2;
	}
	else
	{
		int popping=stack[top];
		stack[top--]=-1;
		return popping;
	}
}
void printstack()
{
	FILE *f=fopen("stack.txt","w");
	int i=0;
	do
	{
		fprintf(f,"%d\n",stack[i++]);

	}while(stack[i]!=-1);
}

ParseTree* insert_in_tree(ParseTree *head,int rule,Grammar G,Node *n)
{
	return head;
}

int search_nont_in_G(int value, Grammar G)
{
	for(int i=1; i<=100; i++)
	{
		if(G.gnum[i][0]==value)
		{
			return i;
		}
	}
	return -1;
}

ParseTree seach_in_tree(ParseTree* head,int rule)
{
	ParseTree searchNode;
	return searchNode;
}

int size_of_rule(int rule, Grammar G)
{
	int size=1;
	while(G.gnum[rule][size]!=-1)
	{
		size++;
	}
	return size;
}

/* END Supporting Functions for Primary Functions */

/* **************************************************************************** */

/* START Primary Functions */

FirstAndFollow ComputeFirst(Grammar G, FirstAndFollow F)
{
	char string[100];

	int no_firsts=0;

	FILE *f=fopen("first.txt","r");
	FILE *f2=fopen("checkfirst.txt","w");

	if(f==NULL)
	{
		printf("Cannot open first read file!");
		exit(1);
	}

	while(!feof(f))
	{
		fgets(string,100,f);

		int j=0;
		int k=0;

		char word[15][30];

		for(int i=0; i<=strlen(string); i++)
		{
			if(string[i]==' ' || string[i]=='\0')
			{
				word[j][k]='\0';
				j++;
				k=0;
			}
			else
			{
				word[j][k]=string[i];
				k++;
			}
		}

		char toinsert[30];

		int g=0;

		for(g=0; g<j; g++)
		{
			for(int z=0; z<30; z++)
			{
				toinsert[z]='\0';
			}

			int x=0;

			do
			{
				if(word[g][x]==13 || word[g][x]==10)
				{
					x++;
				}
				else
				{
					toinsert[x]=word[g][x];
					x++;
				}

			}while(word[g][x]!='\0');

			int hashVal=insert(toinsert,TermTable);

			F.first[no_firsts][g]=hashVal;

			fprintf(f2,"%d ",F.first[no_firsts][g]);
		}

		F.first[no_firsts][g]=-1;
		fprintf(f2,"%d",F.first[no_firsts][g]);
		fprintf(f2,"\n");
		no_firsts++;
	}

	fclose(f);
	fclose(f2);

	return F;
}

FirstAndFollow ComputeFollow(Grammar G, FirstAndFollow F)
{
	char string[100];

	int no_follows=0;

	FILE *f=fopen("follow.txt","r");
	FILE *f2=fopen("checkfollow.txt","w");

	if(f==NULL)
	{
		printf("Cannot open follow read file!");
		exit(1);
	}

	while(!feof(f))
	{
		fgets(string,100,f);

		int j=0;
		int k=0;

		char word[15][30];

		for(int i=0; i<=strlen(string); i++)
		{
			if(string[i]==' ' || string[i]=='\0')
			{
				word[j][k]='\0';
				j++;
				k=0;
			}
			else
			{
				word[j][k]=string[i];
				k++;
			}
		}

		char toinsert[30];

		int g=0;

		for(g=0; g<j; g++)
		{
			for(int z=0; z<30; z++)
			{
				toinsert[z]='\0';
			}

			int x=0;

			do
			{
				if(word[g][x]==13 || word[g][x]==10)
				{
					x++;
				}
				else
				{
					toinsert[x]=word[g][x];
					x++;
				}

			}while(word[g][x]!='\0');

			int hashVal=insert(toinsert,TermTable);

			F.follow[no_follows][g]=hashVal;

			fprintf(f2,"%d ",F.follow[no_follows][g]);
		}

		F.follow[no_follows][g]=-1;

		fprintf(f2,"%d",F.follow[no_follows][g]);
		fprintf(f2,"\n");

		no_follows++;
	}
	fclose(f);
	fclose(f2);

	return F;
}

ParseTable createParseTable(FirstAndFollow F, ParseTable T)
{
	//Initialising table

	for(int i=0; i<no_rules; i++)
	{
		for(int j=0; j<no_terms; j++)
		{
			T.table[i][j]=-1;
		}
	}

	// INDEX OF [][^this] will we index in terminalarray[];

	int eps = insert("EPSILON",TermTable);

	for(int i=1; i<=100; i++)
	{
		for(int j=0; j<58; j++)
		{
			if(isinFIRST(F,j,i) && terminalarray[j]!=eps)
			{
				T.table[i][j]=i; //rule no
			}
			else if(terminalarray[j]==eps)
			{
				int x=1;
				do
				{
					for(int g=0; g<58; g++)
					{
						if(terminalarray[g]==F.follow[i][x])
						{
							T.table[i][g]=i;
						}
					}
				}while(F.follow[i][x]!=-1);
			}
		}
	}
	return T;
}

ParseTree* parseInputSourceCode(char *testcaseFile, ParseTable T, Grammar G)
{
	ParseTree *head;

	head=(ParseTree*)malloc(sizeof(ParseTree));
	head->n=(Node*)malloc(sizeof(Node));
	head->n->t=(Token*)malloc(sizeof(Token));
	strcpy(head->n->t->token,"PROGRAM");
	strcpy(head->n->t->value,"program");
	head->n->t->lineno = 1;
	head->child = NULL;
	head->left = NULL;
	head->right = NULL;
	head->isleaf = 0;
	head->parent = NULL;

	Node *n=(Node*)malloc(sizeof(Node));
	n->t=(Token*)malloc(sizeof(Token));

	FILE *f=fopen(testcaseFile,"r");

	f = getStream(f);

	make_stack();

	push(1697); // push $ on stack
	push(721);  // push program on stack

	//printstack();

	int eps = insert("EPSILON",TermTable);

	n=getNextToken();

	int checkval=-1;

	while(strcmp(n->t->value,"$")!=0)
	{
		//For Debugging - 

		/*printf("%s ",n->t->token);
		printf("%s ",n->t->value);
		printf("%d\n",n->t->lineno);
		n=getNextToken();*/

		checkval=insert(n->t->token,TermTable); // gets hash value of token

		if(isnont(stack[top])) // top of stack is a non terminal
		{
			int firstindex = search_nont_in_G(stack[top],G);

			int secondindex = searchinta(checkval);

			int rule = T.table[firstindex][secondindex];

			if(rule==-1)
			{
				printf("\nSyntax Error! ");
				printf("Token: %s at line no: %d is not correct.",n->t->token,n->t->lineno);
				
				n=getNextToken();
				checkval=insert(n->t->token,TermTable);

				firstindex = search_nont_in_G(stack[top],G);
				secondindex = searchinta(checkval);

				rule = T.table[firstindex][secondindex];

				while(rule==-1)
				{
					n=getNextToken();
				}
			}
			else
			{
				if(head->child==NULL)
					head=insert_in_tree(head,rule,G,n);
				else
				{
					ParseTree newNode=seach_in_tree(head,rule);
				}
				pop();
				int temp=size_of_rule(rule,G);
				for(;temp>0;temp--)
				{
					int pushing=G.gnum[rule][temp];

					if(pushing != eps)
					{
						push(pushing);
					}
				}
			}
		}
		else // top of stack is terminal
		{
			if(stack[top] == checkval) // stack top matches the hashValue of the current token
			{
				pop();
				n=getNextToken();
			}
			else
			{
				printf("\nSyntax Error! ");
				printf("Token: %s at line no: %d is not correct.\n",n->t->token,n->t->lineno);
                exit(0);
			}
		}
	}
	return head;
}

void printParseTree(ParseTree *head,FILE *f)
{
	// PRINT THE DAMN TREE;
}

/* END Primary Functions */

/* **************************************************************************** */