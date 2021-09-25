#include<stdio.h>
#define int64 long long int

// solves n*x==a (mod m), iterations
int solve(int n, int a, int m) {
  int x=0,y=0;
  while(x<m){x++;y+=n;if(y>m)y-=m;if(y==a)return x;}
  fprintf(stderr,"solve: no solutions in %d x = %d (mod %d)\n",n,a,m);
}

int64 A=1ll*2*3*5*11*17*23*29*41;
int p[]={7,13,19,31,37,43};
int m[]={2, 3, 7, 5,10, 6}; // solves m*m+m+1==0 (mod p)
int64 x[6][43][43];

int main() {
  int i,j,ii,jj;
  int64 a,b,c,sum=0;
  for (j=0;j<6;j++)for(a=1;a<p[j];a++)for(b=1;b<p[j];b++)
    x[j][a][b]=solve(a,b,p[j]);

  for(i=1;i<3*3*3*3*3*3;i++){
    a=A;b=1;
    for(ii=i,j=0;j<6;j++,ii/=3)if(!(ii%3))a*=p[j];
    for(ii=i,j=0;j<6;j++,ii/=3)if(jj=ii%3){
      c=m[j];if(jj>1)c=p[j]-1-c;
      c-=b;
      c%=p[j];if(c<0)c+=p[j];
      b+=a*x[j][a%p[j]][c];
      a*=p[j];
    }
    printf("%lld\n",b);
    sum+=b;
  }
  printf("%lld\n",sum);
}
