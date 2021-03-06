#include<stdio.h>
typedef struct tree
{
    int data;
    char color;
    struct tree *left,*right,*parent;
}node;
node* rearrange(node* head,node *p);
node* leftrotate(node *searchnode);
node* rightrotate(node *searchnode);
node* insertnode(node *root,int x)
{
    node *p,*parentpointer,*head=root;
    p=(node*)malloc(sizeof(node));
    p->data=x;
    p->left=p->right=NULL;
    if(root==NULL)
    {
        p->parent=NULL;
        root=p;
        p->color='B';
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
                p->color='R';
                return rearrange(head,p);
            }
        }
        else if(root->data<x)
        {
            root=root->right;
            if(root==NULL)
            {
                p->parent=parentpointer;
                parentpointer->right=p;
                p->color='R';
                return rearrange(head,p);
            }
        }
        else
        {
            printf("THE ELEMENT IS ALDREADY PRESENT\n");
            return;
        }
    }
}
node* rearrange(node *head,node *p)
{
    if(head==p)
    {
        p->color='B';
        return p;
    }
    if(p->parent==NULL)
    {
        p->color='B';
        return head;
    }
    if(p->parent->color=='B')
        return head;
    node *uncle,*parentpointer=p->parent,*grandparent=p->parent->parent;
    if(grandparent==NULL)
    {
        parentpointer->color='B';
        return head;
    }
    if(grandparent->left==parentpointer)
        uncle=grandparent->right;
    else
        uncle=grandparent->left;
    if(uncle==NULL||uncle->color=='B')
    {
        if(grandparent->left==parentpointer&&parentpointer->right==p)
        {
            if(head==grandparent)
                head=head->left->right;
            p->color='B';
            grandparent->color='R';
            parentpointer=leftrotate(parentpointer);
            grandparent=rightrotate(grandparent);
            return head;
        }
        if(grandparent->left==parentpointer&&parentpointer->left==p)
        {
            if(head==grandparent)
                head=head->left;
            parentpointer->color='B';
            grandparent->color='R';
            grandparent=rightrotate(grandparent);
            return head;
        }
        if(grandparent->right==parentpointer&&parentpointer->left==p)
        {
            if(head==grandparent)
                head=head->right->left;
            p->color='B';
            grandparent->color='R';
            parentpointer=rightrotate(parentpointer);
            grandparent=leftrotate(grandparent);
            return head;
        }
        if(grandparent->right==parentpointer&&parentpointer->right==p)
        {
            if(head==grandparent)
                head=head->right;
            parentpointer->color='B';
            grandparent->color='R';
            grandparent=leftrotate(grandparent);
            return head;
        }
    }
    if(uncle->color=='R')
    {
        uncle->color=parentpointer->color='B';
        grandparent->color='R';
        return rearrange(head,grandparent);
    }
}
void printinorder(node *root)
{
    if(root->left!=NULL)
        printinorder(root->left);
    printf("%d -> %c _ ",root->data,root->color);
    if(root->right!=    NULL)
        printinorder(root->right);
}
void printpreorder(node *root)
{
    printf("%d -> %c _ ",root->data,root->color);
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
int main()
{
    node *root=NULL;
    int i,j,n,x,h;
    while(1)
    {
        printf("GIVE YOUR ALTERNATIVE!\n1: INSERT NODE\n2: PRINT INODRER & PRINT PREORDER\n");
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
            break;
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
        }
    }
}
