#include <cstdio>

typedef long long LL;

#define N 5000
int a[N];
int pr[N];
int plen;

int fac[N];
int invfac[N];
int inv[N];
int r[N];

int powmod(int a,int n,int m)
{
	int p=1;
	for(;n;)
	{
		if(n%2) p=p*a%m;
		if(n/=2) a=a*a%m;
	}
	return p;
}

int main()
{
	int i,j,k;
	for(i=2;i<N;i++) if(!a[i])
	{
		if(i>1000) pr[plen++]=i;
		for(j=i;j<N;j+=i) a[j]=1;
	}
	for(i=0;i<plen;i++)
	{
		int p=pr[i];
		inv[1]=1;
		fac[0]=fac[1]=invfac[0]=invfac[1]=1;
		for(j=2;j<p;j++)
		{
			fac[j]=j*fac[j-1]%p;
			inv[j]=inv[p%j]*(p-p/j)%p;
			invfac[j]=inv[j]*invfac[j-1]%p;
		}
		int m=1000000000;
		LL n=LL(m)*m;
		r[i]=1;
		for(;m;n/=p,m/=p)
		{
			int n0=n%p;
			int m0=m%p;
			if(n0<m0) r[i]=0; else
				r[i]=r[i]*fac[n0]%p*invfac[m0]%p*invfac[n0-m0]%p;
		}
	}
	LL ans=0;
	for(i=0;i<plen;i++)
		for(j=0;j<i;j++)
		{
			int m=pr[j];
			int y=(r[j]-r[i]) * powmod(pr[i],m-2,m)%m;
			if(y<0) y+=m;
			int R=y*pr[i]+r[i];
			m*=pr[i];
			for(k=0;k<j;k++)
			{
				int p=pr[k];
				LL cur=(r[k]-R)%p * powmod(m%p,p-2,p)%p;
				if(cur<0) cur+=p;
				cur=m*cur+R;
				ans+=cur;
			}
		}
	printf("%lld\n",ans);
	return 0;
}