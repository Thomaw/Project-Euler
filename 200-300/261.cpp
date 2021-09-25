#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

typedef __int64 LL;
#define eps 1e-9
#define K 10000000000
#define N 100000
char a[N]={1,1};
int q[N];

LL ar[1000000];
int len=0;

int main()
{
	freopen("out.txt","w",stdout);
	int i,j;
	for(i=1;i<N;i++) q[i]=1;
	for(i=2;i<N;i++) if(a[i]==0)
		for(j=i;j<N;j+=i)
		{
			a[j]=1;
			int k,d=0;
			for(k=j;k%i==0;k/=i) d++;
			for(d=(d+1)/2;d--;) q[j]*=i;
		}
	LL m,y,y_;
	for(m=1;2*m*(m+1)<=K;m++)
	{
		LL M=2*m+1;
		LL maxy=2*m*sqrt(m+1)+eps;
		for(y_=q[m];y_<=maxy;y_+=q[m])
		{
			y=y_;
			LL xx=(m+1)*(y*y/m+1);
			LL x=sqrt(xx)+eps;
			if(x*x==xx && x%2==(m+1)%2 && y%2==m%2)
			{
				for(;;)
				{
					if(x>=y+2*m+1 && (y+m)/2<=K) ar[len++]=(y+m)/2;
					LL z=M*x+(M+1)*y;
					y=(M-1)*x+M*y;
					x=z;
					if((y+m)/2>K) break;
				}
			}
		}
	}
	sort(ar,ar+len);
	LL ans=0;
	for(i=0;i<len;i++)
		if(i==0 || ar[i-1]<ar[i]) ans+=ar[i];
	printf("%I64d\n",ans);
	return 0;
}