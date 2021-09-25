const __int64 m = 1000000007;
__int64 a[10001];
__int64 f[10001];
__int64 rf[10001];
__int64 pm(__int64 num, __int64 pow, __int64 mod)
{
	__int64 res;
	for (res = 1; pow; pow >>= 1)
	{
		if (pow & 1)
			res = (res * num) % mod;
		num = (num * num) % mod;
	}
	return res;
}
__int64 pp2(__int64 p) {
	__int64 i = pm(2, p,m-1);
	return pm(2, i-1, m)-1;
}
__int64 x[10001][10001];
void s(int n, int nn) {
	__int64 p, r[10001], s;
	int i, j, l, o, q;
	l = n - 1;
	s = (rf[l] * a[l]) % m;
	p = 1;
	for (i = 1; i <= nn; ++i) {
		p = (p*s) % m;
		r[i] = (p*rf[i]) % m;
	}
	for (i = nn; i > 0; --i)
	{
		if ( i %100==0) std::cout << n << " " << i << "\n";
		q = 0;
		for (o = l; o <= i; o += l) {
			++q;
			for (j = nn; j >= q; --j)
				if (x[i - o][j - q])
					x[i][j] = (x[i][j] + x[i - o][j - q] * r[q]) % m;
		}
	}
}
int main()
{
	__int64 n = 10000;
	__int64 k = 10;
	__int64 i, j,l;
	f[1] = 1;
	for (i = 2; i <= n; ++i)
		f[i] = (f[i-1] * i) % m;
	rf[0] = 1;
	rf[1] = 1;
	for (i = 2; i <= n; ++i)
		rf[i] = pm(f[i], m - 2, m);
	a[1] = 1;		
	for (i = 0; i <= n; ++i)
		for (j = 0; j <= k; ++j)
			x[i][j] = 0;
	x[0][0] = 1;
	for (i = 2; i < n; ++i) {
		a[i] = pp2(i);
		s(i, n);
		for (j = 1; j <= i; ++j) 
			for (l = 0; l <= i; ++l)
				a[i] = (a[i] - ((x[l][j] * f[i]) % m)*rf[i-l]) % m;
		if (a[i] < 0) a[i] += m;
		std::cout << i <<" "<<a[i]<< "\n";
	}
	j = 0;
	for (i = 1; i <= n; ++i)
		j = (j + ((x[i][k] * f[n]) % m)*rf[n - i]) % m;
	std::cout << j;
	std::cin >> i;
    return 0;
}
