#include <iostream>
using namespace std;
typedef unsigned __int32 u32;

#define N 16
#define L 4
#define M 1000000000

u32 g[L];
void main() {
  u32 s=0;
  for(u32 n=1; n<N; n++) {
    for(u32 i=0,gg=n; i<L ;i++,gg>>=1) g[i]=gg&1;
    u32 k=2;
    for(;;k++) {
      k+=g[0]; if(k>=M)k-=M;
      g[0]=k;
      if(g[1])g[1]--;else{g[1]=k;
      if(g[2])g[2]--;else{g[2]=k;
      if(g[3])g[3]--;else break;
      }}
    }
    k-=2; s=(s+k)%M;
    cout << n << " " << k << " " << s  << endl;
  }
  cout << s;
}