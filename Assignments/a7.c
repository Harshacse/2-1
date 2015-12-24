#include<stdio.h>
#include<stdlib.h>
#include <time.h>
typedef struct uni
{
  struct uni *parent;                        //parent pointer
  int rank,path,flag;                        // rank is upper bound of height, flag is check whether the set ends?
}node;

node*** initboard(node ***b,int n)           //b is the two dimensional list of pointers
{
  int i,j;
  node *p;
  for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
	{
	  b[i][j]=(node*)malloc(sizeof(node));
	  b[i][j]->rank=b[i][j]->path=b[i][j]->flag=0;
	  b[i][j]->parent=NULL;
	}
    }
    return b;
}
node* findset(node* p)
{
  while(p->parent!=NULL)
  {
      p=p->parent;
  }
  return p;
}
void unionof(node **p,node **q)
{
    while((*p)->parent!=NULL)
    {
        (*p)=(*p)->parent;
    }
    /*while((*q)->parent!=NULL)
        (*q)=(*q)->parent;*/
    if((*p)->rank==(*q)->rank)
    {
      (*q)->parent=(*p);
      ((*p)->rank)=((*p)->rank)+1;
      return;
    }
    else if((*p)->rank<(*q)->rank)
    {
      (*p)->parent=(*q);
      return;
    }
    (*q)->parent=(*p);
}
int addpath(node ***b,int n)
{
  node *check,*temp;
  int i,j,x,y,k,l,f,h,c=0,choice,checker=0;
  f=h=rand()%(n*n);
  while(1)
    {
      if((h-f)%(n*n)==1)
	    return 0;     //failure
      i=f/n; j=f%n;
      if(findset(b[i][j])->rank!=0)
	  {
	      f=(f+1)%(n*n);
	      continue;
	  }
	  if(i+1<n)
      {
          if(findset(b[i+1][j])->rank==0)
          {
              k=i+1;l=j;
	          break;
          }
      }
      if(i-1>=0)
      {
          if(findset(b[i-1][j])->rank==0)
	      {
	          k=i-1;l=j;
	          break;
	      }
	  }
	  if(j+1<n)
      {
         if(findset(b[i][j+1])->rank==0)
	     {
	         k=i;l=j+1;
	         break;
	     }
	  }
	  if(j-1>=0)
      {
          if(findset(b[i][j-1])->rank==0)
          {
              k=i;l=j-1;
	          break;
          }
	  }
      f=(f+1)%(n*n);
      continue;
    }
    printf("New path: (%d,%d)",i,j);
  while(1)
    {
      printf(" (%d,%d)",k,l);
      check=findset(b[i][j]);
      unionof(&check,&b[k][l]);
      x=i;y=j;
      i=k;j=l;
      choice=rand()%4;
      checker=0;
      while(checker<4)
      {
          switch(choice)
          {
          case 0:
            k=i;l=j-1;
            if(l>=0&&(k!=x||l!=y))
            {
               check=findset(b[i][j]);
               temp=findset(b[k][l]);
               c=0;
               if(temp->rank==0)
               {
	             if(k+1<n)
                 {
                    if(findset(b[k+1][l])!=check)
                     c++;
                 }
                 else
                   c++;
                 if(k-1>=0)
                 {
                    if(findset(b[k-1][l])!=check)
                     c++;
                 }
                 else
                   c++;
                 if(l-1>=0)
                 {
                    if(findset(b[k][l-1])!=check)
                     c++;
                 }
                 else
                   c++;
                 if(c!=3)
                   {
                       checker++;
                       choice=(choice+1)%4;
                       continue;
                   }
	           }
	           else
               {
                   checker++;
                   choice=(choice+1)%4;
                   continue;
               }
	           if(c==3)
                break;
            }
            else
            {
                checker++;
                choice=(choice+1)%4;
                continue;
            }
            if(checker==4)
                break;
          case 1:
            k=i;l=j+1;
            if(l<n&&(k!=x||l!=y))
            {
             check=findset(b[i][j]);
             temp=findset(b[k][l]);
             c=0;
             if(temp->rank==0)
             {
	            if(k+1<n)
                {
                    if(findset(b[k+1][l])!=check)
                        c++;
                }
                else
                c++;
                if(k-1>=0)
                {
                    if(findset(b[k-1][l])!=check)
                    c++;
                }
                else
                c++;
                if(l+1<n)
                {
                    if(findset(b[k][l+1])!=check)
                    c++;
                }
                else
                c++;
                if(c!=3)
                {
                    checker++;
                    choice=(choice+1)%4;
                    continue;
                }
              }
              else
              {
                checker++;
                choice=(choice+1)%4;
                continue;
              }
              if(c==3)
                break;
            }
            else
            {
               checker++;
               choice=(choice+1)%4;
               continue;
            }
            if(checker==4)
                break;
          case 2:
            k=i+1;l=j;
            if(k<n&&(k!=x||l!=y))
            {
              check=findset(&b[i][j]);
              temp=findset(&b[k][l]);
              c=0;
              if(temp->rank==0)
              {
	            if(k+1<n)
                {
                    if(findset(b[k+1][l])!=check)
                        c++;
                }
                else
                c++;
                if(l-1>=0)
                {
                    if(findset(b[k][l-1])!=check)
                    c++;
                }
                else
                c++;
                if(l+1<n)
                {
                    if(findset(b[k][l+1])!=check)
                    c++;
                }
                else
                c++;
                if(c!=3)
                {
                    checker++;
                    choice=(choice+1)%4;
                    continue;
                }
              }
              else
              {
                checker++;
                choice=(choice+1)%4;
                continue;
              }
              if(c==3)
                break;
            }
           else
            {
               checker++;
               choice=(choice+1)%4;
               continue;
            }
            if(checker==4)
                break;
          case 3:
            k=i-1;l=j;
            if(k>=0&&(k!=x||l!=y))
            {
              check=findset(b[i][j]);
              temp=findset(b[k][l]);
              c=0;
              if(temp->rank==0)
              {
	            if(l-1>=0)
                {
                    if(findset(b[k][l-1])!=check)
                        c++;
                }
                else
                c++;
                if(k-1>=0)
                {
                    if(findset(b[k-1][l])!=check)
                    c++;
                }
                else
                c++;
                if(l+1<n)
                {
                    if(findset(b[k][l+1])!=check)
                    c++;
                }
                else
                c++;
                if(c!=3)
                {
                    checker++;
                    choice=(choice+1)%4;
                    continue;
                }
              }
              else
              {
                checker++;
                choice=(choice+1)%4;
                continue;
              }
              if(c==3)
                break;
            }
            else
            {
               checker++;
               choice=(choice+1)%4;
               continue;
            }
            if(checker==4)
                break;
          }
        if(checker==4)
          break;
        if(c==3)
          break;
      }
      if(c==3)
        continue;
      b[i][j]->flag=1;
      printf("\n");
      break;
    }
  return 1;
 }

void addpathnum(node*** b,int n)
{
    int i,j,k=1;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(findset(b[i][j])->rank==0)
                continue;
            if(findset(b[i][j])->path==0)
            {
                findset(b[i][j])->path=k;
                b[i][j]->path=k;
                k++;
            }
            else
                b[i][j]->path=findset(b[i][j])->path;
        }
    }
}
void dash(int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("+-----");
    printf("+\n");
}
void trail(node ***b,int n)
{
    int i,j;
    for(j=0;j<n;j++)
    {
        for(i=0;i<n;i++)
        {
            printf("%d ",b[i][j]->path);
        }
        printf("\n");
    }
}
void printboard(node*** b,int n)
{
    int i,j;
    printf("\n\n\n+++ The puzzle generated with your dimension %d is:\n",n);
    for(j=0;j<n;j++)
    {
        dash(n);
        for(i=0;i<n;i++)
        {
            if(b[i][j]->path==0)
            {
                printf("|xxxxx");
                continue;
            }
            else if(findset(b[i][j])==b[i][j])
                printf("|  %d  ",b[i][j]->path);
            else if(b[i][j]->flag==1)
                printf("|  %d  ",b[i][j]->path);
            else
                printf("|     ");
        }
        printf("|\n");
    }
    dash(n);
}
void printsol(node ***b,int n)
{
    int i,j;
    printf("+++ The solution\n");
    for(j=0;j<n;j++)
    {
        dash(n);
        for(i=0;i<n;i++)
        {
            if(b[i][j]->path==0)
            {
                printf("|xxxxx");
                continue;
            }
            printf("|  %d  ",b[i][j]->path);
        }
        printf("|\n");
    }
    dash(n);
}
int main()
{
  srand((unsigned int)time(NULL));
  node ***b,*p;                                            // bis the two dimensional list of pointers
  int i,j,n;
  printf("Give the value of n,the dimension of the board?\n");
  scanf("%d",&n);
  b=(node***)malloc(n*sizeof(node**));                        // allocating memory to b
  for(i=0;i<n;i++)
    b[i]=(node**)malloc(n*sizeof(node*));                    // allocating memory to b
  printf("+++ Initializing board...\n");
  b=initboard(b,n);                                         //initializing the parameters in b
  printf("+++ Attempting to add new paths...\n");
  while(1)
  {
      if(addpath(b,n)==1)                                   //adding paths in b
        continue;
      break;
  }
  printf("+++ Assigning path numbers...\n");
  addpathnum(b,n);
  trail(b,n);                                        //assigning path numbers to b
  printboard(b,n);
  printf("\n\nWanna see the Solution? enter 1\n");
  scanf("%d",&i);
  if(i==1)
     printsol(b,n);                                       //printing b
}
