#include <stdio.h>
#include <time.h>

typedef __int64 LL;

#define N 11111111
int a[N+1000000];

int main()
{
	freopen("out.txt","w",stdout);
	clock_t start=clock();
	int i,j,k;
	a[1]=1;
	for(i=k=1;k<N;i++)
	{
		a[k]=i;
		for(j=a[i];j--;) a[k++]=i;
	}
	LL ans=0,sa=0,s=0;
	LL n=1;
	for(i=1;n<1e6;i++)
	{
		if(n*n*n<=s+LL(i)*a[i])
		{
			LL q=(n*n*n-s+i-1)/i;
			ans+=sa+q;
			n++;
		}
		s+=LL(i)*a[i];
		sa+=a[i];
	}
	printf("%I64d\n",ans);
	fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));
	return 0;
}