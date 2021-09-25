#include <pe_base>
const int N = 100000000;
const int K = 100000;
int dv[N+1];
int que[N+1];
int main()
{
  for (int i = 1; i <= N; ++i)
  {
    for (int j = i; j <= N; j += i)
    ++dv[j];
  }
  int64 s = 0;
  int p = 0, q = 0;
  for (int i = 1, j = 1; i <= N - K + 1; ++i)
  {
    const int r = i + K - 1;
    while (p < q && que[p] < i) ++p;
    while (j <= r)
    {
      while (p < q && dv[j] > dv[que[q-1]]) --q;
      que[q++] = j++;
    }
    s += dv[que[p]];
  }
  cerr << s << endl;
  return 0;
}