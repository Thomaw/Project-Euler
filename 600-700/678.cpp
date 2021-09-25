// requires p prime and p%4==1
complex_number<ll> prime_square_sum(const ll &p){
    quotient_ring<> s(-1, p);
    s = sqrt(s);
    return gcd<complex_number<ll>>({s.x, 1}, {p, 0});
}

vector<complex_number<ll>> square_sum_list(const vpll &f){
    vector<complex_number<ll>> cs = {{1, 0}};
    for (const pll &p : f){
        vector<complex_number<ll>> this_cs, next_cs;
        if (p.first == 2) this_cs.push_back(power<complex_number<ll>>({1, 1}, p.second));
        else if (p.first % 4 == 1){
            complex_number<ll> c = prime_square_sum(p.first);
            this_cs.push_back(power(c, p.second));
            for (ll i = 1; i <= p.second; ++i) this_cs.push_back(this_cs.back() / c * c.conjugate());
        }
        else if (p.second % 2 == 0) this_cs.push_back({power(p.first, p.second / 2), 0});
        for (const complex_number<ll> c1 : cs) for (const complex_number<ll> c2 : this_cs) next_cs.push_back(ring_abs(c1 * c2));
        cs = next_cs;
    }
    return cs;
}

const ld l2 = logl(2);

ld add_logs(ld l1, ld l2){
    if (l1 < l2) swap(l1, l2);
    if (l1 - l2 > 150) return l1;
    return l1 + logl(1 + expl(l2 - l1));
}

ll solution_count(const ll &n, const vpll &f, const ld &log_n, vll &divs, const ll &e){
    vpll v;
    if (e == 2){
        for (const complex_number<ll> &c : square_sum_list(f)) if (0 < c.y && c.y < c.x) v.push_back({c.y, c.x});
    }
    else if (e % 2 == 0){
        return 0;
    }
    else{
        for (ll i = 0; i < divs.size(); ++i){
            ll s = divs[i];
            if (e * logl(s) + (1 - e) * l2 > log_n){
                divs[i] = divs.back();
                divs.pop_back();
                --i;
                continue;
            }
            ld mini = 0, maxi = (ld) s / 2;
            while (maxi - mini > 0.5){
                ld midi = (mini + maxi) / 2;
                if (add_logs(e * logl(midi), e * logl(s - midi)) < log_n) maxi = midi;
                else mini = midi;
            }
            ll a = maxi; ll b = s - a;
            if (0 < a && a < b && power(a, e) + power(b, e) == n) v.push_back({a, b});
        }
    }
    ll total = 0;
    for (pll p : v){
        while (true){
            ++total;
            ll s1 = sqrtl(p.first), s2 = sqrtl(p.second);
            if (s1 * s1 != p.first || s2 * s2 != p.second) break;
            p = {s1, s2};
        }
    }
    return total;
}

int main(){
    ll N = 1000000000000000000, total = 0;
    sieve(pow(N, 0.334));
    for (ll c = 2; cube(c) <= N; ++c) for (ll f = 3; power(c, f - 1) <= N / c; ++f){
        ll n = power(c, f);
        vpll fac = factorize(c);
        for (pll &p : fac) p.second *= f;
        ld log_n = logl(n);
        vll divs = divisor_list(fac);
        for (ll e = 2; e * l2 <= log_n; ++e) total += solution_count(n, fac, log_n, divs, e);
    }
    cout << total << endl;
    return 0;
}