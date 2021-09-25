#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#pragma comment(linker, "/STACK:16777216")
using namespace std;

#define bit(n) (1<<(n))
#define inf 1000000000
#define eps 1e-9
#define PI 3.1415926535897932385
#define pb push_back
#define sz size()
#define mp make_pair
#define cl clear()
#define all(a) a.begin(),a.end()
#define fill(ar,val) memset(ar,val,sizeof ar)
#define MIN(a,b) if(a>(b)) a=(b)
#define MAX(a,b) if(a<(b)) a=(b)
#define sqr(x) ((x)*(x))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef __int64 LL;

#define X first
#define Y second

clock_t start=clock();

typedef unsigned int UI;

const UI N=10000000000/4;
const int STEP=500;
const int H=N/STEP;
vector<PII> sq[H+1];
vector<PII> sq2[H+1];

int main()
{
	//freopen("out.txt","w",stdout);
	LL ans=0;
	LL tot=0;
	int i,j,k;
	for(int step=0;step<STEP;step++)
	{
		for(i=1;i<=H;i++)
			sq[i].cl,sq2[i].cl;
		UI L=step*H;
		UI R=L+H;
		UI maxa=sqrt(R/2.)+eps;
		UI a,b;
		for(a=1;a<=maxa;a++)
		{
			UI minb=a;
			if(L>=a*a)
			{
				UI curb=sqrt(L-a*a)+1+eps;
				MAX(minb,curb);
			}
			UI maxb=sqrt(R-a*a)+eps;
			for(b=minb;b<=maxb;b++)
			{
				UI cur=a*a+b*b-L;
				sq[cur].pb(mp(a,b));
				if(b>a) sq2[cur].pb(mp(b-a,b+a));
			}
		};
		for(i=1;i<=H;i++) if(sq[i].sz)
		{
			sort(all(sq2[i]));
			int SZ=sq2[i].sz;
			tot+=SZ*sq[i].sz;
			for(j=0;j<SZ;j++)
			{
				int a=sq2[i][j].X,d=sq2[i][j].Y;
				for(k=sq[i].sz;k--;)
				{
					int f=sq[i][k].Y;
					if(d-a<2*f && 2*f<a+d)
						ans+=SZ-j-1;
				}
			}
		}
		printf("step=%d finished\n",step);
		fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));
	};
	printf("%I64d\n",tot);
	printf("%I64d\n",ans);
	fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));
	return 0;
}