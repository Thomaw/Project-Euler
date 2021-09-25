#include <stdio.h>

int main()
{
  __int128 z = 0; long j = 1, n = (long)1e16;
  for (int i = 1; j <= n; j += ++i) {
    long a = n - j + 1, b = a / i; __int128 c = b + 1;
    z += b * c / 2 * i + a % i * c;
  }
  printf("S(%ld) = %ld\n", n, (long)(z % 1000000007));
}