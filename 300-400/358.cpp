#include<stdio.h>
#include<primes.h>
#define nmin 724637682
#define nmax 729927008

long long n,r,a,s=0,i;
char used[nmax];
int main() {
  alloc_sieve(nmax);
  sieve_primes();
  for(n=nmin;n<nmax;n++)if(is_prime(n)&&(56789*n+1)%100000==0) {
    memset(used,0,nmax);
    r=1;s=0;
    for(i=0;!used[r];i++) {
      used[r]=1;
      r*=10;
      s+=a=r/n;
      r-=a*n;
    }
    if(i==n-1) printf(" n=%lld s=%lld\n",n,s);
  }
}