#ifndef MY_LIST_H

#define MY_LIST_H

#define TLISTDATA int

struct TList{
    TLISTDATA data;
    struct TList *ptrNext;
};

typedef struct TList *TptrList;

TptrList ListCreate(TLISTDATA); // Create new list element
TptrList ListAdd(TptrList*, TptrList); // Add element to list
void ListRemove(TptrList *); // Remove element from list
void ListDestroy(TptrList *); // Destroy list elements from pointed to the end
TptrList *ListLast(TptrList *); // Return addres of pointer on last element
void ListIterate(TptrList, TLISTDATA (*)(TLISTDATA)); // Apply modification to stored data
TptrList *ListFind(TptrList *, int (*)(TLISTDATA,TLISTDATA), TLISTDATA); // Search in list
//!!!!!!!!!!!!!!
// criteria must return nonzero value if search must continue and 0 if search is complite

#endif
