#include <stdio.h>
#include <time.h>
#include <math.h>

typedef __int64 LL;
#define MOD 100000000

#define max(a,b) (a>b?a:b)

LL sum(LL n,LL x)
{
	LL a=sqrt(1.*n);
	if(a>n/x) a=n/x;
	LL ans=0;
	LL k;
	LL maxk=n/(a+1);
	for(k=x;k<=maxk;k++)
		ans+=n/k;
	for(k=1;k<a;k++)
		ans+=(n/k-n/(k+1))*k;
	ans+=a*(n/a-max(n/(a+1),x-1));
	return ans%MOD;
}

LL sum2(LL n)
{
	LL ans=0;
	LL a=sqrt(1.*n);
	LL k,maxk=n/(a+1);
	for(k=1;k<=maxk;k++)
		ans=(ans+(n/k)%MOD*((n/(k+1)%MOD)))%MOD;
	for(k=1;k<=a;k++)
	{
		ans=(ans+(n/k-n/(k+1)-1)%MOD*k*k%MOD)%MOD;
		ans=(ans+k*(k-1))%MOD;
	}
	return ans;
}

LL g(LL n)
{
	LL s1=0,s2=0,s3=0,s4=0,s5=0,s6=0;
	LL a,b;
	s1=sum2(n);
	s2=sum(n,2);
	for(b=2;b*b<=n;b++)
		s3=(s3+sum(n/b,b))%MOD;
	for(a=2;a*a<=n;a++)
		s4=(s4+n/a/a)%MOD;
	LL ans=(s1-s2-2*s3+s4)%MOD;
	if(ans<0) ans+=MOD;
	return ans;
}

int main()
{
	freopen("out.txt","w",stdout);
	clock_t start=clock();
	printf("%d\n",int(g(LL(1e12))));
	fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));
	return 0;
}