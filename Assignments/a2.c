
#include<stdio.h>
typedef struct tree
 {
   int data;
   struct tree *left;
   struct tree *right;
}node;
void printnodes(node *root)
{
    if(root->left==NULL)
    {
        printf("{%d",root->data);
        if(root->right==NULL)
        {
            printf("}");
            return;
        }
        printnodes(root->right);
        printf("}");
        return;
    }
    if(root->right==NULL)
    {
        printf("{%d}",root->data);
        if(root->left==NULL)
           return;
        printnodes(root->left);
        return;
    }
    printf("{%d",root->data);
    printnodes(root->left);
    printnodes(root->right);
    printf("}");
}
void insertnode(node **root,int ele)
 {
   if((*root)==NULL)
   {
      node *p;
      p=(node*) malloc(sizeof(node));
      p->data=ele;
      p->left=p->right=NULL;
      (*root)=p;
   }
  else
  {
    if(((*root)->data)>ele)
      insertnode(&(*root)->left,ele);
    else if(((*root)->data)<ele)
      insertnode(&(*root)->right,ele);
    else printf("THE DATA IS ALDREADY GIVEN\n");
  }
}
void printinorder(node *root)
{
    if(root->left!=NULL)
       printinorder(root->left);
    printf("%d ",root->data);
    if(root->right!=NULL)
       printinorder(root->right);
}
 void printpreorder(node *root)
{
    printf("%d ",root->data);
    if(root->left!=NULL)
       printpreorder(root->left);
    if(root->right!=NULL)
       printpreorder(root->right);
}
void searchsmallest(node *root,int x,int k)
{
  if((root->data>x)&&(root->left!=NULL))
    searchsmallest(root->left,x,root->data);
  else if((root->data>x)&&(root->left==NULL))
    printf("+++ search1(%d) : %d\n",x,root->data);
  else if(root->data==x)
    printf("+++ search1(%d) : %d\n",x,x);
     else if((root->data<x)&&(root->right!=NULL))
       searchsmallest(root->right,x,k);
  else if((root->data<x)&&(root->right==NULL))
    {
      if(k!=0)
        printf("+++ search1(%d) : %d\n",x,k);
      else
	printf("NO SUCH ELEMENT EXISTS WITH KNOWN CHARACTERS!!\n");
    }
}
void searchlargest(node *root,int y,int k)
{
  if((root->data>y)&&(root->left!=NULL))
    searchlargest(root->left,y,k);
  else if((root->data>y)&&(root->left==NULL))
    {
      if(k!=0)
        printf("+++ search2(%d) : %d\n",y,k);
      else
	printf("NO SUCH ELEMENT EXISTS WITH KNOWN CHARACTERS!!\n");
    }
  else if(root->data==y)
    printf("+++ search2(%d) : %d\n",y,y);
  else if((root->data<y)&&(root->right!=NULL))
    searchlargest(root->right,y,root->data);
  else if((root->data<y)&&(root->right==NULL))
    printf("+++ search2(%d) : %d\n",y,root->data);
}
void commonnode(node *root,int a,int b)
{
  if(root->data>a&&root->data>b)
    commonnode(root->left,a,b);
  else if(root->data<a&&root->data<b)
    commonnode(root->right,a,b);
  else
    printf("+++ lca(%d,%d) : %d\n",a,b,root->data);
}
node* min(node* root)
{
    while (root->left != NULL)
         root= root->left;
    return root;
}

node* deletenode(node **root,int a)
{
    node* head=(*root);
    while((*root)->data!=a)
    {
        if((*root)->data>a)
            (*root)=(*root)->left;
        else if((*root)->data<a)
            (*root)=(*root)->right;
    }
    if((*root)->right==NULL&&(*root)->left==NULL)
        (*root)=NULL;
    else if(((*root)->right==NULL)&&((*root)->left!=NULL))
        (*root)=(*root)->left;
    else if(((*root)->right!=NULL)&&((*root)->left==NULL))
        (*root)=(*root)->right;
    else
    {
        node *p = min((*root)->right);
        (*root)->data= p->data;
        deletenode(&(*root)->right, p->data);
    }
    return(head);
}
int main()
   {
     int i,x,y,ele,n,j,a,b;
     node *root=NULL;
     while(1)
       {
         printf("GIVE YOR ALTERNATIVE.\n1) PART 1:  \n2) PART 2: \n3) PART 3: \n4) PART 4: \n5) PART 5: \n6) PART 6: \n ");
         scanf("%d",&i);
         switch(i)
           {
            case 1:
              printf("ENTER THE NUMBER OF ELEMENTS\n");
              scanf("%d",&n);
              for(j=0;j<n;j++)
		       {
	             if(root==NULL)
                   printf("++ INSERT \n");
                 else
		           printf("++");
                   scanf("%d",&ele);
                   insertnode(&root,ele);
              }
              break;
            case 2:
	           printf("\nINORDER:  ");
               printinorder(root);
               printf("\nPREORDER:  ");
               printpreorder(root);
               printf("\n");
               printnodes(root);
               break;
	   case 3:
	     printf("ENTER THE VALUE OF x\n");
             scanf("%d",&x);
             searchsmallest(root,x,0);
             break;
           case 4:
             printf("ENTER THE VALUE OF y\n");
             scanf("%d",&y);
             searchlargest(root,y,0);
             break;
           case 5:
             printf("ENTER THE VALUES OF TWO NODES\n");
             scanf("%d %d",&a,&b);
             commonnode(root,a,b);
             break;
           case 6:
             printf("ENTER TEH VALUE OF THE ELEMENT TO BE DELETED\n");
             scanf("%d",&a);
             root=deletenode(&root,a);
             break;
           default:
             printf("ENTER A VALID OPTION\n");
             break;
          }
       }
 }
