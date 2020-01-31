#include <stdio.h>
#include <math.h>

typedef double (*TDFunc)(double) ;

// Numericaly calculate first order derivation of function at specifed point
double Diff(TDFunc f, double x, double eps)
{
    return (f(x+eps)-f(x-eps))/2./eps;
}

// Numericaly calculate second order derivation of function at specifed point
double Diff2(TDFunc f, double x, double eps)
{
    return (f(x+eps)-2.*f(x)+f(x-eps))/eps/eps;
}

double f(double x)
{
    return x*x;
}

double g(double x)
{
    return cos(x);
}

int main(void)
{
    printf("First order derive from x^2 at x=1/2 is: %lg\n",Diff(f,.5,1e-4));
    printf("Second order derive from x^2 at x=1/2 is: %lg\n\n",Diff2(f,.5,1e-4));

    printf("First order derive from cos(x) at x=pi/6 is: %lg\n",Diff(g,M_PI/6.,1e-4));
    printf("Second order derive from cos(x) at x=pi/6 is: %lg",Diff2(g,M_PI/6.,1e-4));
    printf("  ( sqrt(3)/2 = %lg )\n",sqrt(3)/2.);

    return 0;
}