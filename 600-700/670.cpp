int main(){
    ll k = 4;
    matrix<field> M(12, 12);

    for (ll i = 0; i < 8; ++i) M.c[i][i + 4] = 1;
    for (ll i = 9; i < 12; ++i) for (ll j = 4 * (i - 9); j < 12; j += 4)
        M.c[i][j] = (i == 9 ? 1 : 2) * (k - 1) * (k - 2);
    M.c[8][8] = k - 1;
    M.c[8][9] = k - 2;
    for (ll i = 9; i < 12; ++i) M.c[i][10] = k - 2;
    M.c[9][7] = M.c[10][7] = M.c[10][11] = k - 2;

    vector<field> V(12);
    V[8] = k;
    V[9] = k * (k - 1);
    V[10] = V[11] = 2 * k * (k - 1);
    V = M * V;
    V[9] += k * (k - 1);
    V[10] += 2 * k * (k - 1);
    V = M * V;
    V[9] += k * (k - 1);

    ll n;
    cin >> n;
    vector<field> W = power(M, n - 3) * V;
    cout << W[8] + W[9] << endl;

    return 0;
}