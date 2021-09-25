const int maxp = 100000;
#include <pe>

SL void rotate1(string& x)
{
  int y = x[6];
  x[6] = x[4];
  x[4] = x[5];
  x[5] = x[7];
  x[7] = y;
  int y1 = x[8], y2 = x[9];
  x[8] = x[13];
  x[13] = x[3];
  x[3] = x[18];
  x[18] = y1;
  x[9] = x[15];
  x[15] = x[2];
  x[2] = x[16];
  x[16] = y2;
}
SL void rotate2(string& x)
{
  int y = x[15];
  x[15] = x[13];
  x[13] = x[12];
  x[12] = x[14];
  x[14] = y;
  int y1 = x[4], y2 = x[6];
  x[4] = x[0];
  x[0] = x[23];
  x[23] = x[8];
  x[8] = y1;
  x[6] = x[2];
  x[2] = x[21];
  x[21] = x[10];
  x[10] = y2;
}
int g1[24] = {
  23,22,21,20,0,1,2,3,4,5,6,7,
  14,12,15,13,17,19,16,18,11,10,9,8
};
SL void f1(string& x)
{
  auto y = x;
  for (int i = 0; i < 24; ++i)
    x[i] = y[g1[i]];
}
int g2[24] = {
  2,0,3,1,16,17,18,19,9,11,8,10,
  4,5,6,7,20,21,22,23,12,13,14,15
};
SL void f2(string& x)
{
  auto y = x;
  for (int i = 0; i < 24; ++i)
    x[i] = y[g2[i]];
}

SL vector<string> trans(string in)
{
  vector<string> res;
  {
    auto t = in;
    rotate1(t);
    res.pb(t);
  }
  {
    auto t = in;
    rotate2(t);
    res.pb(t);
  }
  {
    auto t = in;
    f1(t);
    res.pb(t);
  }
  {
    auto t = in;
    f2(t);
    res.pb(t);
  }
  return res;
}

unordered_map<string, int> mem;
int visited;
void bfs(const string& t)
{
  queue<string> q;
  q.push(t);
  mem[t] = 1;
  visited = 1;
  while (!q.empty())
  {
    auto now = q.front(); q.pop();
    for (auto& t: trans(now))
    {
      if (mem.count(t) == 0)
      {
        mem[t] = 1;
        if (++visited % 1000000 == 0) dbg(visited);
        q.push(t);
      }
    }
  }
}
int main()
{
  init_primes();

  string t;
  for (int i = 0; i < 24; ++i)
  t.pb(char(i));
  dbg(sz(t));
  bfs(t);
  dbg(sz(mem));
  int128 ans = 0;
  const int color = 10;
  int128 pw[30] = {0};
  pw[0] = 1;
  for (int i = 1; i < 30; ++i)
    pw[i] = pw[i-1] * color;
  for (auto& iter: mem)
  {
    int visited[24] = {0};
    auto& x = iter.first;
    int cnt = 0;
    for (int i = 0; i < 24; ++i)
      if (visited[i] == 0)
      {
        visited[i] = 1;
        for (int y = x[i]; y != i; y = x[y])
        {
          visited[y] = 1;
        }
        ++cnt;
      }
    ans += pw[cnt];
  }
  cout << ans << endl;
  cout << ans / sz(mem) << endl;
  return 0;
}
