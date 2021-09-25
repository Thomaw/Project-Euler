#include <cmath>
#include <iostream>

using namespace std;

bool IsSquare(const int q) {
  for (int r = 1; r * r <= q; ++r) if (r * r == q) return true;
  return false;
}

int main() {
  long long ret = 0;
  for (int q = 1; q <= 2011; ++q) for (int p = 1; p < q && p + q <= 2011; ++p) if (!IsSquare(p) || !IsSquare(q)) {
    bool bad = false;
    for (int i = 1; (p + q - i * i) * (p + q - i * i) >= 4 * p * q; ++i) if ((p + q - i * i) * (p + q - i * i) == 4 * p * q) {
      bad = true;
      break;
    }
    if (!bad) {
      const long double x = sqrt(q) - sqrt(p);
      if (x < 1) {
        const long double log_x = log(x) / log(10);
        const int n = ceil(-2011/ (2 * log_x));
        ret += n;
      }
    }
  }
  cout << ret << endl;
}