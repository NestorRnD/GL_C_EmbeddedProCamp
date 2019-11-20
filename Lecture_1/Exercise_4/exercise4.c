#include <stdio.h>
#include <math.h>

static inline double CirclePerimeter(double r)
{
    if(r<0){
	fprintf(stderr,"!!! ERROR: The radius can't be less then 0.");
	return 0;
    }
    return 2*M_PI*r;
}

static inline double CircleArea(double r)
{
    if(r<0){
	fprintf(stderr,"!!! ERROR: The radius can't be less then 0.");
	return 0;
    }
    return M_PI*r*r;
}

int main(void)
{
    double
	R=6,
	P,S;

    // Perimeter calculation
    P=CirclePerimeter(R);
    printf("Perimeter is %lg meters.\n",P);

    // Area calculation
    S=CircleArea(R);
    printf("Area is %lg square meters.\n",S);

    return 0;
}
