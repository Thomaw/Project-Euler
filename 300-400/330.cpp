// 330.cpp
/* Given the defined sequences A(n), B(n) in the problem description, obtain
 * C(n) = A(n) + B(n) modulo 77777777 = 7*11*73*101*137 for n = 10^9.
 *
 * See writeup in E330 for explanation of what follows. The idea is simply to
 * calculate C(n) modulo p (which has period p(p-1)) for each prime, then use
 * the Chinese Remainder Theorem.
 */

#include <iostream>
#include <functional>
#include <primes.h>

using namespace std;
using ProjectEuler::powMod32;
using ProjectEuler::Congruence;
using ProjectEuler::ChineseRemainder;

/* Get the Nth ordered Bell number modulo p, for an odd prime p.
 * Simply use the explicit solution for this, which is given by
 *
 *          Sum{z = 1 -> (p-1)} 2^{-z}*z^N
 *
 * for N > 0, working modulo p: see writeup in E330 thread.
 */
uint64_t orderedBell(uint64_t N, uint64_t const & p) {
    if (N == 0)
        return 1;
    N %= (p - 1);

    uint64_t const i2 = (p + 1)/2;
    uint64_t i2pow = i2*i2, alpha = i2;

    for (uint64_t z = 2; z < p; z++, i2pow = (i2pow * i2) % p) {
        alpha += (i2pow * powMod32(z, N, p)) % p;
        if (alpha >= p)
            alpha -= p; 
    }
    return alpha;
}

/* Calculate C(N) modulo p. It is shown in E330 thread writeup that
 *
 *      C(N) = N*C(N - 1) - alpha(N),
 *
 * and working modulo p this recursion terminates at the first N == 0 mod p.
 * Here, alpha(N) is the N'th ordered Bell number, calculated above.
 */
Congruence CSeq(uint64_t N, uint64_t const & p) {
    N %= (p*(p - 1));
    function<uint64_t(uint64_t,uint64_t)> getCoeff = [&](uint64_t const & n,
                                                         uint64_t const & r) {
        if (n == 0)
            return uint64_t(0);
        uint64_t pre = 0;
        if (r != 0)
            pre = (r*getCoeff(n - 1, r - 1)) % p;
        return (pre + (p - orderedBell(n, p))) % p;
    };
    return Congruence(getCoeff(N, N % p), p);
}

int main () {
    uint64_t const N = 1000000000;
    vector<uint64_t> pFacts = {7, 11, 73, 101, 137};
    
    vector<Congruence> congs;
    for (auto p : pFacts)
        congs.push_back(CSeq(N, p));

    Congruence collect = congs.back();
    for (auto it = congs.begin(); next(it) != congs.end(); ++it)
        collect = ChineseRemainder(collect, *it);

    cout << collect.r << endl;
    return 0;
}