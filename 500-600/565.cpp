#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef unsigned __int64 u64;
typedef unsigned __int128 u128;
#define L 100000000000
#define L1 320000
#define M 2017
#define L2 (L/M)
u64 inv(u64 n,u64 m=M){return n>1?m/n*(m-inv(m%n,m))%m:1;}
unsigned char np[L1],np2[L2];
u64 e[M];
int main() {
  vector<pair<u64,u64>> ab;
  for(u64 n=2; n<L1; n++) if(!np[n]) {
    for(u64 x=n*n; x<L1; x+=n) np[x]=1;
    if(n<M)
      for(u64 x=(inv(n)*(M-1)%M*n+1)/M; x<L2; x+=n) np2[x]=1;
    if(n>M)
      for(u64 x=n*n; x<L; x+=n) if((x+1)%M==0) {for(u64 y=(x+1)/M; y<L2; y+=n) np2[y]=1;break;}
    for(u64 m=n*n,s=n+1; m<=L; m*=n) if((s+=m)%M==0) {ab.push_back(make_pair(m,n));break;}
  }
  for(u64 x=1,i=M-1; x<L2; x++,i+=M) if(!np2[x]) ab.push_back(make_pair(i,i));
  sort(ab.begin(),ab.end());
  u64 s=0;
  for(u64 i=0; i<ab.size(); i++) {
    u64 a=ab[i].first,b=ab[i].second*a;
    s+=a*(L/a)*(L/a+1)/2;
    for(u64 c=b; c<=L; c+=b) s-=c;
    for(u64 j=i+1; j<ab.size(); j++) {
      u64 c=a*ab[j].first; if(c>L) break;
      s-=c*(L/c)*(L/c+1)/2;
    }
  }
  cout<<s;
}