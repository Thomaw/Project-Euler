#include <stdio.h>
#include <math.h>
typedef long long ll;
ll reverse(ll n) {
  ll r=0;
  while(n) r=r*10+n%10,n/=10;
  return r;
}
int issquare(ll n) {
  int q;
  if((n&3)>1) return 0;
  q=(int)(.5+sqrt(n+.5));
  return q*q==n;
}
int check(ll n) {
  int num=0,i;
  ll v;
  for(i=2;(ll)i*i*i<n;i++) {
    v=n-i*i*i;
    if(issquare(v)) num++;
  }
  return num;
}

int main() {
  int len,times=10,i,k,found=0;
  ll ans=0,n;
  for(len=1;;len++) {
    for(i=times/10;i<times;i++) {
      n=i*times+reverse(i);
      if(check(n)==4) {
        printf("found %I64d\n",n);
        ans+=n;
        found++;
        if(found==5) goto done;
      }
    }
    for(i=times/10;i<times;i++) for(k=0;k<10;k++) {
      n=i*times*10+k*times+reverse(i);
      if(check(n)==4) {
        printf("found %I64d\n",n);
        ans+=n;
        found++;
        if(found==5) goto done;
      }
    }
    times*=10;
  }
done:
  printf("%I64d\n",ans);
  return 0;
}
