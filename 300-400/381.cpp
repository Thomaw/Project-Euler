#include <iostream>
using namespace std;
typedef unsigned __int64 u64;
#define L 100000000
char np[L+1];

u64 inv(u64 n, u64 m) { return n>1 ? m/n*(m-inv(m%n, m))%m : 1; }
u64 S(u64 n) {
  u64 s1=n-1;
  u64 s2=s1*inv(n-1,n)%n;
  u64 s3=s2*inv(n-2,n)%n;
  u64 s4=s3*inv(n-3,n)%n;
  u64 s5=s4*inv(n-4,n)%n;
  return (s1+s2+s3+s4+s5)%n;
}

void main() {
  u64 s=0;
  for(u64 n=2;n<L;n++) if(!np[n]) {
    for(u64 x=n*n;x<=L;x+=n) np[x]=1;
    if(n>=5) s+=S(n);
  }
  cout << s << endl;
}