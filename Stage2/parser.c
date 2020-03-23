/*  parser.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "parser.h"
#include "hash.h"

char *TermTable[MOD]; //RIP

int no_firsts=0;
int no_follows=0;

int stack[100];
int stack_max=99;   //max value for indexing stack
int top=-1;         // top pointer

ParseTree *head;

/* **************************************************************************** */

/* **************************************************************************** */

/* START Supporting Functions for Primary Functions */

Grammar getGrammar(FILE *f)
{
	Grammar G;

	for(int i=0; i<GR; i++)
	{
		for(int j=0; j<30; j++)
		{
			G.gnum[i][j]=-1;
		}
	}

	int no_rules=0;

	char string[100];

	//FILE *f2=fopen("checkgrammar.txt","w");

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

			int current=0;

			do
			{
				if(word[g][current]==13 || word[g][current]==10)
				{
					//fprintf(f2,"\n \n %d \n \n",word[g][current]);
					current++;
				}
				else
				{
					toinsert[current]=word[g][current];
					current++;
				}

			}while(word[g][current]!='\0');

			//printf("%s\n",toinsert);

			int hashVal=compareTerm(toinsert);

			//printf("%d\n",hashVal);

			G.gnum[no_rules][g]=hashVal;

			//fprintf(f2,"%d ",G.gnum[no_rules][g]);

		}

		G.gnum[no_rules][g]=-1;
		//fprintf(f2,"%d",G.gnum[no_rules][g]);
		//fprintf(f2,"\n");
		no_rules++;
	}

	fclose(f);
	//fclose(f2);
	//printTerms();
	return G;
}

int compareTerm(char *tocomp)
{
	//printf("%s\n",tocomp);
	for(int i=0; i<(NTER + TER); i++)
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
	//printf("Comes here! ");
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

void insert_in_tree(ParseTree *current, int rule, Grammar G, Node *n)
{

	//NEEDS PLAGIRISM CHECK

	int *rules=G.gnum[rule];

	int i=1;

	ParseTree *temp, *sib, *right, *left;

	current->isVisited = 1;
	current->rule = rule;

	while(rules[i]!=-1)
	{

		temp = (ParseTree *)malloc(sizeof(ParseTree));
		temp->n = (Node*)malloc(sizeof(Node));
		temp->n->t = (Token*)malloc(sizeof(Token));
		temp->value = rules[i];
		temp->n=n;

		/*printf("Inside Loop of Insert!\n");
		printf("Lexeme: %s\n",temp->n->t->token);
		printf("Value: %s\n",temp->n->t->value);
		printf("Line No: %d\n",temp->n->t->lineno);
		printf("***************************\n");*/

		if(rules[i] >= NTER)
		{
			temp->isleaf = 1;
		}
		else
		{
			temp->isleaf = 0;
		}

		temp->left = NULL;
		temp->left = NULL;
        temp->right = NULL;
        temp->child = NULL;
        temp->parent = current;

        temp->isVisited = 0;

        if(current->child==NULL)
        {
        	//printf("Come here when no child ! %s\n",terms[current->value]);
        	current->child = temp;
        }
        else //if current has children already
        {
        	//printf("Come here when child ! %s\n",terms[current->value]);
            sib = current->child;

            while(sib->right!=NULL)
            {
                right = sib -> right;
                sib = right;

            }
            sib -> right = temp;
            temp -> left = sib;
            sib->n=n;
        }
        i++;
	}
}

ParseTree* searchposition(ParseTree *trav, int stacktop)
{
	ParseTree *temp;

	if(trav == NULL)
	{
		//printf("Come here in search cond trav is null !\n");
		return NULL;
	}
	else if((trav->value == stacktop) && (!trav->isVisited))
	{
		//printf("Come here in search trav stacktop wala! %s \n",terms[trav->value]);
		return trav;
	}
	else if((temp = searchposition(trav->child,stacktop))!=NULL)
	{
		//printf("Come here in search trav child! %s \n",terms[temp->value]);
		return temp;
	}
	else if((temp = searchposition(trav->right,stacktop))!=NULL)
	{
		//printf("Come here in search trav right! %s \n",terms[temp->value]);
		return temp;
	}
	else
	{
		//printf("Come here in search last else!\n");
		//printf("Come here in search trav stacktop wala! %s \n",terms[trav->child->value]);
		return NULL;
	}
}

ParseTree* returnhead()
{
	return head;
}

/* END Supporting Functions for Primary Functions */

/* **************************************************************************** */

/* START Primary Functions */

FirstAndFollow ComputeFirst(FirstAndFollow F, Grammar G)
{
	for(int i=0; i<120; i++)
	{
		for(int j=0; j<15; j++)
		{
			F.first[i][j]=-1;
		}
	}

	FILE *f=fopen("first.txt","r");

	char string[100];

	//FILE *f2=fopen("checkfirst.txt","w");

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

			int current=0;

			do
			{
				if(word[g][current]==13 || word[g][current]==10)
				{
					//fprintf(f2,"\n \n %d \n \n",word[g][current]);
					current++;
				}
				else
				{
					toinsert[current]=word[g][current];
					current++;
				}

			}while(word[g][current]!='\0');

			//printf("%s\n",toinsert);

			int hashVal=compareTerm(toinsert);

			F.first[no_firsts][g]=hashVal;

			//fprintf(f2,"%d ",F.first[no_firsts][g]);
		}

		F.first[no_firsts][g]=-1;
		//fprintf(f2,"%d",F.first[no_firsts][g]);
		//fprintf(f2,"\n");
		no_firsts++;
	}

	fclose(f);
	//fclose(f2);

	return F;
}

FirstAndFollow ComputeFollow(FirstAndFollow F, Grammar G)
{
	for(int i=0; i<120; i++)
	{
		for(int j=0; j<15; j++)
		{
			F.follow[i][j]=-1;
		}
	}

	FILE *f=fopen("follow.txt","r");

	char string[100];

	//FILE *f2=fopen("checkfollow.txt","w");

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

			int current=0;

			do
			{
				if(word[g][current]==13 || word[g][current]==10)
				{
					//fprintf(f2,"\n \n %d \n \n",word[g][current]);
					current++;
				}
				else
				{
					toinsert[current]=word[g][current];
					current++;
				}

			}while(word[g][current]!='\0');

			int hashVal=compareTerm(toinsert);

			F.follow[no_follows][g]=hashVal;

			//fprintf(f2,"%d ",F.follow[no_follows][g]);
		}

		F.follow[no_follows][g]=-1;
		//fprintf(f2,"%d",F.follow[no_follows][g]);
		//fprintf(f2,"\n");
		no_follows++;
	}

	fclose(f);
	//fclose(f2);

	return F;
}

void printFF(FirstAndFollow F)
{
	FILE *f4=fopen("newfirst.txt","w");
	FILE *f5=fopen("newfollow.txt","w");

	for(int i=0; i<120; i++)
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
	for(int i=0; i<120; i++)
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

	//printFF(F);
	
	for(int i=0; i<NTER; i++) // non terminals
	{
		for(int j=0; j<TER; j++) // terminals
		{
			T.table[i][j]=-1;
		}
	}
	int flag=0;

	for(int i=1; i<GR; i++) // non terminals
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

		for(int k=0; k<no_firsts; k++)
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
					if(F.first[k][l]==EPS) // EPSILON
					{
						//printf("Every Value: %d %d %d %d %d\n",i,j,k,l,F.first[k][l]);
						//printf("FOUND EPSILON %d %d %d %d\n",i,j,k,l);
						flag=1;
						continue;
					}

					//printf("Insert value %s: %d %d %d\n",terms[term],i,j,k);

					//printf("In First: %d %d\n",term,F.first[k][l]-53);

					T.table[term][F.first[k][l]-NTER]=i;

					//printf("RANGEOP: %d\n",T.table[term][57]);
				}
				break;
			}
		}

		if(flag==1)
		{
			//printf("In flag here!\n");
			for(int k=0; k<no_follows; k++)
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

						T.table[G.gnum[i][0]][F.follow[k][l]-NTER]=i;
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
	for(int i=0; i<TER; i++)
	{
		fprintf(f,"%s,",terms[i+NTER]);
	}
	fprintf(f,"\n");
	for(int i=0; i<NTER; i++)
	{
		fprintf(f,"%s,",terms[i]);
		for(int j=0; j<TER; j++)
		{
			fprintf(f,"%d,",T.table[i][j]);
		}
		fprintf(f,"\n");
	}
}

void parseInputSourceCode(FILE *f, ParseTable T, Grammar G)
{
	head=(ParseTree*)malloc(sizeof(ParseTree));
	head->n=(Node*)malloc(sizeof(Node));
	head->n->t=(Token*)malloc(sizeof(Token));
	strcpy(head->n->t->token,"PROGRAM");
	strcpy(head->n->t->value,"program");
	head->n->t->lineno = 1;
	head->value = 0;
	head->rule = 1;
	head->child = NULL;
	head->right = NULL;
	head->parent = NULL;
	head->left = NULL;
	head->isVisited = 0;

	Node *n=(Node*)malloc(sizeof(Node));
	n->t=(Token*)malloc(sizeof(Token));

	f = getStream(f);

	make_stack();
	
	push(DOL); // push $ on stack
	push(0);  // push program on stack

	//printf("%s ",terms[91])

	//printstack();

	n=getNextToken();

	/*printf("Lexeme: %s\n",n->t->token);
	printf("Value: %s\n",n->t->value);
	printf("Line No: %d\n",n->t->lineno);
	printf("***************************\n");*/

	//printf("\n");

	T.table[0][1]=1; // expicitly added DEF for program (t9.txt)
	T.table[0][2]=1; // expicitly added DRIVERDEF for program (t9.txt)
	T.table[49][0]=93;
	T.table[20][74-NTER]=40;
	T.table[30][6]=55;

	while(strcmp(n->t->value,"$")!=0)
	{
		/*printf("Lexeme: %s\n",n->t->token);
		printf("Value: %s\n",n->t->value);
		printf("Line No: %d\n",n->t->lineno);
		printf("***************************\n");*/

		if((strcmp(n->t->token,"Error")==0) || (strcmp(n->t->token,"Error,Id size>20")==0))
		{
			//printf("Lexical Error! %s at line no: %d",n->t->value,n->t->lineno);
			exit(0);
		}		
		//fprintf(fs,"\nStack (TOP OF STACK IS LEFT MOST ELEMENT: \n");
		for(int i=top; i>=0; i--)
		{
			//fprintf(fs,"%s ",terms[stack[i]]);
		}
		//fprintf(fs,"\n\n");
		
		int X=stack[top];

		if(strcmp(n->t->token,"Error")==0)
		{
			break;
		}

		int a=compareTerm(n->t->token);

		//fprintf(fs,"Top of stack: %s | Input Token: %s | Input Token Lexeme: %s\n",terms[X],terms[a],n->t->value);

		if(X==a)
		{
			//fprintf(fs,"ACTION: Popping top of stack because same terminal found at input.\n");
			pop();
			n=getNextToken();
			a=compareTerm(n->t->token);
		}
		else if(X>=NTER)
		{
			printf("\nSyntactical Error! Error: %s at line no: %d, Expected: %s.\n",terms[a],n->t->lineno,terms[X]);
			//fprintf(fs,"\nSyntactical Error! Error: %s at line no: %d, Expected: %s.\n",terms[a],n->t->lineno,terms[X]);
			exit(0);
			//pop();
			//error recovery
		}
		else if(T.table[X][a-NTER]==-1)
		{
			printf("\nSyntactical Error! Error: %s at line no: %d.\n",terms[a],n->t->lineno);
			//fprintf(fs,"\nSyntactical Error! Error: %s at line no: %d.\n",terms[a],n->t->lineno);
			exit(0);
			/*while(T.table[X][a-NTER]==-1)
			{
				n=getNextToken();
				a=compareTerm(n->t->token);
			}*/
		}
		else if(T.table[X][a-NTER]!=-1)
		{
			/*if(stack[top]==0)
			{
				insert_in_tree(stack[top],T.table[X][a-NTER],G,n);
			}
			else
			{
				//printf("SENDING VALUE: \n%d %d\n",stack[top],T.table[X][a-NTER]);
				insert_in_tree(stack[top],T.table[X][a-NTER],G,n);
			}*/

			if(head->child == NULL)
			{
				//printf("Rule to be used first: %d\n",T.table[X][a-NTER]);
				//printf("Searched node = %s | Rule No: %d \n",terms[head->value],T.table[X][a-NTER]);
				insert_in_tree(head,T.table[X][a-NTER],G,n); //the rule number going there might be wrong
			}
			else
			{
				ParseTree *internode=(ParseTree *)malloc(sizeof(ParseTree));
				internode = searchposition(head,stack[top]);
				//printf("Searched node = %s | Rule No: %d \n",terms[internode->value],T.table[X][a-NTER]);
				insert_in_tree(internode,T.table[X][a-NTER],G,n);
			}

			//fprintf(fs,"Entry exists in Parse Table\n");

			//fprintf(fs,"Rule no to use in grammar.txt: %d | X = %d | a-NTER = %d \n",T.table[X][a-NTER],X,a-NTER);

			pop();

			if(X==30 && a==63)
			{
				T.table[X][a-NTER]=55; // FOR COMMA IN idList_again
			}

			int glno=T.table[X][a-NTER];

			//fprintf(fs,"\nPushing these on stack now: \n");

			for(int f=29; f>0 ;f--)
			{
				if(G.gnum[glno][f]==-1 || G.gnum[glno][f]==EPS)
				{
					continue;
				}
				else
				{
					push(G.gnum[glno][f]);
					//fprintf(fs,"%s ",terms[G.gnum[glno][f]]);
				}
				//fprintf(fs,"\n");
			}
		}
		X=stack[top];
		//fprintf(fs,"\n");
	}
	if(stack[top]==3)
	{
		//fprintf(fs,"\nStack (TOP OF STACK IS LEFT MOST ELEMENT: \n");
		for(int i=top; i>=0; i--)
		{
			//fprintf(fs,"%s ",terms[stack[i]]);
		}
		ParseTree *internode=(ParseTree *)malloc(sizeof(ParseTree));
		internode = searchposition(head,stack[top]);
		//printf("Searched node = %s | Rule No: %d \n",terms[internode->value],6);
		insert_in_tree(internode,6,G,n);
		//fprintf(fs,"\n\n");
		pop();
		//fprintf(fs,"\notherModules not used hence popping it!\n\n");
	}
	if(stack[top]==DOL)
	{
		//fprintf(fs,"\nStack (TOP OF STACK IS LEFT MOST ELEMENT: \n");
		for(int i=top; i>=0; i--)
		{
			//fprintf(fs,"%s ",terms[stack[i]]);
		}
		//fprintf(fs,"\n");
		printf("\n\tParsing successfully for input file....!");
		//fprintf(fs,"\n\tParsing successfully for input file....!");
	}
}

void printParseTreeToFile(ParseTree *trav, FILE *f)
{
	if(trav == NULL)
	{
		return;
	}

	printParseTreeToFile(trav->child,f);

	char lexeme[30];
	char valueifnumber[30];
	char parent[30];
	char isleaf[5];
	char nodesymbol[30];

	if(trav->isleaf == 0)
        strcpy(isleaf, "No");
    else
        strcpy(isleaf, "Yes");

	if(trav->value>=NTER)
	{
		strcpy(lexeme,terms[trav->value]);
		strcpy(nodesymbol, "----");
	}
	else
	{
		strcpy(lexeme, "----");
		strcpy(nodesymbol,terms[trav->value]);	
	}

	if(trav->parent==NULL)
	{
		strcpy(parent,"ROOT");
	}
	else
	{
		strcpy(parent,terms[trav->parent->value]);
	}

	if(!strcmp(trav->n->t->token,"NUM") || !strcmp(trav->n->t->token,"RNUM"))
	{
		strcpy(valueifnumber,trav->n->t->value);
	}
	else
	{
		strcpy(valueifnumber,"----");
	}

	fprintf(f,"%s         %d       %s            %s            %s            %s            %s\n",lexeme,trav->n->t->lineno,trav->n->t->token,valueifnumber,parent,isleaf,nodesymbol);

	printParseTreeToFile(trav->right,f);
}

void printParseTree(FILE *f)
{
	//printf("\n%s",terms[head->child->right->right->value]);
	fprintf(f,"Lexeme        Line No        Node Token       ValueIfNumber     Parent       isleaf       Node Symbol\n");
	printParseTreeToFile(head,f);
	//printf("\n\n ** Random Term: %s ** \n\n",head->child->right->right->child->right->right->right->right->child->right->child->child->child->right->child->n->t->token);
}

/* END Primary Functions */

/* **************************************************************************** */