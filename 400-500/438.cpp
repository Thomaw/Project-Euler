#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <algorithm>

#define N 7
struct epspoly
{
	int _[N+1];
};

struct condition
{
	epspoly _[N+1];
};

static condition data[N][N+1];

long long recurse(int a[N], int level)
{
	// find minimal and maximal values for a[level-1]
	// use data[N-level]
	if (level == N + 1) {
		//printf("(%d,%d,%d,%d)\n", a[0], a[1], a[2], a[3]);
		int result = 0;
		for (int i = 0; i < N; i++)
			result += abs(a[i]);
		return result;
	}
	int min = INT_MIN, max = INT_MAX;
	int x, i, j;
	long long result = 0;
	bool curIsMin = true;
	for (x = level; x >= 0; x--, curIsMin = !curIsMin) {
		int val = data[N-level][x]._[N]._[0];
		int epsmult;
		for (i = 1; i < level; i++)
			val += data[N-level][x]._[N-i]._[0] * a[i-1];
		val = -val / data[N-level][x]._[N-level]._[0];
		for (j=1;;j++) {
			epsmult = data[N-level][x]._[N]._[j];
			for (i = 1; i < level; i++)
				epsmult += data[N-level][x]._[N-i]._[j] * a[i-1];
			if (epsmult)
				break;
		}
		if (curIsMin) {
			// a[level-1] > val - epsmult * eps^j
			if (epsmult < 0)
				val++;
			min = std::max(min, val);
		} else {
			// a[level-1] < val - epsmult * eps^j
			if (epsmult > 0)
				val--;
			max = std::min(max, val);
		}
	}
	//printf("level=%d: min=%d, max=%d\n", level, min, max);
	for (a[level-1] = min; a[level-1] <= max; a[level-1]++)
		result += recurse(a, level + 1);
	return result;
}

int main()
{
	int a[N];
	long long sum = 0;
	int i, j, k, x;
	memset(data, 0, sizeof(data));
	// top-level: data[0][*] for f(*+1)
	for (x = 0; x <= N; x++) {
		// data[0][x] = f(x+1-eps)
		for (i = 0; i <= N; i++) {
			// split (x+1-eps)^i to powers eps^j
			int coeff = (i & 1) ? -1 : 1;
			for (j = i; j >= 0; j--) {
				data[0][x]._[i]._[j] = coeff;
				coeff = -coeff * (x + 1) * j / (i - j + 1);
			}
		}
	}
	// calculate differences: data[k][x] = data[k-1][x+1] - data[k-1][x]
	for (k = 1; k < N; k++)
		for (x = 0; x <= N - k; x++)
			for (i = 0; i <= N; i++)
				for (j = 0; j <= i; j++)
					data[k][x]._[i]._[j] = data[k-1][x+1]._[i]._[j] - data[k-1][x]._[i]._[j];
	// find a
	sum += recurse(a, 1);
	printf("%lld\n", sum);
	return 0;
}