#include <stdio.h>
#include <math.h>

#define limit 100000000
#define lfsize 120000000

long long unsigned count=0, a,b,c, x,n,p, i,j, opti,imax;
long double optb,optc;
int lfactor[lfsize];

int main() {
  for (i=0;i<lfsize;i++) lfactor[i]=1;
  for (i=2;i<lfsize;i++) 
    if (lfactor[i]==1) 
      for (j=i*i;j<lfsize;j+=i) if (lfactor[j]==1) lfactor[j]=i;

  for (x=0;;x++) {
    a=3*x+2;
    optb=exp(log(2.0*(x+1)*(x+1)*(8*x+5))/3);
    optc=optb/2;
    if (a+optb+optc>limit) break;

    n=8*x+5;
    p=1;b=x+1;c=1;
    while (n>1) {
      p=lfactor[n];if (p==1) p=n;
      i=0; do {n/=p;if (i++&1) b*=p;} while (p==lfactor[n]||(n==p));
      if (i&1) c*=p;
    }

    opti=sqrt(optc/c);
    imax=sqrt(limit/c);

    for (i=opti;i>=1;i--) if (b%i==0) {
      if (a+b/i+c*i*i>limit) break;
      count++;
    }
    for (i=opti+1;i<=imax;i++) if (b%i==0){
      if (a+b/i+c*i*i>limit) break;
      count++;
    }
  }

  printf("count=%llu\n",count);
}
