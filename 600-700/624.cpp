//p is odd, not necessarily prime
std::pair<unsigned long long, unsigned long long> LucasFibonacci(unsigned long long n, unsigned long long p) {
    typedef std::pair<unsigned long long, unsigned long long> pUll;
    if (n == 1) {
        return pUll(1, 1);
    }

    auto[Lh, Fh] = LucasFibonacci(n/2, p);
    unsigned long long inv = (p + 1) / 2;

    unsigned long long L = (inv*((5 * Fh*Fh + Lh * Lh) % p) % p);
    unsigned long long F = (Lh * Fh) % p;
    if (n % 2) {
        L = (inv*(5 * F + L)) % p;
        F = (2*p + L - 2*F) % p;
    }

    return pUll(L, F);
}


void solve_624() {
    auto start = std::chrono::high_resolution_clock::now();

    unsigned exp = 18;
    unsigned long long n = intPow(10,exp);
    unsigned long long p = 1'000'000'009;

    std::pair<unsigned long long, unsigned long long> LF = LucasFibonacci(n,p); //(L_n,F_n) mod p
    unsigned long long L = LF.first; //L_n mod p
    unsigned long long F = ((p + 1) / 2 * (p + L - LF.second)) % p; //F_{n-1} mod p

    unsigned long long power2 = intPowMod(2, n, p);

    unsigned long long a = power2 * F;
    (n % 2) ? a += 1 : a -= 1;
    a %= p;

    unsigned long long b = power2*power2 + p - (power2 * L) % p;
    (n % 2) ? b -= 1 : b += 1;
    b %= p;

    unsigned long long q = (intPowMod(b, p - 2, p)*a) % p;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> elapsed = end - start;
    std::cout << "Q(P(10^" << exp << ")," << p <<")=" << q << "." << std::endl;
    std::cout << "Computation took " << elapsed.count() << " microseconds." << std::endl;
}