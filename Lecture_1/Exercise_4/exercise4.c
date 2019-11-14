#include <stdio.h>
#include <math.h>

int main(void){
    double
	R=6,
	P,S;

    // Perimeter calculation
    P=2*M_PI*R;
    printf("Perimeter is %lg meters.\n",P);

    // Area calculation
    S=M_PI*R*R;
    printf("Area is %lg square meters.\n",S);

    return 0;
}
