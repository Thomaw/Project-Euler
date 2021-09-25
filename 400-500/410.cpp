#include <cstdio>

typedef long long LL;

void calc_primes(int x,int *pr)
{
	int len=0;
	for(int p=2;p*p<=x;p++)
		if(x%p==0)
		{
			pr[len++]=p;
			for(;x%p==0;x/=p);
		}
	if(x>1) pr[len++]=x;
	pr[len++]=0;
}

bool coprime(int m,int *pr)
{
	for(int i=0;pr[i];i++)
		if(m % pr[i] == 0) return false;
	return true;
}

LL solve(int R,int X)
{
	int A = X<R?X:R;
	LL sum = 0;
	for(int n=1;n*(n+1)<=A;n++)
	{
		int maxm=A/n;
		int Xn=X/n,Rn=R/n;
		int pr[10];
		calc_primes(n,pr);
		for(int m=n+1;m<=maxm;m++) if(coprime(m,pr))
		{
			if((m+n)%2)
				sum += (LL(Xn/m) * (Rn/m) + 1) / 2;
			else
				sum += LL(Xn/m) * (Rn/m);
		}
	}	
	return 2LL*R*X + 4*sum;
}

int main()
{
	printf("%lld\n",2*solve(100000000,1000000000));
	return 0;
}