#include <iostream>
#include <map>
using namespace std;
typedef unsigned __int64 u64;
typedef unsigned char u8;

#define L 200000

int p[L+1],pp;
u8 np[L+1];

int LL=sqrt((double)L);

u64 r(u64 s0) {
  u64 ss=s0;
  map<int,int> mn,m1;
  int q0;

  for(int n0=0; (q0=p[n0])<=LL; n0++) if(q0>0) {
    int ms=q0,mr=0;
    while(ms*q0<=L) ms*=q0;
    for(int q=q0;;q*=q0) {
      int r=L/q; while(np[r])r--;
      if(r<=LL)break;
      int s=q*r-r;
      if(ms<s) { ms=s; mr=r; }
    }
    ms-=q0;
    if(mr && mn.count(mr)) {
      int n1=mn[mr];
      np[mr]=1;
      p[n0]^=-1; u64 r1=r(s0+ms);     p[n0]^=-1;
      p[n1]^=-1; u64 r2=r(s0+m1[mr]); p[n1]^=-1;
      np[mr]=0;
      return r1>r2 ? r1 : r2;
    }
    ss+=ms;
    mn[mr]=n0;
    m1[mr]=ms;
  }
  return ss;
}

void main() {
  u64 ss=1;
  for(int n=2;n<=L;n++) if(!np[n]) {
    for(int x=n+n;x<=L;x+=n) np[x]=1;
    ss+=p[pp++]=n;
  }
  cout << r(ss);
}