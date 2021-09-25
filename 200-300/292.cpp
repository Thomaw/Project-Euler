#includes

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)

#define PI acos(-1.0)
#define eps 1.0E-9
#define N 120
typedef long long ll;

vector <pair <double, pair <int, int> > > v;
ll dp[2][140][140][140];
int d3[10000];

int main(void){
	int i,j,k,x,y,d;
	
	for(i=-N;i<=N;i++) for(j=-N;j<=N;j++) for(k=1;k<=N;k++) if(i*i + j*j == k*k){
		double theta = atan2(j,i);
		while(theta < -eps) theta += 2.0 * PI;
		v.push_back(make_pair(theta,make_pair(i,j)));
	}
	sort(v.begin(),v.end());
	REP(i,v.size()) d3[i] = (int)sqrt(v[i].second.first*v[i].second.first + v[i].second.second*v[i].second.second + 0.5);
	
	dp[0][70][70][0] = 1;
	int sz = 0;
	i = 0;
	while(i < v.size()){
		int cur = sz % 2, next = (sz + 1) % 2;
		for(j=i;j<v.size();j++) if(fabs(v[j].first - v[i].first) > eps) break;
		
		REP(x,140) REP(y,140) REP(d,N+1) dp[next][x][y][d] = dp[cur][x][y][d];
		REP(x,140) REP(y,140) REP(d,N+1) if(dp[cur][x][y][d] > 0) for(k=i;k<j;k++){
			int x2 = x + v[k].second.first, y2 = y + v[k].second.second, d2 = d + d3[k];
			if(2*abs(x2-70) <= N && 2*abs(y2-70) <= N && d2 <= N) dp[next][x2][y2][d2] += dp[cur][x][y][d];
		}
			
		sz++; i = j;
	}
	
	ll ans = 0;
	REP(i,N+1) ans += dp[sz%2][70][70][i];
	ans--;
	int tmp = 0;
	REP(i,v.size()) if(d3[i] * 2 <= N) tmp++;
	ans -= tmp / 2;
	cout << ans << endl;
	
	return 0;
}