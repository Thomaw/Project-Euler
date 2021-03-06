#include<stdio.h>
#include<math.h>
#define N 10000000000ll

int main() {
  long long b,bmax=sqrtl(2*N-1),s=0;

  #pragma omp parallel for reduction(+:s) schedule(dynamic)
  for(b=2;b<=bmax;b+=2) {
    long long c,cmax,t,diff;
    cmax=sqrtl((((long double)N)*4*N+1)/(1+b*b)-1);
    t=1+b*b;diff=-1;
    for(c=b;c<=cmax;diff+=(4*c+4)*(1+b*b),c+=2) {
      while(diff>0) diff-=2*t+1, t++;
      if(diff==0 && t%2==0) s+=t/2;
      diff-=4*b*t+4*b*b, t+=2*b;
    }
  }

  printf("%lld\n",s);
}