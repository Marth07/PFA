

#define INTEGRATION_C

#include "integration.h"

bool setQuadFormula(QuadFormula *qf, char *name)
{
	if (strcmp(name, "left") == 0)
	{
		qf->nsub = 0.0;
		qf->w[0] = 1.0;
		qf->x[0] = 1.0;
		return true;
	}
	if (strcmp(name, "right") == 0)
	{
		qf->nsub = 0.0;
		qf->w[0] = 1.0;
		qf->x[0] = 1.0;
		return true;
	}
	if (strcmp(name, "middle") == 0)
	{
		qf->nsub = 0.0;
		qf->w[0] = 1.0;
		qf->x[0] = 0.5;
		return true;
	}
	if (strcmp(name, "trapezes") == 0)
	{
		qf->nsub = 1.0;
		qf->w[0] = 0.5;
		qf->w[1] = 0.5;
		qf->x[0] = 0.0;
		qf->x[1] = 1.0;
		return true;
	}
	if (strcmp(name, "simpson") == 0)
	{
		qf->nsub = 2.0;
		qf->w[0] = 1.0 / 6.0;
		qf->w[1] = 2.0 / 3.0;
		qf->w[2] = 1.0 / 6.0;
		qf->x[0] = 0.0;
		qf->x[1] = 0.5;
		qf->x[2] = 1.0;
		return true;
	}
	if (strcmp(name, "gauss2") == 0)
	{
		qf->nsub = 1.0;
		qf->w[0] = 0.5;
		qf->w[1] = 0.5;
		qf->x[0] = 0.5 - 1.0 / (2.0 * sqrt(3.0));
		qf->x[1] = 0.5 + 1.0 / (2.0 * sqrt(3.0));
		return true;
	}
	if (strcmp(name, "gauss3") == 0)
	{
		qf->nsub = 2.0;
		qf->w[0] = 5.0 / 18.0;
		qf->w[1] = 4.0 / 9.0;
		qf->w[2] = 5.0 / 18.0;
		qf->x[0] = 0.5 * (1.0 - sqrt(0.6));
		qf->x[1] = 0.5;
		qf->x[2] = 0.5 * (1.0 + sqrt(0.6));
		return true;
	}

	return false;
}

/* This function is not required ,but it may useful to debug */
void printQuadFormula(QuadFormula *qf)
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
double integrate(double (*f)(double), double a, double b, int N, QuadFormula *qf)
{
    double total_integral = 0.0;

    if (setQuadFormula(qf, qf->name) == false)
    {
        return 0.0;
    }

    if (a == b || f == NULL || N <= 0)
    {
        return 0.0;
    }

    double h = (b - a) / N;

    for (size_t i = 0; i < (size_t)N; i++)
    {
        qf->a1 = a + h * i;
        qf->b1 = a + h * (i + 1);
        
        double subdivision_sum = 0.0;
        int num_points = (int)qf->nsub + 1;

        for (int k = 0; k < num_points; k++)
        {
            subdivision_sum += qf->w[k] * f(qf->a1 + qf->x[k] * (qf->b1 - qf->a1));
        }

        total_integral += (qf->b1 - qf->a1) * subdivision_sum;
    }

    return total_integral;
}

double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula *qf)
{
	if (dx <= 0)
	{
		return 0.0;
	}
	double diff = b - a;
	if (diff < 0)
	{
		diff = -diff;
	}

	int N = (int)(diff / dx +0.5);
	if (N == 0)
	{
		N = 1;
	}
	return integrate(f, a, b, N, qf);
}
