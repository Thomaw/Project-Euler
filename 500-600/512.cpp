#include <iostream>
typedef unsigned __int64 u64;
#define L 500000000ULL
#define L2 (L/2)
int phi[L2+1];
void main() {
  u64 s=1;
  for(u64 n=1; n<=L2; n++) phi[n]=1;
  for(u64 n=3; n<=L; n+=2) {
    if(phi[n>>1]==1) {
      for(u64 x=n>>1; x<=L2; x+=n) phi[x]*=n-1;
      for(u64 xx=n*n; xx<=L; xx*=n)
      for(u64 x=xx>>1; x<=L2; x+=xx) phi[x]*=n;
    }
    s+=phi[n>>1];
  }
  std::cout << s;
}