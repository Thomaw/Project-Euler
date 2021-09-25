#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef unsigned __int64 u64;
#define L 1000000ULL
#define N L*L
char np[L+1];
vector<u64> p;
vector<double> d;

double r(u64 n=1,u64 c=7,u64 i=0){
  if(c==1) return 1.0/((double)n*n)*d[i];
  double s=0;
  for(; i+c<p.size() && pow(p[i],c)*n<N; i++) for(u64 x=n; (x*=p[i])<N; ) s+=r(x,c-1,i+1);
  return s;
}

int main(){
  for(u64 n=2;n<=L;n++) if(!np[n]){
    for(u64 x=n*n;x<=L;x+=n) np[x]=1;
    p.push_back(n);
  }
  d.resize(p.size());
  double x,y,z=0;
  for(int i=p.size()-1; i>=0; i--) {
    for(x=y=p[i]*p[i]; x<N; x*=y) z+=1.0/x;
    d[i]=z;
  }
  cout<<r()*6/M_PI/M_PI;
}