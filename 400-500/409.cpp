#include <iostream>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)

typedef long long ll;
#define MOD 1000000007ll

int N;
ll dp[10000010];

int main(void){
	int i;
	
	cin >> N;
	
	dp[0] = 1;
	
	ll two = 1;
	REP(i,N) two = two * 2 % MOD;
	
	ll prod = 1;
	REP(i,N){
		dp[i+1] = (prod - dp[i] + MOD) % MOD;
		if(i >= 1){
			ll tmp = dp[i-1] * i % MOD * (two - 1 - i + 1) % MOD;
			dp[i+1] = (dp[i+1] - tmp + MOD) % MOD;
		}
		prod = prod * (two - 1 - i + MOD) % MOD;
	}
	
	ll ans = (prod - dp[N] + MOD) % MOD;
	cout << ans << endl;
	
	return 0;
}