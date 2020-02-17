/*	lexer.c
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthan Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

#include "lexer.h"

/* ******************************************************* */

/* START Supporting Functions for Primary Functions */



/* END Supporting Functions for Primary Functions */

/* ******************************************************* */

/* START Primary Functions */

FILE *getStream(FILE *fp)
{
	if(fp==NULL)
	{
		printf("Cannot Open File!");
		exit(0);
	}
	return NULL;
}

void removeComments(char *testcaseFile, char *cleanFile)
{
	FILE *f1 = fopen(testcaseFile, "r");
	if(f1==NULL)
	{
		printf("Error opening file for removing comments!");
		return;
	}

	FILE *f2 = fopen(cleanFile, "w");
	if(f2==NULL)
	{
		printf("Error opening file for removing comments!");
		return;
	}

	char c; // Reading Character my character

	while(!feof(f1))
	{
		c = fgetc(f1); // Gets initial character

		if(c=='*')
		{
			c=fgetc(f1);

			if(c=='*')
			{
				while((c=fgetc(f1))!='*' && (c=fgetc(f1))!='*')
					continue; // ignore everything till double **

				c = fgetc(f1); // Gets the character after the last *
			}
		}

		fputc(c,f2);
	}

	fclose(f1);
	fclose(f2);
}

Node* getNextToken()
{
	return NULL;
}

/* END Primary Functions */

/* ******************************************************* */