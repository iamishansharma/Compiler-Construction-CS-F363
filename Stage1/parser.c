/*	parser.c 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "parser.h"
#include "hash.h"

char *TermTable[1007];

int no_nont=100; 	// no of non terminals
int no_t=59; 		// no of terminals - 55 in LangSepc + <<< + >>> + epsilon as "esp" + "$" = 59
int no_rules=100; 	// total no of grammar rules

int stack[100];
int stack_max=99; 	//max value for indexing stack
int top=-1; 		// top pointer

Term t[111];


/* HARD CODE the terms here*/
/*
	strcpy(t[0].termname,"$");
	t[0].nont=false;

	// Non-Terminals 

	strcpy(t[1].termname,"program");
	t[1].nont=true;

	strcpy(t[2].termname,"moduleDeclarations");
	t[2].nont=true;

	strcpy(t[3].termname,"moduleDeclaration");
	t[3].nont=true;

	strcpy(t[4].termname,"otherModules");
	t[4].nont=true;

	strcpy(t[5].termname,"driverModule");
	t[5].nont=true;

	strcpy(t[6].termname,"module");
	t[6].nont=true;

	strcpy(t[7].termname,"ret");
	t[7].nont=true;

	strcpy(t[8].termname,"input_plist");
	t[8].nont=true;

	strcpy(t[9].termname,"input_plist_again");
	t[9].nont=true;

	strcpy(t[10].termname,"output_plist");
	t[10].nont=true;

	strcpy(t[11].termname,"output_plist_again");
	t[11].nont=true;

	strcpy(t[12].termname,"dataType");
	t[12].nont=true;

	strcpy(t[13].termname,"type");
	t[13].nont=true;

	strcpy(t[14].termname,"moduleDef");
	t[14].nont=true;

	strcpy(t[15].termname,"statements");
	t[15].nont=true;

	strcpy(t[16].termname,"statement");
	t[16].nont=true;

	strcpy(t[17].termname,"ioStmt");
	t[17].nont=true;

	strcpy(t[18].termname,"whichId");
	t[18].nont=true;

	strcpy(t[19].termname,"simpleStmt");
	t[19].nont=true;

	strcpy(t[20].termname,"assignmentStmt");
	t[20].nont=true;

	strcpy(t[21].termname,"whichStmt");
	t[21].nont=true;

	strcpy(t[22].termname,"lvalueIDStmt");
	t[22].nont=true;

	strcpy(t[23].termname,"lvalueARRStmt");
	t[23].nont=true;

	strcpy(t[24].termname,"index");
	t[24].nont=true;

	strcpy(t[25].termname,"moduleReuseStmt");
	t[25].nont=true;

	strcpy(t[26].termname,"optional");
	t[26].nont=true;

	strcpy(t[27].termname,"idList");
	t[27].nont=true;

	strcpy(t[28].termname,"idList_again");
	t[28].nont=true;

	strcpy(t[29].termname,"expression");
	t[29].nont=true;

	strcpy(t[30].termname,"unary");
	t[30].nont=true;

	strcpy(t[31].termname,"arithmeticOrBooleanExpr");
	t[31].nont=true;

	strcpy(t[32].termname,"arithmeticOrBooleanExpr_again");
	t[32].nont=true;

	strcpy(t[33].termname,"recTerm");
	t[33].nont=true;

	strcpy(t[34].termname,"recTerm_again");
	t[34].nont=true;

	strcpy(t[35].termname,"arithmeticExpr");
	t[35].nont=true;

	strcpy(t[36].termname,"arithmeticExpr_again");
	t[36].nont=true;

	strcpy(t[37].termname,"term");
	t[37].nont=true;

	strcpy(t[38].termname,"term_again");
	t[38].nont=true;

	strcpy(t[39].termname,"factor");
	t[39].nont=true;

	strcpy(t[40].termname,"var");
	t[40].nont=true;

	strcpy(t[41].termname,"booleanConstants");
	t[41].nont=true;

	strcpy(t[42].termname,"prec2_op");
	t[42].nont=true;

	strcpy(t[43].termname,"prec1_op");
	t[43].nont=true;

	strcpy(t[44].termname,"logicalOp");
	t[44].nont=true;

	strcpy(t[45].termname,"relationalOp");
	t[45].nont=true;

	strcpy(t[46].termname,"declareStmt");
	t[46].nont=true;

	strcpy(t[47].termname,"conditionalStmt");
	t[47].nont=true;

	strcpy(t[48].termname,"caseStmts");
	t[48].nont=true;

	strcpy(t[49].termname,"caseStmts_again");
	t[49].nont=true;

	strcpy(t[50].termname,"value");
	t[50].nont=true;

	strcpy(t[51].termname,"default");
	t[51].nont=true;

	strcpy(t[52].termname,"iterativeStmt");
	t[52].nont=true;

	strcpy(t[53].termname,"range");
	t[53].nont=true;

	// Terminals 

	strcpy(t[54].termname,"AND");
	t[54].nont=false;;

	strcpy(t[55].termname,"ARRAY");
	t[55].nont=false;;

	strcpy(t[56].termname,"ASSIGNOP");
	t[56].nont=false;;

	strcpy(t[57].termname,"BC");
	t[57].nont=false;;

	strcpy(t[58].termname,"BO");
	t[58].nont=false;;

	strcpy(t[59].termname,"BOOLEAN");
	t[59].nont=false;

	strcpy(t[60].termname,"BREAK");
	t[60].nont=false;

	strcpy(t[61].termname,"CASE");
	t[61].nont=false;

	strcpy(t[62].termname,"COLON");
	t[62].nont=false;

	strcpy(t[63].termname,"COMMA");
	t[63].nont=false;

	strcpy(t[64].termname,"DECLARE");
	t[64].nont=false;

	strcpy(t[65].termname,"DEF");
	t[65].nont=false;

	strcpy(t[66].termname,"DEFAULT");
	t[66].nont=false;

	strcpy(t[67].termname,"DIV");
	t[67].nont=false;

	strcpy(t[68].termname,"DRIVER");
	t[68].nont=false;

	strcpy(t[69].termname,"DRIVERDEF");
	t[69].nont=false;

	strcpy(t[70].termname,"DRIVERENDDEF");
	t[70].nont=false;

	strcpy(t[71].termname,"END");
	t[71].nont=false;

	strcpy(t[72].termname,"ENDDEF");
	t[72].nont=false;

	strcpy(t[73].termname,"EQ");
	t[73].nont=false;

	strcpy(t[74].termname,"FALSE");
	t[74].nont=false;

	strcpy(t[75].termname,"FOR");
	t[75].nont=false;

	strcpy(t[76].termname,"GE");
	t[76].nont=false;

	strcpy(t[77].termname,"GET_VALUE");
	t[77].nont=false;

	strcpy(t[78].termname,"GT");
	t[78].nont=false;

	strcpy(t[79].termname,"ID");
	t[79].nont=false;

	strcpy(t[80].termname,"IN");
	t[80].nont=false;

	strcpy(t[81].termname,"INPUT");
	t[81].nont=false;

	strcpy(t[82].termname,"INTEGER");
	t[82].nont=false;

	strcpy(t[83].termname,"LE");
	t[83].nont=false;

	strcpy(t[84].termname,"LT");
	t[84].nont=false;

	strcpy(t[85].termname,"MINUS");
	t[85].nont=false;

	strcpy(t[86].termname,"MODULE");
	t[86].nont=false;

	strcpy(t[87].termname,"MUL");
	t[87].nont=false;

	strcpy(t[88].termname,"NE");
	t[88].nont=false;

	strcpy(t[89].termname,"NUM");
	t[89].nont=false;

	strcpy(t[90].termname,"OF");
	t[90].nont=false;

	strcpy(t[91].termname,"OR");
	t[91].nont=false;

	strcpy(t[92].termname,"PARAMETERS");
	t[92].nont=false;

	strcpy(t[93].termname,"PLUS");
	t[93].nont=false;

	strcpy(t[94].termname,"PRINT");
	t[94].nont=false;

	strcpy(t[95].termname,"PROGRAM");
	t[95].nont=false;

	strcpy(t[96].termname,"RANGEOP");
	t[96].nont=false;

	strcpy(t[97].termname,"REAL");
	t[97].nont=false;

	strcpy(t[98].termname,"RETURNS");
	t[98].nont=false;

	strcpy(t[99].termname,"RNUM");
	t[99].nont=false;

	strcpy(t[100].termname,"SEMICOL");
	t[100].nont=false;

	strcpy(t[101].termname,"SQBC");
	t[101].nont=false;

	strcpy(t[102].termname,"SQBO");
	t[102].nont=false;

	strcpy(t[103].termname,"START");
	t[103].nont=false;

	strcpy(t[104].termname,"SWITCH");
	t[104].nont=false;

	strcpy(t[105].termname,"TAKES");
	t[105].nont=false;

	strcpy(t[106].termname,"TRUE");
	t[106].nont=false;

	strcpy(t[107].termname,"USE");
	t[107].nont=false;

	strcpy(t[108].termname,"WHILE");
	t[108].nont=false;

	strcpy(t[109].termname,"WITH");
	t[109].nont=false;

	strcpy(t[110].termname,"EPSILON");
	t[110].nont=false;
*/
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

	int rule_no=0;

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
				if(!((word[g][x]>='a') && (word[g][x]<='z') || (word[g][x]>='A') && (word[g][x]<='Z')))
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

			//fprintf(f2,"%s",toinsert);

			int hashVal=insert(toinsert,TermTable);
			fprintf(f2,"%d ",hashVal);
			//G.gnum[rule_no][g]=hashVal;
		}

		fprintf(f2,"\n");

		//G.gnum[rule_no][g]=-1;
		//rule_no++;
	}
	fclose(f);
	fclose(f2);
	return G;
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
		if(F.first[nonterminal][i]==/*value of "eps"*/111)
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

/* END Supporting Functions for Primary Functions */

/* **************************************************************************** */

/* START Primary Functions */

FirstAndFollow ComputeFirstAndFollowSets(Grammar G, FirstAndFollow F)
{
	return F;
}

void createParseTable(FirstAndFollow F, ParseTable T)
{
	//Initialising table

	for(int i=0; i<no_nont; i++)
	{
		for(int j=0; j<no_t; j++)
		{
			T.table[i][j]=-2;
		}
	}

	/*
		Parse Table - 

		Non terminals x Terminals 

							$ INTEGER REAL BOOLEAN ... AND SO ON
		<program>
		<moduleDeclations>

		etc 

		1. do this for very terminal- 

			if $ is in FIRST(program) - 

				put value of table[0][0]=rule_no; //Rule number of <program>

			//start of terminals is at index 53
		
		2. if eps is in FIRST(program) - 

			put rule_no //Rule Number of program in 
			every terminal that is in FOLLOW(program)
	*/

	for(int nt=0; nt<no_nont; nt++)
	{
		for(int ter=53; ter<112; ter++)
		{
			if(isinFIRST(F,nt,ter))
			{
				T.table[nt][ter-53]=nt; // rule value is same as nt value;
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
}

void parseInputSourceCode(char *testcaseFile, ParseTable T)
{
	
}

void printParseTree(ParseTree PT, char *outfile)
{
	FILE *f=fopen(outfile,"w");

	if(f==NULL)
	{
		printf("Cannot open Parse Tree print file!");
		exit(1);
	}
}

/* END Primary Functions */

/* **************************************************************************** */