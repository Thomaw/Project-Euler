int m=40;
#define N 150
ll f[N+5][N+5][N+5][43];
int main()
{
	f[0][0][0][0]=1;
	for(int i=0;i<=N;++i)
		for(int s=0;s<=i;++s)
			for(int t=0;t<=i;++t)
				for(int u=0;u<=m;++u) if(f[i][s][t][u])
					for(int w=max(i+1+u-m,1);w<=i+1;++w)
					{
						int ss=s,tt=t;
						if(ss>=w) ++ss;
						if(tt>=w) ++tt;
						if(tt&&w>tt) continue;
						if(ss&&ss<w&&(tt==0||w<tt)) tt=w;
						if(w!=i+1&&(ss==0||w+1<ss)) ss=w+1;
						(f[i+1][ss][tt][u+i+1-w]+=f[i][s][t][u])%=MOD;
					}
	for(int i=0;i<=N;++i)
	{
		ll aa=0;
		for(int s=0;s<=i;++s)
			for(int t=0;t<=i;++t)
				for(int u=0;u<=m;++u) (aa+=f[i][s][t][u])%=MOD;
		cerr<<aa<<",";
	}
	cerr<<"\n";
}