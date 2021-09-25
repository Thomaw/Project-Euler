#define LIMIT 100000000000ULL
#define PRIME_LIMIT 22000000

typedef unsigned long long int int_64;

int_64 p245(void) {
    int i = 0;
    int p;
    int sqrt_limit = (int)sqrt(LIMIT);
    int_64 result = 0;
    
    primes = sieve(PRIME_LIMIT);

    for ( i = 0; (p = primes[i]) < sqrt_limit ; i++) {
        result += search(p, p-1, i+1, p-1);
    }
    
    return result;
}

int_64 search(int_64 n, int_64 phi, int i, int_64 m) {
    int_64 m1, r;
    int_64 n1, phi1;
    int_64 result;
    int p, q;
    
    result = 0;
    
    // check the numbers at this level, (and go deeper as required)
    while (1) {
        p = primes[i++];
        
        n1 = n*p;
        
        if ( n1 > LIMIT ) {
            break;
        }
        
        phi1 = phi*(p-1);
        
        r = (n1-1) % (n1-phi1);
        
        if ( r == 0 ) {
            result += n1;
        }

        m1 = (n1-1) / (n1-phi1);
        
        if ( m1 >= m ) {
            i--;
            break;
        }

        result += search(n1, phi1, i, m1);
    }
    
    // check if we need to go a level deeper, although this level is exhuasted
    while (1) {
        p = primes[i++];
        q = primes[i];
        
        n1 = n*p*q;
        
        if ( n1 > LIMIT ) {
            break;
        }
        
        phi1 = phi*(p-1)*(q-1);
        m1 = (n1-1)/ (n1-phi1);
        
        if (m1 >= m) {
            break;
        }
        
        n1 = n*p;
        phi1 = phi*(p-1);
        result += search(n1, phi1, i, (n1-1)/(n1-phi1));
    }
    
    return result;
}