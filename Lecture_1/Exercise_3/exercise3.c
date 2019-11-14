#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

double read_param(const char *msg)
{
    double res=0;
    char *buff=NULL,*p=NULL,lch;
    if(msg)
	printf("\t%s",msg);
    else
	printf("\t? = ");
    while(1){
	scanf("%ms",&buff);
	res=strtod(buff,&p);
	lch=*p;
	free(buff);
	if(lch)
	    printf("\t>>> Please enter numeric value.\n\t? = ");
	else break;
    }
    return res;
}

int main(void)
{
    double h,w;
    const double scale=100./2.54;
    printf("Input parameters.\n");
    do{
	h=read_param("Enter height (m): ");
	if(h<0)
	    printf("\t>>> Height mast be positive.\n");
    }while(h<0);
    do{
	w=read_param("Enter weight (m): ");
	if(w<0)
	    printf("\t>>> Weight mast be positive.\n");
    }while(w<0);
    printf("Results:\n"
	   "\tPerimeter (in inches) is %lg\n"
	   "\tArea (in square inches) is %lg\n",
	   2.*(h+w)*scale, h*w*scale*scale
	);
    return 0;
}