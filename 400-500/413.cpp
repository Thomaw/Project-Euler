#include <cstdio>
#include <string>
#include <map>
using namespace std;

typedef long long LL;

#define N 19

typedef map<string,LL> MSL;

int main()
{
	LL tot=0;
	LL ans[N+1]={0};
	for(int n=1;n<=N;n++)
	{
		MSL prev;
		string zero(n+1,'0');
		prev[zero]=1;
		for(int k=0;k<n;k++)
		{	
			MSL cur;
			for(MSL::iterator it=prev.begin();it!=prev.end();++it)
			{
				int was = (it->first)[n]-'0';
				LL val = it->second;
				int cnt[N];
				for(int i=0;i<n;i++)
					cnt[i] = (it->first)[i]-'0';
				for(int d=!k;d<10;d++)
				{
					int cnt1[N]={0};
					cnt1[d%n]++;
					for(int i=0;i<n;i++)
						cnt1[(10*i+d)%n]+=cnt[i];
					string ss(n+1,'0');
					ss[n] = was + cnt1[0];
					if(ss[n]<2) {
						ss[n] += '0';
						for(int i=0;i<n;i++) {
							ss[i] = min(cnt1[i],2)+'0';
						}
						cur[ss]+=val;
					}
				}
			}
			prev=cur;
			if(k==n-1) 
			{
				for(MSL::iterator it=prev.begin();it!=prev.end();++it)
					if((it->first)[n]=='1')
						ans[n] += it->second;
			}
		}
		tot+=ans[n];
		fprintf(stderr,"n=%d %lld %lld\n",n,ans[n],tot);
	}
	printf("%lld\n",tot);
	return 0;
}