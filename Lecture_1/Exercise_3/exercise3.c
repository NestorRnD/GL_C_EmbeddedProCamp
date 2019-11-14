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
	    printf("\tPlease enter numeric value.\n\t? = ");
	else break;
    }
    return res;
}

int main(void)
{
    double h,w;
    const double scale=100./2.54;
    printf("Input parameters.\n");
    h=read_param("Enter height (m): ");
    w=read_param("Enter weight (m): ");
    printf("Results:\n"
	   "\tPerimeter (in inches) is %lg\n"
	   "\tArea (in inches) is %lg\n",
	   2.*(h+w)*scale, h*w*scale*scale
	);
    return 0;
}