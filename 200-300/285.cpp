// Euler285.cpp

#include <stdio.h>
#include <math.h>
#define FOR(a,b,c)	for (int(a)=(b);(a)<=(c);(a)++)
int main(int argc, char* argv[])
{
	double a = 0.0, b, t, s, r;
	FOR (k,1,100000) {
		FOR (m,0,k==1?0:1) {
			r = 1.0+(0.5-m)/k;
			b = sqrt(r*r-1.0/k/k)-1.0/k;
			t = 2.0*asin(b/sqrt(2.0)/r);
			s = 0.5*(b*b+(t-sin(t))*r*r);
			a += (-2*m+1)*k*s;
		}
	}
	printf("%.10lf\n", a);
}