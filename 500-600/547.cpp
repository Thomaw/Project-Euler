#include <stdio.h>
#include <math.h>

#define N 40

// \int \sqrt(x^2+y^2) dx dy
double int00raw(double x, double y)
{
	double h = sqrt(x*x + y*y);
	return ((x == 0 ? 0 : x*x*x*log(h + y)) + (y == 0 ? 0 : y*y*y*log(h + x)) + 2*x*y*h) / 6;
}

// \int \sqrt(x^2+y^2) y dx dy
double int01raw(double x, double y)
{
	double h = sqrt(x*x + y*y);
	return (3 * (y == 0 ? 0 : y*y*y*y*log(h + x)) + x*h*(2*x*x + 5*y*y)) / 24;
}

// \int \sqrt(x^2+y^2) x dx dy
double int10raw(double x, double y)
{
	return int01raw(y, x);
}

// \int \sqrt(x^2+y^2) x y dx dy
double int11raw(double x, double y)
{
	double h = sqrt(x*x + y*y);
	return h*h*h*h*h / 15;
}

// \int \sqrt(x^2+y^2)(x*xmul+xshift)(y*ymul+yshift) dx dy
double intsraw(int xmul, double xshift, int ymul, double yshift, double x, double y)
{
	return int00raw(x, y) * xshift * yshift + int01raw(x, y) * xshift * ymul + int10raw(x, y) * xmul * yshift + int11raw(x, y) * xmul * ymul;
}

double ints(int xmul, double xshift, int ymul, double yshift, double xlower, double xupper, double ylower, double yupper)
{
	return intsraw(xmul, xshift, ymul, yshift, xupper, yupper) +
		intsraw(xmul, xshift, ymul, yshift, xlower, ylower) -
		intsraw(xmul, xshift, ymul, yshift, xlower, yupper) -
		intsraw(xmul, xshift, ymul, yshift, xupper, ylower);
}

double f(int xa, int xb, int ya, int yb)
{
	return ints(1, xa, 1, ya, -xa, -xb, -ya, -yb) +
		ints(0, xa-xb, 1, ya, -xb, N-xa, -ya, -yb) +
		ints(-1, N-xb, 1, ya, N-xa, N-xb, -ya, -yb)+
		ints(1, xa, 0, ya-yb, -xa, -xb, -yb, N-ya) +
		ints(0, xa-xb, 0, ya-yb, -xb, N-xa, -yb, N-ya) +
		ints(-1, N-xb, 0, ya-yb, N-xa, N-xb, -yb, N-ya) +
		ints(1, xa, -1, N-yb, -xa, -xb, N-ya, N-yb) +
		ints(0, xa-xb, -1, N-yb, -xb, N-xa, N-ya, N-yb) +
		ints(-1, N-xb, -1, N-yb, N-xa, N-xb, N-ya, N-yb);
}

double full(int a, int b)
{
	return 4 * ints(-1, a, -1, b, 0, a, 0, b);
}

int main()
{
	double result = 0;
	double fulln = full(N, N);
	int xa, xb, ya, yb;
	for (xb = 1; xb < N; xb++)
		for (xa = xb + 1; xa < N; xa++)
			for (yb = 1; yb < N; yb++)
				for (ya = yb + 1; ya < N; ya++) {
					int area = N*N - (xa-xb)*(ya-yb);
					result += (fulln - 2 * f(xa, xb, ya, yb) + full(xa - xb, ya - yb)) / (area*area);
				}
	printf("%lf\n", result);
	return 0;
}