#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include <gmpxx.h>

using namespace std;

template<typename T>
T mod_power(T value, T power, T mod);

template<typename T>
T power(T value, int power);

template<typename T>
T combinations(T n, T k);

void simplify(pair<mpz_class, mpz_class>& v);

constexpr int mod = 1000000007;

class FaulhabersFormula {
    struct Cache {
        static constexpr int64_t CACHE_LIMIT = 100000;
        vector<int> cache;
    public:
        Cache() : cache(CACHE_LIMIT, -1)
        {
        }

        void clear() {
            cache.assign(CACHE_LIMIT, -1);
        }

        int get_value(int64_t n) const {
            if (n < CACHE_LIMIT) {
                return cache[n];
            } else {
                return -1;
            }
        }
        void put_value(int64_t n, int64_t value) {
            if (n < CACHE_LIMIT) {
                cache[n] = value;
            }
        }
    };

    using fraction_t = pair<int64_t, int64_t>; // first - numerator, second - denominator
    vector<fraction_t> bernoulli_numbers;
    vector<int64_t> inverse_denoms_product;
    vector<int64_t> inverse_powers;
    vector<int64_t> combinations_cache;
    vector<int64_t> multiplicator_cache;
    static constexpr int MAX_P = 64;

    Cache cache;

    void calculate_bernoulli_numbers();
public:

    FaulhabersFormula()
    {
        calculate_bernoulli_numbers();
    }

    void clear_cache() {
        cache.clear();
    }

    int64_t sum(uint64_t n, int p);
};

void FaulhabersFormula::calculate_bernoulli_numbers() {
    bernoulli_numbers.clear();
    bernoulli_numbers.push_back(fraction_t{1, 1});

    mpz_class f = 1;
    vector<pair<mpz_class, mpz_class>> c(MAX_P + 1);
    c[0].first = 1;
    for (auto& v: c) {
        v.second = 1;
    }

    for (int n = 1; n <= MAX_P; ++n) {
        f *= n;
        for (int k = n; k > 0; --k) {
            c[k].first = c[k - 1].first;
            c[k].second = c[k - 1].second * (k + 1);
            simplify(c[k]);
        }

        mpz_class denom_prod = accumulate(c.begin() + 1, c.begin() + n + 1, mpz_class(1),
            [](mpz_class prod, typename decltype(c)::value_type b) { return prod * b.second; });
        c[0].first = 0;
        c[0].second = denom_prod;
        for (int i = 1; i <= n; ++i) {
            c[0].first -= c[i].first * (denom_prod / c[i].second);
        }
        simplify(c[0]);

        auto res = c[0];
        res.first *= f;
        simplify(res);
        res.first %= mod;
        if (res.first < 0) {
            res.first += mod;
        }
        if (res.second >= mod) {
            abort();
        }
        bernoulli_numbers.push_back(make_pair(res.first.get_si(), res.second.get_si()));
    }

    bernoulli_numbers[1].first = 1;

    vector<mpz_class> denoms_product(bernoulli_numbers.size());
    inverse_denoms_product.resize(bernoulli_numbers.size());
    mpz_class product = 1;
    for (int i = 0; i <= MAX_P; ++i) {
        product *= bernoulli_numbers[i].second;
        denoms_product[i] = product;
        inverse_denoms_product[i] = mod_power<mpz_class>(product, mod - 2, mod).get_si();
    }
    inverse_powers.resize(MAX_P + 2);
    for (int i = 1; i <= MAX_P + 1; ++i) {
        inverse_powers[i] = mod_power<mpz_class>(i, mod - 2, mod).get_si();
    }

    combinations_cache.resize((MAX_P + 2) * (MAX_P + 2));
    for (int n = 1; n <= MAX_P + 1; ++n) {
        for (int k = 0; k <= n; ++k) {
            mpz_class c = combinations<mpz_class>(n, k) % mod;
            combinations_cache[n * MAX_P + k] = c.get_si();
        }
    }

    multiplicator_cache.resize((MAX_P + 1) * (MAX_P + 1));
    for (int p = 1; p <= MAX_P; ++p) {
        for (int i = 0; i <= p; ++i) {
            mpz_class c = (denoms_product[p] / bernoulli_numbers[i].second) % mod;
            multiplicator_cache[p * MAX_P + i] = c.get_si();
        }
    }
};

// https://en.wikipedia.org/wiki/Faulhaber%27s_formula
int64_t FaulhabersFormula::sum(uint64_t n, int p) {
    int from_cache = cache.get_value(n);
    if (from_cache >= 0) {
        return from_cache;
    }

    int64_t sum = 0;
    for (int j = 0; j <= p; ++j) {
        int64_t numerator = (combinations_cache[(p + 1) * MAX_P + j] * bernoulli_numbers[j].first) % mod;
        numerator = (numerator * mod_power<int64_t>(n % mod, p + 1 - j, mod)) % mod;

        sum = (sum + numerator * multiplicator_cache[p * MAX_P + j]) % mod;
    }
    sum = (sum * inverse_denoms_product[p]) % mod;
    sum = (sum * inverse_powers[p + 1]) % mod;

    cache.put_value(n, sum);

    return sum;
}

FaulhabersFormula formula;
vector<int> primes;
vector<int64_t> prime_squares;

int64_t mod_sk(int64_t limit, int p, int64_t next_prime_index) {
    int64_t result = formula.sum(limit, p);

    for (int64_t j = next_prime_index; prime_squares[j] <= limit; ++j) {
        int64_t coefficient = mod_power<int64_t>(int64_t(primes[j]), p, mod);
        coefficient = (coefficient * (coefficient - 1)) % mod;

        int64_t new_limit = limit / prime_squares[j];
        int64_t v = (coefficient * mod_sk(new_limit, p, j + 1)) % mod;
        result = (result + mod - v) % mod;
        for (int64_t mul = prime_squares[j] * primes[j]; mul <= limit; mul *= primes[j]) {
            int64_t v = (coefficient * mod_sk(limit / mul, p, j + 1)) % mod;
            result = (result + mod - v) % mod;
        }
    }

    return result % mod;
}

int main() {
    constexpr int64_t limit = int64_t(1000000) * 1000000;

    constexpr int MAX_PRIME = 2000000;
    vector<bool> sieve(MAX_PRIME + 1);

    for (int i = 2; i * i <= MAX_PRIME; ++i) {
        if (!sieve[i]) {
            for (int j = i + i; j <= MAX_PRIME; j += i) {
                sieve[j] = true;
            }
        }
    }
    for (int i = 2; i <= MAX_PRIME; ++i) {
        if (!sieve[i]) {
            primes.push_back(i);
        }
    }

    prime_squares.resize(primes.size());
    for (size_t i = 0; i < primes.size(); ++i) {
        prime_squares[i] = int64_t(primes[i]) * primes[i];
        if (prime_squares[i] > limit) {
            primes.resize(i + 1);
            prime_squares.resize(i + 1);
            break;
        }
    }

    mpz_class answer = 0;
    for (int k = 1; k <= 50; ++k) {
        cout << k << endl;
        formula.clear_cache();
        answer += mod_sk(limit, k, 0);
    }

    cout << "Answer: " << answer % mod << endl;

    return 0;
}

void simplify(pair<mpz_class, mpz_class>& v) {
    if (v.first == 0) {
        v.second = 1;
    } else {
        mpz_class g = gcd(abs(v.first), abs(v.second));
        v.first /= g;
        v.second /= g;
    }
}


template<typename T>
T mod_power(T value, T power, T mod) {
    T result = 1;
    while (power > 0) {
        if (power % 2 == 1) {
            result = (result * value) % mod;
        }
        power /= 2;
        value = (value * value) % mod;
    }
    return result;
}

template<typename T>
T power(T value, int power) {
    T result = 1;
    while (power > 0) {
        if (power % 2 == 1) {
            result *= value;
        }
        power /= 2;
        value *= value;
    }
    return result;
}

template<typename T>
T combinations(T n, T k) {
    T result = 1;
    for (int i = 1; i <= k; ++i) {
        result *= (n - i + 1);
        result /= i;
    }

    return result;
}
