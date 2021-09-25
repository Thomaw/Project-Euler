//400ms
#include <iostream>
using namespace std;

double v;
#define integrate(name,XXX) \
double name()\
{\
  double s=0;\
  for(double t=0,x0=1,y0=0; t<=1; t+=1./(1<<20)) {\
    double x1=(1-t)*(1-t)*(1-t)+3*(1-t)*(1-t)*t+3*(1-t)*t*t*v;\
    double y1=3*(1-t)*(1-t)*t*v+3*(1-t)*t*t+t*t*t;\
    s+=XXX;\
    x0=x1; y0=y1;\
  }\
  return s;\
}
integrate(A, (y1+y0)*(x0-x1)/2 )
integrate(L, sqrt((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1)) )

void main() {
  cout.precision(10);cout.setf(ios::fixed);
  double sq=0.785398163397448309615; //pi/4
  for(double v0=0,a=0.5,b=1; (v=(a+b)/2)!=v0; v0=v)
    A()<sq? a=v:b=v;
  sq*=2;
  cout << 100*(L()-sq)/sq;
}