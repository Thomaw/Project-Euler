#include <stdio.h>

long long dp[65][2][2];
bool vis[64] = {0};

int cycleLength(int t){
	for (int len=0; ; len++){
		if (vis[t]) return len;
		else vis[t] = 1;
		int a = (t&(1<<0))?1:0;
		int b = (t&(1<<1))?1:0;
		int c = (t&(1<<2))?1:0;
		t = (t>>1) | ((a^(b&c))<<5);
	}
}

long long rec(int L, int P, int S){
	if (L==0) return P!=S || P==0;
	if (dp[L][P][S]) return dp[L][P][S];
	return dp[L][P][S] = rec(L-1,0,S) + (1-P) * rec(L-1,1,S);
}

int main(){
	long long res = 1;
	for (int i=0; i<(1<<6); i++){
		int L = cycleLength(i);
		if (L==0) continue;
		res *= rec(L-1,0,0) + rec(L-1,1,1);
	}
	printf("%lld\n",res);
}