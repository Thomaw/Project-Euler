#include <iostream>
#include <vector>

using namespace std;

long powerMod( long base, long exp, long modulus)
{
  base = base % modulus;
  assert( exp >= 0);

  if( exp == 0)
    return 1;
  if( exp % 2)
    return (base * powerMod( base, exp - 1, modulus)) % modulus;
  long sq_root = powerMod( base, exp / 2, modulus);
  return (sq_root * sq_root) % modulus;
}



int main()
{
  const long modulus = 100000;
  const long max_val = 1000000000000;

  // generate factor list (no mults. of 2 or 5)
  vector<long> factors;
  for( int i = 1; i <= modulus; ++i)
    if( (i % 2) && (i % 5))
      factors.push_back( i);
  long num_factors = factors.size();

  // running products of all factors
  vector<long> products;
  long last_value = 1;
  for( vector<long>::iterator it = factors.begin(); it != factors.end(); ++it)
  {
    last_value = (last_value * *it) % modulus;
    products.push_back( last_value);
  }

  long result = 1;  // storage for result

  // contribution due to each 2^i 5^j set of multiples
  for( long power2 = 1; power2 <= max_val; power2 *= 2)
    for( long power5 = 1; power2 * power5 <= max_val; power5 *= 5)
    {
      long factor = power2 * power5;
      long count = max_val / factor + max_val / (10 * factor)
	- max_val / (2 * factor) - max_val / (5 * factor);
      long q = count / num_factors;
      long r = count % num_factors;

      // this may be null op by some Euler theorem...
      result = (result * powerMod( products.back(), q, modulus)) % modulus;
      if( r > 0)
	result = (result * products[ r - 1]) % modulus;
    }

  // how many factors of 5?
  long fives = 0;
  for( long size = max_val / 5; size >= 1; size /= 5)
    fives += size;

  // how many factors of 2?
  long twos = 0;
  for( long size = max_val / 2; size >= 1; size /= 2)
    twos += size;

  long excess_two_mult_factor = powerMod( 2, twos - fives, modulus);
  result = (result * excess_two_mult_factor) % modulus;

  cout << "result = " << result << endl;
}