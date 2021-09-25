#include <iostream>
#include <vector>
using namespace std;
typedef unsigned __int8 u8;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;
typedef unsigned __int128 u128;
#define L  10000000000000000ULL
#define L1 100000000ULL

u64 powmod(u64 x,u64 y,u64 m){u64 r=1; for(;y;y>>=1){if(y&1)r=(u128)r*x%m; x=(u128)x*x%m;} return r;}
//#define T0(x) if(n%x==0)return n==x;
#define T1(r)\
  x=powmod(r,d,n); if(x!=1 && x!=n-1){\
  for(i=s;--i;){x=(u128)x*x%n; if(x==1)return 0; if(x==n-1)break;}\
  if(!i)return 0;}
int is_prime(u64 n){
//  T0(2)T0(3)T0(5)T0(7)T0(11)T0(13)
  u64 d=n-1,s=0,x,i; for(;~d&1;d>>=1)s++; 
  T1(2)T1(1215) if(n<65281)return 1;
  T1(34862)     if(n<518548801)return 1;
  T1(574237825)
  return 1;
}
 
#define M (315*8*2*3*5*7*11*13)
#define N (L/M*M)
u8 r1[M];
vector<u32> r;
u32 d[]={1,6,1,4,315,2,1,24,1};
//u32 d[]={1,24,1,2,315,4,1,6,1};
void c(u64 x) {
  int i=-4;
  u64 ss=0;
  for(auto y:d) { 
    u64 p=(x+i++)/y;
    if(!is_prime(p)) return;
    ss+=p;
  }
  cout << ss; exit(0);
}

int main() {
#pragma omp parallel for
  for(int i=0; i<M; i++)
  for(int j=0; j<=8; j++) {
    int x=(M+i+j-4)%M;
    if(x%d[j]==0) {
      x/=d[j];
      if(x%2 && x%3 && x%5 && x%7 && x%11 && x%13) continue;
    }
    r1[i]=1;
  }
  for(int i=M-1; i; i--) if(!r1[i]) r.push_back(i);
#pragma omp parallel for schedule(static, 1)
  for(u64 dd=0;dd<N;dd+=M)
    for(auto x:r) c(N-dd+x);
}