#include <iostream>
#include <vector>
#include <math.h>

int main (int argc, const char * argv[])
{
    const unsigned long long L = 500000000000LL;
    long double sqrt3 = sqrtl(3);
    long double R = L / sqrt3;

    unsigned long long i, j = 0;
    const unsigned long long maxprime = R / (7*7*13*13);
    char *sieve = new(std::nothrow) char[maxprime + 1];
    
    if (!sieve) {
        std::cout << "Memory allocation error!" << std::endl;
        return 1;
    }
    
    memset((sieve + 2), 1, maxprime*sizeof(char));
    
    for (i = 2; i*i < maxprime; ++i)
        if (sieve[i]) {
            for (j = i*i; j <= maxprime; j += i)
                sieve[j] = 0;
        }
    
    std::vector<unsigned long long> primes_1;
    std::vector<unsigned long long> primes_2;

    unsigned long long primescount = 0;
    for (i = 2; i < maxprime; ++i)
        if (sieve[i]) {
            ++primescount;
            if (i % 3 == 1) {
                primes_1.push_back(i);
            } else if (i % 3 == 2) {
                primes_2.push_back(i);
            }
        }
    
    char *onlysecond = new(std::nothrow) char[maxprime + 1];
    
    if (!onlysecond) {
        std::cout << "Memory allocation error!" << std::endl;
        return 1;
    }
    
    long long maxfree = R / (19*13*13*7*7) + 1;    
    memset(onlysecond, 1, (maxfree + 1)*sizeof(char));

    for (i = 1; i < maxfree; ++i) {
        if (i % 3 == 0) {
            onlysecond[i] = 0;
            continue;
        }
        
        if (sieve[i]) {
            if (i % 3 == 1)
                onlysecond[i] = 0;
            continue;
        }
        
        unsigned long long y = i;
        while (y % 2 == 0) {
            y /= 2;
        }
        
        while (y % 3 == 0) {
            y /= 3;
        }
        
        while (y % 5 == 0) {
            y /= 5;
        }

        while (y % 11 == 0) {
            y /= 11;
        }
        
        for (j = 0; j < primes_1.size(); ++j) {
            unsigned long long p = primes_1[j];
            
            if (y < p)
                break;
            
            if (y % p == 0) {
                onlysecond[i] = 0;
                break;
            }
        }
    }
    
    long long count = 0;
    
    for (size_t i = 0; i < primes_1.size(); ++i) {
        long double p = primes_1[i];
        if (p > R / powl(7, 12))
            break;
        
        long double a = p;
        for (size_t j = 0; j < primes_1.size(); ++j) {
            
            if (j == i)
                continue;
            
            long double q = primes_1[j];
            if (q > powl(R/a, 1.0/12.0))
                break;
            
            long double b = powl(q, 12);
            long double r = a*b;
            
            unsigned long long g = 1;
            long double w = R / r;
                        
            while (g <= w) {
                if (onlysecond[g]) {
                    long double alpha = 1;
                    while (alpha*g <= w) {
                        alpha *= sqrt3;
                        count++;
                    }
                }
                ++g;
            }
        }
    }
        
    for (size_t i = 0; i < primes_1.size(); ++i) {
        long double p = primes_1[i];
        if (p > sqrtl(R / powl(7, 7)))
            break;
        
        long double a = p*p;
        for (size_t j = 0; j < primes_1.size(); ++j) {
            
            if (j == i)
                continue;
            
            long double q = primes_1[j];
            if (q > powl(R/a, 1.0/7.0))
                break;
            
            long double b = powl(q, 7);
            long double r = a*b;
            
            unsigned long long g = 1;
            long double w = R / r;
                        
            while (g <= w) {
                if (onlysecond[g]) {
                    long double alpha = 1;
                    while (alpha*g <= w) {
                        alpha *= sqrt3;
                        count++;
                    }
                }
                ++g;
            }
        }
    }
        
    for (size_t i = 0; i < primes_1.size(); ++i) {
        long double p = primes_1[i];
        long double a = p;
                
        for (size_t j = 0; j < primes_1.size(); ++j) {
            
            if (j == i)
                continue;
            
            long double q = primes_1[j];
            
            if (q > sqrtl(R/a))
                break;
            
            long double b = q*q;
            
            for (size_t k = j + 1; k < primes_1.size(); ++k) {
                if (k == i)
                    continue;
            
                long double s = primes_1[k];
                
                if (s > sqrtl(R/(a*b)))
                    break;
                
                long double c = s*s;
                long double r = a*b*c;
                            
                unsigned long long g = 1;
                long double w = R / r;
                                
                while (g <= w) {
                    if (onlysecond[g]) {
                        long double alpha = 1;
                        while (alpha*g <= w) {                            
                            alpha *= sqrt3;
                            count++;
                        }
                    }
                    ++g;
                }       
            }
        }
    }

    std::cout << count << std::endl;

    return 0;
}