#include<stdio.h>
#define INFINITY 1234567890
#define CAPACITY 100

void packpos(int a[],int m)
{
  int i,cartoono=1,sum=0,x=0;
  for(i=0;i<m;i++)
    {
      sum+=a[i];
      if(sum>100)
	{
	  printf("Carton %d: Packing A[%d ... %d]: Total cost = %d\n",cartoono,x,i-1,sum-a[i]);
	  cartoono++;
	  x=i;
	  sum=a[i];
	}
    }
  printf("Carton %d: Packing A[%d ... %d]: Total cost = %d\n",cartoono,x,i-1,sum);
  printf("*** Total number of cartons needed = %d\n",cartoono);
}
int calculate(int  b[],int **c,int i,int j,int m)
{
  int sum;
  if(i==j)
    return b[i];
  if(c[i][j]!=0)
    return c[i][j];
  return c[i][j-1]+b[j];
}

//+++The recursive function I am using is c[i][j]=c[i][j-1]+b[j]
void packposnegdone(int b[],int m)
{
  int i,j,**c,**a,cartonno=0,sum,x;
  c=(int**)malloc(m*sizeof(int*));
  a=(int**)malloc(m*sizeof(int*));
  for(i=0;i<m;i++)
    {
      c[i]=(int*)malloc(m*sizeof(int));
      a[i]=(int*)malloc(m*sizeof(int));
    }
  for(i=0;i<m;i++)
    {
      for(j=i;j<m;j++)
	{
	  c[i][j]=a[i][j]=0;
	  c[i][j]=calculate(b,c,i,j,m);
	}
    }
  i=0;
  while(i<m)
    {
      for(j=i;j<m;j++)
	{
          if(c[i][j]<=100)
	    {
	      x=j;
	    }
	}
      cartonno++;
      printf("Carton %d: Packing A[%d ... %d]: Total cost = %d\n",cartonno,i,x,c[i][x]);
      i=x+1;
    }
  printf("*** Total number of cartons needed = %d\n",cartonno);
}
void packposneg ( int *A, int m )
{
   int *T, *S;
   int i, j, k, c;

   printf("\n+++ Packing items of both positive and negative costs\n");

   T = (int *)malloc((m + 1) * sizeof(int));
   S = (int *)malloc((m + 1) * sizeof(int));
   T[m] = S[m] = 0; /* No cartons are needed to pack A[m,m-1] */

   /* Populate T[i] and S[i] for i=m-1,m-2,...,1,0 (in that order) */
   for (i=m-1; i>=0; --i) {
      c = 0; T[i] = INFINITY; S[i] = -1;
      for (j=i; j<m; ++j) {  /* Look up to the end of A[] */
         c += A[j];
         if ((c <= CAPACITY) && (1 + T[j+1] <= T[i])) { /* Better packing found */
            T[i] = 1 + T[j+1];
            S[i] = j;
         }
      }
   }

   /* Print an optimal solution. S[] gives an optimal packing for each carton. */
   i = j = 0;
   while (i < m) {
      ++j;
      c = 0; for (k=i; k<=S[i]; ++k) c += A[k];
      printf("    Carton %2d: Packing A[%-2d ... %2d]: Total cost = %d\n", j, i, S[i], c);
      i = S[i] + 1;
   }

   printf("*** Total number of cartons needed = %d\n", T[0]);
}
int main()
{
  int m,i,a[100],b[100];
  printf("Enter thr value of m\n");
  scanf("%d",&m);
  printf("+++ Input array with positive entries\n");
  for(i=0;i<m;i++)
    {
      scanf("%d",&a[i]);
     }
  printf("+++ Packing items of positive costs\n");
  packpos(a,m);
  printf("+++ Input array with positive and negative entries\n");
  for(i=0;i<m;i++)
    scanf("%d",&b[i]);
  packposneg(b,m);
}
