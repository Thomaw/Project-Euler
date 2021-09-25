const __int64 m= 1000000007;
__int64 modpow(__int64 base, __int64 exp, __int64 modulus) {
	base %= modulus;
	__int64 result = 1;
	while (exp > 0) {
		if (exp & 1) result = (result * base) % modulus;
		base = (base * base) % modulus;
		exp >>= 1;
	}
	return result;
}
__int64 inv[20];
__int64 c(__int64 n, __int64 k) {
	n %= m;
	__int64 r=1;
	for (int i = 1; i <= k; i++) r = (((r*(n + 1 - i)) % m)*inv[i]) % m;
	return r;
}
__int64 lim[20];
__int64 cs(__int64 n, __int64 k,int st) {
	if (n < 0) return 0;
	__int64 r = 0;
	r = c(n + k, k);
	for (int i = st; i <= k; i++) 
		r -= cs(n - lim[i]-1, k,i+1);
	while (r < 0) r += m;
	return r;
}
__int64 s(__int64 n, __int64 k, __int64 b) {
	lim[1] = b;
	for (int i = 2; i <= k; i++) lim[i] = lim[i - 1] * b;
	return cs(n, k,1);
}

int main()
{
	int i;
	for (i = 1; i <= 19; i++) inv[i] = modpow(i, m - 2, m);
	__int64 r = 0;
	__int64 n = 1000000000;
	for (i = 10; i <= 15; i++) {
		n *= 10;
		r += s(n, i, i);
	}
	std::cout << r%m;
	std::cin >> i;
    return 0;
}