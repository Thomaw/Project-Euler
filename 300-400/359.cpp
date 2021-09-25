#include <cstdio>

typedef long long LL;

#define MOD 100000000

int T(LL f)
{
	f%=2*MOD;
	return (f*(f+1)/2)%MOD;
}

LL P(LL r,LL f)
{
	if(r==1) return T(f);
	LL a1,k;
	if(r%2==0)
	{
		k=r+1;
		LL R=r%(2*MOD);
		a1=(R*R/2)%MOD;
	}
	else
	{
		k=r;
		LL R=r%(2*MOD);
		a1=((R*R-1)/2)%MOD;
	}
	if(f==1) return a1;
	int x=T(k+f-2);
	int y=T(k-1);
	int res=0;
	if(f%2)
		res=x-y+a1;
	else
		res=x+y-a1;
	res%=MOD;
	if(res<0) res+=MOD;
	return res;
}

int main()
{
	int ans=0;
	for(int i=0;i<=27;i++)
		for(int j=0;j<=12;j++)
		{
			LL r=1;
			for(int k=i;k--;) r*=2;
			for(int k=j;k--;) r*=3;
			LL f=71328803586048LL/r;
			ans=(ans+P(r,f))%MOD;
		}
	printf("%d\n",ans);
	return 0;
}