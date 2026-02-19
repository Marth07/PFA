



#define INTEGRATION_C

#include "integration.h"

bool setQuadFormula(QuadFormula* qf, char* name)
{
	if(strcmp(name,"left")==0){
		qf-> nsub = 0.0;
		qf -> w[0] = 1.0;
		qf ->  x[0] = 0.0;
		return true;
	}
	if(strcmp(name,"rigth")==0){
		qf-> nsub = 0.0;
		qf -> w[0] = 1.0;
		qf ->  x[0] = 1.0;
		return true;
	}
	if(strcmp(name,"middle")==0){
		qf-> nsub = 0.0;
		qf -> w[0] = 1.0;
		qf ->  x[0] = 0.5;
		return true;
	}
	if(strcmp(name,"left")==0){
		qf-> nsub = 1.0;
		qf -> w[0] = 0.5;
		qf-> w[1] = 0.5;
		qf ->  x[0] = 0.0;
		qf -> x[1] = 1.0;
		return true;
	}


  return true;
}

/* This function is not required ,but it may useful to debug */
void printQuadFormula(QuadFormula* qf)
{
  printf("Quadratic formula: %s\n", qf->name);
  /* Print everything else that may be useful */
}


/* Approximate the integral of function f from a to b.
   - f is a pointer to a function pointer
   - a and b are the integration bounds
   - Interval [a,b] is split in N subdivisions [ai,bi]
   - Integral of f on each subdivision [ai,bi] is approximated by the quadrature formula qf.
*/
double integrate(double (*f)(double), double a, double b, int N, QuadFormula* qf)
{
	double sum = 0.0;
	if(setQuadFormula(qf,qf->name)==false){
		return sum;}
	if(a==b || f == NULL)
	{
		return 0.0;
	}
	double p = (a - b);
	for( size_t i = 1; i<N;i++){
		qf->a1 = a + (b-a)/N*i;
		qf->b1 = a + (b-a)/N*(i+1);
		if(strcmp(qf->name,"left")==0)
		{
			sum += (qf->b1 - qf->a1) + f(qf->a1);
		}
		if (strcmp(qf->name,"right")==0)
		{
			sum += (qf->b1 - qf->a1) + f(qf->b1);
		}
		if (strcmp(qf->name,"middle")==0)
		{
			sum += (qf->b1 - qf->a1) + f((qf->b1 + qf-> a1)/2);
		}
		if (strcmp(qf->name,"trapezes")==0)
		{
			sum += (qf->b1 - qf->a1) + (0.5*f(qf->b1) + 0.5*f(qf->a1));
		}
	}
	return sum;
}



double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf)
{
  return 0.0;
}


