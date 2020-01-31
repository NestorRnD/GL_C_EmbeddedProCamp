#include <stdio.h>
#include "mystack.h"

#include "../myLib/mylist.h"

static TptrList StackHead=NULL;

int Push(int data)
{
    if( ListAdd(&StackHead,ListCreate(data)) == NULL )
	return 0;
    return 1;
}

int isEmpty()
{
    return (StackHead==NULL)?1:0;
}

int Read(int *pData)
{
    if(isEmpty())
	return 0;
    *pData=StackHead->data;
    return 1;
}

int Pop(int *pData)
{
    if( (pData==NULL) || (Read(pData)==0) )
	return 0;
    ListRemove(&StackHead);
    return 1;
}

void StackDestroy()
{
     ListDestroy(&StackHead);
}

static int PrintData(int *d)
{
    printf("->[%i]",*d);
    return 1;
}

void StackPrint()
{
    if(isEmpty()==1){
	printf("Stack is empty.\n");
	return;
    }
    printf("Stack: Head");
    ListIterate(StackHead,PrintData);
    printf("->NULL\n");
}

void PrintTop() // Use Read to print value 1n stack top
{
    int i;
    if(Read(&i)==0){
	printf("Stack is empty.\n");
	return;
    }
    printf("In stack top: %i\n",i);
}
