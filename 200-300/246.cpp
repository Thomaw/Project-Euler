#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

inline long long square(long long n) {
	return n*n;
}

// coefficients of ellipse
long long a2 = 7500*7500;
long long b2 = 2500*12500;

long double A2 = 7500*7500;
long double B2 = 2500*12500;

// center of ellipse
long long ecx = 3000;
long long ecy = 1500;

bool insideellipse(long long x, long long y) {
	// x^2/a^2 + y^2/b^2 - 1 <= 0
	// x^2*b^2 + y^2*a^2 - a^2*b^2 <= 0

	return square(x-ecx)*b2 + square(y-ecy)*a2 - a2*b2 <= 0;
}

// center of circle
int ccx = -2000;
int ccy =  1500;

// radius of circle
int rc  = 15000;

bool insidecircle(long long x, long long y) {
	return square(x-ccx) + square(y-ccy) <= square(rc);
}

bool keep(int ox, int oy) {
	// change coordinates
	ox -= ecx;
	oy -= ecy;

	long double x = ox;
	long double y = oy;

	long double x0, y0;
	long double x1, y1;

	if (ox==0) {
		y0 = y1 = B2/y;
		x0 = sqrt(A2*(1-y0*y0/B2));
		x1 = -x0;
	} else if (oy==0) {
		x0 = x1 = A2/x;
		y0 = sqrt(B2*(1-x0*x0/A2));
		y1 = -y0;
	} else if (abs(ox)<abs(oy)) {
		// 2nd degree equation - looking for y

		long double a = A2*A2*y*y/(B2*B2*x*x) + A2/B2;
		long double b = -2*A2*A2*y/(B2*x*x);
		long double c = A2*A2/(x*x)-A2;

		long double delta = b*b - 4*a*c;

		y0 = (-b + sqrt(delta))/(2*a);
		y1 = (-b - sqrt(delta))/(2*a);

		x0 = (1 - y*y0/B2)*A2/x;
		x1 = (1 - y*y1/B2)*A2/x;
	} else {
		// 2nd degree equation - looking for x

		long double a = B2*B2*x*x/(A2*A2*y*y) + B2/A2;
		long double b = -2*B2*B2*x/(A2*y*y);
		long double c = B2*B2/(y*y)-B2;

		long double delta = b*b - 4*a*c;

		x0 = (-b + sqrt(delta))/(2*a);
		x1 = (-b - sqrt(delta))/(2*a);

		y0 = (1 - x*x0/A2)*B2/y;
		y1 = (1 - x*x1/A2)*B2/y;
	}

	// scalar product
	long double norm0 = sqrt((x-x0)*(x-x0) + (y-y0)*(y-y0));
	long double norm1 = sqrt((x-x1)*(x-x1) + (y-y1)*(y-y1));

	long double prod = ( (x-x0)*(x-x1) + (y-y0)*(y-y1) ) / ( norm0 * norm1 );

	return prod < sqrt(1/2.);
}

int main(int argc,char **argv) {
	// looking for the first interval
	// at each y : [xmin..xmax] contains the good points
	int y = ecy;

	int xmin = ecx;
	while (insideellipse(xmin,y)) {
		xmin++;
	}
	int xmax = xmin;
	while (keep(xmax+1,y)) {
		xmax++;
	}

	int result = 0;

	do {
		if (y==ecy) {
			// counted twice
			result += (xmax-xmin+1)*2;
		} else {
			// counted 4 times
			result += (xmax-xmin+1)*4;

			// except for y axis (count twice)
			if (xmin==ecx) {
				result -= 2;
			}
		}

		y++;

		while (xmin>ecx && !insideellipse(xmin-1,y)) {
			xmin--;
		}
		while (xmax>=ecx && !keep(xmax,y)) {
			xmax--;
		}
	} while (xmin < xmax);

	printf("SOLUTION => %d\n", result);

	return 0;
}