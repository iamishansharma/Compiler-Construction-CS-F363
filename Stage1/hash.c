/*  driver.c 
    
    Batch No: 14

    Members: 

    Ishan Sharma 2016B2A70773P
    Sarthan Sahu 2015B5A70749P
    Anirudh Garg 2017A7PS0142P
    Sanjeev Singla 2017A7PS0152P

*/

#include "hash.h"
#include <string.h>

int no_terms=0;
int no_terminals=0;
int no_nonterminals=0;

int hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % MOD;
}

bool isnont(int hashVal)
{
    int i=0;
    for(i=0; i<no_terms; i++)
    {
        if(hashVal==t[i].hashValue)
        {
            break;
        }
    }
    return t[i].nont;
}

int search(char *str,char **Hashtable)
{
    int hashValue = hash(str);

    while(Hashtable[hashValue])
    {
        if(~ strcmp(Hashtable[hashValue],str))
        {
            return 1;

        }
        else
        {
            hashValue++;
        }
    }
    return 0;
}

int insert(char *str,char **Hashtable)
{
    int hashValue = hash(str);

    if(search(str,Hashtable))
    {
        return hashValue;
    }

    while(Hashtable[hashValue])
    {
        hashValue++;
    }

    Hashtable[hashValue] = (char*)(malloc(sizeof(char)*strlen(str)));

    strcpy(Hashtable[hashValue],str);

    strcpy(t[no_terms].termname,str);

    if(str[0]>='a' && str[0]<='z')
    {
        t[no_terms].nont=true;
        no_nonterminals++;
    }
    else
    {
        t[no_terms].nont=false;
        no_terminals++;
    }

    t[no_terms].hashValue=hashValue;

    no_terms++;

    if(no_terms==110)
    {
        Hashtable[1301] = (char*)(malloc(sizeof(char)*strlen(str)));
        strcpy(Hashtable[1301],"SWITCH"); //dealing with switch conflict
        strcpy(t[110].termname,"SWITCH");
        t[110].nont=false;
        t[110].hashValue=1301;
        no_terms++;
        no_terminals++;
    }

    return hashValue;
}

void printTerms()
{   
    FILE *f=fopen("terms.txt","w");

    for(int i=0; i<no_terms; i++)
    {
        fprintf(f,"Term %d: \n",i);
        fprintf(f,"\n");
        fprintf(f,"\t%s",t[i].termname);
        fprintf(f,"\n\t%d",t[i].nont);
        fprintf(f,"\n\t%d\n",t[i].hashValue);
        fprintf(f,"\n");
    }
    fclose(f);
}
 
/*int hashcallparser(char *tosearch, Term t, int sizeofT)
{
    int hash=0;

    for(int i=0; i<sizeofT; i++)
        hash=insert(t[i].termname,TermTable);

    int retval=insert(tosearch,TermTable);

    return retval;
}

int hashcalllexer(char *tosearch, char **Keywords, int sizeofK)
{
    int hash=0;

    for(int i=0; i<sizeofK; i++)
        hash=insert(t[i].termname,KeywordTable);

    int retval=insert(tosearch,KeywordTable);

    return retval;
}*/