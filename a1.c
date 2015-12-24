#include<stdio.h>
int main()
{
  int a[100],i,j=0,n,k,tot=0,l;
  printf("ENTER THE LENGTH OF THE ARRAY, THE VALUE OF n\n");
  scanf("%d",&n);
  printf("ENTER THE ELEMENTS OF THE ARRAY\n");
  for(i=0;i<n;i++)
    {
      scanf("%d",&a[i]);
    }
  printf("ENTER THE VALUE OF THE REQUIRED SUM\n");
  scanf("%d",&k);
  for(i=0;i<n;)
    {
      if(tot>k)
        {
          tot-=a[j];
          j++;
          continue;
        }
      else if(tot==k)
        {
          printf("+++ Sub array found...\n");
          for(l=j;l<i;l++)
              printf("%d  ",a[l]);
          printf("\n");
          printf("IT IS FROM %d TO %d\n",a[j],a[i-1]);
	  return;
        }
      tot+=a[i];
      i++;
    }
  if(tot==k)
  {
      printf("+++ Sub array found...\n");
      for(l=j;l<i;l++)
        printf("%d  ",a[l]);
      printf("\n");
  }
  printf("NO MATCH FOUND\n");

}
