#include <stdio.h>
#include <primesieve/soe/PrimeSieve.h>
typedef long long ll;
ll N,ans;

void pcb(uint64_t p) {
  ans-=(p>N/p?N/p:p);
}

int main(int argc, char* argv[]) {
  ans=N=(argc<1?1:atoll(argv[1]));
  PrimeSieve ps;
  ps.generatePrimes(2,N,pcb);
  printf("%lld\n",ans);
}