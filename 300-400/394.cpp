#include<stdio.h>
#define N 10000000ll 
int main() {
  long double L=7.5,dL=(L-1)/(N-1),l=1,l0,E0=1,E,sE=0;
  long long i;

  for(i=1;i<N;i++) {
    l0=l;
    l+=dL;
    E= 1 + (2*dL*sE+(E0-1)*l0*l0+dL*dL*E0) / (l*l);
    sE+=E*dL;
    E0=E;
  }
  printf("%.12llf\n",E);
}