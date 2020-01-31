#include <stdlib.h>
#include "myqueue.h"

#define INDINC(i) pQueue->i=(pQueue->i+1)%pQueue->size

int queueInit(TQueue *pQueue, size_t size)
{
    pQueue->size=0;
    if( (pQueue == NULL) || (size == 0) ) return 0;

    // Allocate memory for queue
    pQueue->Queue=(int*)malloc(sizeof(int)*size);
    if( pQueue->Queue == NULL ) return 0;

    pQueue->size=size;
    pQueue->indFirst=0;
    pQueue->indLast=0;
    pQueue->isFull=0;
}

void queueDestroy(TQueue *pQueue)
{
    if( (pQueue->size == 0) || (pQueue->Queue == NULL) )
	return;
    pQueue->size=0;
    free(pQueue->Queue);
    pQueue->Queue=NULL;
}



int queuePut(TQueue *pQueue, int n)
{
    if( (pQueue->size == 0) || (pQueue->isFull == 1) ) return 0;
    (pQueue->Queue)[pQueue->indLast]=n;
    INDINC(indLast);
    if( pQueue->indLast == pQueue->indFirst )
	pQueue->isFull=1;
    return 1;
}

int queueRead(TQueue *pQueue, int *pn)
{
    if( (pQueue->size == 0) || queueIsEmpty(pQueue) )
	return 0;
    *pn=pQueue->Queue[pQueue->indFirst];
    return 1;
}

int queueGet(TQueue *pQueue, int *pn)
{
    if( queueRead(pQueue,pn)==0 ) return 0;
    INDINC(indFirst);
    pQueue->isFull=0;
    return 1;
}

#undef INC

