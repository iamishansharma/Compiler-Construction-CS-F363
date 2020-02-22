#include "hash.h"

#define MOD 1007

int hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % MOD;
}

int search(char *str,char **Hashtable)
{
    int hashValue = hash(str);
    //printf("in serach %d \n",hashValue);
    while(Hashtable[hashValue])
    {
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

    printf("FI: %s ",str);

    if(search(str,Hashtable))
    {
        //printf("Found!");
        printf("FI: %d\n",hashValue);
        return hashValue;
    }
    //printf("in insert %d \n",hashValue);
    while(Hashtable[hashValue])
    {
        hashValue++;
    }

    Hashtable[hashValue] = (char *)(malloc(sizeof(char)*strlen(str)));
    strcpy(Hashtable[hashValue],str);
    printf("FI: %d\n",hashValue);
    return hashValue;
    //printf("%s",Hashtable[hashValue]);
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