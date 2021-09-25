#include <cstdio>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef pair<LL,LL> PLL;

#define mp make_pair

const LL M = 10000000000;
const int sqM = 100000;
const int N = 50000000;
int a[N];
int p[3333333];
int plen;

int pi[201]={0,455052511, ..., 3001134};

map<LL,int> cnt;
map<PLL,int> dp;

int DP(LL x,LL d)
{
	if(dp.count(PLL(x,d))) return dp[PLL(x,d)];
	int &res=dp[PLL(x,d)];
	if(x==1) return res=1;
	int q[10];
	int i,j;
	for(i=j=0;i<10;i++)
		if(x%p[i]==0) q[j++]=p[i];
	for(int mask=0;mask<(1<<j);mask++)
	{
		LL y=1;
		for(i=0;i<j;i++)
			if(mask & (1<<i)) y*=q[i];
		if(y<=d)
			res+=DP(x/y,y);
	}
	return res;
}

void rec(int maxd,int i,LL x)
{
	cnt[x]=DP(x,x);
	for(int j=1;j<=maxd;j++)
	{
		x*=p[i];
		if(x>M) break;
		rec(j,i+1,x);
	}
}

LL calc(VI a)
{
	sort(a.begin(),a.end());
	reverse(a.begin(),a.end());
	LL d=1;
	for(int i=0;i<a.size();i++)
		for(int j=a[i];j--;)
			d*=p[i];
	return d;
}

LL ans=0;
VI aa;
int tot=0;
void gen(LL x,int i)
{
	int k;
	for(k=1;;k++)
	{
		int prpi;
		if(k==1)
			prpi = x<=200?pi[x]:a[M/x];
		else
		{
			int q = pow(M/x+0.,1./k)+1e-9;
			prpi=a[q];
		}
		if(prpi<=i) break;
		aa.push_back(k);
		LL w=calc(aa);
		ans+=(prpi-i)*cnt[w];
		aa.pop_back();
	}
	for(;i<plen && x*p[i]<=M/p[i];i++)
	{
		LL y=x;
		for(k=1;;k++)
		{
			x*=p[i];
			if(x>M/p[i]) break;
			aa.push_back(k);
			gen(x,i+1);
			aa.pop_back();
		}
		x=y;
	}
}


int main()
{
	int i,j;
	for(i=2;(j=i*i)<N;i++) if(!a[i])
		for(;j<N;j+=i) a[j]=1;
	for(i=2;i<sqM;i++)
		if(!a[i]) p[plen++]=i;
	for(i=2;i<N;i++)
		a[i]=a[i-1]+!a[i];
	rec(50,0,1);
	gen(1,0);
	printf("%lld\n",ans);
	return 0;
}