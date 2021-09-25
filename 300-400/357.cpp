#include <cstdio>
#include <ctime>

typedef long long LL;

#define N 100000002
char a[N];

int main()
{
	int i,j;
	for(i=2;i<N;i++) if(!a[i])
		for(j=i+i;j<N;j+=i) a[j]=i;
	int totsum=1;
	for(int n=2;n<N-1;n++) if(!a[n+1] && !a[n/2+2])
	{
		int d;
		for(d=3;d*d<=n;d++)
			if(n%d==0 && a[d+n/d]) break;
		if(d*d>n) totsum+=n;
	}
	printf("%lld\n",totsum);
	return 0;
}