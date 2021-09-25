#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

const double eps = 1e-12;

double pi = acos(-1);

// Area of polygon (vertices oriented counterclockwise)
double area (vector<double> X, vector<double> Y)
{	int n = X.size(), i;
	double A = 0;
	for (i = 0; i < n; i++)
		A += X[i] * Y[(i+1)%n] - Y[i] * X[(i+1)%n];
	return A/2;
}

// Intersection point of lines ab and cd (assumed not to be parallel)
pair<double,double> intersection (double xa, double ya, double xb, double yb,
	double xc, double yc, double xd, double yd)
{	double d = (xa-xb)*(yc-yd) - (xc-xd)*(ya-yb);
	double x = -((xa-xb)*(xc*yd-xd*yc) - (xc-xd)*(xa*yb-xb*ya)) / d;
	double y =  ((ya-yb)*(yc*xd-yd*xc) - (yc-yd)*(ya*xb-yb*xa)) / d;
	return make_pair(x, y);
}

// Returns largest value that the side length can have,
// such that the pentagon, rotated by angle phi, fits in the L-shaped corridor
// (It finds the smallest corridor width in which the unit pentagon fits, and returns the inverse)
double sidelength (double phi, vector<double> X, vector<double> Y)
{	int i;
	double cs, sn, xmin, ymin, x;
	vector<double> Xr(5), Yr(5);
	// Rotate pentagon by angle phi (clockwise)
	cs = cos(phi);
	sn = sin(phi);
	xmin = ymin = 1e9;
	for (i = 0; i < 5; i++)
	{	xmin = min(xmin, Xr[i] = cs*X[i] + sn*Y[i]);
		ymin = min(ymin, Yr[i] = cs*Y[i] - sn*X[i]);
	}
	// Translate
	for (i = 0; i < 5; i++)
	{	Xr[i] -= xmin;
		Yr[i] -= ymin;
	}
	// Find the intersection of the pentagon with line x=y
	// This will be the intersection with the side between vertices 2 & 3 or 3 & 4,
	// depending on the location of vertex 3 with respect to x=y.
	i = (Xr[3] < Yr[3] ? 2 : 4);
	pair<double,double> P = intersection(Xr[3], Yr[3], Xr[i], Yr[i], 0, 0, 1, 1);
	x = P.first;
	// Check if the vertices fit in the corridor, widen if necessary
	for (i = 0; i < 5; i++)
		x = max(x, min(Xr[i], Yr[i]));
	return 1/x;
}

double tablearea (double theta)
{	// Construct unit pentagon (with symmetry axis on y-axis)
	vector<double> X(5), Y(5), Xr(5), Yr(5);
	X[0] = -.5; Y[0] = 0;
	X[1] = .5; Y[1] = 0;
	X[2] = .5-cos(theta); Y[2] = sin(theta);
	X[3] = 0; Y[3] = Y[2] - sqrt(1-X[2]*X[2]);
	X[4] = -X[2]; Y[4] = Y[2];
	// Find the smallest value of the side length among all rotations phi
	double phi, d, dmin = 1e9;
	// First, among discrete values of phi
	int n = 10000, j, k = 0;
	for (j = 0; j <= n; j++)
	{	phi = pi/2 * j/n;
		d = sidelength(phi, X, Y);
		if (d < dmin)
		{	dmin = d;
			k = j;
		}
	}
	// Next, a ternary search near the discrete minimum
	double lb = pi/2 * (k-1)/n;
	double ub = pi/2 * (k+1)/n;
	double phi1, phi2, d1, d2;
	while (ub-lb > eps)
	{	phi1 = (2*lb+ub)/3;
		phi2 = (lb+2*ub)/3;
		d1 = sidelength(phi1, X, Y);
		d2 = sidelength(phi2, X, Y);
		if (d1 > d2)
			lb = phi1;
		else
			ub = phi2;
	}
	phi = (lb+ub)/2;
	d = sidelength(phi, X, Y);
	return d*d * area(X, Y);
}

int main()
{	double lb = pi/2, ub = 2*pi/3, theta, theta1, theta2, A1, A2;
	// Ternay search
	while (ub-lb > eps)
	{	theta1 = (2*lb+ub)/3;
		theta2 = (lb+2*ub)/3;
		A1 = tablearea(theta1);
		A2 = tablearea(theta2);
		if (A1 < A2)
			lb = theta1;
		else
			ub = theta2;
	}
	theta = (lb+ub)/2;
	printf("%.10lf\n", tablearea(theta));
	return 0;
}