#include<cstdio>
#include<cstring>

char t[99]="100001000101100101010001011000010100000000010100100001001010000000000000000000000000";
int ar[99];
__int64 dp[99][4];

__int64 fans(int n, int s) {
	s=2*s+ar[n-1];
	if(s<0||s>3) return 0;
	if(n==1) return s<3;
	if(dp[n][s]) return dp[n][s];
	return dp[n][s]=fans(n-1,s)+fans(n-1,s-1)+fans(n-1,s-2);
}

int main() {
	int N=strlen(t);
	for(int i=0;i<N;i++) ar[i] = t[N-i-1]-'0';
	printf("%I64d\n",fans(N,0));
	return 0;
}