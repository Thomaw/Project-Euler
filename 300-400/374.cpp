#include <cstdio>

typedef long long LL;

#define MOD 982451653
#define K 15000000
int inv[K];
int sum[K];

int main()
{
	LL N=100000000000000LL;
	int fac=2;
	inv[1]=1;
	inv[2]=(MOD+1)/2;
	sum[2]=inv[2];
	int ans=1;
	LL n=0;
	for(int k=3;;k++)
	{
		fac=LL(fac)*k%MOD;
		inv[k]=LL(MOD-MOD/k)*inv[MOD%k]%MOD;
		sum[k]=sum[k-1]+inv[k];
		if(sum[k]>=MOD) sum[k]-=MOD;
		n+=k;
		if(n>=N)
		{
			ans=(ans+LL(fac)*(sum[k]+MOD-sum[n-N+1])%MOD*(k-2))%MOD;
			break;
		}
		ans=(ans+LL(fac)*(k-2)%MOD*(sum[k]+LL(1+inv[k])%MOD*inv[2]%MOD))%MOD;
		if(n+1==N) break;
	}
	printf("%d\n",ans);
	return 0;
}