/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "integration.h"

double f(double t)
{
    return sin(t * t);
}

int main()
{
    QuadFormula qf;
    double I1, I2, I3;

    strcpy(qf.name, "trapezes");
    I1 = integrate(f, -1.0, 4.0, 10, &qf);
    
    strcpy(qf.name, "middle");
    I2 = integrate(f, -1.0, 4.0, 10, &qf);
    
    strcpy(qf.name, "left");
    I3 = integrate_dx(f, -1.0, 4.0, 0.1, &qf);

    printf("I1 (gauss2): %f\n", I1);
    printf("I2 (gauss3):   %f\n", I2);
    printf("I3 (simpson):     %f\n", I3);

    return 0;
}