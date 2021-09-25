#include<cstdio>

const int MAX_N = 1e6;

char grundy[MAX_N+1];

int main() {
  int s = 0;
  for(int n = 2; n <= MAX_N; ++n)
    {
      int accessible = 0;
      for(int k = 0; 2*k <= n-2; ++k)
        accessible |= 1 << (grundy[k] ^ grundy[n-k-2]);
      grundy[n] = __builtin_ctz(~accessible);
      s += grundy[n] > 0;
    }
  printf("%d\n", s);
}