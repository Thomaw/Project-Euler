//lines I've changed of ZhouYuChen's code are indicated with //; minimal changes so spacing is funny
#include<bits/stdc++.h>
using namespace std;

int64_t C(int n) {
	map<int, vector<pair<int,int>>> d;
	//int c = 0;
	for(int a = -n; a <=n; ++a)
		for(int b = -n; b <=n; ++b)
			if(a * b >= -n && a * b <=n + 1) //{
				d[a*b].push_back({a, b});
				//++c;
			//}
	auto ck = [=](pair<int, int> a, pair<int,int> b) {
		return abs(a.first*b.second) <= n && abs(a.second * b.first) <= n;
	};
	int64_t res = 0;
	for(int m11 = -n; m11 <= n + 1; ++m11)
	  for(int m22 = -m11/2 + ((m11>0 && m11&1==1)?0:1), m33, sym; m22 <= min(m11, n+1-m11); ++m22) {//
			m33 = 1 - m11 - m22;
			sym = (m11==m22 || m22==m33)?3:6;//
			//if(m33 >= -n && m33 <= n + 1) {
				int cnt = 0;
				for(auto p1 : d[m11]) {
				  if ((p1.first<0) || ((p1.first==0) && (p1.second<0)) || (p1.first<p1.second)) continue; //
				  int dbl = (p1.first==p1.second)?1:2;//
				for(auto p2 : d[m22]) if(ck(p1, p2))
				for(auto p3 : d[m33]) if(ck(p1, p3) && ck(p2, p3))
					cnt += dbl;//
				}
				int mul = 2;
				if(m11 == n+1) --mul;//
				if(m33 == -n) --mul;//
				res += mul * cnt * sym;//
			//}
		}
	return res + 2;
}


int main() {
	cout << C(200) << endl;
}