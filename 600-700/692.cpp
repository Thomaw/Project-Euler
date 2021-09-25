#include <cmath>
#include <iostream>
using ull = unsigned long long;
ull fibs[90];
long double phi = (1.0+sqrt(5.0))/2.0;
void calc_fibs() {
  fibs[0] = 0;
  fibs[1] = 1;
  for (int i = 2; i < 90; ++i) {
    fibs[i] = fibs[i - 1] + fibs[i - 2];
  }
}
ull search(int i, ull n) {
  auto elem = [&](ull c){ return (c - 1)*fibs[i+1] + fibs[i+2]*floor(c*phi); };
  auto prop = [&](ull c) { return elem(c) < n; };
  ull c = 1;
  if (!prop(c)) return 0;
  while (prop(c)) c <<= 1;
  ull low = c >> 1;
  ull high = c;
  // We know the true answer is in [low, high). We know prop(low), and !prop(high).
  while (high - low > 1) {
    ull mid = low + (high - low) / 2;
    if (prop(mid)) low = mid;
    else high = mid;
  }
  return low;
}
ull g(ull n) {
  ull su = 0;
  ++n;
  ull fib;
  for (int i = 0; (fib = fibs[i+2]) <= n; ++i) {
    su += search(i, n) * fib;
  }
  return su;
}
int main() {
  calc_fibs();
  std::cout << "G(23416728348467685) = " << g(23416728348467685ull) << std::endl;
}
