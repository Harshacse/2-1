#include<stdio.h>
#include<stdlib.h>
typedef struct heap
{
    int priority,min;
}maxheap;
void dash()
{
    int i;
    for(i=0;i<15;i++)
        printf("-");
    printf("\n");
}
void makeheap(maxheap array[],int i,int n)
{
    int leftchild=2*i,rightchild=2*i+1,greater,temp1;
    if(leftchild<=n&&array[leftchild].priority>array[i].priority)
        greater=leftchild;
    else
        greater=i;
    if(rightchild<=n&&array[rightchild].priority>array[greater].priority)
        greater=rightchild;
    if(greater!=i)
    {
        temp1=array[greater].priority;
        array[greater].priority=array[i].data;
        array[i].priority=temp1;
        makeheap(array,greater,n);
    }
}
int* initindex(maxheap array[],int n)
{
    int i,j;
    int indexarray[100];
    int *p=indexarray;
    for(i=1;i<=n;i++)
        indexarray[array[i].index]=i;
    return p;
}

void printheap(maxheap array[],int n)
{
    int i;
    for(i=1;i<=n;i++)
        printf("(%d,%d) ",array[i].index,array[i].pr);
    printf("\n");
}
void printarray(int array[],int n)
{
    int i;
    for(i=1;i<=n;i++)
        printf("%d(%d) ",array[i],i-1);
    printf("\n");
}
void upvote(maxheap array[],int index)
{
    (array[index].data)=array[index].data+1;
    int temp=index,temp1,temp2;
    while(array[index/2].data<array[index].data)
    {
        temp1=array[index].data;
        temp2=array[index].index;
        array[index].data=array[index/2].data;
        array[index].index=array[index/2].index;
        array[index/2].data=temp1;
        array[index/2].index=temp2;
        index/=2;
        if(index==1)
            break;
    }
}
void downvote(maxheap array[],int index,int n)
{
    int temp=index,temp1,temp2,leftchild=2*index,rightchild=2*index+1,greater,check=0;
    if(array[index].data==0)
        return;
    (array[index].data)=(array[index].data)-1;
    while(1)
    {
        if(leftchild>n)
            break;
        if(leftchild<=n&&array[leftchild].data>array[index].data)
           greater=leftchild;
        else
           greater=index;
        if(rightchild<=n&&array[rightchild].data>array[greater].data)
        greater=rightchild;
        if(greater!=index)
        {
            temp1=array[greater].data;
            temp2=array[greater].index;
            array[greater].data=array[index].data;
            array[greater].index=array[index].index;
            array[index].data=temp1;
            array[index].index=temp2;
            check=1;
        }
        if(check)
            break;
    }
}



int main()
{
    maxheap array[100];
    int i,n,tempindex,indexarray[100],*p,temp2,check=0;
    printf("ENTER THE VALUE OF n\n");
    scanf("%d",&n);
    printf("GIVE THE RATINGS OF THE %d IMAGES\n",n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&array[i].data);
        //array[i].data=rand()%15;
        array[i].index=i-1;
        printf(" ratings for image %d\n",i);
    }
    printf("CURRENT HEAP(%d nodes)\n      ",n);
    printheap(array,n);
    for(i=n/2;i>=1;i--)
        makeheap(array,i,n);
    dash();
    printf("\nCURRENT HEAP(%d nodes)\n      ",n);
    printheap(array,n);
    printf("check!! %d",array[1].index);
    p=initindex(array,n);
    printf("\nCURRENT INDEX ARRAY(%d nodes)\n      ",n);
    printarray(p,n);
    while(1)
    {
        printf("ENTER YOUR ALTERNATIVE\n1) UP-VOTE\n2) DOWN-VOTE\n3) DELETE\n4) INSERT\n");
        scanf("%d",&i);
        switch(i)
        {
        case 1:
            printf("GIVE THE VALUE OF INDEX\n");
            scanf("%d",&tempindex);
            printf("Operation: upvote(%d)\n",tempindex);
            p=initindex(array,n);
            upvote(array,p[tempindex]);
            printheap(array,n);
            dash();
            break;
        case 2:
            printf("GIVE THE VALUE OF INDEX\n");
            scanf("%d",&tempindex);
            printf("Operation: downvote(%d)\n",tempindex);
            p=initindex(array,n);
            downvote(array,p[tempindex],n);
            printheap(array,n);
            dash();
            break;
        case 3:
            break;
        case 5:
            check=5;
            break;
        }
        if(check==5)
            break;
    }
}
