//cl /openmp /O2 /Ox /favor:INTEL64 1.cpp
#include <windows.h>
#include <iostream>
#include <vector>
using namespace std;
typedef unsigned __int64 u64;
u64 gcd(u64 a,u64 b){ while(b){u64 c=a%b; a=b; b=c;} return a;}
#define L 1000000000000ULL
vector<u64> fact[1000000+1];

u64 coprime_count(u64 c,u64 n) {
  auto &f=fact[n];
  u64 z=c, l=1<<f.size();
  for(u64 m0=1; m0<l; m0++){
    u64 r=1,d=1;
    for(u64 m=m0,i=0; m; m>>=1,i++) if(m&1) {r*=f[i];d=-d;}
    z+=c/r*d;
  }
  return z;
}

void main() {
  u64 t0=GetTickCount();
  u64 s=0,l=sqrt(L);
  for(u64 n=2; n<=l; n++) if(fact[n].empty()) for(u64 x=n; x<=l; x+=n) fact[x].push_back(n);
#pragma omp parallel for reduction(+ : s) schedule(dynamic,1)
  for(__int64 n=2; n<=l; n++) {
    u64 l0=L/n;
    u64 l2=min(n-1,l0-n);
    u64 f2=coprime_count(l2,n);
    for(u64 k=2; l2 && l0/k>k; k++) {
      u64 l1=l0/k<n? 0 : min(n-1,l0/k-n);
      if(l1<l2) {
        u64 f1=coprime_count(l1,n);
        s+=(f2-f1)*(k-1);
        f2=f1;
        l2=l1;
      }
    }
    for(u64 m=1; m<=l2; m++)
      if(gcd(n,m)==1) s+=l0/(n+m);
  }
  cout << s;
  cout << endl << GetTickCount()-t0;
}