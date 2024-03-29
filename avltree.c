#include<stdio.h> 
#include<stdlib.h> 
#include<stdbool.h> 
struct node 
{ 
int info,balance; 
struct node *lchild,*rchild; 
}; 
typedef struct node * NODEPTR; 
void inorder(NODEPTR); 
NODEPTR insert (int , NODEPTR, bool *); 
NODEPTR search(NODEPTR,int); 

int main(void) 
{ 
bool ht_inc; 
int info,choice; 
NODEPTR root; 
root = NULL; 
while(1) 
{ 
printf("1.Insert\n2.Display\n3.Quit\nEnter your choice : "); 
scanf("%d",&choice); 
switch(choice) 
{ 
case 1:printf("Enter the value to be inserted : "); 
scanf("%d", &info); 
if( search(root,info) == NULL ) 
root=insert(info, root, &ht_inc); 
else 
printf("Duplicate value ignored\n"); 
break; 
case 2:if(root==NULL) 
{ 
printf("Tree is empty\n"); 
continue; 
} 
printf("Tree is :\n"); 

printf("Inorder Traversal is: "); 
inorder(root); 
printf("\n \n"); 
break; 
case 3:exit(1); 
default:printf("Wrong choice\n"); 
} 
} 
return 0; 
} 

NODEPTR search(NODEPTR ptr,int info) 
{ 
if(ptr!=NULL) 
if(info < ptr->info) 
ptr=search(ptr->lchild,info); 
else if( info > ptr->info) 
ptr=search(ptr->rchild,info); 
return(ptr); 
} 

NODEPTR insert (int info, NODEPTR pptr, bool *ht_inc) 
{ 
NODEPTR aptr,bptr; 
if(pptr==NULL) 
{ 
pptr = (NODEPTR) malloc(sizeof(struct node)); 
pptr->info = info; 
pptr->lchild = NULL; 
pptr->rchild = NULL; 
pptr->balance = 0; 
*ht_inc = true; 
return (pptr); 
} 
if(info < pptr->info) 
{ 
pptr->lchild = insert(info, pptr->lchild,ht_inc); 
if(*ht_inc==true) 
{ 
switch(pptr->balance) 
{ 
case -1:
pptr->balance = 0; 
*ht_inc = false; 
break; 
case 0: 
pptr->balance = 1; 
break; 
case 1: 
aptr = pptr->lchild; 
if(aptr->balance == 1) 
{ 
printf("\nLR Rotation performed during Insertion\n\n"); 
pptr->lchild= aptr->rchild; 
aptr->rchild = pptr; 
pptr->balance = 0; 
aptr->balance=0; 
pptr = aptr; 
} 
else 
{ 
printf("\nLR Rotation performed during Insertion\n\n"); 
bptr = aptr->rchild; 
aptr->rchild = bptr->lchild; 
bptr->lchild = aptr; 
pptr->lchild = bptr->rchild; 
bptr->rchild = pptr; 
if(bptr->balance == 1 ) 
pptr->balance = -1; 
else 
pptr->balance = 0; 
if(bptr->balance == -1) 
aptr->balance = 1; 
else 
aptr->balance = 0; 
bptr->balance=0; 
pptr=bptr; 
} 
*ht_inc = false; 
} 
} 
} 
if(info > pptr->info) 
{ 
pptr->rchild = insert(info, pptr->rchild,ht_inc); 
if(*ht_inc==true) 
{ 
switch(pptr->balance) 
{ 
case 1: 
pptr->balance = 0; 
*ht_inc = false; 
break; 
case 0: 
pptr->balance = -1; 
break; 
case -1: 
aptr = pptr->rchild; 
if(aptr->balance == -1) 
{ 
printf("\nL Rotation performed during Insertion\n\n"); 
pptr->rchild= aptr->lchild; 
aptr->lchild = pptr; 
pptr->balance = 0; 
aptr->balance=0; 

pptr = aptr; 
} 
else 
{ 
printf("\nRL Rotation performed during Insertion\n\n");
bptr = aptr->lchild; 
aptr->lchild = bptr->rchild; 
bptr->rchild = aptr; 
pptr->rchild = bptr->lchild; 
bptr->lchild = pptr; 
if(bptr->balance == -1) 
pptr->balance = 1; 
else 
pptr->balance = 0; 
if(bptr->balance == 1) 
aptr->balance = -1; 
else 
aptr->balance = 0; 
bptr->balance=0; 
pptr = bptr; 
} 
*ht_inc = false; 
} 
} 
} 
return(pptr); 
} 

void inorder(NODEPTR ptr) 
{ 
if(ptr!=NULL) 
{ 
inorder(ptr->lchild); 
printf("%d(%d) ",ptr->info,ptr->balance); 
inorder(ptr->rchild); 
} 
}


