#includes

using namespace std;

typedef long long ll;

int main(void){
	ll ans = 0;
	for(ll n=1;n<=(1<<30);n++){
		ll x = n ^ (2*n) ^ (3*n);
		if(x == 0) ans++;
	}
	cout << ans << endl;
	return 0;
}