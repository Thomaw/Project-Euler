#include <iostream>
using namespace std;
typedef unsigned __int64 u64;
#define L 100000000
u64 gcd(u64 a,u64 b){while(b){u64 c=a%b;a=b;b=c;}return a;}
char np[L];
int main() {
  u64 s=0;
  np[1]=1;
  for(u64 n=2; n<L; n++) if(!np[n]) for(u64 x=n*n; x<L; x+=n) np[x]=1;
  for(u64 z=2; z<L/4; z+=z<4?1:2)
  for(u64 y=1,a,b; (a=z*y*y-1)<L; y++) if(!np[a])
  for(u64 x=y+1,c; (c=z*x*x-1)<L; x++) if(!np[c] && !np[b=z*y*x-1] && gcd(x,y)==1) s+=a+b+c;
  cout << s;
}