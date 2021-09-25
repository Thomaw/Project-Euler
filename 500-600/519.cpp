#include<bits/stdc++.h>
using namespace std;
const int N=20000,N1=N+1,M=1e9;
int T[N1][N1]; //sum in row of http://oeis.org/A168396
int f[N1],g[N1];
int F[N1],G[N1];
int main(){
	f[0]=1;
	for(int i=1;i<=N;++i){
		for(int j=1;j<i;++j)
			T[i][j]=(T[i][j-1]+T[i-j][min(i-j,j+1)])%M;
		T[i][i]=(T[i][i-1]+1)%M;
		g[i]=f[i]=T[i][1];
		for(int j=1;j<i;++j)
			g[i]=(g[i]+(g[j]*(int64_t)(M-f[i-j])))%M;
	}
	for(int i=1;i<=N;++i)G[i]=g[i]*(2-(i==1)) %M;
	F[0]=1;
	for(int i=1;i<=N;++i)
		for(int j=1;j<=i;++j)
			F[i]=(F[i]+(2LL-(i==j))*G[j]*F[i-j]) %M;
	cout << F[N]*3LL%M << endl;
}