#include<iostream>
#include<gmpxx.h>
typedef long double LLF;
//typedef mpz_class LLF;

#define N 10000000
#define M 100
#define K (N/(M-1))

LLF a,b,c, E=0,dE,cnt,all=1,binom_M[M-1]={1};
int i,k,n;

int main() {
  for(i=0;i<M-1;i++) all=all*(N-1-i)/(i+1);  // C(N-1,M-1)
  for(i=0;i<M-2;i++) binom_M[i+1]=binom_M[i]*(M-i)/(i+1);  // C(M,i)

  for(k=1;k<=K;k++) {  // length of second part
    dE=0; 
    a=(N-M*k-1>=0);         // C(N-Mk-1,n-1)            n>=1
    b=(N-M*k+k-1>=0);       // C(N-Mk+k-1,n)            n>=0
    c=(N-M*k>=0);           // C(N-Mk,n)                n>=0

    for(n=0;n<=M-2;n++) { // number of parts longer than second 
      cnt=0;
      // case 1: all 100-n parts equal k
      if(n==0) { if(N==M*k) cnt++; }
      else {
        cnt+=a;
        a=a*(N-M*k-1 -(n-1))/n;
      }
      // case 2: one of those 100-n parts is smaller by 1,2,3..k-1
      if(k>1) {
        cnt+=(M-n)*(b-c);
        b=b*(N-M*k+k-1 -n)/(n+1);
        c=c*(N-M*k -n)/(n+1);
      }
      dE+=cnt*binom_M[n];
    }
    E+=k*dE;
  }
  std::cout.precision(12);
  std::cout<<"E="<<E/all<<std::endl;
  //std::cout<<"E="<<mpq_class(E)/all<<std::endl;
}