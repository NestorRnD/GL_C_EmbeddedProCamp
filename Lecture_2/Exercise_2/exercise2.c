#include <stdio.h>

/*
 * This function return the biggest element in array.
 * If indPtr != NULL it mast contain the adress of
 * variable where the function put index of the max element.
 * If array contain the biggest value many times the
 * function return the index of first of them.
 *
 */

int findMax(int *A, size_t n, size_t *indPtr)
{
    size_t i,mi=0;

    if(n<1){
	fprintf(stderr,"Error: Empty array or bed array size\n");
	return 0;
    }

    for(i=1;i<n;i++)
	if(A[mi]<A[i]) mi=i;
    if(indPtr != NULL)
	*indPtr=mi;

    return A[mi];
}

void printArr(int *A, size_t n)
{
    size_t i;
    for(i=0;i<n;i++)
	printf("[%u]=%d ",i,A[i]);
    printf("\n");
}

int main(void)
{
    int max,
	arrA[]={1,5,-234,123,23,54,67,12,45,67,21};
    size_t ind,
	n=sizeof(arrA)/sizeof(arrA[0]);

    printf("In array:\n");
    printArr(arrA,n);
    max=findMax(arrA,n,&ind);
    printf("The biggest element is [%u]=%d.\n",ind,max);

    return 0;
}