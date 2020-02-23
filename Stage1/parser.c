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
int no_nont=53;
int no_t=58;

int no_firsts=0;
int no_follows=0;

int stack[100];
int stack_max=99;   //max value for indexing stack
int top=-1;         // top pointer

/* **************************************************************************** */

/* **************************************************************************** */

/* START Supporting Functions for Primary Functions */

Grammar getGrammar(FILE *f)
{
	Grammar G;

	for(int i=0; i<101; i++)
	{
		for(int j=0; j<30; j++)
		{
			G.gnum[i][j]=-1;
		}
	}

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

			int hashVal=compareTerm(toinsert);

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

int compareTerm(char *tocomp)
{
	//printf("%s\n",tocomp);
	for(int i=0; i<110; i++)
	{

		if(strcmp(tocomp,terms[i])==0)
		{
			return i;
		}
	}
	return -1;
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

FirstAndFollow ComputeFirst(FirstAndFollow F)
{

	FILE *f=fopen("first.txt","r");

	char string[100];

	FILE *f2=fopen("checkfirst.txt","w");

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

			int hashVal=compareTerm(toinsert);

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

	//printTerms();

	return F;
}

FirstAndFollow ComputeFollow(FirstAndFollow F)
{

	FILE *f=fopen("follow.txt","r");

	char string[100];

	FILE *f2=fopen("checkfollow.txt","w");

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

			int hashVal=compareTerm(toinsert);

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
	//printTerms();
	return F;
}

ParseTable createParseTable(FirstAndFollow F, ParseTable T, Grammar G)
{
	//Initialising table

	for(int i=0; i<53; i++) // non terminals
	{
		for(int j=0; j<58; j++) // terminals
		{
			T.table[i][j]=-1;
		}
	}

	for(int i=1; i<101; i++) // non terminals
	{
		int flag=0;

		int j=1;

		int term=G.gnum[i][0];

		for(;j<30; j++)
		{
			//int alpha=G.gnum[i][j];
			if(G.gnum[i][j]==-1)
			{
				break;
			}

			for(int k=0; k<94; k++)
			{
				if(G.gnum[i][j]==F.first[k][0])
				{
					for(int l=1; ;l++)
					{
						if(F.first[k][l]==-1)
						{
							break;
						}
						if(F.first[k][l]==54)
						{
							flag=1;
							continue;
						}

						T.table[term][F.first[k][l]-53]=i;
					}
					break;
				}
			}
		}

		if(flag==1)
		{
			for(int k=0; k<53; k++)
			{
				if(G.gnum[i][0]==F.follow[k][0])
				{
					for(int l=1; ;l++)
					{
						if(F.first[k][l]==-1)
						{
							break;
						}
						T.table[G.gnum[i][0]][F.follow[k][l]-53]=i;
					}
					break;
				}
			}
		}
	}
	return T;
}

void printTable(ParseTable T)
{
	FILE *f=fopen("checktable.csv","w");
	fprintf(f,",");
	for(int i=0; i<58; i++)
	{
		fprintf(f,"%s,",terms[i+53]);
	}
	fprintf(f,"\n");
	for(int i=0; i<53; i++)
	{
		fprintf(f,"%s,",terms[i]);
		for(int j=0; j<58; j++)
		{
			fprintf(f,"%d,",T.table[i][j]);
		}
		fprintf(f,"\n");
	}
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

	push(53); // push $ on stack
	push(0);  // push program on stack

	//printstack();

	int eps = 54;

	n=getNextToken();

	while(strcmp(n->t->value,"$")!=0)
	{
		//For Debugging - 

		/*printf("%s ",n->t->token);
		printf("%s ",n->t->value);
		printf("%d\n",n->t->lineno);
		n=getNextToken();*/
		int X=stack[top];

		int a=compareTerm(n->t->token);

		break;

		while(X!=53)
		{
			if(X==a)
			{
				pop();
				n=getNextToken();
			}
			else if(X>=53)
			{
				//Xerror();
				printf("X is a terminal\n");
			}
			else if(T.table[X][a-53]==-1)
			{
				//Xerror();
				printf("Entry does not exist\n");
			}
			else if(T.table[X][a-53]!=-1)
			{
				printf("%d ",T.table[X][a-53]);
				pop();
				int glno=T.table[X][a-53];
				for(int f=30; f>0 ;f--)
				{
					if(G.gnum[glno][f]==-1)
					{
						continue;
					}
					else
					{
						push(G.gnum[glno][f]);
					}
				}
			}
			X=stack[top];
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