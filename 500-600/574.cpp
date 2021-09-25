#include <stdio.h>

#define  N 3800

int p[N],n,id,i;
__int128 bm,d=1;

int prime(int n) {
  int i;
  for (i=2;i*i<=n;i++) if (n%i==0) return 0;
  return 1;
}

void crt(int j,__int128 s) {
  long long b,inv=0;
  if (j<id) {
    for (inv=0;inv<p[j];inv++) if (d/p[j]*inv%p[j]==1) break;
    for (b=0;b<p[j];b++)
      if ((b*b+b*n)%p[j]==0)
        crt(j+1,(s+d/p[j]*inv*b)%d);
  } else if (s&&s<bm) bm=s;
}

int main() {
  long long s=1; // For 1+1=2.
  // Otherwise either A or B is even. No need for checking divisibility by 2.
  // It doubles the speed.
  for (n=3;n<N;n++)
    if (prime(n)) {
      p[i++]=n;
      while (n>=p[id]*p[id]) d*=p[id++];
      long long a=(n+1)/2;
      while (a<n&&a*(n-a)%d) a++; // A+B<q^2
      if (a==n) { // A-B<q^2
        bm=d;
        crt(0,0);
        a=bm+n;
      }
      s+=a;
    }
  printf("%llu\n",s);
  return 0;
}