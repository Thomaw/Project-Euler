#include <stdio.h>

int euler287(int n,int N,long long x, long long y)
{
	if (n==0) return 2;
	long long sideoff=(1<<n)-1;
	long long R2=1;
	R2<<=2*N-2;
	long long x2=x+sideoff;
	long long y2=y+sideoff;
	long long d;
	int t=0;
	d=x*x+y*y;
	if (d<=R2) t+=1;
	d=x2*x2+y*y;
	if (d<=R2) t+=1;
	d=x*x+y2*y2;
	if (d<=R2) t+=1;
	d=x2*x2+y2*y2;
	if (d<=R2) t+=1;
	if (n<N)
	{
		if (t==0) return 2;
		if (t==4) return 2;
	}
	int dx,dy;
	t=1;
	for(dx=0;dx<2;dx++)
	for(dy=0;dy<2;dy++)
	{
		t+=euler287(n-1,N,x+dx*(1<<(n-1)),y+dy*(1<<(n-1)));
	}
	return t;
}
int main(int argc,char *argv[])
{
	int N=24;
	printf("Ans=%d\n",euler287(N,N,-(1<<(N-1)),-(1<<(N-1))));
	return 0;
}