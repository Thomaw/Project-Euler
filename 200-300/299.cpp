#include <stdio.h>
#define limit 100000000ll
#define int long long int
int gcd(int a,int b){while(b){int c=a%b;a=b;b=c;} return a;}
int i,j,a,b,d,s=0;

#undef int
int main() {
  for(i=1;i*i<2*limit;i+=2)for(j=1;j<i;j+=2)if(gcd(i,j)==1) {
    b=(i*i-j*j)/2;
    d=i*j;
    a=b+d-(i*i+j*j)/2;
    if(b+d>=limit)break;
    s+=(limit-1)/(b+d)*2;
  }
  for(i=1;4*i*i<limit;i++)for(j=1;;j+=2)if(gcd(i,j)==1){
    a=2*i*i+j*j;
    b=a+2*i*j;
    d=b;
    if(2*b>=limit)break;
    s+=(limit-1)/(2*b);
  }
  printf("s=%lld\n",s);
}