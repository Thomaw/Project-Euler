ld ea(ld pa, ld pb, ld p){
    ld A = 1 - (1 - pa - pb) * (1 - p), B = pa * (1 - p), C = pb * (1 - p);
    ld s = sqrt(A * A - 4 * B * C);
    ld x1 = (A + s) / (2 * B), x2 = (A - s) / (2 * B);
    vvld M(6, vld(6, 0));
    M[0][0] = x1; M[0][1] = -1; M[5][4] = x2; M[5][5] = -1;
    for (int i = 1; i <= 4; i++) {M[i][i - 1] = C; M[i][i] = -A; M[i][i + 1] = B;}
    vld v(6, 0);
    v[2] = -pa; v[3] = pb - 1; v[4] = -1; v[5] = (x2 - 1) / p;
    return (matrixInverse(M) * v)[2];
}

ld solve(ll k){
    ld pa = 1 / sqrt(k + 3);
    ld pb = pa + 1.0 / k / k;
    ld p = 1.0 / k / k / k;
    return ea(pa, pb, p);
}

ld H(int n){
    ld total = 0;
    for (int k = 3; k <= n; k++) total += solve(k);
    return total;
}

int main(){
    cout.precision(30);
    cout << H(3) << endl;
    cout << H(50) << endl;
    cout << H(100) << endl;
    cout << H(1000) << endl;
    cout << H(10000) << endl;
    cout << H(100000) << endl;
    cout << H(1000000) << endl;
    cout << ea(0.25, 0.25, 0.5) << endl;
    cout << ea(0.47, 0.48, 0.001) << endl;
    return 0;
}