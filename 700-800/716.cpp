Mint C(int n, int m) {
    vector<Mint> p2(n + m + 1);
    p2[0] = 1;
    for (int i = 1; i < (int)p2.size(); ++i) {
        p2[i] = p2[i - 1] * 2;
    }
    Mint ans = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            ans += p2[n - i + m - j - 2] * i * j * 4 * 2;
        }
    }
    ans += p2[n + m] - p2[n] * 2 - p2[m] * 2 + 4;
    ans += (p2[n] * 2 + p2[m] * 2 - 4) * n * m;
    ans -= 2 * (n - 1) * (m - 1);
    return ans;
}