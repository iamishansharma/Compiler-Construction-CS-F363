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
	for(int i=0; i<111; i++)
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
	for(int i=0; i<112; i++)
	{
		for(int j=0; j<15; j++)
		{
			F.first[i][j]=-1;
		}
	}

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

		//printf("%s\n",string);

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

			//printf("%s\n",toinsert);

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

	return F;
}

FirstAndFollow ComputeFollow(FirstAndFollow F)
{
	for(int i=0; i<112; i++)
	{
		for(int j=0; j<15; j++)
		{
			F.follow[i][j]=-1;
		}
	}

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

	return F;
}

void printFF(FirstAndFollow F)
{
	FILE *f4=fopen("newfirst.txt","w");
	FILE *f5=fopen("newfollow.txt","w");

	for(int i=0; i<112; i++)
	{
		for(int j=0; j<15; j++)
		{
			if(F.first[i][j]==-1)
			{
				;
			}
			else
			{
				fprintf(f4,"%s ",terms[F.first[i][j]]);
			}
		}
		fprintf(f4,"\n");
	}
	for(int i=0; i<112; i++)
	{
		for(int j=0; j<15; j++)
		{
			if(F.follow[i][j]==-1)
			{
				;
			}
			else
			{
				fprintf(f5,"%s ",terms[F.follow[i][j]]);
			}
		}
		fprintf(f5,"\n");
	}
}

ParseTable createParseTable(FirstAndFollow F, ParseTable T, Grammar G)
{
	//Initialising table

	printFF(F);
	
	for(int i=0; i<53; i++) // non terminals
	{
		for(int j=0; j<58; j++) // terminals
		{
			T.table[i][j]=-1;
		}
	}
	int flag=0;

	for(int i=1; i<101; i++) // non terminals
	{
		flag=0;

		int j=1;

		int term=G.gnum[i][0];

		//int alpha=G.gnum[i][j];
		//printf("First for %d %d %d\n",i,j,G.gnum[i][j]);

		if(G.gnum[i][j]==-1)
		{
			//printf("Break for -1 in Grammar Rule %d %d\n",i,j);
			break;
		}

		for(int k=0; k<94; k++)
		{
			if(G.gnum[i][j]==F.first[k][0])
			{
				//printf("FOUND FIRST %d %d %d %d\n",i,j,k,F.first[k][0]);
				for(int l=1; ;l++)
				{
					if(F.first[k][l]==-1)
					{
						//printf("Outside first set %d %d %d %d\n",i,j,k,l);
						break;
					}
					if(F.first[k][l]==56)
					{
						//printf("Every Value: %d %d %d %d %d\n",i,j,k,l,F.first[k][l]);
						//printf("FOUND EPSILON %d %d %d %d\n",i,j,k,l);
						flag=1;
						continue;
					}

					//printf("Insert value %s: %d %d %d\n",terms[term],i,j,k);

					//printf("In First: %d %d\n",term,F.first[k][l]-53);

					T.table[term][F.first[k][l]-53]=i;

					//printf("RANGEOP: %d\n",T.table[term][57]);
				}
				break;
			}
		}

		if(flag==1)
		{
			//printf("In flag here!\n");
			for(int k=0; k<53; k++)
			{
				if(G.gnum[i][0]==F.follow[k][0])
				{
					//printf("FOUND FOLLOW %d %d %d\n",i,j,k);
					for(int l=1; ;l++)
					{
						//printf("Every Value: %d %d %d %d %s\n",i,j,k,l,terms[F.follow[k][l]]);
						if(F.follow[k][l]==-1)
						{
							//printf("Outside follow set %d %d %d %d\n",i,j,k,l);
							break;
						}
						//printf("Insert value %s: %d %d %d\n",terms[term],i,j,k);

						//printf("In Follow: %d %d\n",G.gnum[i][0],F.follow[k][l]-53);

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

	push(91); // push $ on stack
	push(0);  // push program on stack

	//printstack();

	int eps = 56;

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