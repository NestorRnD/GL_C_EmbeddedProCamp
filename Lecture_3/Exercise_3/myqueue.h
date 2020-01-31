#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#define EMPTYQUEUE {NULL,0,0,0,0}

typedef struct{
    int *Queue;
    size_t size;
    size_t indFirst;
    size_t indLast;
    char isFull;
} TQueue;

void queueDestroy(TQueue *); // Destroy queue structure
void queueClear(TQueue *); // Clear queue

// next functions on success return 1 or otherwise return 0.
int queueInit(TQueue *, size_t); // Create new queue of the specified size
int queuePut(TQueue *, int); // Put new element in queue
int queueRead(TQueue *, int *); // Read first element from queue. The queue not changed.
int queueGet(TQueue *, int *); // Get first element from queue.

static inline int queueIsEmpty(TQueue *pQueue)
{
    return (pQueue->indLast == pQueue->indFirst) && (!pQueue->isFull);
}

#endif
