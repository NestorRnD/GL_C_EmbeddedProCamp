#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void){
    char *buff=NULL,*p=NULL,lch;
    uint16_t n,i;
    long int inp;

    printf("Enter the natural number in range [1,500].\n\t");
    while(1){
	scanf("%ms",&buff);
	inp=strtol(buff,&p,10);
	lch=*p;
	free(buff);
	if(lch)
	    printf("\t>>> Please, enter the numeric value.\n\t? = ");
	else{
	    if((inp<1)|(inp>500))
		printf("\t>>> The number mast be in range [1,500].\n\t? = ");
	    else break;
	}
    }
    n=(uint16_t)inp;

    printf("%u divided without remainder next numbers:\n",n);
    for(i=1;n*i<=500;i++)
	printf(" %u",n*i);
    printf("\n");
    return 0;
}
