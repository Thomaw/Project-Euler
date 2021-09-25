#includes

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)

#define N 50000000
typedef long long ll;

ll a[N+10];

int main(void){
	int i,ans=0;
	
	REP(i,N) a[i] = 2ll*i*i + 2*i + 1;
	for(i=1;i<N;i++){
		if(a[i] == 2ll*i*i + 2*i + 1) ans++;
		if(a[i] > 1){
			ll p = a[i];
			for(ll j=i;j<N;j+=p) while(a[j] % p == 0) a[j] /= p;
			for(ll j=p-1-i;j<N;j+=p) while(a[j] % p == 0) a[j] /= p;
		}
	}
	
	cout << ans << endl;
	
	return 0;
}