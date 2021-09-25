#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using vi=vector<int>;
using ld=long double;

unordered_map <ll,ld> memo[60][5][60][17];

ll my_hash(vi &vec)
{
	ll ret=0;
	for (int i : vec)
		ret=ret*10+i;
	return ret;
}

ld recc(int to_end, int curr, vi still, int wasted, int want)
{
	if (want<0)
		return 0;
	if (!to_end)
		return (!want);
	sort(still.begin(), still.end());
	reverse(still.begin(), still.end());
	while(!still.empty() && !still.back())
		still.pop_back();
	ll ha=my_hash(still);
	if (memo[to_end][curr][wasted][want].count(ha))
		return memo[to_end][curr][wasted][want][ha];
	ld res=0;
	if (curr)
		res+=curr*recc(to_end-1, 0, still, wasted+curr-1, want);
	for (int i=0; i<(int)still.size(); i++)
	{
		int rem=still[i];
		still[i]=curr;
		res+=rem*recc(to_end-1, rem-1, still, wasted, want-(rem==1));
		still[i]=rem;
	}
	if (wasted)
	{
		still.push_back(curr);
		res+=wasted*recc(to_end-1, 0, still, wasted-1, want);
	}
	res/=to_end;
	return memo[to_end][curr][wasted][want][ha]=res;
}

int main()
{
	ld res=0;
	res+=recc(52, 0, vi(13, 4), 0, 2);
	res+=recc(52, 0, vi(13, 4), 0, 3);
	res+=recc(52, 0, vi(13, 4), 0, 5);
	res+=recc(52, 0, vi(13, 4), 0, 7);
	res+=recc(52, 0, vi(13, 4), 0, 11);
	res+=recc(52, 0, vi(13, 4), 0, 13);
	printf("%.10lf\n", (double)res);
	return 0;
}