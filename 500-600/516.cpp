#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;
typedef unsigned __int128 u128;
#define L 1000000000000ULL
u64 powmod(u64 x,u64 y,u64 m){u64 r=1; for(;y;y>>=1){if(y&1)r=(u128)r*x%m; x=(u128)x*x%m;} return r;}
// tested for 10^12, supposed to work up to 21,652,684,502,221
#define T0(x) if(n%x==0)return n==x;
#define T1(r) x=powmod(r,d,n); if(x!=1 && x!=n-1){for(i=s;--i;){x=(u128)x*x%n;if(x==1)return 0;if(x==n-1)break;}if(!i)return 0;}
int is_prime(u64 n){
  T0(2)T0(3)T0(5)T0(7)T0(11)T0(13)
  u64 d=n-1,s=0,x,i; for(;~d&1;d>>=1)s++; 
  T1(2)T1(1215) if(n<65281)return 1;
  T1(34862)     if(n<518548801)return 1;
  T1(574237825)
  return 1;
}

vector<u64> a,b,c;
u32 ss=0;
void r(u64 n=1, u64 i=3){
  u64 l=L/n;
  ss+=c[upper_bound(a.begin(),a.end(),l)-a.begin()-1]*n;
  for(;b[i]<=l;i++) r(n*b[i],i+1);
}

int main() {
  for(u64 x=1;x<=L;x*=2) 
  for(u64 y=x;y<=L;y*=3) 
  for(u64 z=y;z<=L;z*=5) {
    a.push_back(z);
    if(is_prime(z+1)) b.push_back(z+1);
  }
  sort(a.begin(),a.end()); u32 s=0; for(auto x:a)c.push_back(s+=x);
  sort(b.begin(),b.end()); b.push_back(-1);
  r();
  cout << ss;
  return 0;
}