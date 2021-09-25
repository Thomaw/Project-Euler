const ll N = 1e12;

bool iss(ll n, ll r){
    vector<int> d;
    ll n2 = n;
    while(n2){
        d.push_back(n2%10);
        n2 /= 10;
    }
    reverse(d.begin(), d.end());
    int m = d.size();

    FOR(mask, 1<<(m-1)){
        if (mask == 0) continue;
        ll s = 0;
        ll x = d[0];
        FOR(i, m-1){
            if ((mask >> i) & 1){
                s += x;
                x = d[i+1];
            }
            else{
                x = 10*x + d[i+1];
            }
        }
        s += x;
        if (s == r)
            return 1;
    }
    return 0;
}

int main(int argc, char** argv) {
    const ll N2 = sqrti(N);
    ll sol = 0;
#pragma omp parallel for reduction(+:sol)
    for(ll r = 1; r <= N2; r++){
        if (iss(r*r, r))
            sol += r*r;
    }
    cout << sol << endl;
    return 0;
}