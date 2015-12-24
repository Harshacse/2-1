/*NAME:PONNADA HARSHA VARDHAN
 ROLL: 14CS30022
 PC No: 27*/


#include<stdio.h>
void makeheap(int H[],int i,int n)                //it makes heap with root i
{
  int left,middle,right,greater=-1,temp;
  middle=3*i; left=middle-1; right=middle+1;      //left,right and middle are the childs.. greater is the index of the smallest element among the parent and children
  //calculates the smallesat index element
  if(left<=n)
    {
      if(H[left]<H[i])
        greater=left;
      else
	greater=i;
    }
  if(middle<=n)
    {
      if(H[middle]<H[greater])
        greater=middle;
    }
  if(right<=n)
    {
      if(H[right]<H[greater])
	greater=right;
    }
  //exchanges with index i
  if(greater!=-1&&greater!=i)
    {
      temp=H[greater];
      H[greater]=H[i];
      H[i]=temp;
      makeheap(H,greater,n);
    }
}

void buildheap(int H[],int n)
{
  int i;
  //the elements from n/3 to n are heaps as they are single elemts
  for(i=n/3;i>0;i--)
    makeheap(H,i,n);
}
void deletemin(int H[],int n)
{
  int greater,left=2,middle=3,right=4,i=1,temp;     //left,right and middle are the childs.. greater is the index of the smallest element among the parent and children
  temp=H[1]; H[1]=H[n];H[n]=temp;
  printf("%d ",H[n]);
  n--;
  while(1)
    {
      greater=-1;
      middle=3*i; left=middle-1; right=middle+1;
      if(left<=n)
	{
	  if(H[left]<H[i])
	    greater=left;
          else
	    greater=i;
	}
      if(middle<=n)
	{
	  if(H[middle]<H[greater])
	    greater=middle;
	}
      if(right<=n)
	{
	  if(H[right]<H[greater])
	    greater=right;
	}
      if(greater!=i&&greater!=-1)
	{
          temp=H[greater];
	  H[greater]=H[i];
	  H[i]=temp;
	  i=greater;
	  continue;
	}
      break;
    }
}
void insert(int H[],int n,int x);
void ksmallest(int H[],int n,int k)
{
  int x=n,i,value,j;
  //performs k delete mins
  for(i=0;i<k;i++)
    {
      deletemin(H,x);
      x--;
    }
  printf("\n");
  //makes k insertions
  for(i=0;i<k;i++)
    {
      value=H[x+1];
      insert(H,x,value);
      x++;
    }
}
void insert(int H[],int n,int x)
{
  H[n+1]=x;n++;
  int greater,left,middle,right,i,temp=n,temp1;
   while(temp>0)
    {
      i=temp/3;
      if(3*i+1<temp)
	i=i+1;
      if(i==0)
	break;
      if(H[i]>H[temp])
	{
	  temp1=H[i];
	  H[i]=H[temp];
	  H[temp]=temp1;
	  temp=i;
	  continue;
	}
      break;
    }
}
void printsmall(int H[],int n,int a,int i)
{
  int left,middle,right;
  if(i==1)
    {
      if(H[1]<=a)
	printf("%d ",H[1]);
      else
	return;
    }
  middle=3*i; left=middle-1; right=middle+1;
  if(H[left]<=a&&left<=n)
    {
      printf("%d ",H[left]);
      printsmall(H,n,a,left);
    }
  if(H[middle]<=a&&middle<=n)
    {
      printf("%d ",H[middle]);
      printsmall(H,n,a,middle);
    }
  if(H[right]<=a&&right<=n)
    {
      printf("%d ",H[right]);
      printsmall(H,n,a,right);
    }
}
int main()
{
  int H[100],n,i,j,k,a;
  printf("Give the size,n\n");
  scanf("%d",&n);
  printf("Reading elements\n");
  for(i=1;i<=n;i++)
    {
      scanf("%d",&H[i]);
    }
  buildheap(H,n);                                 //for building heap
  printf("---Heap after buildingheap():\n");
  for(i=1;i<=n;i++)
    printf("%d  ",H[i]);
  printf("\nEnter the value of k\n");
  scanf("%d",&k);
  printf("+++Finding the %d smallest elements in the heap\n",k);
  ksmallest(H,n,k);                              //for printing k smallest numbers
  printf("---Heap after ksmallest():\n");
  for(i=1;i<=n;i++)
    printf("%d  ",H[i]);
  printf("\nEnter the value of a\n");
  scanf("%d",&a);
  printsmall(H,n,a,1);
  printf("\n---Heap after printsmall():\n");
  for(i=1;i<=n;i++)
    printf("%d  ",H[i]);
}
