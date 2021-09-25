    i64 n;
    cin >> n;
    i64 m = sqrt(n);
    vi64 ps = genPrimes(n / (m + 1));
    i64 ans = 0;
    for (i64 p: ps) {
        vi64 div = {n};
        i64 q = p;
        while (q <= n) {
            div.pb(n / q);
            q *= p;
        }
        forn(i, div.size() - 1) div[i] -= div[i + 1];
        forn(i, div.size()) div[i] %= P;
        forn(i, div.size()) forn(j, i) add(ans, div[i] * div[j] % P * (i - j));
    }
    cout << ans << '\n';

    TPrimeCounter pc;
    pc.init(n);

    for1(i, m + 1) pc.prime_count(i, false);
    pc.do_precalc();
    for1(i, m) {
        i64 x = pc.prime_count(i, true) - pc.prime_count(i + 1, true);
        x %= P;
        i64 r = i, t = n - i;
        r %= P; t %= P;
        add(ans, r * t % P * x);
    }
    cout << ans * 2 % P << '\n';