#include<stdio.h>
long long int n=10000000,k=4000000,p=1000000007;
long long int inv_x_mod_p[10000002]={1,1};

long long int modpow(long long int base,long long int exp,long long int modulus) {
  base %= modulus;
  long long int result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}
int main(void){


long long int i,ANS=0;
for(i=2;i<=n+1;i++){inv_x_mod_p[i]=((inv_x_mod_p[p%i]*(p-p/i))%p);}
for(i=2;i<=n+1;i++){inv_x_mod_p[i]=(inv_x_mod_p[i-1]*inv_x_mod_p[i])%p;}


for(i=0;i<=k;i+=2){ANS=(ANS+((((inv_x_mod_p[i]*inv_x_mod_p[n+1-i])%p)*modpow(k-i,n,p))%p))%p;}
for(i=1;i<=k;i+=2){ANS=(ANS+p-((((inv_x_mod_p[i]*inv_x_mod_p[n+1-i])%p)*modpow(k-i,n,p))%p))%p;}
long long int tmp=1;
for(i=2;i<=n+1;i++)tmp=(tmp*i)%p;
ANS=(ANS*tmp)%p;
printf("%lld\n",ANS);
return 0;}