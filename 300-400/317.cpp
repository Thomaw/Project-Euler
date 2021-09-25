#include<stdio.h>
#include<math.h>
int main() {
  long double g=9.81,v=20,h=100,x=0,a,y=0,V=0,dx=0.0001,t;
  while(y>-h){
    x+=dx;
    a=atan((v*v/g)/x);
    t=x/v/cos(a);
    y=v*t*sin(a)-g/2*t*t;
    V+=(y+h)*dx*2*M_PI*x;
  }
  printf("V=%llf\n",V);
}