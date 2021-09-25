long int euler543() {

    long int F[45] = {0, 1};
    for (int i = 2; i <= 44; i++) {F[i] = F[i - 2] + F[i - 1]; }

    long int sum = 2; // Seed with value for 3rd Fibonacci number
    for (int i = 4; i <= 44; i++){
        sum += primesieve::parallel_count_primes(1, F[i]) +                         // k=1
            F[i] / 2 - 2 + primesieve::parallel_count_primes(1, F[i] - 2) +         // k=2
            (F[i] / 2 - 2) * (F[i] + 1) - 2 * (F[i] / 2 * (F[i] / 2 + 1) / 2 - 3);  // k>2
    }
        
    return sum;

}