#define ll long long
#define rep(i,l,r)for(ll i=l;i<r;i++)
#define N 1000000000000000000
ll po(ll a,int n){ll x=1;while(n--)x*=a;return x;}
ll ans;
main(){
	double ttt=log2(N);
	ll crN=cbrt(N);
	rep(i,2,crN+1){
		ll n=i;
		int index=ttt/log2(i)+1;
		rep(e,2,index+1){
			ll x[10]={},cnt=0;
			ll t=n;
			x[cnt++]=t;
			while(1){
				if(pow(t,e)>N)break;
				t=po(t,e);
				rep(k,0,cnt){
					if(t+x[k]<=N)ans+=k?1:cnt;
					else break;
				}
				x[cnt++]=t;
			}
		}
	}
	ll srN=sqrt(N);
	ans+=srN-crN-1;
	if(srN*(srN+1)<=N)ans++;
	printf("%lld",ans);
}