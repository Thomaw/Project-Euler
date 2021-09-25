#include <cstdio>
#include <set>
#include <cmath>
#include <vector>
#include <cassert>
//1805315691966540?

int const cutoff = 200000;//1638400000;
int64_t const len = 1000000/*cutoff+2*/; //(int64_t)cutoff*cutoff+2;

int primeFac[len];
int primes[len/10];
int numPrimes;

std::vector<int64_t> factors(int64_t v, int64_t q)
{
    if(v == 1)
        return std::vector<int64_t>(1, 1);

    //int p = primeFac[v];
    int64_t p = v;
    for(int index = 0; primes[index] < q && index < numPrimes; ++index)
        if(v%primes[index] == 0)
    {
        p = primes[index];
        break;
    }
    int count = 0;
    //std::printf("* %ld %ld  %ld\n", v, p, q);
    //assert(v < len);
    //while(p == primeFac[v])
    while(v%p == 0)
    {
        ++count;
        v /= p;
        //std::printf("  %d %d\n", v, p);
    }
    std::vector<int64_t> ret = factors(v, std::min(2+(int64_t)sqrt(v), q));
    int siz = ret.size();
    for(int c = 0; c < count; ++c)
        for(int s = 0; s < siz; ++s)
            ret.push_back(ret[s+c*siz]*p);
    //std::printf("/ %ld %ld  %ld\n", v, p, q);
    return ret;
}

int main()
{
    for(int i = 0; i < len; ++i)
        primeFac[i] = i;
    for(int i = 2; i < len; ++i)
        if(primeFac[i] == i)
            for(int j = i; j < len; j += i)
                primeFac[j] = i;

    numPrimes = 0;
    for(int i = 2; i < len; ++i)
        if(primeFac[i] == i)
            primes[numPrimes++] = i;

    std::vector<int64_t> test = factors(120, 120);
    for(std::vector<int64_t>::iterator i = test.begin(); i != test.end(); ++i)
        std::printf("%ld ", *i);
    std::printf("\n\n");

    std::set<uint64_t> A;

    // s = p+q
    for(int64_t q = 1; q <= cutoff; ++q)
    {
        int64_t zeroModS = q*q+1;
        std::vector<int64_t> S = factors(zeroModS, q);//std::min(q, 2000000000000000/(q*q)));
        if(q == 100000000)
        {
            std::printf("q = %ld\nS.size() = %zu\n", q, S.size());
            for(std::vector<int64_t>::iterator i = S.begin(); i != S.end(); ++i)
                std::printf("    %lu\n", *i);
        }
        //for(int sign = -1; sign <= 1; sign += 2)
        int sign = -1;
        for(std::vector<int64_t>::iterator i = S.begin(); i != S.end(); ++i)
        {
            int64_t s = sign * *i;
            int64_t p = s-q;
            int64_t r = zeroModS/s-q; //-(p*q-1)/(p+q);
            int64_t __attribute__((mode(TI))) a = p*q; a *= r;
            if(a > 1 && a < 2000000000000000 && p < 2000000000000000/*(1LL<<62)*/)
                A.insert(a);
        }
    }

    unsigned n = 0;
    for(std::set<uint64_t>::iterator i = A.begin(); i != A.end(); ++i)
    {
        ++n;
        std::printf("%lu\n", *i);
        if(n == 150000)
        {
            std::printf("Done\n");
            break;
        }
    }
    std::printf("set size = %zu\n", A.size());
}

/*
int main()
{
    int cutoff = 1000000000;
    std::set<uint64_t> a;
    for(int p = 1; p < cutoff; ++p)
    {
        int range = std::min(cutoff/p, p);
        for(int q = -range; q <= range; ++q)
            if(q != 0 && p+q != 0)
        {
            if(((int64_t)p*q-1) % (p+q) == 0)
            {
                int r = -(p*q-1)/(p+q);
                if(r < cutoff)
                    a.insert(std::max((int64_t)p*q*r, -(int64_t)p*q*r));
            }
        }
    }
    a.erase(0);
    unsigned n = 0;
    for(std::set<uint64_t>::iterator i = a.begin(); i != a.end(); ++i)
    {
        ++n;
        std::printf("%lu\n", *i);
        if(n == 150000)
        {
            std::printf("Done\n");
            break;
        }
    }
    std::printf("set size = %zu\n", a.size());
}
*/