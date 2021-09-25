int main() {
    const long long N = 6;
    const long long K = 2;
    const long long offset = (K - 2 + N) % N;
  
    long long denominator = pow(2, N)-1;
    denominator *= denominator;
    long long numerator = 0;
    for (int i = 0; i < N; i++) {
        int rotIndex = (offset - i + N) % N;
        numerator += pow(2, N-1-i) * pow(2, N-1-rotIndex);
    }

    // 1104/3969, which is just 368/1323 unreduced
    cout << numerator << " / " << denominator << endl;
    return 0;
}