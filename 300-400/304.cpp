#include <iostream>
#include "mpir.h"
#define S 100000000000000LL
#define L 100000
#define M 1234567891011LL

mpz_t n;
void main() {
  __int64 nn=1,s=0,f0=512884989226,f1=921144120792,f;
  for(double x=S+1;nn<=L;x++) {
    f=(f0+f1)%M; f0=f1;f1=f;
    mpz_set_d(n,x); 
    if(mpz_probab_prime_p(n, 5)){ s+=f; nn++; };
  }
  std::cout << s%M;
}