#include <windows.h>
#include <iostream>
#include "mpir.h"
using namespace std;
typedef unsigned __int64 u64;
typedef unsigned __int32 u32;
typedef unsigned __int8 u8;
#define L 10000000000ULL

void main() {
  char *np=(char *)VirtualAlloc(0, (L+1), MEM_COMMIT, PAGE_READWRITE);
  char *mu=(char *)VirtualAlloc(0, (L+1), MEM_COMMIT, PAGE_READWRITE);

  for(u64 n=1;n<=L;n++) mu[n]=1;
  for(u64 n=2;n<=L;n++) if(!np[n]) {
    if(n<=100000){
      u64 nn=n*n;
      for(u64 x=nn;x<=L;x+=n)  np[x]=1;
      for(u64 x=nn;x<=L;x+=nn) mu[x]=0;
    }
    for(u64 x=n;x<=L;x+=n) mu[x]*=-1;
  }

  mpz_t x,y,z;
  mpz_init_set_si(x,3);
  mpz_init(y);
  mpz_init(z);
  u64 s=3;
  for(u64 n=1;n<=L;n++) {
    u64 k=L/n;
    mpz_set_d(y,k);
    mpz_add_ui(z,y,3);
    mpz_mul(z,z,y);
    mpz_mul(z,z,y);
    mpz_mul_si(z,z,mu[n]);
    mpz_add(x,x,z);
  }
  cout << mpz_get_str(NULL,10,x) << endl;
}