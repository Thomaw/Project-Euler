#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <vector>
using namespace std;

#define pb push_back
#define sz size()
#define cl clear()

typedef vector<int> VI;

clock_t start=clock();

int main()
{
	freopen("out.txt","w",stdout);
	const int n=11;
	int p[n];
	int i,j;
	for(i=0;i<n;i++) p[i]=i;
	int maxnum=0;
	vector<VI> res;
	do
	{
		int a[n];
		for(i=0;i<n;i++) a[i]=p[i];
		int num=0;
		for(i=0;i<n;i++) if(a[i]!=i)
		{
			for(j=i+1;a[j]!=i;j++);
			if(j<n-1) reverse(a+j,a+n),num++;
			reverse(a+i,a+n),num++;
		}
		if(maxnum<num)
		{
			maxnum=num;
			res.cl;
		}
		if(maxnum==num)
		{
			VI tmp(n);
			for(i=0;i<n;i++) tmp[i]=p[i];
			res.pb(tmp);
		}
	}
	while(next_permutation(p,p+n));
	printf("%d %d\n",maxnum,res.sz);
	i=2010;
	for(j=0;j<n;j++)
		printf("%c",res[i][j]+'A');
	printf("\n");
	fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));
	return 0;
}
