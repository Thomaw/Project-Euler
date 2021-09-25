#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
#include <cassert>
using namespace std;
#define rep(i,a,n) for (ll i=a;i<n;i++)
#define per(i,a,n) for (ll i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define ACCU accumulate
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long ll;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef vector<ll> VL;
const ll mod=1000000007;
const double eps=1e-9;
const double pi=acos(0)*2;
ll powmod(ll a,ll b) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll powmod(ll a,ll b,ll mod) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
const ll N=20000000;
int pr[N+100],p[N+100],tot,mu[N+100];
int sp[N+100],sn[N+100],tc[N+100],tcn;
ll ans;
pair<PII,int> evt[2*N+100];
VI cy;
vector<PII> cx;
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
ll mul(ll a,ll b) { return (a%mod)*(b%mod)%mod;}
void init() {
	mu[1]=1;p[1]=1;
	rep(i,2,N+1) {
		if (!p[i]) p[i]=i,pr[++tot]=i,mu[i]=-1;
		for (int j=1;j<=tot&&pr[j]*i<=N;j++) {
			p[i*pr[j]]=pr[j];
			if (p[i]==pr[j]) break;
			else mu[i*pr[j]]=-mu[i];
		}
	}
	rep(i,1,N+1) sp[i]=sp[i-1]+(mu[i]==1);
	rep(i,1,N+1) sn[i]=sn[i-1]+(mu[i]==-1);
}
void add(int x,int w) { for (;x<=tcn;x+=x&-x) tc[x]+=w;}
int query(int x) { int s=0;for (;x;x-=x&-x) s+=tc[x];return s;}
void solve(int l,int r) {
	if (l==r) return;
	int md=(l+r)>>1;
	solve(l,md);
	solve(md+1,r);
	if (l+10000<r) printf("%d %d\n",l,r); // then we calculate what the left adding operations contributes to right query operations.
	cy.clear();
	rep(i,l,md+1) if (evt[i].se==1) cy.pb(evt[i].fi.se);
	rep(i,md+1,r+1) if (evt[i].se==0) cy.pb(evt[i].fi.se);
	sort(all(cy));
	cy.erase(unique(all(cy)),cy.end());  // store all y-axis for discretization.
	tcn=SZ(cy);
	rep(i,1,tcn+1) tc[i]=0;
	cx.clear();
	rep(i,l,md+1) if (evt[i].se==1) cx.pb(mp(evt[i].fi.fi,i));
	rep(i,md+1,r+1) if (evt[i].se==0) cx.pb(mp(evt[i].fi.fi,i));
	sort(all(cx)); // store all operation and sort by x-axis, use a fenwick tree.
	rep(i,0,SZ(cx)) {
		int id=cx[i].se,r=lower_bound(all(cy),evt[id].fi.se)-cy.begin()+1;
		if (evt[id].se==1) add(r,1);
		else ans+=query(r); // add to the answer.
	}
}

int main() {
	init();
	evt[0]=mp(mp(0,0),1);
	rep(b,1,N+1) {
		evt[2*b-1]=mp(mp(100*sp[b]-99*sn[b],100*sn[b]-99*sp[b]),0); // 0-query
		evt[2*b]=mp(mp(100*sp[b]-99*sn[b],100*sn[b]-99*sp[b]),1); // 1-add, first we query ,then we add the point.
	}
	solve(0,2*N); // deal with all operations.
	printf("%I64d\n",ans);
	printf("%d\n",(int)clock());
	return 0;
}