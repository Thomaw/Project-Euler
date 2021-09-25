#include <iostream>
#include <cmath>

#define L 1000000000000000000ULL
#define L3 1000000

using ull = unsigned long long;
ull factor[L3+1];
ull facs[8];
int fac3(int n) {
  if (n == 1) return 0;
  int facidx = -1;
  while (n > 1) {
    ull p = factor[n];
    if (p == 0) p = n;
    while (n % p == 0) n /= p;
    if (facidx == -1) {
      facidx = 0;
      facs[facidx] = p;
    } else if (p != facs[facidx]) {
      ++facidx;
      facs[facidx] = p;
    }
  }
  return facidx + 1;
}
ull rec(ull N, int idx) {
   if (idx == -1) return L / N;
   ull a = rec(N, idx - 1);
   __int128 NN = N;
   for (int i = 1; i <= 2; ++i) {
     NN *= facs[idx];
     if (NN > L) break;
     a += rec(NN, idx - 1);
   }
   return a;
}
int main() {
  for (int i = 2; i * i <= L3; ++i) {
    if (factor[i] != 0) continue;
    for (int j = i*i; j <= L3; j += i) factor[j] = i;
  }
  ull sum = 0;
  ull n = 1;
  while (true) {
    ull N = n*n*n;
    if (N > L) break;
    int nfacs = fac3(n);
    sum += rec(N, nfacs - 1);
    ++n;
  }
  std::cout << sum << std::endl;
}
