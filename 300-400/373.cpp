#include <cstdio>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;

const double eps = 1e-9;

int gcd(int a,int b)
{
	int c;
	while(b) c=a%b,a=b,b=c;
	return a;
}

const int maxR = 10000000;
int minp[maxR+1];

VPII factor(int n)
{
	VPII res;
	for(;n>1;)
	{
		int d=minp[n];
		int k=0;
		for(;n%d==0;n/=d) k++;
		res.push_back(PII(d,k));
	}
	return res;
}

int p4[]={5,13,17,29,37};
VI best;

void rec(int i,int k,int n)
{
	if(i) best.push_back(n);
	if(i==5) return;
	for(int j=1;j<=k;j++)
	{
		n*=p4[i];
		if(n>maxR) break;
		rec(i+1,j,n);
	}
}

int count(int R)
{
	int n=2*R;
	VI div;
	int d;
	for(d=1;d*d<n;d++)
		if(n%d==0) div.push_back(d),div.push_back(n/d);
	if(d*d==n) div.push_back(d);
	sort(div.begin(),div.end());
	VI bigd;
	for(int i=0;i<div.size();i++)
		for(int j=0;j<=i;j++) if(n/div[i]%div[j]==0)
		{
			int d=n/div[i]/div[j];
			if(d<=div[j]) bigd.push_back(div[i]);
		}
	sort(bigd.begin(),bigd.end());
	VI tmp;
	for(int i=0;i<bigd.size();i++)
	{
		int d=bigd[i],j;
		for(j=0;j<tmp.size() && d%tmp[j];j++);
		if(j==tmp.size())
			tmp.push_back(d);
	}
	bigd=tmp;
	set<VI> sols;
	set<int> ss;
	for(int i=0;i<bigd.size();i++)
	{
		int d=bigd[i];
		for(int s=d;s<=R;s+=d)
			if(!ss.count(s)) ss.insert(s);
	}
	for(set<int>::iterator it=ss.begin();it!=ss.end();++it)
	{
		int s=*it;
		LL ds2=LL(R)*R-LL(s)*s;
		int ds=sqrt(ds2+0.)+eps;
		if(LL(ds)*ds!=ds2) continue;
		for(int sign=-1;sign<=1;sign+=2)
		{
			int w=R+sign*ds;
			int g=gcd(w,s);
			LL q=LL(s/g)*(s/g);
			LL p=LL(w/g)*(w/g);
			for(int x=1;x<=s-x;x++)
			{
				int y=s-x;
				if(LL(x)*y%q) continue;
				LL c=LL(x)*y/q*p;
				LL D2=LL(s)*s+4*c;
				LL D=sqrt(D2+0.)+eps;
				if(D*D==D2)
				{
					LL z=(-s+D)/2;
					int w=gcd(gcd(x,y),gcd(z,R));
					if(w>1) continue;
					int a[3]={x,y,z};
					sort(a,a+3);
					VI cur(a,a+3);
					if(!sols.count(cur))
						sols.insert(cur);
				}
			}
		}
	}
	return sols.size();
}

int main()
{
	for(int i=2;i<=maxR;i++) if(!minp[i])
		for(int j=i;j<=maxR;j+=i) if(!minp[j]) minp[j]=i;
	rec(0,10,1);
	sort(best.begin(),best.end());
	map<VI,int> num;
	for(int i=0;i<best.size();i++)
	{
		int R=best[i];
		int cnt=count(R);
		VPII fct=factor(R);
		VI deg;
		for(int i=0;i<fct.size();i++)
			deg.push_back(fct[i].second);
		sort(deg.begin(),deg.end());
		num[deg]=cnt;
	}
	LL sum=0;
	for(int R=1;R<=maxR;R++)
	{
		VPII fct=factor(R);
		VI deg;
		int i;
		for(i=0;i<fct.size();i++)
		{
			if(fct[i].first%4!=1) break;
			deg.push_back(fct[i].second);
		}
		if(i<fct.size()) continue;
		sort(deg.begin(),deg.end());
		LL cnt=maxR/R;
		sum+=R*cnt*(cnt+1)/2*num[deg];
	}
	printf("%lld\n",sum);
	return 0;
}