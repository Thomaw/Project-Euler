#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1ll<<60;
ll powmod(ll a,ll b) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
// head

const ll N=1000000000000ll;
/*
ll solve(ll k,ll n,ll p1,ll p2) {
	if (k>=n) return p1;
	else {
		return mod-1-max(solve(k*2,n,(3*p1+2*p2)%mod,p1),solve(k*2+1,n,(2*p1+3*p2)%mod,p1));
	}
}*/
ll check(ll k,ll n,ll p1,ll p2,int ty,ll v) {
	// ty=0 check w<=v else check w>=v
	if (k>=n) {
		return (ty==0&&p1<=v)||(ty==1&&p1>=v);
	} else {
		if (ty==0) {
			if (rand()%2==0) return check(k*2,n,(3*p1+2*p2)&(mod-1),p1,ty^1,mod-1-v)||check(k*2+1,n,(2*p1+3*p2)&(mod-1),p1,ty^1,mod-1-v);
			else return check(k*2+1,n,(2*p1+3*p2)&(mod-1),p1,ty^1,mod-1-v)||check(k*2,n,(3*p1+2*p2)&(mod-1),p1,ty^1,mod-1-v);
		} else {
			if (rand()%2==0) return check(k*2,n,(3*p1+2*p2)&(mod-1),p1,ty^1,mod-1-v)&&check(k*2+1,n,(2*p1+3*p2)&(mod-1),p1,ty^1,mod-1-v);
			else return check(k*2+1,n,(2*p1+3*p2)&(mod-1),p1,ty^1,mod-1-v)&&check(k*2,n,(3*p1+2*p2)&(mod-1),p1,ty^1,mod-1-v);
		}
	}
}
int main() {
	// mod-
	ll l=-1,r=mod-1;
	while (l+1!=r) {
		ll md=(l+r)>>1;
		if (check(1,N,1,0,0,md)) r=md; else l=md;
		printf("%I64d %I64d\n",l,r);
	}
	printf("%I64d\n",r);
}