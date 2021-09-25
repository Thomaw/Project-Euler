#include <cstdio>
#include <cstring>

typedef long long LL;

const int MOD = 1000000000;
const int n = 18;
struct matr
{
	int _[n][n];
};

void operator*=(matr &a, const matr &b)
{
	matr c;
	memset(c._,0,sizeof c._);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			for(int k=0;k<n;k++)
				c._[i][j]=(c._[i][j]+LL(a._[i][k])*b._[k][j])%MOD;
	a=c;
}

int x[10];
int y[10]={1};

int f(LL pw)
{
	if(pw<10) return x[pw];
	matr a;
	memset(a._,0,sizeof a._);
	for(int i=0;i<9;i++) a._[0][i]=10;
	for(int i=0;i<9;i++) a._[0][i+9]=i+1;
	for(int i=1;i<9;i++) a._[i][i-1]=1;
	for(int i=0;i<9;i++) a._[9][i+9]=1;
	for(int i=1;i<9;i++) a._[i+9][i+8]=1;
	matr p;
	memset(p._,0,sizeof p._);
	for(int i=0;i<n;i++) p._[i][i]=1;
	for(LL d=pw-9;d>0;)
	{
		if(d%2) p*=a;
		if(d/=2) a*=a;
	}
	int ans=0;
	for(int i=0;i<9;i++)
		ans=(ans+LL(p._[0][i])*x[9-i]+LL(p._[0][9+i])*y[9-i])%MOD;
	return ans;
}

int main()
{
	for(int k=1;k<10;k++)
		for(int d=1;d<=9 && d<=k;d++)
		{
			x[k]=(x[k]+LL(10)*x[k-d]+LL(d)*y[k-d])%MOD;
			y[k]=(y[k]+y[k-d])%MOD;
		}
	int ans=0;
	LL pw=1;
	for(int i=1;i<=17;i++)
	{
		pw*=13;
		ans=(ans+f(pw))%MOD;
	}
	printf("%d\n",ans);
	return 0;
}