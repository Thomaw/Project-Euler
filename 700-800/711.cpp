using ll=long long;
const int nax=15*1000*1007;
const ll mod=1000*1000*1000+7;

int n;

ll power[nax];
ll many[nax];
ll sum[nax];
ll strange[nax];

int main()
{
	scanf("%d", &n);
	power[0]=1;
	for (int i=1; i<=n; i++)
		power[i]=(power[i-1]*2)%mod;
	strange[8]=8;
	for (int i=10; i<=n; i+=2)
		strange[i]=(strange[i-2]*4+i/2*3-8)%mod;
	many[4]=5;
	for (int i=6; i<=n; i+=2)
		many[i]=(many[i-2]*2-(i/2-3))%mod;
	sum[6]=179;
	for (int i=8; i<=n; i+=2)
		sum[i]=(sum[i-2]*2+power[i-1]+power[i-3]+power[i-2]*(many[i]-many[i-2]+mod)-strange[i]+mod)%mod;
	printf("%lld\n", (sum[n]+power[n])%mod);
	return 0;
}