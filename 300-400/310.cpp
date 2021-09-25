#includes

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)

#define N 100001
typedef long long ll;

int g[N+10];
ll a[100];

int main(void){
	int i,j,k,d;
	
	REP(i,N){
		set <int> s;
		for(j=1;j*j<=i;j++) s.insert(g[i-j*j]);
		for(j=0;;j++) if(s.find(j) == s.end()) break;
		g[i] = j;
	}
	
	REP(i,N) a[g[i]]++;
	
	ll ans = 0;
	REP(i,100) REP(j,100) REP(k,100) if((i^j^k) == 0){
		if(i < j && j < k) ans += a[i] * a[j] * a[k];
		if(i == j && j < k) ans += a[i] * (a[i] + 1) / 2 * a[k];
		if(i < j && j == k) ans += a[i] * a[j] * (a[j] + 1) / 2;
		if(i == j && j == k) ans += a[i] * (a[i] + 1) * (a[i] + 2) / 6;
	}
	
	cout << ans << endl;
	
	return 0;
}