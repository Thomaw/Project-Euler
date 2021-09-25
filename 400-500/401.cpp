#include <cmath>
#include <cstdio>
typedef long long ll;
int m=1000000000;

int s(ll n) {
    ll x=n, y=n+1, z=2*n+1;
    if (x%2==0) x/=2; else y/=2; 
    if (x%3==0) x/=3; else if (y%3==0) y/=3; else z/=3;
    return (((x%m)*(y%m)%m)*(z%m))%m;
}
int main(){
    ll N = 1000000000000000LL; ll t=0; ll b=(ll)pow(N,.5);
    for(ll k=1;k<=b;k++)t+=(k*k%m*((N/k-k+1)%m)+s(N/k)-s(k))%m;
    printf("%d",t%m);
}
//281632621