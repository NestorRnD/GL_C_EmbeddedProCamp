#include <stdio.h>

#include "../myLib/mylist.h"

TptrList StackHead=NULL;

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

#define StackDestroy() ListDestroy(&StackHead)

int PrintData(int *d)
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

int main(void)
{
    int n;

    // Try operation on empty stack
    StackPrint();
    PrintTop();

    if(Pop(&n)==0)
	printf("Can't pop value couse stack is empty.\n");
    else
	printf("Get %i.\n",n);

    // Add 10 to Stack
    Push(10);
    PrintTop();
    // Add 20 to Stack
    Push(20);
    PrintTop();
    // Add 30 to Stack
    Push(30);
    StackPrint();

    if(Pop(&n)==0)
	printf("Can't pop value couse stack is empty.\n");
    else
	printf("Get %i.\n",n);

    StackPrint();

    if(Pop(&n)==0)
	printf("Can't pop value couse stack is empty.\n");
    else
	printf("Get %i.\n",n);

    StackPrint();

    printf("Destroy stack.\n");
    StackDestroy();
    StackPrint();

    return 0;
}
