#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

long long GCD(long long x, long long y) {
  while (true) {
    if (x == 0) return y; else y %= x;
    if (y == 0) return x; else x %= y;
  }
}

typedef vector<long long> Vector;

const long long kMin = 1;
const long long kMax = 1000000;

int main() {
  vector<Vector> triples(kMax);
  for (long long f = kMin; f < kMax; ++f) for (long long n = kMin; f * n * n < kMax; ++n) for (long long m = kMin; m < n; ++m) if (m % 2 == 0 || n % 2 == 0) if (GCD(m, n) == 1) {
    long long x = f * (n * n - m * m);
    long long y = f * (2 * m * n);
    long long z = f * (n * n + m * m);
    if (x < kMax && y < kMax && z < kMax) {
      // cout << x << ' ' << y << ' ' << z << endl;
      triples[x].push_back(y);
      triples[y].push_back(x);
    }
  }
  long long c = 0;
  for (long long w = kMin; w < kMax; ++w) {
    Vector v = triples[w];
    for (int i = 0; i < v.size(); ++i) for (int j = i + 1; j < v.size(); ++j) if ((v[i] * v[j]) % (v[i] + v[j]) == 0) {
      // cout << w << ' ' << v[i] << ' ' << v[j] << endl;
      ++c;
    }
  }
  cout << c << endl;
  return 0;
}