#include <stdio.h>
typedef __int64 LL;

#define n 552
#define MOD 1000000000

int main()
{
	//freopen("out.txt","w",stdout);
	int s,r;
	int i,j,k;
	LL a[n][n]={0};
	for(s=0;s<=23;s++)
		for(r=0;r<23;r++)
		{
			int i=23*s+r;
			for(int d=0;d<10 && d<=s;d++)
			{
				int s1=s-d;
				int r1=(((r-d)*7)%23+23)%23;
				int j=23*s1+r1;
				a[i][j]++;
			}
		}
	LL p[n][n]={0};
	for(i=0;i<n;i++) p[i][i]=1;
	LL x=1;
	for(i=0;i<12;i++) x*=11;
	//x=9;
	for(;x;)
	{
		if(x%2)
		{
			int b[n][n]={0};
			for(i=0;i<n;i++)
				for(j=0;j<n;j++)
					for(k=0;k<n;k++)
						b[i][j]=(b[i][j]+p[i][k]*a[k][j])%MOD;
			for(i=0;i<n;i++)
				for(j=0;j<n;j++)
					p[i][j]=b[i][j];
		}
		if(x/=2)
		{
			int b[n][n]={0};
			for(i=0;i<n;i++)
				for(j=0;j<n;j++)
					for(k=0;k<n;k++)
						b[i][j]=(b[i][j]+a[i][k]*a[k][j])%MOD;
			for(i=0;i<n;i++)
				for(j=0;j<n;j++)
					a[i][j]=b[i][j];
		}
	}
	printf("%d\n",int(p[23*23][0]));
	return 0;
}