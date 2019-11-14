#include <stdio.h>
#include <stdint.h>

int main(void){
    uint64_t n=0,i;
    
    n--;
    for(i=2;n>0;i++)
	n/=i;
    printf("%d\n",i);
    return 0;
}