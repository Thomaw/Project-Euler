#include <math.h>
#include <time.h>7

typedef unsigned long long ULL;

int PRIMES[78498];
int Af[17];
int *T1, *T2, Tidx = 0;

main()
{
	buildPrimesArray();
	e_417();
}

// 50e6: 114901031794347 Elapsed time: ~ 30'
// 1e8:   446572970925740 Elapsed time: ~ 2 hours

e_417()
{
	int i, j, k, l, m, n;
	int x, y;
	int e, g;
	ULL s = 1;
	int c[17];

	int HTL = 3001132;
	int MAXP = 49999991;
	T1 = malloc(sizeof(int) * HTL);
	T2 = malloc(sizeof(int) * HTL);
	if ((T1 == 0) || (T2 == 0))
	{
		printf("malloc fail!");
		return 0;
	}
	T1[Tidx] = 3;
	T2[Tidx++] = 1;

	int kp, Afp[17];

	for (i = 6; i <= 100000000; i++)
	{
		k = factors(i);
		if (!(i & 1))
		{
			kp = k;
			for (j = 0; j < k; j++)
			{
				Afp[j] = Af[j];
			}
		}
		if (k == 2)
		{
			if ((Af[0] == 2) || (Af[0] == 5))
			{
				continue;
			}
			if (Af[1] == 1)
			{
				e = i - 1;
				for (j = 0; j < kp; j += 2)
				{
					e /= bPow(Afp[j], Afp[j + 1]);
					g = modPow(10, e, i);
					while (g != 1)
					{
						g = modPow(g, Afp[j], i);
						e *= Afp[j];
					}
				}
				if (i <= MAXP)
				{
					T1[Tidx] = i;
					T2[Tidx++] = e;
				}
				s += (ULL) e;
			}
			else
			{
				if (Af[0] == 3)
				{
					s += (ULL) bPow(3, Af[1] - 2);
				}
				else if (Af[0] == 487)
				{
					s += (ULL) 486;
				}
				else
				{
					m = Af[0];
					n = bSearch(m);
					s += (ULL) n *(bPow(m, Af[1] - 1));
				}
			}
		}
		else
		{
			x = 0;
			for (j = 0; j < k; j += 2)
			{
				l = Af[j];
				if ((l == 2) || (l == 5))
				{
					continue;
				}
				if (l == 3)
				{
					if (Af[j + 1] > 1)
					{
						y = bPow(3, Af[j + 1] - 2);
					}
					else
					{
						y = 1;
					}
				}
				else if (l == 487)
				{
					y = 486;
				}
				else
				{
					n = bSearch(l);
					if (Af[j + 1] > 1)
					{
						y = n * (bPow(l, Af[j + 1] - 1));
					}
					else
					{
						y = n;
					}
				}
				c[x++] = y;
			}
			if (x)
			{
				if (x == 1)
				{
					s += (ULL) c[0];
				}
				else
				{
					for (j = 1, y = c[0]; j < x; j++)
					{
						y = (y / gcd(y, c[j])) * c[j];
					}
					s += (ULL) y;
				}
			}
		}
	}
	printf("%llu\n", s);
	return 0;
}

gcd(int a, int b)
{
	int t;
	while (b != 0)
	{
		t = b;
		b = a % t;
		a = t;
	}
	return a;
}

bSearch(int key)
{
	int left = 0, right = Tidx - 1, middle;

	while (left <= right)
	{
		middle = (left + right) / 2;
		if (T1[middle] == key)
		{
			return T2[middle];
		}
		if (T1[middle] > key)
		{
			right = middle - 1;
		}
		if (T1[middle] < key)
		{
			left = middle + 1;
		}
	}
	printf("key %u not found\n", key);
	exit(1);
}

 factors(int n)
{
	int s = sqrt(n);
	int i, p, pi;
	int k = 0;
	for (i = 0, p = PRIMES[0]; p <= s; p = PRIMES[++i])
	{
		if (n % p == 0)
		{
			pi = 0;
			while (n % p == 0)
			{
				++pi;
				n /= p;
			}
			Af[k++] = p;
			Af[k++] = pi;
		}
		if (n == 1)
		{
			Af[k] = 0;
			return k;
		}
	}
	Af[k++] = n;
	Af[k++] = 1;
	Af[k] = 0;
	return k;
}

buildPrimesArray()
{
	int limit = 1000000;
	int i, j, l, s;
	l = (limit / 2) + 1;
	int *a = malloc(sizeof(int) * l);
	if (a == 0)
	{
		printf("build:malloc fail!");
		return 0;
	}
	for (j = 0, i = 3; i < limit; i += 2)
	{
		a[j++] = i;
	}
	s = sqrt(limit);
	for (i = 0; i <= s; i++)
	{
		if (a[i])
		{
			j = (a[i] * (i + 1)) + i;
			while (j < l)
			{
				a[j] = 0;
				j += a[i];
			}
		}
	}
	PRIMES[0] = 2;
	for (i = 0, j = 1; i < l; i++)
	{
		if (a[i])
		{
			PRIMES[j++] = a[i];
		}
	}
	free(a);
}

modPow(b, e, m)
{
	ULL li = 1;
	ULL lb = (ULL) b;
	ULL le = (ULL) e;
	ULL lm = (ULL) m;

	while (1)
	{
		if (le % 2 == 1)
		{
			li = (li * lb) % lm;
		}
		le >>= 1;
		if (!le)
		{
			return (int)li;
		}
		lb = (lb * lb) % lm;
	}
}

bPow(b, e)
{
	int i = 1;
	while (1)
	{
		if (e % 2 == 1)
		{
			i *= b;
		}
		e >>= 1;
		if (!e)
		{
			return i;
		}
		b *= b;
	}
}
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