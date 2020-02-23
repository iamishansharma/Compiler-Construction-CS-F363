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

int** computeFirsts(int i,int j,Grammar G)
{
	//int count j ,k;
	/// G[1] = A-> BCD

	int F[101][15];

	int temp[15]; 

	temp[0] = -1;

	int count=0;

	int eps = insert("EPSILON",TermTable);

	for(i=1;i<=100;i++)
	{
		for(int g=1; g<15; g++)
		{
			F[i][g]=-1;
		}
			int setEps = 0;

			hashVal=G.gnum[i][j];

			if(isnont(hashVal)==0)
			{
				F[i][count] = i; //store hash value
				return F;
			}
			else if(hashVal==eps)
			{
				F[i][count]=eps;// = GrammarTable[i][j];
				count++;
			}
			else
			{
				do
				{
					temp = computeFirsts(i,j,G);

					for(int k=1; k<20; k++)
					{
						if(temp[k]==-1)
						{
							break;
						}
						else
						{
							if(temp[k]==eps)
							{
								setEps =1;
								continue;
							}
							F[i][count] = temp[k];
							count++;
						}
					}
					j++;

				}while{ j<20 && setEps}            
			}
			// hardcoded for now
	}
	return F;  
}

int* computeFollows(Grammar G)
{
	//int count j ,k;
	/// G[1] = A-> BCD
	int F[101][15];
	
	int temp[15]; //assuming max 15 in 1 set
	temp[0] = -1;
	int count=0;
	int setEps =0;
	int eps = 345;// can get from hash as well.
	
	for(int i=0;i<Size(GrammarTable);i++)
	{
			
			int j;
			//int f=20;
			for(j =0;f<20;f++)
			{
				if(G[i][f]==-1)
				{
					break;
				}
			}
			for(int g=1;g<15;g++){
			F[i][g]=-1;
	}
			if(GrammarTable[i][0].start == 1)
			{
				F[i][count] = -2;// -2 reprsensts $ 
				return F;

			}
			elseif(GrammarTable[i][j] ==eps)
			{
				F[i][count]=eps;// = GrammarTable[i][j];
				count++;

			}
			else
			{
				
				do
				{
					temp = computeFollows(G[i][j]);
					for(int k=1;k<20;k++)
					{
						if(temp[k]==-1)
						{
							break;
						}
						else
						{
							if(temp[k]==eps)
							{
								setEps =1;
								continue;
							}
							F[i][count] = temp[k];
							count++;
						}
					}

				}while{ j>0 && setEps}            
			}
	}
	return F;
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

/* END Supporting Functions for Primary Functions */

/* **************************************************************************** */

/* START Primary Functions */

FirstAndFollow ComputeFirstAndFollowSets(Grammar G, FirstAndFollow F)
{

	F.first=computeFirsts(G);
	//F.follow=computeFollows(G);

	return F;
}

ParseTable createParseTable(FirstAndFollow F, ParseTable T)
{
	//Initialising table

	for(int i=0; i<no_rules; i++)
	{
		for(int j=0; j<no_terms; j++)
		{
			T.table[i][j]=-2;
		}
	}

	for(int nt=1; nt<no_rules; nt++)
	{
		for(int j=0; (j<no_terms && t[j].nont==0); j++)
		{
			if(isinFIRST(F,nt,j))
			{
				T.table[nt][j]=nt; // rule value is same as nt value;
			}
			if(epsinFIRST(F,nt))
			{
				int i=0;
				do
				{
					T.table[nt][F.follow[nt][i]]=nt;
					i++;

				}while(F.follow[nt][i]!=-1);
			}
		}
	}

	return T;
}

ParseTree* parseInputSourceCode(char *testcaseFile, ParseTable T)
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

	n=getNextToken();
	//printf("\n");
	
	while(strcmp(n->t->value,"$")!=0)
	{
		//For Debugging - 

		/*printf("%s ",n->t->token);
		printf("%s ",n->t->value);
		printf("%d\n",n->t->lineno);
		n=getNextToken();*/
		
	}
	return head;
}

void printParseTree(ParseTree *head,FILE *f)
{
	// PRINT THE DAMN TREE;
}

/* END Primary Functions */

/* **************************************************************************** */