#include <stdio.h>
#include <math.h>
#define MAXX 1000000000000000000ll
bool isprime[1000001];
long long primes[80000];

int v1[20];
int v2[20];
int alldepths[1000000];
int pp[1000000][20];
int power[1000000][20];
int cands;
int gcd(int a,int b)
{
	if(b==0)
		return a;
	if(a==-1)
		return b;
	int t;
	while(b!=0)
	{
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}
void findit(long long N,long long NP,int pid,int depth,int gcd1,int gcd2)
{
	long long NNP=NP;
	for(int i=pid-1;i>=0;i--)
	{
		int NPpows=0;
		while(NNP%primes[i]==0)
		{
			NPpows++;
			NNP/=primes[i];
		}
		v1[depth]=primes[i];
		long long val=primes[i]*primes[i];
		int vpow=3;
		while(val<=(MAXX+1)/(N*primes[i]))
		{
			v2[depth]=vpow;
			findit(N*primes[i]*val,NNP*(primes[i]-1),i,depth+1,gcd(gcd1,vpow),gcd(gcd2,NPpows+vpow-1));
			val*=primes[i];
			vpow++;
		}
		
		if(NP%primes[i]==0)
		{
			if(primes[i]*primes[i]<=(MAXX+1)/N)
			{
				v2[depth]=2;
				findit(N*primes[i]*primes[i],NNP*(primes[i]-1),i,depth+1,gcd(gcd1,2),gcd(gcd2,NPpows+1));
			}
		}
		if(NP%primes[i]==0 && NP%(primes[i]*primes[i])>0)
			return;
		gcd2=gcd(gcd2,NPpows);
	}
	if(NNP==1 && gcd1==1 && gcd2==1 && N<=MAXX)
	{
		
		cands++;
	}
	
	
}

int main()
{
	for(int i=0;i<=1000000;i++)
		isprime[i]=1;
	

	for(int i=2;i<=1000000;i++)
	{
		int jmax=1000000/i;
		for(int j=2;j<=jmax;j++)
			isprime[i*j]=0;
	}
	int count=0;
	int np=0;
	for(int i=2;i<=1000000;i++)
		if(isprime[i])
		{
			primes[np++]=i;
		}
	
	cands=0;
	findit(1,1,np,0,-1,-1);
	
	printf("%d\n",cands);
	
	
	
	
			
}
	