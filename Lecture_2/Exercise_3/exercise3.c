#include <stdio.h>

#include "mylist.h"


TLISTDATA PrintData(TLISTDATA d)
{
    printf("->[%i]",d);
    return d;
}


void ListPrint(TptrList head)
{
    printf("List is: Head");
    ListIterate(head,PrintData);
    printf("->NULL\n");
}

static int Sum;

int CalcSum(int d)
{
    Sum+=d;
    return d;
}

int SumOfElems(TptrList head)
{
    Sum=0;
    ListIterate(head,CalcSum);
    return Sum;
}


int insCrit(int data, int param){
    return data<param;
}


#define TOPINSERT(elem) 	ListAdd(&Head,ListCreate(elem))
#define LASTINSERT(elem)	{TptrList *pL=ListLast(&Head);\
				ListAdd((*pL==NULL)?pL:&((*pL)->ptrNext),ListCreate(elem));}
#define ORDERINSERT(elem)	ListAdd(ListFind(&Head,insCrit,elem),ListCreate(elem))

int main(void)
{
    TptrList Head=NULL;

    ListPrint(Head);

    printf("Insert 10 in tail.\n");
    LASTINSERT(10);
    ListPrint(Head);

    printf("Insert 5 in top.\n");
    TOPINSERT(5);
    ListPrint(Head);

    printf("Insert 15 in tail.\n");
    LASTINSERT(15);
    ListPrint(Head);

    printf("Insert 7.\n");
    ORDERINSERT(7);
    ListPrint(Head);

    printf("Insert 12.\n");
    ORDERINSERT(12);
    ListPrint(Head);

    printf("Insert 1.\n");
    ORDERINSERT(1);
    ListPrint(Head);

    printf("Sum of all elems is equal to %i\n",SumOfElems(Head));

    printf("Remove first element.\n");
    ListRemove(&Head);
    ListPrint(Head);

    printf("Remove last element.\n");
    ListRemove(ListLast(&Head));
    ListPrint(Head);

    printf("Remove first element that >=7.\n");
    ListRemove(ListFind(&Head,insCrit,7));
    ListPrint(Head);

    printf("Remove first element that >=7.\n");
    ListRemove(ListFind(&Head,insCrit,7));
    ListPrint(Head);

    printf("Destroy list.\n");
    ListDestroy(&Head);
    ListPrint(Head);

    printf("Try to remove first element.\n");
    ListRemove(&Head);
    ListPrint(Head);

    return 0;
}