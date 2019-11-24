#include <stdio.h>
#include "mystack.h"


int main(void)
{
    int n;

#define POPnPRINT if(Pop(&n)==0)printf("Can't pop value couse stack is empty.\n");\
		  else printf("Get %i.\n",n);

    // Try operation on empty stack
    StackPrint();
    PrintTop();
    POPnPRINT

    // Add some elements to stack
    // Add 10 to Stack
    Push(10);
    PrintTop();
    // Add 20 to Stack
    Push(20);
    PrintTop();
    // Add 30 to Stack
    Push(30);
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
