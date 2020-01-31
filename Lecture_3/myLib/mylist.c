#include <stdlib.h>
#include "mylist.h"

TptrList ListAdd(TptrList *link, TptrList elem)
{
    if( elem != NULL ){
	elem->ptrNext=*link;
	*link=elem;
    }
    return elem;
}

void ListRemove(TptrList *link)
{
    TptrList pL=(*link);
    if( pL != NULL ){
	*link=pL->ptrNext;
	free(pL);
    }
}

void ListDestroy(TptrList *link)
{
    while( (*link) != NULL )
	ListRemove(link);
}

TptrList ListCreate(TLISTDATA d)
{
    TptrList p;
    p=malloc(sizeof(struct TList));
    if( p != NULL ){
	p->ptrNext=NULL;
	p->data=d;
    }
    return p;
}

TptrList *ListLast(TptrList *link)
{
    if( (*link) != NULL )
	while(((*link)->ptrNext)!=NULL)
	    link=&((*link)->ptrNext);
    return link;
}

void ListIterate(TptrList head, int (*fdApply)(TLISTDATA *))
{
    while((head != NULL) && (fdApply != NULL)){
	if(fdApply(&(head->data))==0) break;
	head=head->ptrNext;
    }
}

TptrList *ListFind(TptrList *link, int (*criteria)(TLISTDATA,TLISTDATA), TLISTDATA param){
    while( ((*link) != NULL) && (criteria((*link)->data,param)) )
	link=&((*link)->ptrNext);
    return link;
}
