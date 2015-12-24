#include<stdio.h>
#include<math.h>
#include<string.h>
#define MAX_ITER_CN 10
#define MAX_REC_LEVEL 4
typedef struct t
{
    unsigned int s,t,a,b,n;
    char **string;
}hash;
hash init(hash table)
{
    int x;
    table.s=8;
    table.t=3;
    table.n=0;
    table.a=1;
    table.b=3;
    table.string=(char**)malloc((table.s)*sizeof(char*));
    for(x=0;x<table.s;x++)
        table.string[x]=NULL;
    return table;
}
unsigned int hashing(char str[],int c,int t);
int search(hash table,char str[])
{
    unsigned int i=hashing(str,table.a,table.t),j=hashing(str,table.b,table.t);
    if(table.string[i]==NULL)
        return 0;
    if(table.string[j]==NULL)
        return 0;
    if(!(strcmp(table.string[i],str)))
        return 1;
    if(!(strcmp(table.string[j],str)))
        return 1;
    return 0;
}
unsigned int hashing(char str[],int c,int t)
{
    unsigned int l=strlen(str),j,m1=0,m2=0,A;
    A=65791;
    for(j=0;j<l;j++)
      m2=A*m2+str[j];
    m2=m2*c;
    m2=m2>>(32-t);
    return m2;
}
hash rehash(hash table,int type,int *status);
hash insert(hash table,char *str,int level,int *status)
{
    hash table1,table2;
    int k,check,yes=1,no=0;
    unsigned int i,j;
    char *str1;
    str1=(char*)malloc(100*(sizeof(char*)));
    if(search(table,str))
    {
        i=hashing(str,table.a,table.t);
        j=hashing(str,table.b,table.t);
        printf("--- Insert(%s): (%d,%d): aldready present\n",str,i,j);
        return table;
    }
    for(k=0;k<MAX_ITER_CN;k++)
    {
        i=hashing(str,table.a,table.t);
        j=hashing(str,table.b,table.t);
        if(table.string[i]==NULL||table.string[j]==NULL)
        {
           if(table.string[i]==NULL)
           {
               table.string[i]=str;
               printf("--- Insert(%s): (%d,%d):insert at index %d: success\n",str,i,j,i);
               (status)=&yes;
               //printf("\n check: %s",table.string[i]);
           }
           else if(table.string[j]==NULL)
           {
               table.string[j]=str;
               printf("--- Insert(%s): (%d,%d):insert at index %d: success\n",str,i,j,j);
               (status)=&yes;
               //printf("\n check: %s",table.string[j]);
           }
           (table.n)++;
           if((float)table.n/(float)table.s>0.5)
           {
               printf("+++ High load factor(n=%d,s=%d). Rehashing necessary...\n",table.n,table.s);
               printf("Rehashing with doubled size %d\n",2*(table.s));
               table=rehash(table,0,&check);
               if(check==1)
               {
                   printf("Rehashing successful...\n");
                   return table;
               }
               else
                {
                    printf("Insertion failure\n");
                    status=&no;
                    return table;
                }
           }
           else
            return table;
        }
        else
        {
           str1=table.string[i];
           table.string[i]=str;
           table=insert(table,str1,0,0);
        }
    }
    if(level>=MAX_REC_LEVEL)
    {
        printf("Insertion failure\n");
        return;
    }
    else
    {
        table=rehash(table,1,&check);
        if(!(check))
        {
            table=rehash(table,0,&check);
            if(!(check))
            {
                printf("Insertion failure\n");
                return;
            }
        }
        else
            table=insert(table,str,level+1,0);
    }
  return table;
}
hash rehash(hash table,int type,int *status)
{
   int j,x,yes=1,no=0;
   status=&no;
   hash table1;
   char *str1;
   if(type)
     {

       table1.s=table.s;
       table1.t=table.t;
       table1.n=0;
       (table1.a)=(table.a)+2;
       (table1.b)=(table.b)+2;
       table1.string=(char**)malloc((table1.s)*sizeof(char*));
       for(x=0;x<table1.s;x++)
         table1.string[x]=NULL;
       for(j=0;j<table.s;j++)
       {
           if(table1.string[j]!=NULL)
           {
               str1=table.string[j];
               printf("Relocating (%s):(%d,%d): ",str1,hashing(str1,table.a,table.t),hashing(str1,table.b,table.t));
               table1=insert(table1,str1,11,status);
               if(!(*status))
                  printf("Rehashing is unsuccessful...\n");
           }
       }
       status=&yes;
       return table1;
     }
   else
     {
       table1.s=(table.s)*2;
       table1.t=(table.t)+1;
       table1.n=0;
       (table1.a)=(table.a);
       (table1.b)=(table.b);
       table1.string=(char**)malloc((table1.s)*sizeof(char*));
       for(x=0;x<table1.s;x++)
         table1.string[x]=NULL;
       for(j=0;j<table.s;j++)
        {
           if(table.string[j]!=NULL)
           {
               str1=table.string[j];
               printf("Relocating (%s):(%d,%d): ",str1,hashing(str1,table1.a,table1.t),hashing(str1,table1.b,table1.t));
               table1=insert(table1,str1,11,0);
           }
        }
       *status=1;
       return table1;
     }
 }
hash deleted(hash table,char str[])
 {
     int i=hashing(str,table.a,table.t),j=hashing(str,table.b,table.t);
     printf("+++ Delete(%s) : (%d,%d): ");
     if(!(strcmp(table.string[i],str)))
     {
        table.string[i]=NULL;
        printf("Deletion at index %d: SUCCESS\n",i);
        return table;
     }
     if(!(strcmp(table.string[i],str)))
     {
         table.string[j]=NULL;
         printf("Deletion at index %d: SUCCESS\n",j);
         return table;
     }
     printf("FAILURE\n");
     return table;
 }
int main()
{
  int ninit,i,j,nsearch,m,n,yes=0,no=0;
  char *arr;
  hash table;
  table=init(table);
  printf("ENTER THE VALUE OF ninit\n");
  scanf("%d",&ninit);
  printf("GIVE THE %d STRINGS\n",ninit);
  for(i=0;i<ninit;i++)
    {
      arr=(char*)malloc(100*sizeof(char));
      scanf("%s",arr);
      table=insert(table,arr,0,&no);
    }
  printf("GIVE THE VALUE OF nsearch\n");
  scanf("%d",&nsearch);
  printf("GIVE THE STRINGS\n");
  for(j=0;j<nsearch;j++)
    {
        scanf("%s",arr);
        m=hashing(arr,table.a,table.t);
        n=hashing(arr,table.b,table.t);
        if(search(table,arr))
        {
            printf("+++Search(%s):(%d,%d):SUCCESS",arr,m,n);
        }
        else
            printf("+++Search(%s):(%d,%d):FAILURE",arr,m,n);
    }
  printf("GIVE THE VALUE OF ndelete\n");
  scanf("%d",&nsearch);
  for(j=0;j<nsearch;j++)
  {
      scanf("%s",arr);
      table=deleted(table,arr);
  }

}
