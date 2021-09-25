#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void Throw(int d,int n,int s,int P[])
  {
  if(n==0) 
    {
    P[s]++;
    return;
    }
  
  for(int i=1;i<=d;i++) Throw(d,n-1,s+i,P);
  }
  

int main()
  {  
  double time=clock();
  
  const int M = 36;
  
  int P[M+1],C[M+1];
  for(int i=0;i<=M;i++) P[i]=C[i]=0;
  
  Throw(4,9,0,P);
  Throw(6,6,0,C);
  
  long long a=0,b=0;
  for(int i=1;i<=M;i++)
     {
     for(int j=1;j<i;j++) a+=P[i]*C[j];
     for(int j=1;j<=M;j++) b+=P[i]*C[j];
     }
  
  cout.precision(7);
  cout<<double(a)/double(b)<<" in "<<clock()-time<<"ms"<<endl;  
  system("Pause"); return 0;
  }
