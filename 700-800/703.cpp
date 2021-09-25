#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using vi=vector<int>;
using vll=vector<ll>;
const int nax=1400*1007;
const ll mod=1001001011;

int n;
int tab[nax];
vi graph[nax];

int vis[nax];

ll res=1;

vll com(vll a, vll b)
{
	vll ret(2);
	for (int i=0; i<2; i++)
		for (int j=0; j<2; j++)
			if (i+j<2)
				ret[i]=(ret[i]+a[i]*b[j])%mod;
	return ret;
}

vll dfs(int v, int s, int o=-1)
{
	vis[v]=1;
	if (o==v)
		return {!s, s};
	if (o==-1)
		o=v;
	vll ret{1, 1};
	for (int i : graph[v])
		ret=com(ret, dfs(i, s, o));
	return ret;
}

int main()
{
	scanf("%d", &n);
	for (int i=0; i<(1<<n); i++)
	{
		int x=(i>>1);
		int a=(i)&1;
		int b=(i>>1)&1;
		int c=(i>>2)&1;
		tab[i]=x|((a&(b^c))<<(n-1));
		graph[tab[i]].push_back(i);
	}
	for (int i=0; i<(1<<n); i++)
	{
		if (vis[i])
			continue;
		int v=i;
		int u=tab[i];
		while(v!=u)
		{
			v=tab[v];
			u=tab[tab[u]];
		}
		ll cur=0;
		for (int j=0; j<2; j++)
			cur+=dfs(v, j)[j];
		res=(res*cur)%mod;
	}
	printf("%lld\n", res);
	return 0;
}