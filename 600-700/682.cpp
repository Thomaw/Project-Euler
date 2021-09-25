int main(){
    ll N = 100, n = 10000000;
    vector<vector<field>> dp2(N + 1, vector<field>(2 * N + 1));
    dp2[0][N] = 1;
    for (ll i = 2; i <= N; i += 2) for (ll j = -i / 2; j <= i / 2; j += 2) dp2[i][N + j] = 1;
    vector<vector<field>> dp3(N + 1, vector<field>(2 * N + 1));
    dp3[0][N] = 1;
    for (ll i = 2; i <= N; ++i) for (ll j = -i / 2; j <= i / 2; ++j){
        dp3[i][N + j] = dp2[i][N + j];
        if (i >= 3) dp3[i][N + j] += dp3[i - 3][N + j - 1] + dp3[i - 3][N + j + 1];
        if (i >= 6) dp3[i][N + j] -= dp3[i - 6][N + j];
    }
    vector<vector<field>> dp5(N + 1, vector<field>(2 * N + 1));
    dp5[0][N] = 1;
    for (ll i = 2; i <= N; ++i) for (ll j = -i / 2; j <= i / 2; ++j){
        dp5[i][N + j] = dp3[i][N + j];
        if (i >= 5) dp5[i][N + j] += dp5[i - 5][N + j - 1] + dp5[i - 5][N + j + 1];
        if (i >= 10) dp5[i][N + j] -= dp5[i - 10][N + j];
    }
    vector<field> v(N + 1);
    for (ll i = 0; i <= N; ++i) v[i] = dp5[i][N];
    cout << solve_linear_recurrence(v, berlekamp_massey(v), n) << endl;
    return 0;
}