
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <complex>
#pragma comment(linker, "/STACK:266777216")
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef vector<double> VD;
typedef pair<double,double> PDD;

const int inf=1000000000;
const LL INF=LL(inf)*inf;
const double eps=1e-9;
const double PI=2*acos(0.0);
#define bit(n) (1<<(n))
#define bit64(n) ((LL(1))<<(n))
#define pb push_back
#define sz size()
#define mp make_pair
#define cl clear()
#define all(a) (a).begin(),(a).end()
#define fill(ar,val) memset((ar),(val),sizeof (ar))
#define MIN(a,b) {if((a)>(b)) (a)=(b);}
#define MAX(a,b) {if((a)<(b)) (a)=(b);}
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define sqr(x) ((x)*(x))
#define X first
#define Y second


#define p_len 4
const int p=10000;
#define NN 55/p_len

struct num
{
	int len;
	int it[NN];

	num(LL n=0)
	{
		for(len=0;n>0;n/=p) it[len++]=n%p;
	}

	LL val()
	{
		LL res=0;
		for(int i=len;i--;)
			res=p*res+it[i];
		return res;
	}

	double Dval()
	{
		double res=0;
		for(int i=len;i--;)
			res=p*res+it[i];
		return res;
	}

	bool read()
	{
		char w[NN*p_len];
		if(scanf("%s",w)==-1) return false;
		int i,n=strlen(w),m=0,p=1;
		len=0;
		for(i=0;i<n;i++)
		{
			m+=p*(w[n-i-1]-'0');p*=10;
			if((i+1)%p_len==0)
			{
				it[len++]=m;
				m=0;p=1;
			}
		}
		if(m>0) it[len++]=m;
		return true;
	}

	void print() const
	{
		if(len==0) printf("0"); else
		{
			int i=len-1;
			printf("%d",it[i]);
			char s[10];
			sprintf(s,"%%0%dd",p_len);
			for(i--;i>=0;i--) printf(s,it[i]);
		}
		printf("\n");
	}

	num operator+(const num &b) const
	{
		num s;
		int i,d=0;
		int maxlen=len>b.len?len:b.len;
		for(i=0;i<maxlen;i++)
		{
			if(i<len) d+=it[i];
			if(i<b.len) d+=b.it[i];
			s.it[i]=d%p;
			d/=p;
		}
		if(d>0) s.it[i++]=d;
		s.len=i;
		return s;
	}

	void operator+=(const num &b)
	{
		int i;
		int d=0;
		int maxlen=len>b.len?len:b.len;
		for(i=0;i<maxlen;i++)
		{
			if(i<len) d+=it[i];
			if(i<b.len) d+=b.it[i];
			it[i]=d%p;
			d/=p;
		}
		if(d>0) it[i++]=d;
		len=i;
	}

	void operator++()
	{
		int i;
		for(i=0;i<len && it[i]==p-1;i++) it[i]=0;
		if(i==len) it[len++]=1; else it[i]++;
	}

	num operator-(const num &b) const
	{
		num s;
		int i;
		int r,d=0;
		for(i=0;i<len;i++)
		{
			d+=it[i]-(i<b.len?b.it[i]:0);
			r=d%p;
			if(r<0) r+=p;
			s.it[i]=r;
			d=(d-r)/p;
		}
		for(i--;i>=0 && s.it[i]==0;i--);
		s.len=i+1;
		return s;
	}

	void operator-=(const num &b)
	{
		int i;
		int r,d=0;
		for(i=0;i<len;i++)
		{
			d+=it[i]-(i<b.len?b.it[i]:0);
			r=d%p;
			if(r<0) r+=p;
			it[i]=r;
			d=(d-r)/p;
		}
		for(i--;i>=0 && it[i]==0;i--);
		len=i+1;
	}

	void operator--()
	{
		int i;
		for(i=0;i<len && it[i]==0;i++) it[i]=p-1;
		it[i]--;
		if(it[len-1]==0) len--;
	}

	num operator*(int b) const
	{
		num prod(0);
		if(b==0) return prod;
		int i;
		int d=0;
		for(i=0;i<len;i++)
		{
			d+=it[i]*b;
			prod.it[i]=d%p;
			d/=p;
		}
		for(;d>0;d/=p) prod.it[i++]=d%p;
		prod.len=i;
		return prod;
	}

	void operator*=(int b)
	{
		if(b==0) { len=0; return; }
		int i;
		int d=0;
		for(i=0;i<len;i++)
		{
			d+=it[i]*b;
			it[i]=d%p;
			d/=p;
		}
		for(;d>0;d/=p) it[i++]=d%p;
		len=i;
	}

	bool operator==(const num &b) const
	{
		if(len!=b.len) return false;
		int i;
		for(i=len-1;i>=0 && it[i]==b.it[i];i--);
		return i<0;
	}

	bool operator!=(const num &b) const
	{
		if(len!=b.len) return true;
		int i;
		for(i=len-1;i>=0 && it[i]==b.it[i];i--);
		return i>=0;
	}

	bool operator<(const num &b) const
	{
		if(len!=b.len) return len<b.len;
		int i;
		for(i=len-1;i>=0 && it[i]==b.it[i];i--);
		return i>=0 && it[i]<b.it[i];
	}

	bool operator<=(const num &b) const
	{
		if(len!=b.len) return len<b.len;
		int i;
		for(i=len-1;i>=0 && it[i]==b.it[i];i--);
		return i<0 || it[i]<b.it[i];
	}

	bool operator>(const num &b) const
	{
		if(len!=b.len) return len>b.len;
		int i;
		for(i=len-1;i>=0 && it[i]==b.it[i];i--);
		return i>=0 && it[i]>b.it[i];
	}

	bool operator>=(const num &b) const
	{
		if(len!=b.len) return len>b.len;
		int i;
		for(i=len-1;i>=0 && it[i]==b.it[i];i--);
		return i<0 || it[i]>b.it[i];
	}

	num operator/(int q) const
	{
		num b;
		int i;
		int c=0;
		for(i=len-1;i>=0;i--)
		{
			c=p*c+it[i];
			b.it[i]=c/q;
			c%=q;
		}
		for(i=len-1;i>=0 && b.it[i]==0;i--);
		b.len=i+1;
		return b;
	}

	void operator/=(int q)
	{
		int i;
		int c=0;
		for(i=len-1;i>=0;i--)
		{
			c=p*c+it[i];
			it[i]=c/q;
			c%=q;
		}
		for(i=len-1;i>=0 && it[i]==0;i--);
		len=i+1;
	}

	int operator%(int b) const
	{
		int s=0;
		for(int i=len-1;i>=0;i--) s=(p*s+it[i])%b;
		return s;
	}
};


num operator*(num &a,num &b)
{
	num prod(0);
	memset(prod.it,0,sizeof prod.it);
	if(b.len==0 || a.len==0) return prod;
	int i,j,d;
	for(i=0;i<a.len;i++)
	{
		if(a.it[i]>0)
		{
			d=0;
			for(j=0;j<b.len;j++)
			{
				d+=prod.it[i+j]+a.it[i]*b.it[j];
				prod.it[i+j]=d%p;
				d/=p;
			}
			if(d>0) prod.it[i+j]=d;
		}
	}
	prod.len=a.len+b.len;
	if(prod.it[prod.len-1]==0) prod.len--;
	return prod;
}

num pow(num a,int n)
{
	num p(1);
	for(;n;)
	{
		if(n%2) p=p*a;
		if(n/=2) a=a*a;
	}
	return p;
}

num operator/(num &a,num &b)
{
	num s,w;
	int i,j,v,vv=0,m=b.len;
	s.len=0;
	for(i=0;i<=m;i++) s.it[i]=0;
	if(b.it[m-1]<p/2)
	{
		vv=p/(b.it[m-1]+1);
		a*=vv;b*=vv;
	}
	v=b.it[m-1];
	for(i=a.len-1;i>=0;i--)
	{
		for(j=s.len;j>0;j--) s.it[j]=s.it[j-1];
		s.it[0]=a.it[i];
		for(j=s.len;j>=0 && s.it[j]==0;j--);
		s.len=j+1;
		int q=(p*s.it[m]+s.it[m-1])/v;
		if(q>=p) q=p-1;
		if(b*q>s){q--;if(b*q>s)q--;}
		w.it[i]=q;
		s-=b*q;
	}
	if(vv)
	{
		a/=vv;b/=vv;s/=vv;
	}
	for(i=a.len-1;i>=0 && w.it[i]==0;i--);
	w.len=i+1;
	return w;
}

num operator%(num &a,num &b)
{
	num s,w;
	int i,j,v,vv=0,m=b.len;
	s.len=0;
	for(i=0;i<=m;i++) s.it[i]=0;
	if(b.it[m-1]<p/2)
	{
		vv=p/(b.it[m-1]+1);
		a*=vv;b*=vv;
	}
	v=b.it[m-1];
	for(i=a.len-1;i>=0;i--)
	{
		for(j=s.len;j>0;j--) s.it[j]=s.it[j-1];
		s.it[0]=a.it[i];
		for(j=s.len;j>=0 && s.it[j]==0;j--);
		s.len=j+1;
		int q=(p*s.it[m]+s.it[m-1])/v;
		if(q>=p) q=p-1;
		if(b*q>s){q--;if(b*q>s)q--;}
		w.it[i]=q;
		s-=b*q;
	}
	if(vv)
	{
		a/=vv;b/=vv;s/=vv;
	}
	for(i=a.len-1;i>=0 && w.it[i]==0;i--);
	w.len=i+1;
	return s;
}

void divide(num &a,num &b,num &w,num &s)//a=b*w+s
{
	int i,j,v,vv=0,m=b.len;
	s.len=0;
	for(i=0;i<=m;i++) s.it[i]=0;
	if(b.it[m-1]<p/2)
	{
		vv=p/(b.it[m-1]+1);
		a*=vv;b*=vv;
	}
	v=b.it[m-1];
	for(i=a.len-1;i>=0;i--)
	{
		for(j=s.len;j>0;j--) s.it[j]=s.it[j-1];
		s.it[0]=a.it[i];
		for(j=s.len;j>=0 && s.it[j]==0;j--);
		s.len=j+1;
		int q=(p*s.it[m]+s.it[m-1])/v;
		if(q>=p) q=p-1;
		if(b*q>s){q--;if(b*q>s)q--;}
		w.it[i]=q;
		s-=b*q;
	}
	if(vv)
	{
		a/=vv;b/=vv;s/=vv;
	}
	for(i=a.len-1;i>=0 && w.it[i]==0;i--);
	w.len=i+1;
}

#define MOD 600000000

LL down_sqrt(num xx)
{
	double appr=sqrt(xx.Dval());
	num L=LL(appr*(1-1e-9));
	num R=LL(appr*(1+1e-9))+1;
	while(L+1<R)
	{
		num M=(L+R)/2;
		if(M*M<=xx) L=M; else R=M;
	}
	return L.val();
}

LL up_sqrt(num xx)
{
	double appr=sqrt(xx.Dval());
	num L=LL(appr*(1-1e-9));
	num R=LL(appr*(1+1e-9))+1;
	while(L+1<R)
	{
		num M=(L+R)/2;
		if(M*M<xx) L=M; else R=M;
	}
	return R.val();
}

LL brute(LL N)
{
	LL ans=0;
	for(LL c=0;c<=N+1;c++)
	{
		LL cnt;
		if(c*c<=4*N) {
			LL maxa = min(N,down_sqrt(c*c+4*N));
			cnt = c%2 ? (maxa+1)/2*2 : maxa/2*2+1;
		} else {
			LL maxa=min(N,down_sqrt(c*c+4*N));
			LL mina=up_sqrt(c*c-4*N)-1;
			cnt = ((maxa+c%2)/2-(mina+c%2)/2)*2;
			//fprintf(stderr,"c=%3lld cnt=%3lld\n",c,cnt/2);
		}
		cnt%=MOD;
		LL c1=c%MOD;
		ans=(ans+cnt*(c1+1)%MOD*(c1*c1%MOD-c1+6))%MOD;
	}
	if(ans<0) ans+=MOD;
	return ans/6;
}

LL func(LL c,LL N)
{
	num c2=num(c)*num(c);
	LL maxa=min(N,down_sqrt(c2+4*N));
	LL mina=up_sqrt(c2-4*N)-1;
	LL res=(maxa+c%2)/2-(mina+c%2)/2;
	if(res<0) res=0;
	return res;
}

LL sum(LL x)
{
	int mod=2*MOD;
	x%=mod;
	LL res=x+2;
	res=(res*x+11)%mod;
	res=(res*x+34)%mod;
	res=(res*x)%mod;
	return res/2;
}

LL smart(LL N)
{
	LL ans=0;
	LL c;
	for(c=0;c*c<=4*N;c++)
	{
		if(c%10000==0) fprintf(stderr,"c=%lld\n",c);
		LL maxa = min(N,down_sqrt(c*c+4*N));
		LL cnt = c%2 ? (maxa+1)/2*2 : maxa/2*2+1;
		cnt%=MOD;
		LL c1=c%MOD;
		ans=(ans+cnt*(c1+1)%MOD*(c1*c1%MOD-c1+6))%MOD;
	}
	c--;
	LL prev=N+1;
	for(LL k=1;;k++)
	{
		if(k%1000==0) fprintf(stderr,"k=%lld\n",k);
		LL k0=func(prev,N);
		MAX(k,k0);
		LL L=c;
		LL R=prev;
		while(L+1<R)
		{
			LL M=(L+R)/2;
			LL fnc=func(M,N);
			if(fnc>k) L=M; else R=M;
		}
		if(L<prev)
		{
			LL sum1=sum(L);
			LL sum2=sum(prev);
			ans=(ans+(sum2-sum1)*k)%MOD;
		}
		prev=L;
		if(prev==c) break;
	}
	if(ans<0) ans+=MOD;
	return ans/6;
}

void check()
{
	fprintf(stderr,"%lld\n",smart(5));
	fprintf(stderr,"%lld\n",smart(100));
	//return;
	for(LL N=1;N<=200;N++)
	{
		LL cor=brute(N);
		LL res=smart(N);
		fprintf(stderr,"%lld %lld %lld\n",N,cor,res);
		assert(cor==res);
	}
	for(int it=0;it<20;it++)
	{
		int rnd1=rand()%bit(15);
		int rnd2=rand()%bit(15);
		LL N=(rnd1*bit(15)+rnd2)%10000+1;
		LL cor=brute(N);
		LL res=smart(N);
		fprintf(stderr,"%lld %lld %lld\n",N,cor,res);
		assert(cor==res);
	}
}

int main()
{
	clock_t start=clock();
	//freopen("in.txt","rt",stdin);
	freopen("out.txt","wt",stdout);
	//check();
	LL ans=smart(1000000000000LL);
	printf("%lld\n",ans);
	fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));
	return 0;
}