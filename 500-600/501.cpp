// How many numbers <= n have a prime divisor <= *p, where p is a pointer into an array or primes 
// in increasing order, and pi_c[] is an array of pre-calculated values of pi(x), where x < size
// and size is about n ** (2/3)
long long do_cnt(long long n, int *p, int *pi_c, int size)
{
  long long r;

  // trivial case 1: All numbers <= p have a divisor <= p
  if (n <= *p)
    return n;
  
  // trivial case 2: All numbers <= p ** 2 have a divisor <= p except for primes in range (p, p ** 2)
  if (n < size && n <= (long long)*p * *p)
    return n - pi_c[n] + pi_c[*p];

  // Now it's just inclusion-exclusion
  for(r = 0; *p != 2; p--)
    r += n / *p - do_cnt(n / *p, p - 1, pi_c, size) + 1;
  
  return r + n / 2 + 1;
}

// Count primes <= n, where primes[] is an array of primes <= sqrt(n), pi_c[] and 
// size are described above
long long pi(long long n, int *primes, int *pi_c, int size)
{
  long long s;
  
  if (n < size)
    return pi_c[n];
  
  s = sqrt(n) + 1;
  
  // Count numbers less than n divisble by a prime <= s, these are all composite except
  // for those primes <= s
  return n + pi_c[s] - do_cnt(n, primes + pi_c[s] - 1, pi_c, size);
}