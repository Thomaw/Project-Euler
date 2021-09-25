#include<stdio.h>
#include<stdlib.h>

#define N 10000000 

typedef long double LLF;

LLF *inv,*suminv;
char *moebius;

int main() {

  int i,j,ii;
  char squares=1;
  
  inv=malloc((N+1)*sizeof(LLF));
  suminv=malloc((N+1)*sizeof(LLF));
  suminv[0]=inv[0]=0;
  for(i=1;i<=N;i++) suminv[i]=suminv[i-1]+(inv[i]=1.l/i);

  moebius=malloc((N+1)*sizeof(char));
  for(i=0;i<=N;i++) moebius[i]=2;
  moebius[1]=1;

  for(i=2;i<=N;i++) {
    if(moebius[i]==2) {
      for(j=i;j<=N;j+=i) {
        if(moebius[j]==2) moebius[j]=-1;
        else moebius[j]=-moebius[j];
      }
      if(squares) {
        ii=i*i;
        squares = ii<N;
        for(j=ii;j<=N;j+=ii) moebius[j]=0;
      }
    }
  }
  for(;i<=N;i++) if(moebius[j]==2) moebius[j]=-1;

  int p,q,t;
  LLF total = 0;

  for(t=1;t<=N;t++) if(moebius[t]) { 
    LLF sum=0,d;
    LL qmax=N/t;
    for(q=2;q<=qmax;q++) {
      p=qmax-q;
      if(q-1<p) p=q-1;
      d = p+inv[t]*suminv[p];
        if(p<q-1) d+=(N-t*q+1)*inv[t]*(suminv[q-1]-suminv[p]);
        sum+=inv[t*q]*d;
    }
    total+=moebius[t]*sum;
  }

  printf("%.10llf\n",total);
}
