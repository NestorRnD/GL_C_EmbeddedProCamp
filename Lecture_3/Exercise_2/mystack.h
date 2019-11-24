#ifndef MY_STACK_H

#define MY_STACK_H

#include "../myLib/mylist.h"

int isEmpty(); // Check: Stack is empty? Return 1 if true else return 0.

int Push(int); // Push value to stack. If succes return 1 else return 0.
int Pop(int *); // Pop value from the top of stack. If succes return 1 else return 0.
int Read(int *); // Read value from the top of stack. If succes return 1 else return 0.

void StackDestroy(); // Destroy stack. Free allocated memory.

void StackPrint(); // Print stack.
void PrintTop(); // Use Read to print value 1n stack top.

#endif