#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef unsigned __int8  u8;
typedef unsigned __int64 u64;
#define N 500500
#define L (N*16)
#define M 500500507ULL
u64 powmod(u64 x,u64 y,u64 m=M){u64 r=1; for(;y;y>>=1){if(y&1)r=r*x%m; x=x*x%m;} return r;}

struct xpowy{
  u64 x,y;
  bool operator <(xpowy &b){ return log(x)*(y+1)>log(b.x)*(b.y+1); }
};
u8 np[L+1];

void main() {
  vector<xpowy> v;
  for(u64 n=2; n<=L; n++) 
  if(!np[n]){
    for(u64 x=n*n; x<=L; x+=n) np[x]=1;
    v.push_back({n,0});
  }
  make_heap(v.begin(),v.end());

  for(int i=0;i<N;i++){
    v[0].y=v[0].y*2+1;
    pop_heap(v.begin(),v.end());
    push_heap(v.begin(),v.end());
  }

  u64 s=1;
  for(auto x:v) s=s*powmod(x.x,x.y)%M;
  cout << s;
}