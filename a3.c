#include<stdio.h>
#include<math.h>
typedef struct tree
{
    int data;
    struct tree *left,*right,*parent;
}node;
node *insertnode(node *root,int x)
{
    node *parentpointer;
    node *head=root;
    node *p=(node*)malloc(sizeof(node));
    p->data=x;
    p->left=NULL;
    p->right=NULL;
    if(root==NULL)
    {
        p->right=NULL;
        p->left=NULL;
        p->parent=NULL;
        root=p;
        return(root);
    }
    while(root!=NULL)
    {
        parentpointer=root;
        if(root->data>x)
        {
            root=root->left;
            if(root==NULL)
            {
                p->parent=parentpointer;
                parentpointer->left=p;
                return head;
            }
        }

        else if(root->data<x)
        {
            root=root->right;
            if(root==NULL)
            {
                p->parent=parentpointer;
                parentpointer->right=p;
                return head;
            }
        }
        else
        {
            printf("ELEMENT IS ALDREADY PRESENT!!\n");
            return;
        }
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
node *search(node *root,int x)
{
    if(root->data>x)
        search(root->left,x);
    else if(root->data<x)
        search(root->right,x);
    else
        return root;
}
int height(node *root)
{
    if(root==NULL)
        return -1;
    if(root->left==NULL && root->right==NULL)
        return 0;
    int lefth=0,righth=0;
    lefth=1+height(root->left);
    righth=1+height(root->right);
    if(lefth>righth)
        return lefth;
    else
        return righth;
}
node *leftrotate(node *searchnode)
{
    node *parentnode=searchnode->parent,*rightchild=searchnode->right;
    if(rightchild==NULL)
        return searchnode;
    else
    {
        if(parentnode!=NULL)
        {
            if(parentnode->left==searchnode)
                parentnode->left=rightchild;
            else
                parentnode->right=rightchild;
        }
        node *grandchild=rightchild->left;
        if(grandchild==NULL)
        {
            rightchild->parent=parentnode;
            rightchild->left=searchnode;
            searchnode->parent=rightchild;
            searchnode->right=NULL;
            return rightchild;
        }
        rightchild->parent=parentnode;
        rightchild->left=searchnode;
        searchnode->parent=rightchild;
        searchnode->right=grandchild;
        grandchild->parent=searchnode;
        return rightchild;
    }
}
node* rightrotate(node *searchnode)
{
    node *parentnode=searchnode->parent,*leftchild=searchnode->left;
    if(leftchild==NULL)
        return searchnode;
    else
    {
        if(parentnode!=NULL)
        {
            if(parentnode->left==searchnode)
                parentnode->left=leftchild;
            else
                parentnode->right=leftchild;
        }
        node *grandchild=leftchild->right;
        if(grandchild==NULL)
        {
            leftchild->parent=parentnode;
            leftchild->right=searchnode;
            searchnode->parent=leftchild;
            searchnode->left=NULL;
            return leftchild;
        }
        leftchild->parent=parentnode;
        leftchild->right=searchnode;
        searchnode->parent=leftchild;
        searchnode->left=grandchild;
        grandchild->parent=searchnode;
        return leftchild;
    }
}
node* makeskew(node *root)
{
    node *head=root;
    while(root!=NULL)
    {
        while(root->left!=NULL)
           root=rightrotate(root);
        root=root->right;
    }
    while(head->parent!=NULL)
        head=head->parent;
    return head;
}
int countnodes(node* root)
{
    if(root!=NULL)
        return (1+countnodes(root->left)+countnodes(root->right));
    if(root==NULL)
        return 0;
}
int floorlog(int x)
{
    int j=0;
    while(x>1)
    {
        x=x/2;
        j++;
    }
    return j;
}
node* treebalance(node *root)
{
    int n=countnodes(root);
    int l=floorlog(n+1),c,j;
    if(pow(2,l)==n+1)
        c=pow(2,l-1);
    else
        c=n+1-pow(2,l);
    for(j=0;j<c;j++)
    {
        if(root->right!=NULL)
        {
            root=leftrotate(root);
            root=root->right;
        }
    }
    n=n-c;
    while(root->parent!=NULL)
        root=root->parent;
    while(n>1)
    {
        n=n/2;
        for(j=0;j<n;j++)
        {
            root=leftrotate(root);
            root=root->right;
        }
        while(root->parent!=NULL)
            root=root->parent;
    }
    return root;
}

int main()
{
    node *root=NULL,*searchnode;
    int check1=0,check2=0;
    int i,j,n,x,h;
    while(1)
    {
        printf("GIVE YOUR ALTERNATIVE\n1: INSERT NODE \n2: INORDER & PREORDER & HEIGHT\n3: LEFT-ROTATE & RIGHT-ROTATE\n4: MAKE SKEW\n5: TREE BALANCE\n");
        scanf("%d",&i);
        switch(i)
        {
            case 1:
                printf("ENTER THE NUMBER OF ELEMENTS\n");
                scanf("%d",&n);
                printf("ENTER THE ELEMENTS\n");
                for(j=0;j<n;j++)
                    {
                        scanf("%d",&x);
                        root=insertnode(root,x);
                    }
            case 2:
                printf("PREORDRER: ");
                printpreorder(root);
                printf("\n");
                printf("INORDRER: ");
                printinorder(root);
                printf("\n");
                h=height(root);
                printf("HEIGHT: %d\n",h);
                break;
            case 3:
                check2=0;
                while(1)
                {
                    printf("GIVE YOUR ALTERNATIVE\n1: LEFT ROTATE\n2: RIGHT ROTATE\n3: EXIT\n");
                    scanf("%d",&j);
                    switch(j)
                    {
                    case 1:
                        printf("ENTER THE VALUE OF x\n");
                        scanf("%d",&x);
                        searchnode=search(root,x);
                        if(searchnode==root)
                            root=root->right;
                        searchnode=leftrotate(searchnode);
                        break;
                    case 2:
                        printf("ENTER THE VALUE OF x\n");
                        scanf("%d",&x);
                        searchnode=search(root,x);
                        if(searchnode==root)
                            root=root->left;
                        searchnode=rightrotate(searchnode);
                        break;
                    case 3:
                        check2=1;
                        break;
                    }
                    if(check2)
                        break;
                }
                break;
        case 4:
            root=makeskew(root);
            break;
        case 5:
            root=treebalance(root);
            break;
        }
    }
}
