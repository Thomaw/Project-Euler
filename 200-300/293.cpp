#include <iostream>
using namespace std;

#define L 1000000000U
typedef unsigned short u16;
typedef unsigned char u8;

u8 mm[1000];

void main() {
  u16 *fact=new u16[L];  memset(fact, 0, L*2);
  u8  *admi=new u8 [L];
  for(int n=2; n<L; n++) admi[n]=1-n&1;

  int pp=0;

  for(int n=2; n<L; n++) {
    if(fact[n]) continue;
    for(int x=n+n; x<=L; x+=n) {
      if(fact[x] && fact[x]!=pp) admi[x]=0;
      fact[x]=n;
    }
    pp=n;
  }

  int s=0;
  for(int n=2; n<L; n++) {
    if(!admi[n]) continue;
    int m;
    for(m=2;fact[n+m];m++);
//    cout << n << " " << m << endl;
    if(mm[m]) continue; mm[m]=1;
    s+=m;
  }

  cout << s;
}