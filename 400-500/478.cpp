    int N;
    cin >> N;
    const i64 P = deg(11, 8);
    const i64 tp = totient(P), tp2 = 2 * tp;
    i64 G = 0;
    vi mu = moebius(N);
    for (int i = 1; i <= N; ++i) {
        G += tp2 + mu[i] * (degMod(N / i + 1, 3, tp2) - 1);
    }
    G %= tp2;
    vi phi(N + 1);
    phi[1] = 1;
    vi mind = genPrimes(N + 1, true);
    for (int i = 2; i <= N; ++i) {
        int p = mind[i];
        if (mind[i] == mind[i / p]) phi[i] = phi[i / p] * p;
        else phi[i] = phi[i / p] * (p - 1);
    }
    i64 ans = degMod(2, G, P) + P - 1;
    for (int b = 1; b <= N; ++b) {
        int w = phi[b] * 6;
        i64 T = 0;
        for (int d = 1; d <= N / b; ++d) {
            T += mu[d] * ((N / d + 1) % tp2 * (N / d / b) % tp2);
            T += tp2 - mu[d] * (1LL * (N / d / b) * (N / d / b + 1) / 2 % tp2) * b % tp2;
            T %= tp2;
        }
        ans += P - 1LL * w * (degMod(2, (G + tp2 - 1) / 2, P) - degMod(2, (G + tp2 - 1) / 2 + tp2 - T, P) + P) % P;
        ans %= P;
    }
    cout << ans << '\n';