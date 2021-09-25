#include <set>
#include <iostream>
using namespace std;

int main() {
  set<int> Fibs;
  for (int a=1, b=2, c=0; a <= 14142; c=a+b, a=b, b=c)
    Fibs.insert(a);

  set< pair<int, int> > moves;
  for (int m = 1; m*m <= 14142; ++m)
    for (int n = 0; n < m; ++n)
      for (int k = 1; k <= (14142 / (m*m + n*n)); ++k) {
        int A = 2*k*m*n, B = k*(m*m-n*n), C = k*(m*m + n*n);
        if (A <= 10000 && B <= 10000 && Fibs.find(C) != Fibs.end()) {
          moves.insert(pair<int, int>(A, B));
          moves.insert(pair<int, int>(B, A));
        }
      }

  auto A = new unsigned long long[16384][16834];
  for (int i = 0; i <= 10000; ++i) {
    for (int j = 0; j <= 10000; ++j) {
      A[i][j] = (i || j) ? 0 : 1;
      for (auto move : moves)
        if (i - move.first >= 0 && j - move.second >= 0)
          A[i][j] += A[i - move.first][j - move.second];
      A[i][j] %= 1000000007ULL;
    }
  }

  cout << "A[3][4]=" << A[3][4] << endl;
  cout << "A[10][10]=" << A[10][10] << endl;
  cout << "A[10000][10000]=" << A[10000][10000] << endl;
}