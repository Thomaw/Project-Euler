#include <cstdio>

typedef __int64 LL;

#define MOD 100000007
#define N 1010101
int fac[N];
int inv[N];
int invfac[N];

int bin(int n,int m)
{
	return LL(fac[n+m])*invfac[n]%MOD*invfac[m]%MOD;
}

int f(int n,int h)
{
	int ans=0;
	int pw2=1;
	int d;
	for(int k=0;(d=n-3*k-1)>=0;k++,pw2=pw2*2%MOD)
	{
		if(d%2) continue;
		int l=d/2;
		int cur=LL(fac[k+l+1])*bin(k,l)%MOD*pw2%MOD*fac[k+h]%MOD*fac[k+l]%MOD;
		ans=(ans+cur)%MOD;
	}
	return ans;
}

int main()
{
	int n;
	fac[0]=fac[1]=inv[1]=invfac[0]=invfac[1]=1;
	for(n=2;n<N;n++)
	{
		inv[n]=inv[MOD%n]*LL(MOD-MOD/n)%MOD;
		fac[n]=LL(n)*fac[n-1]%MOD;
		invfac[n]=LL(inv[n])*invfac[n-1]%MOD;
	}
	n=1000000;
	int ans=(f(n,0)+2*f(n-1,1)+f(n-2,2))%MOD;
	printf("%d\n",ans);
	return 0;
}