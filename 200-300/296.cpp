#includes

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)

#define N 100000

typedef long long ll;

ll gcd(ll x, ll y){
	return x ? gcd(y%x,x) : y;
}

int main(void){
	ll x,y,ans=0;
	
	for(x=1;x+x+x<=N;x++) for(y=x;x+y+y<=N;y++){
		ll zmin = y;
		ll zmax = min(N-x-y,x+y-1);
		ll d = gcd(x,y);
		ll z = (x+y) / d;
		ans += zmax/z - (zmin-1)/z;
	}
	
	cout << ans << endl;
	
	return 0;
}