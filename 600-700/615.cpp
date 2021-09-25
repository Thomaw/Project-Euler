int upd(const void*a, const void*b){return*(double*)a<*(double*)b?-1:*(double*)a>*(double*)b?1:0;}
void sortup(double*a,int n){qsort(a,n,sizeof(double),upd);}

#define ll long long
int prime[10000010];
void makep(ll n){prime[0]=prime[1]=1;for(int i=2;i*i<=n;i++)if(!prime[i])for(int j=i*i;j<=n;j+=i)prime[j]=1;}
ll pom(ll a,ll n,int m){ll x=1;for(a%=m;n;n/=2)n&1?x=x*a%m:0,a=a*a%m;return x;}

#define M 100000
#define MOD 123454321
double s[2000000];
int cnt=0;

void f(double n,int p){
	double nn=n;
	while(nn<M){
		s[cnt++]=nn;
		nn*=2;
	}
	while(n/2*p<M){
		f(n/2*p,p);
		while(prime[++p]);
	}
}

int main(){
	makep(M*2);
	f(1,3);
	printf("%d\n",cnt);
	sortup(s,cnt);
//	printf("%f\n",s[999999]);
	ll ans=s[999999]*1024;
	printf("%lld\n",pom(2,1000000-10,MOD)*ans%MOD);
}