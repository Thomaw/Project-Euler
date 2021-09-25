const int maxp = 100000;
#include <pe>

vector<int64> edges;

void dfs(int last, int64 limit, int64 value)
{
  edges.pb(value);
  for (int i = 0; i < last; ++i)
  {
    const int64 p = plist[i];
    if (value > limit / p) break;
    for (int64 t = value; t <= limit / p;)
    {
      t *= p;
      dfs(i, limit, t);
    }
  }
}

int main()
{
  init_primes();
  dfs(9, 100000000, 1);
  sort(all(edges));
  const int n = sz(edges);
  map<int64, int> mem;
  for (int i = 0, j = 0; j < n; ++j)
  {
    while (edges[i] * 11 < 10 * edges[j]) ++i;
    for (int k = i; k <= j; ++k) mem[edges[k]*edges[j]]++;
  }
  int64 result = 0;
  for (int n = 2; n <= 100; ++n)
  {
    int64 ans = 0;
    for (auto& iter: mem) if (iter.second == n)
    {
      ans = iter.first;
      break;
    }
    result += ans;
  }
  dbg(result);
  return 0;
}