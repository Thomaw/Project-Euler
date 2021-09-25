#include <cstdio>
using namespace std;

typedef long long int64;

int64 floor(int64 a, int64 b) {
	return a/b;
}

int64 ceil(int64 a, int64 b) {
	return (a+b-1)/b;
}

int64 f(int64 n, int64 x) {
	return floor(x+ceil(n, x), 2);
}

double solve(int64 L, int64 R, int64 x) {
	if (f(L, x) == x && f(R, x) == x)
		return 1;
	if (f(L, x) == f(R, x))
		return 1+solve(L, R, f(L, x));
	int64 k = ceil(L, x);
	double res = 0;
	int64 sum = 0;
	for (;;) {
		int64 k1 = (k-1)*x+1, k2 = k*x;
		k1 = max(k1, L);
		k2 = min(k2, R);
		if (k1 > k2) break;
		assert(ceil(k1, x) == ceil(k2, x));
		assert(f(k1, x) == f(k2, x));
		if (f(k1, x) != x)
			res += (k2-k1+1)*solve(k1, k2, f(k1, x));
		sum += k2-k1+1;
		++k;
	}
	assert(sum == R-L+1);
	res = res/sum+1;
	return res;
}

int main() {
	printf("%.10lf\n", solve(10000000000000LL, 99999999999999LL, 7000000));
}