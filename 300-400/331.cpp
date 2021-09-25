#include <iostream>
using namespace std;
typedef unsigned __int64 u64;
typedef unsigned char u8;
 
u8 xx[1<<30];
 
void main() {
  u64 ss=3;
  for(u64 i=4;i<=31;i+=2) {
    u64 n=(1U<<i)-i;
    memset(xx,0,n);

    u64 x=n-1,y=0;
    u64 n1=x*x, n2=n*n;
    u64 d=n1+1;
    while(x>y){
      xx[x]^=1;
      xx[y]^=1;
      bool f1 = d+y+y >= n2;
      bool f2 = d-x-x <  n1;
      if(f1) d-=(x--<<1)-1;
      if(f2) d+=(y++<<1)+1;
    };
    xx[x]^=1;
    if(x<y) xx[y]^=1;
 
    u64 s=0;
    for(u64 x=0; x<n; x++) s+=xx[x];
    s=2*s*(n-s);
 
    x=n-1, y=0;
    d=n1+1;
    while(x>y){
      if(xx[x]^xx[y]) s-=2; else s+=2;
      bool f1 = d+y+y >= n2;
      bool f2 = d-x-x <  n1;
      if(f1) d-=(x--<<1)-1;
      if(f2) d+=(y++<<1)+1;
    }
    if(x==y) s++;

    cout << n << " " << s << " " << (ss+=s) << endl;
  }
}