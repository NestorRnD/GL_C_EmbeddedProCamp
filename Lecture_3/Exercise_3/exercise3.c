#include <stdio.h>
#include "myqueue.h"

void printQueue(TQueue *pQueue){ // help function for printing all values in specifed queue
    size_t i;
    if(pQueue->size==0){
	printf(" - Queue wasn't initialized.\n");
	return;
    }

    if(queueIsEmpty(pQueue)){
	printf(" - Queue is empty.\n");
	return;
    }

    printf(" - Queue is: ");
    if(!pQueue->isFull)
	printf("Last->[]");

    i=pQueue->indLast;

    do{
	if(i==0)i=pQueue->size-1;
	else i--;
	printf("->[%i]",pQueue->Queue[i]);
    }while( i!=pQueue->indFirst );

    if(!pQueue->isFull)
	printf("<-First\n");
    else printf("<-First&Last\n");

}

#define PUT(n) (queuePut(&myQ,n)==1) ? printf("Put %i to queue.\n  - ",n) : printf("   >>> ERROR: Can't put value to queue.\n")
#define GET(n) (queueGet(&myQ,&n)==1) ? printf("Get value from queue. It is %i\n - ",n) : printf("   >>> ERROR: Can't get value from queue.\n")
#define READ(n) (queueRead(&myQ,&n)==1) ? printf("Read value from queue.\n - The value %i is first in queue.\n",n)\
					: printf("   >>> ERROR: Can't read value from queue.\n")

int main(){
    TQueue myQ=EMPTYQUEUE;
    int n;

    printf("Print queue befor init.\n");
    printQueue(&myQ);

    if(queueInit(&myQ,3)==0){
	fprintf(stderr,"   >>> ERROR: Can't initialize queue.\n");
	return 1;
    }
    printf("Print queue after init.\n");
    printQueue(&myQ);

    printf("Try to get value from empty queue.\n");
    GET(n);

    printf("Try to read value from empty queue.\n");
    READ(n);

    PUT(10);
    printQueue(&myQ);

    READ(n);

    PUT(n+5);
    printQueue(&myQ);

    READ(n);

    PUT(n+10);
    printQueue(&myQ);

    GET(n);
    printQueue(&myQ);

    PUT(2*n+5);
    printQueue(&myQ);

    READ(n);

    printf("Try to put value to full queue.\n");
    PUT(n+5);

    GET(n);
    printQueue(&myQ);

    printf("Free memory alocated for queue.\n");
    queueDestroy(&myQ);


    printf("Try to put, get and read value to/from queue.\n");
    PUT(1);
    GET(n);
    READ(n);

    return 0;
}
