#include <stdio.h>
#include <math.h>
#define ll long long
#define MODD 40353607
#define EULERPHI 34588806
ll modpow(ll v,ll p)
{
  if(p==0)
    return 1;
  ll x=modpow(v,p/2);
  if(p&1)
    return ((ll)x*(ll)x*v)%MODD;
  else
    return ((ll)x*(ll)x)%MODD; 
}

int main()
{

  ll thrinv=modpow(3,EULERPHI-1);
  ll twoinv=modpow(2,EULERPHI-1);
  printf("%lld %lld\n",thrinv,twoinv);
  ll N;
  scanf("%lld",&N);
  printf("%lld\n",(MODD+(thrinv*(modpow(4,N+1)-1)-twoinv*(modpow(3,N+1)-1)+2*(modpow(2,N+1)-1))%MODD)%MODD);


}