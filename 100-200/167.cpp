#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main(void) {
  const long long i = 100000000000LL;
  long long total = 0;
  for(int n = 2; n <= 10; n++) {
    cout << endl << n << ":" << endl;

    int x = 0, y = 0;
    map<int, int> m;
    map<int, int>::iterator mit;
    vector<int> U; U.push_back(2*n + 1);

    do {
      m[U.back() + 2]++;
      if (x != 0) {
        m[U.back() + x]++;
      } else {
        for(int j = 0; j < U.size() - 1; j++)
          m[U.back() + U[j]]++;
      }

      if ((U.back() & 1) == 0) {
        x = U.back(); y = U.size() - 1;
        cout << "  x = " << x << endl;
        for(mit = m.begin(); mit != m.end(); mit++) {
          if ((mit->first & 1) == 0) mit->second++;
        }
      }

      mit = m.begin();
      while (mit->second > 1) mit++;
      U.push_back(mit->first);
      m.erase(m.begin(), ++mit);

    } while (U.back() - U[U.size() - 2] != x);

    int period = U.size() - 2, diff = U.back() - *U.begin();
    cout << "  period " << period << ", difference " << diff << endl;

    int s = (i - 3) % period;
    if (s >= y) s++;
    long long u = ((i - 3) / period) * diff + U[s];
    cout << "  U(2, " << U[0] << ")_" << i <<
      " = U(2, " << U[0] << ")_" << s + 2 << " + " <<
      diff << " * " << (i - 3) / period << " = " << u << endl;

    total += u;
  }

  cout << endl << "TOTAL: " << total << endl;
  return 0;
}