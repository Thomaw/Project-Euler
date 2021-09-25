long long total_popcount(long long n) {
    // sum of popcount(i) for i from 1 to n
    n += 1;
    long long res = 0;
    for (int i = 60; i >= 0; --i) {
        long long b = 1ll << i;
        long long m = n / (2 * b);
        res += m * b;
        m = n % (2 * b);
        res += max(0ll, m - b);
    }
    return res;
}

long long S(long long n) {
    long long ans = 0;
    int len = 0;
    for (long long d = 1; d <= n; d = d * 2 + 1) {
        ++len;
        long long cnt = min(d, n - d);
        ans += cnt * len + total_popcount(cnt) - total_popcount(d + cnt) + total_popcount(d);
    }
    return ans;
}