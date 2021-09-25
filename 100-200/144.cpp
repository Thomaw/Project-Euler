#include<iostream>
#include"math.h"

struct point{ double x,y; };

point vertex(double m, double c, point old){
	double x1, x2;
	point b;
	// solution of 4x^2 + (mx+c)^2 = 100:
	x1 = (-2*m*c + sqrt(400*m*m+1600-16*c*c))/(8+2*m*m);
	x2 = (-2*m*c - sqrt(400*m*m+1600-16*c*c))/(8+2*m*m);
	if (fabs(old.x-x1)<0.0001) b.x = x2; else b.x = x1;
	b.y = m*b.x + c;
	return b;	
}

point next(point a, point b){
	double new_slope = tan(-atan((a.y-b.y)/(a.x-b.x))+2*atan(-4*b.x/b.y));
	return vertex(new_slope, b.y-new_slope*b.x, b);
}

int main(){
	point a,b,c;
	a.x = 0; a.y = 10.1;
	b.x = 1.4; b.y = -9.6;
	int i = 1;
	while (!(fabs(b.x) < 0.01 && b.y>0)) {
		c = b;
		b = next(a, b);
		a = c;
		std::cout << "\r" << i++  << "   ";
	}
	return 0;
}