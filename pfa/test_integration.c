/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/
#include <math.h>
#include "integration.h"
#include <stdio.h>
/* Code here everything you need to test the integration methods and show your numericzal results */

int main()
{
	double f(double t)
	{
		return sin(t*t);
	}
	QuadFormula qf;
	double I1, I2, I3;
	setQuadFormula(&qf, "trapezes");
	I1 = integrate(f, -1, 4, 10, &qf);
	setQuadFormula(&qf, "middle");
	I2 = integrate(f, -1, 4, 10, &qf);
	setQuadFormula(&qf, "simpson");
	I3 = integrate_dx(f, -1, 4, 0.1, &qf);
	printf("%f\n",I1);
}
