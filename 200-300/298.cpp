#includes

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)

typedef pair <vector <int>, vector <int> > state;
map <state, int> mp;

bool used[100000];
int S,graph[100000][20],score[100000][20];
double dp[2][100000][110];

void func(vector <int> L, vector <int> R){
	int x,i,j,k;
	
	int cur = mp[make_pair(L,R)];
	if(used[cur]) return; used[cur] = true;
	
	REP(x,10){
		int d = 0;
		
		bool found1 = false;
		REP(i,L.size()) if(L[i] == x) found1 = true;
		vector <int> L2;
		if(found1){
			REP(i,L.size()) if(L[i] != x) L2.push_back(L[i]);
			L2.push_back(x);
		} else {
			REP(i,L.size()) if(i != 0 || L.size() != 5) L2.push_back(L[i]);
			L2.push_back(x);
		}
		if(found1) d++;
		
		bool found2 = false;
		REP(i,R.size()) if(R[i] == x) found2 = true;
		vector <int> R2;
		if(found2){
			R2 = R;
		} else {
			REP(i,R.size()) if(i != 0 || R.size() != 5) R2.push_back(R[i]);
			R2.push_back(x);
		}
		if(found2) d--;
		
		vector <int> L3,R3;
		int a[20];
		REP(j,10) a[j] = -1;
		k = 0;
		REP(k,L2.size()) {L3.push_back(k); a[L2[k]] = k;}
		REP(j,R2.size()) if(a[R2[j]] != -1) R3.push_back(a[R2[j]]); else {R3.push_back(k); k++;}
		
		int next;
		if(mp.find(make_pair(L3,R3)) != mp.end()){
			next = mp[make_pair(L3,R3)]; graph[cur][x] = next; score[cur][x] = d;
		} else {
			next = S; mp[make_pair(L3,R3)] = S; S++; graph[cur][x] = next; score[cur][x] = d; func(L3,R3);
		}
	}
}

int main(void){
	vector <int> v;
	mp[make_pair(v,v)] = 0; S = 1;
	func(v,v);
	
	int i,j,k,x;
	
	dp[0][0][55] = 1.0;
	REP(i,50){
		int cur = i % 2, next = (i+1) % 2;
		REP(j,S) REP(k,110) dp[next][j][k] = 0.0;
		REP(j,S) REP(k,110) if(dp[cur][j][k] > 0.0) REP(x,10) dp[next][graph[j][x]][k+score[j][x]] += dp[cur][j][k] * 0.1;
	}
	
	double ans = 0.0;
	REP(i,S) REP(j,110) ans += abs(j-55) * dp[0][i][j];
	printf("%.8f\n",ans);
	
	return 0;
}