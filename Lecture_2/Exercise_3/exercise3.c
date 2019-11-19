#include <stdio.h>
#include <stdlib.h>

#define TLISTDATA int

struct TList{
    TLISTDATA data;
    struct TList *ptrNext;
};

typedef struct TList *TptrList;

TptrList ListAdd(TptrList *link, TptrList elem)
{
    if(elem!=NULL){
	elem->ptrNext=*link;
	*link=elem;
    }
    return elem;
}

void ListRemove(TptrList *link, void (*fddel)(TLISTDATA))
{
    TptrList pL=(*link);
    if(pL!=NULL){
	if(fddel!=NULL)
	    fddel(pL->data);
	*link=pL->ptrNext;
	free(pL);
    }
}

void ListDestroy(TptrList *head, void (*fddel)(TLISTDATA))
{
    while((*head)!=NULL)
	ListRemove(head,fddel);
}

TptrList ListCreate(TLISTDATA d, TLISTDATA (*fdassign)(const TLISTDATA))
{
    TptrList p;
    p=malloc(sizeof(struct TList));
    if(p!=NULL){
	p->ptrNext=NULL;
	if(fdassign!=NULL)
	    p->data=fdassign(d);
	else
	    p->data=d;
    }
    return p;
}

TptrList ListLast(TptrList head)
{
    if(head!=NULL)
	while((head->ptrNext)!=NULL)
	    head=head->ptrNext;
    return head;
}

void ListIterate(const TptrList head, TLISTDATA (*fdapply)(TLISTDATA))
{
    TptrList p=head;
    while((p != NULL) && (fdapply!=NULL)){
	p->data=fdapply(p->data);
	p=p->ptrNext;
    }
}

//!!!!!!!!!!!!!!
TptrList *ListFind();

TLISTDATA PrintData(TLISTDATA d)
{
    printf(" -> %i",d);
    return d;
}


void ListPrint(TptrList head)
{
    printf("List is:\nHead ");
    ListIterate(head,PrintData);
    printf(" -> NULL\n");
}

static int Sum;

TLISTDATA CalcSum(TLISTDATA d)
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

int main(void)
{
    TptrList Head=NULL,pL;

    ListPrint(Head);

    Head=ListCreate(10,NULL);
    ListPrint(Head);

    pL=ListCreate(5,NULL);
    ListAdd(&Head,pL);
    ListPrint(Head);

    ListAdd(
	&(ListLast(Head)->ptrNext),
	ListCreate(15,NULL));
    ListPrint(Head);

    printf("Sum of elems equal %i",SumOfElems(Head));

    ListDestroy(&Head,NULL);

    return 0;
}