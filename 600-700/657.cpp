// 657.cpp
/*
 * Incomplete Words I.
 *
 * How many incomplete words of length <= n are there from an alphabet of a
 * letters?
 *
 * Let C(a, n) be the number of complete words of length n. Find that
 *
 *     C(a, n) = a*C(a, n - 1) + a*C(a - 1, n - 1),
 *
 * since there are `a' possibilities for the leading letter, and the `tail' is
 * either itself complete on `a' letters or else it must be complete on the
 * remaining a - 1 letters. Look at the o.g.f. for this and find the recursion
 *
 *     c_a(x) = (a*x/(1 - a*x)) * c_{a - 1}(x)
 *
 *  => c_a(x) = (a! x^a)/((1 - x)(1 - 2*x)(1 - 3*x) ... (1 - a*x)).
 *
 * This can be split by partial fractions and by induction, using e.g.
 *
 *     c_a(x) = -c_{a-1}(x) + c_{a-1}(x)/(1 - a*x),
 *
 * the partial fraction decomposition of each ((1 - a*x)(1 - b*x)), and proof
 * by induction, with the result
 *
 *     c_a(x) = Sum_{b = 0 to a} (-1)^(a + b) (a choose b)/(1 - b*x).
 *
 * Since there are a^n words of length n find that the generating function for
 * incomplete words of length n is
 *
 *     i_a(x) = 1/(1 - a*x) - c_a(x) = Sum_{b = 0 to a - 1} nu(b)/(1 - b*x).
 *
 * where
 *
 *     nu(b) = (-1)^{a + b + 1} (a Choose b).
 *
 * Thus the generating function for I(a, n) is simply i_a(x)/(1 - x). The
 * coefficients of 1/((1 - x)(1 - b*x)) are straightforward to calculate (they
 * are simply sums of powers), and nu(b) can also be calculated from nu(b-1).
 *
 * So simply doing the sum is roughly O(n). NB: the below assumes a is not near
 * to p in size (so can be a little blase about underflow).
 */

#include <iostream>
#include <primes.h>

using namespace std;
using ProjectEuler::powMod32;
using ProjectEuler::mod_inverse;

/*
 * Obtain the n'th coefficient of 1/((1 - x)(1 - b * x)), modulo p.
 */
inline uint64_t sumPowers(uint64_t b, uint64_t n, uint64_t p) {
    if (b == 0)
        return 1;
    if (b == 1)
        return (n + 1) % p;
    uint64_t res = powMod32(b, n + 1, p) - 1;
    return (res * mod_inverse(b - 1, p)) % p;
}

int main () {
    uint64_t const a = 10000000, n = 1000000000000ULL, p = 1000000007;

    /*
     * Within the loop, nu (or nu(b)) represents the coefficient
     *
     *     (-1)^(a + b + 1) (a choose b).
     */
    uint64_t sum = 0, nu = (a % 2 == 0) ? (p - 1) : (1);

    for (uint64_t b = 0; b < a; b++) {
        sum += (nu * sumPowers(b, n, p)) % p;
        if (sum >= p)
            sum -= p;

        /*
         * Update nu for the next value of b using the recursion:
         *
         *     nu(b + 1) = -(a - b)*nu(b)/(b + 1).
         */
        nu = (nu * mod_inverse(b + 1, p)) % p;
        nu = (nu * (a - b)) % p;
        nu = p - nu;
    }

    cout << sum << endl;
    return 0;
}
