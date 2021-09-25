#include <stdio.h>
#include <time.h>

clock_t start=clock();

#define N 20001
double f[N],m[N],a[N],b[N];

int main()
{
	freopen("out.txt","w",stdout);
	int n,k;
	for(n=1;n<N;n++)
	{
		if(n<=2)
		{
			f[n]=m[n]=n;
		}
		else
		{
			if(n==3)
			{
				f[1]=7./9;
				f[2]=m[2]=7./3;
				f[3]=m[3]=3;
			}
			else
			{
				f[n]=n;
				int k0=n/2+2;
				a[k0]=(n-k0+1)*m[k0-2]/n;
				b[k0]=(k0-1.)/n;
				double c;
				for(k=k0;k<n;k++)
				{
					c=n-(n-k)*b[k];
					b[k+1]=k/c;
					a[k+1]=a[k]*(n-k)/c;
				}
				for(k=n;k>=k0;k--)
					f[k-1]=a[k]+b[k]*f[k];
				m[k0-1]=f[k0-1];
				for(k=1;k<k0-1;k++)
					f[k]=((n-k)*m[k-1]+k*m[k+1])/n;
			}
		}
	}
	printf("%.6lf\n",f[(N-1)/2]);
	fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));
	return 0;
}