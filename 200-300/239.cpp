#include <stdio.h>

double P(int k) {
	double res = 1.0;
	for (int i = 0; i < 22; i ++) {
		if (i < k) res *= 22 - i;
		else res *= 75 + k - i;
		res /= 97 - i;
	}
	for (int i = 0; i < k; i ++) {
		res *= 22 - i;
		res /= k - i;
	}
	return res;
}

double Q(int n, int k) {
	if (k == 0) return 1.0;
	if (k == 1) return (n - 1.0) / n;
	return ((k - 1) * Q(n - 1, k - 2) + (n - k) * Q(n - 1, k - 1)) / n;
}

int main(int argc, char* argv[]) {
	double res = 0.0;
	for (int i = 0; i <= 22; i ++) {
		res += P(i) * Q(22, i);
	}
	res = res * 2300 / 100 / 99 / 98;
	printf("res=%.15f\n", res);
}