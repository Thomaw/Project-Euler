#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

inline ll modPow(ll a, ll b, ll mod){
	__int128 ret = 1;
	__int128 aa = a;
	__int128 md = mod;
	while(b){
		if(b&1)(ret *= aa) %= md;
		(aa *= aa) %= mod;
		b >>= 1;
	}
	return ret;
}

inline ll f(ll p){
	ll a = modPow(2, p, p - 1) + p - 2;
	return modPow(2, a, p);
}

inline ll g(ll p){
	__int128 tmp = modPow(2, p, p*p);
	tmp *= f(p);
	tmp %= (p*p);
	return tmp/p;
}

const int N = 10000000;
bool prime[N + 1];

void pre(){
	for(int i = 2; i <= N; i++){
		prime[i] = true;
	}
	for(int i = 2; i*i <= N; i++){
		if(prime[i]){
			for(int j = i*i; j <= N; j += i){
				prime[j] = false;
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cout<<setprecision(32);

	pre();
	ll ans = 0;
	for(int i = 3; i <= N; i++){
		if(prime[i])ans += g(i);
	}
	cout<<ans<<endl;

	return 0;
}