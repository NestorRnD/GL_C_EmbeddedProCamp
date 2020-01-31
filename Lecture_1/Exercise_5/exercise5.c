#include <stdio.h>
#include <stdint.h>

uint64_t factorial(uint8_t n)
{
    uint64_t prod=1;
    if(n>22){
	fprintf(stderr,"Error: Can't calculate factorial of %d. The result is to big.\n",n);
	return 0;
    }
    for(;n>1;n--)
	prod*=n;
    return prod;
}

#define PRINTFACTORIAL(k) printf("%d! = %lu\n",k,factorial(k))

int main(void)
{
    PRINTFACTORIAL(10);
/*
    PRINTFACTORIAL(20);
    PRINTFACTORIAL(21);
    PRINTFACTORIAL(22);
    PRINTFACTORIAL(23);
//*/
    return 0;
}
