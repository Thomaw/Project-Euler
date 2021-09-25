#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>

typedef __int64 int64;
typedef unsigned __int64 uint64;
struct timer
{
   clock_t t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", getTime()); }
   double getTime() { return ((double)clock()-(double)t)/(double)CLOCKS_PER_SEC; }
};

double choose(int n, int k)
{
    double accum = 1;
    int i=0;
    while (++i<=k)
         accum *= (double)(n-k+i) / i;
    return accum;
}

void f267()
{
   // for a=number of heads -> F(a,f)=(1+2f)^a * (1-f)^(1000-a)
   // dF/df=0 -> f_max(a)=(3a-1000)/2000
   // find the lowest a that satisfies
   // F(a,f_max(a))=(3a/1000)^a * ((3000-3a)/2000)^(1000-a) > 10^9
   double lg2000=log10(2000);
   int a=500, b=0, diff;
   while (diff=a-b, b=a, diff!=0)
   {
      if (diff<0)
         diff=-diff;
      double a3=a*3, d=a*(log10(a3)-3)+(1000-a)*(log10(3000-a3)-lg2000);
      if (d>9)
         a-=diff/2;
      else
         a+=diff/2;
   }
   // find the number of ways to choose below this lowest a
   double t=0;
   while (--a>0)
      t+=choose(1000,a);
   printf("p=%.12f\n", 1-t/pow(2,1000));
}
int main(int argc, char**argv)
{
   timer t;
   f267();
   return 0;
}
/*
p=0.999992836187
runtime 0.002 secs
*/