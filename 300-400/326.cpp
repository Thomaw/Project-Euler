#include <stdio.h>
#include <time.h>

typedef __int64 LL;

const int p=1000000000;

struct num
{
	int len;
	int it[3];

	num(LL n=0)
	{
		for(len=0;n>0;n/=p) it[len++]=n%p;
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

	int operator%(int b) const
	{
		LL s=0;
		for(int i=len-1;i>=0;i--) s=(p*s+it[i])%b;
		return s;
	}
};

LL N=1e12;
const int M=1000000;

LL cnt[M]={0};

int main()
{
	clock_t start=clock();
	freopen("out.txt","w",stdout);
	int sM=1;
	int T=6*M;
	cnt[0]=1;
	cnt[1]=(N-1)/T+1;;
	num s(1);
	for(LL n=2;n<=T;n++)
	{
		int an=s%n;
		sM=(sM+an)%M;
		cnt[sM]+=(N-n)/T+1;
		s+=num(LL(n)*an);
	}
	LL ans=0;
	for(int i=0;i<M;i++)
		ans+=LL(cnt[i])*(cnt[i]-1)/2;
	printf("%I64d\n",ans);
	fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));
	return 0;
}