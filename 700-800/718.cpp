    int p;
    cin >> p;
    i64 a = deg(17, p), b = deg(19, p), c = deg(23, p);
    i64 abc = a + b + c;

    vi dist(c, 1e9);
    dist[abc % c] = abc / c;
    deque<int> q;
    q.pb(abc % c);
    while (!q.empty()) {
        int x = q.front();
        q.pop_front();
        forn(z, 2) {
            int y = x + (z ? b : a);
            int D = dist[x];
            while (y >= c) y -= c, ++D;
            if (D < dist[y]) {
                dist[y] = D;
                if (D == dist[x]) q.push_front(y);
                else q.push_back(y);
            }
        }
    }

    i64 ans = 0;
    forn(i, c) {
        assert(dist[i] < 1e8);
        (ans += 1LL * i * dist[i]) %= P;
        (ans += 1LL * c * sumr(dist[i] - 1)) %= P;
    }
    cout << ans << '\n';
