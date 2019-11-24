#include <stdio.h>
#include "mystack.h"

#define POPnPRINT if(Pop(&n)==0)fprintf(stderr,"Can't pop value couse stack is empty.\n");\
		  else printf("Get %i.\n",n);

#define PUSHnPRINT(n) if(Push(n)==0)fprintf(stderr,"Can't push new value to stack. Maybe not enough memory.");\
		      else printf("Push %i to stack.\n",n);

int main(void)
{
    int n;



    // Try operation on empty stack
    StackPrint();
    PrintTop();
    POPnPRINT

    // Add some elements to stack
    // Add 10 to Stack
    PUSHnPRINT(10);
    PrintTop();
    // Add 20 to Stack
    PUSHnPRINT(20);
    PrintTop();
    // Add 30 to Stack
    PUSHnPRINT(30);
    StackPrint();

    // Pop elements from stack
    POPnPRINT
    StackPrint();

    POPnPRINT
    StackPrint();

    // Destroy stack
    printf("Destroy stack.\n");
    StackDestroy();
    StackPrint();

    return 0;
}
