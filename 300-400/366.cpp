#include <cstdio>
#include <vector>
using namespace std;

typedef __int64 LL;
typedef pair<LL,LL> PLL;
typedef vector<PLL> VPLL;

#define pb push_back
#define sz size()
#define mp make_pair
#define X first
#define Y second

#define MOD 200000000
#define N 90

int main()
{
	LL f[N]={0,1};
	VPLL LR[N];
	LL NN=LL(1000000000)*1000000000;
	int ans=0;
	int i;
	LL sum=0;
	for(int n=2;n<N;n++)
	{
		f[n]=f[n-1]+f[n-2];
		if(n<=5) LR[n].pb(mp(0,f[n-1]-1)); else
		{
			LR[n].pb(mp(0,(f[n]-1)/2));
			for(i=0;i<LR[n-2].sz;i++)
				LR[n].pb(LR[n-2][i]);
			LR[n][1].X+=(f[n]+1)/2-f[n-2];
		}
		for(i=0;i<LR[n].sz;i++) if(sum<NN)
		{
			LL l=LR[n][i].X;
			LL r=LR[n][i].Y;
			LL len=r-l+1;
			if(sum+len>NN)
			{
				len=NN-sum;
				r=l+len-1;
			}
			sum+=len;
			if(l<=r)
			{
				len%=MOD;
				r%=MOD;
				l%=MOD;
				ans=(ans+len*(l+r))%MOD;
			}
		}
	}
	printf("%d\n",ans/2);
	return 0;
}