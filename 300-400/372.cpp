#include<stdio.h>
#include<math.h>

//#define N 100
//#define M 1
//#define N 100000ll
//#define M 1001ll

#define N 1000000000ll
#define M 2000001ll

int main() {

  long double t1,t2,s1,s2;
  long long count=0,t3=0,o,omax,ymin,ymax,x,y;

  omax=N*N/(M*M);
  for(o=1;o<=omax;o+=2) {
    t1=sqrtl(o);
    t2=sqrtl(o+1);    
    t3=t2;
    if(t3*t3<o+1)t3=0;

    s1=t1*M;
    s2=t2*M;
    for(x=M;x<=N;x++,s1+=t1,s2+=t2) {
      ymin=s1-1;
      while(ymin*ymin<o*x*x)ymin++;

      ymax=s2+1;
      while(ymax*ymax>=(o+1)*x*x)ymax--;
      
      if(ymin>N)break;
      if(ymax>N)ymax=N;
      if(ymax<ymin)continue;
      
      count+=ymax-ymin+1;
    }
  }
  printf("%lld\n",count);
  
}