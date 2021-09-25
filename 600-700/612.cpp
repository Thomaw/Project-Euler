#include <stdint.h>
#include <iostream>

// factorial() and modpow() are left out to save space.

uint64_t P(unsigned n, unsigned k) {
    return k > n ? 0 : factorial(n) / factorial(n-k);
}

int main() {
    const uint64_t M = 1000267129;
    const uint64_t HALF = 500133565;
    const uint64_t NPOW = 18;
    const uint64_t N = modpow(10, NPOW, M);

    uint64_t T[NPOW+1][10] = {{0}};
    uint64_t U[NPOW+1][10] = {{0}};
    T[0][0] = 1;
    for (unsigned n = 1; n <= NPOW; ++n) {
        for (unsigned k = 1; k < 10; ++k) {
            T[n][k] = (k*T[n-1][k] + T[n-1][k-1]) % M;
            U[n][k-1] = (k-1)*T[n][k] % M;
        }
    }

    uint64_t enemies = 0;
    for (uint64_t n1 = 1; n1 <= NPOW; ++n1) {
        for (uint64_t n2 = 1; n2 <= NPOW; ++n2) {
            for (uint64_t k1 = 1; k1 <= 9; ++k1) {
                for (uint64_t k2 = 1; k2 <= 9; ++k2) {
                    uint64_t A = P(9, k1+k2);
                    enemies += T[n1][k1] * T[n2][k2] % M * A % M;
                    enemies += T[n1][k1] * U[n2][k2] % M * A % M;
                    enemies += U[n1][k1] * T[n2][k2] % M * A % M;
                    enemies %= M;
                }
            }
        }
    }

    uint64_t allpairs = (N-1+M) * (N-2+M) % M;
    std::cout << (allpairs - enemies + M) * HALF % M << '\n';
}
