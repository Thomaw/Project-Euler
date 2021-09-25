#include <pe.hpp>

int main() {
  const long double C = log(2) / log(10);
  const int diff[]{196, 289, 485};
  int k = 12710;
  for (int id = 45; id < 678910; ++id) {
    for (int d : diff) {
      const long double now = C * (k + d);
      if ((int)pow(10, now - int64(now) + 2) == 123) {
        k += d;
        break;
      }
    }
  }
  dbg(k);
  return 0;
}