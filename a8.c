#include<stdio.h>
#include<stdlib.h>
typedef struct greedy
{
    int pen,time;
} node;
typedef struct temporary
{
    int index;
    float ratio;
} new;
typedef struct part2
{
    int penalty[100],tim[100];
    int count,index;
    float ratio[100],mean[100];
} chain;
/*to merge the two arrays*/
void merge(new a[], int l, int m, int r)
{
    int i, j, k,n1=m-l+1,n2=r-m;
    /* create temp arrays */
    float L[n1],R[n1];
    int L1[n1],R1[n2];
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
    {
        L[i]= a[l + i].ratio;
        L1[i]= a[l + i].index;
    }
    for (j = 0; j < n2; j++)
    {
        R[j]=a[m + 1+ j].ratio;
        R1[j]=a[m + 1+ j].index;
    }
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k].ratio= L[i];
            a[k].index= L1[i];
            i++;
        }
        else
        {
            a[k].ratio= R[j];
            a[k].index= R1[j];
            j++;
        }
        k++;
    }
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        a[k].ratio= L[i];
        a[k].index= L1[i];
        i++;
        k++;
    }
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        a[k].ratio =R[j];
        a[k].index= R1[j];
        j++;
        k++;
    }
}
/* l is the left index and r is the right index of the array to be sorted */
void mergesort(new a[], int l, int r)
{
    int m=(r+l)/2;
    if(l>=r)
        return;
    mergesort(a, l, m);
    mergesort(a, m+1, r);
    merge(a, l, m, r);
}
void optnocons(node *head,int n)
{
    new temp[100],temp1[100];
    int sumt=0,sump=0,Obj=0,Time=0;
    int i;
    for(i=0; i<n; i++)
    {
        temp[i].ratio=(float)(head[i].pen)/(float)head[i].time;
        temp[i].index=i;
    }
    mergesort(temp,0,n-1);
    printf("+++The optimal solution is\n");
    for(i=n-1; i>-1; i--)
    {
        printf("Selecting Task %d: (%d,%d)\n",n-i,head[temp[i].index].pen,head[temp[i].index].time);
        Time+=head[temp[i].index].time;
        Obj+=(head[temp[i].index].pen)*Time;
    }
    printf("Minimized Objective function= %d",Obj);

    return;
}
chain* buildchains(node *head,int n,chain *chainhead,int m)
{
    int i,j,x;
    chainhead=(chain*)malloc(m*sizeof(chain));
    for(i=0; i<m; i++)
        chainhead[i].count=0;
    printf("Moving tasks to chains\n");
    for(i=0; i<n; i++)
    {
        scanf("%d",&x);
        chainhead[x].penalty[chainhead[x].count]=head[i].pen;
        chainhead[x].tim[chainhead[x].count]=head[i].time;
        (chainhead[x].count)++;
    }
    for(i=0; i<m; ++i)
    {
        printf("Chain %d:",i);
        for(j=0; j<chainhead[i].count; j++)
        {
            printf("%d ",chainhead[i].penalty[j]);
        }
        printf("\n        ");
        for(j=0; j<chainhead[i].count; j++)
        {
            printf("%d ",chainhead[i].tim[j]);
        }
        printf("\n");
    }
    return chainhead;
}
void optchain(node *head,int n,chain *chainhead,int m)
{
    int i,j,k=0,a,b,sump,sumt,x,y,Obj=0,Time=0;
    float maxmean,max;
    for(i=0; i<m; i++)
    {
        sump=sumt=0;
        for(j=0; j<chainhead[i].count; j++)
        {
            sump+=chainhead[i].penalty[j];
            sumt+=chainhead[i].tim[j];
            chainhead[i].mean[j]=(float)sump/(float)sumt;
        }
        chainhead[i].index=0;
    }
    while(k<n)
    {
        max=0;
        for(i=0; i<m; i++)
        {
            if(chainhead[i].index==chainhead[i].count)
                continue;
            maxmean=0.0;
            for(j=chainhead[i].index; j<chainhead[i].count; j++)
            {
                if(chainhead[i].mean[j]>maxmean)
                {
                    maxmean=chainhead[i].mean[j];
                    a=j;
                }
            }
            if(maxmean>max)
            {
                max=maxmean;
                x=i;
                y=a;
            }
        }
        for(i=chainhead[x].index; i<=y; i++)
        {
            printf("Selecting Task %d of Chain %d (%d,%d)\n",k,x,chainhead[x].penalty[i],chainhead[x].tim[i]);
            k++; Time+=chainhead[x].tim[i];
            Obj+=(chainhead[x].penalty[i])*Time;
        }
        chainhead[x].index+=(y-chainhead[x].index+1);
        sump=sumt=0;
        for(j=chainhead[x].index; j<chainhead[x].count; j++)
        {
            sump+=chainhead[x].penalty[j];
            sumt+=chainhead[x].tim[j];
            chainhead[x].mean[j]=(float)sump/(float)sumt;
        }
    }
    printf("Minimized Objective function= %d",Obj);
}
int main()
{
    int n,i,a,b,m;
    node *head;
    chain *chainhead;
    printf("Enter the value of n\n");
    scanf("%d",&n);
    head=(node*)malloc(n*sizeof(node));
    for(i=0; i<n; i++)
    {
        scanf("%d %d",&a,&b);
        head[i].pen=a;
        head[i].time=b;
    }
    printf("+++ Optimization without constraints\n");
    optnocons(head,n);
    printf("\nEnter the value of m\n");
    scanf("%d",&m);
    chainhead=buildchains(head,n,chainhead,m);
    optchain(head,n,chainhead,m);
    return 0;
}
