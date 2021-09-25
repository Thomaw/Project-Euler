const int maxp = 100000;
#include <pe>

unordered_map<int64, int> mem;
void dfs(int64 curr, int64 m, int64 value)
{
  if (curr == 4)
  {
    ++mem[value];
  }
  else
  {
    int64 sm = m;
    for (;;)
    {
      dfs(curr+1, m - sm, value + (4 - curr) * sm);
      if (sm == 0)
      {
        break;
      }
      sm = sm - 1 & m;
    }
  }
}

int main()
{
  for (int k = 1; k <= 7; ++k)
  {
    dbg(k);
    mem.clear();
    int64 dest = 1;
    for (int i = 0; i < k; ++i) dest *= 10;
    dfs(0, dest, 0);
    int64 total = 0;
    for (auto& iter: mem) if (iter.second % 2) ++total;
    dbg(total);
  }
  return 0;
}
