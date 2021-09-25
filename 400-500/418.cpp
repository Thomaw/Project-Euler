#include <stdio.h>
#include <math.h>

typedef unsigned long long ull;

int p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,-1};
int pn;
int ev[20];

void addev(int n,int *ev) {
	int i;
	for(i=0;i<pn;i++) while(n%p[i]==0) n/=p[i],ev[i]++;
	if(n>1) printf("error, left %d\n",n);
}

void createfac(int n,int *ev) {
	int i;
	for(i=0;i<pn;i++) ev[i]=0;
	for(i=1;i<=n;i++) addev(i,ev);
}

void create(int n,int *ev) {
	int i;
	for(i=0;i<pn;i++) ev[i]=0;
	addev(n,ev);
}

long double bestratio;
int count;
long double best2;
ull b1,b2,b3;

void btr2(int *cv,int *dv,int *ev,int at,long double a,long double b,long double tot) {
	long double r=b;
	int i,j;
	if(b*b*a>tot) return;
	if(at==pn) {
		/* c/a is lower? */
		if(b>=a) {
			double c=tot/a/b;
			/* find lowest possible c */
			if(best2<c) return;
			best2=c;
			if(c/a<bestratio) {
				b1=b2=b3=1;
				for(i=0;i<pn;i++) {
					for(j=0;j<cv[i];j++) b1*=p[i];
					for(;j<dv[i];j++) b2*=p[i];
					for(;j<ev[i];j++) b3*=p[i];
				}
				bestratio=c/a;
				printf("- %I64d %I64d %I64d => %I64d\n",b1,b2,b3,b1+b2+b3);
			}
		}
		return;
	}
	for(i=cv[at];i<=ev[at];i++,r*=p[at]) {
		dv[at]=i;
		btr2(cv,dv,ev,at+1,a,r,tot);
	}
}

void btr(int *cv,int *ev,int at,long double cur,long double tot) {
	long double r=cur,c;
	int i;
	/* prune on cur > tot^1/3 */
	if(cur*cur*cur>tot) return;
	if(at==pn) {
		count++;
		/* sanity */
		c=sqrt(tot/cur);
		if(c/cur>bestratio) return;
		int dv[20];
		best2=1e100;
		btr2(cv,dv,ev,0,cur,1,tot);
		return;
	}
	for(i=0;i<=ev[at];i++,r*=p[at]) {
		cv[at]=i;
		btr(cv,ev,at+1,r,tot);
	}
}

int solve(int *ev) {
	long double d=1;
	int i,j,cv[20];
	printf("solve ");
	for(i=0;i<pn;i++) printf("%d ",ev[i]); printf("\n");
	for(i=0;i<pn;i++) for(j=0;j<ev[i];j++) d*=p[i];
	count=0;
	bestratio=1e100;
	/* naive seed */
	{
		long double x=1,y=1,z=1;
		for(i=0;i<pn;i++) {
			for(j=0;j<ev[i];) {
				if(j<ev[i]) z*=p[i],j++;
				if(j<ev[i]) y*=p[i],j++;
				if(j<ev[i]) x*=p[i],j++;
			}
		}
		printf("naive %f %f %f\n",(double)x,(double)y,(double)z);
		bestratio=z/x;
	}
	btr(cv,ev,0,1,d);
	printf("comb %d\n",count);
	printf("%I64u %I64u %I64u = %I64d\n",b1,b2,b3,b1+b2+b3);
	return 0;
}

int main() {
	for(pn=0;p[pn]>0;pn++);
	printf("%d primes\n",pn);
	create(165,ev);
	solve(ev);
	create(100100,ev);
	solve(ev);
	createfac(20,ev);
	solve(ev);
	createfac(43,ev);
	solve(ev);
	return 0;
}