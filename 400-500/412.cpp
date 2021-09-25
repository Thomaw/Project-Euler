#include <iostream>
using namespace std;
typedef unsigned __int64 u64;
#define R 5000
#define M 76543217

u64 inv(u64 n, u64 m=M) { return n>1 ? m/n*(m-inv(m%n, m))%m : 1; }
u64 factmod(u64 n, u64 p=M) { 
  u64 res = 1; 
//  while (n) { 
    for (u64 i = 1, m = n % p; i <= m; i++) res = res * i % p; 
//    if ((n /= p) & 1 ) res = p - res; 
//  } 
  return res; 
}

void main() {
  u64 a=1,b=1;
  u64 i1=R,i2=0,i3=R*3,i4=R*2;
  u64 f1=factmod(i1);
  u64 f2=factmod(i2);
  u64 f3=factmod(i3);
  u64 f4=factmod(i4);
  while(i2<R) {
    a=a*f1%M*inv(f2)%M;
    b=b*f3%M*inv(f4)%M;
    f1=f1*++i1%M;
    f2=f2*++i2%M;
    f3=f3*++i3%M;
    f4=f4*++i4%M;
  }
  cout << factmod(R*R*3)*inv(a*a%M*b%M)%M;
}