#include<stdio.h>
#include"primes.h"
#define N 10000000000ll
#define M 100000  /*sqrt(N)*/
#define bigint long long
#include"math.h"

bigint primes[M],nprimes,i;
int factors[30],powers[30];

bigint sum=0;
void teste(bigint n, int level) {
  int i;
  bigint f=1,f3,pr,pw;
  for(i=0;i<level;i++){
    pr=factors[i];
    f*=pr-1;
    for(pw=(powers[i]*2-1)%3;pw--;)f*=pr;
  }
  f3=(bigint)roundl(powl(f,1./3));
  if(f3*f3*f3==f) sum+=n;
}

void recurse(int level,int ip, bigint n) {
  bigint n0=n,i,nmax;
  if(n>1) teste(n,level);
  for(i=ip;i--;){
    n=n0;
    factors[level]=primes[i];
    powers[level]=0;
    if(level==0) {
      n=primes[i]*primes[i];
      powers[level]=2;
      nmax=N/primes[i]/primes[i]/primes[i];
      while(n<N){
        recurse(level+1,i,n);
        if(n>nmax)break;
        n*=primes[i]*primes[i]*primes[i];
        powers[level]+=3;
      }
    }
    else {
      nmax=N/primes[i];
      while(n<=nmax){
        n*=primes[i];
        powers[level]++;
        recurse(level+1,i,n);
      }
    }
  }
}

int main() {
  alloc_sieve(M);
  sieve_primes();
  nprimes=0;
  for(i=2;i<M;i++)if(is_prime(i))primes[nprimes++]=i;
  printf("\n%d\n",nprimes);
  recurse(0,nprimes,1);
  printf("%lld",sum);
}