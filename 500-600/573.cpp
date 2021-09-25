#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const int N = 1000000;

int main() {
	ld res = 1.0, temp = 1.0;
	for (int i = 2; i <= N; i++) {
		temp = temp * (N - i + 1) / N;
		res += temp;
	}
	cout << setprecision(14) << (double)res << "\n";
        cout << "Time elapsed : " << (1.0 * clock() / CLOCKS_PER_SEC) << " seconds\n";
	return 0;
}
