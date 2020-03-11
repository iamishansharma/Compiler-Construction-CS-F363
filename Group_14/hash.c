/*  driver.c 
    
    Batch No: 14

    Members: 

    Ishan Sharma 2016B2A70773P
    Sarthak Sahu 2015B5A70749P
    Anirudh Garg 2017A7PS0142P
    Sanjeev Singla 2017A7PS0152P

*/

#include "hash.h"
#include <string.h>

int no_terms=0;
int no_terminals=0;
int no_nonterminals=0;

int terminalarray[58];

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

/*int search(char *str,char **Hashtable)
{
    //printf("IN SAEACH: %s; \n",str);

    int hashValue = hash(str);

    printf("IN SAEACH: %s; %d; %s \n",str,hashValue,Hashtable[hashValue]);

    while(Hashtable[hashValue])
    {
        if(strcmp(Hashtable[hashValue],str)==0)
        {
            return 1;

        }
        else
        {
            hashValue++;
        }
    }

    if(strcmp(Hashtable[hashValue],str)==0)
    {
        return 1;
    }
    return 0;
}*/

int search(char *str,char **Hashtable){
    int hashValue = hash(str);
    printf("IN SAEACH: %s; %d; %s \n",str,hashValue,Hashtable[hashValue]);
    while(Hashtable[hashValue]){
        if(~ strcmp(Hashtable[hashValue],str)){
            return 1;
        }else{
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
        //printf("Found!");
        return hashValue;
    }
    //printf("in insert %d \n",hashValue);
    while(Hashtable[hashValue])
    {
        hashValue++;
    }

    Hashtable[hashValue] = (char *)(malloc(sizeof(char)*strlen(str)));

    strcpy(Hashtable[hashValue],str);

    //printf("IN INSERT: %s \n",Hashtable[hashValue]);

    return hashValue;
}

/*int insert(char *str,char **Hashtable)
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

    return hashValue;
}*/

void printTerms()
{   
    FILE *f=fopen("terms.txt","w");

    //printta();

    for(int i=0; i<no_terms; i++)
    {
        if(t[i].nont==1)
        {
            /*fprintf(f,"Term %d: \n",i);
            fprintf(f,"\n");
            fprintf(f,"\t%s",t[i].termname);
            fprintf(f,"\n\t%d",t[i].nont);
            fprintf(f,"\n\t%d\n",t[i].hashValue);
            fprintf(f,"\n");*/
            fprintf(f,"\"%s\",\n",t[i].termname);
        }
    }
    for(int i=0; i<no_terms; i++)
    {
        if(t[i].nont==0)
        {
            /*fprintf(f,"Term %d: \n",i);
            fprintf(f,"\n");
            fprintf(f,"\t%s",t[i].termname);
            fprintf(f,"\n\t%d",t[i].nont);
            fprintf(f,"\n\t%d\n",t[i].hashValue);
            fprintf(f,"\n");*/
            fprintf(f,"\"%s\",\n",t[i].termname);
        }
    }
    fclose(f);
}

void printta()
{
    FILE *f=fopen("ta.txt","w");

    for(int i=0; i<58; i++)
    {
        fprintf(f,"%d\n",terminalarray[i]);
    }
}

int searchinta(int checkval)
{
    for(int i=0; i<58; i++)
    {
        if(terminalarray[i]==checkval)
        {
            return i;
        }
    }
    return -1;
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