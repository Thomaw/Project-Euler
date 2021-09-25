#include <pe.hpp>

const int64 mod = 1000000007;

map<int, int> state2id;

int nfa[100][5];
int state[100];

int nextId = 0;
SL int get_id(int s) {
  auto where = state2id.find(s);
  if (where != state2id.end()) {
    return where->second;
  }
  state[nextId] = s;
  return state2id[s] = nextId++;
}

SL int trans(int old, int add, int p) {
  int w = old % 2;
  old /= 2;
  int v = old % 3;
  old /= 3;
  int u = old % 3;
  if (w && p) return -1;
  if (p) {
    if (add < 2) return -1;
    add -= 2;
  }
  if (add < u + v) return -1;
  add -= u + v;
  if (add >= 3) add -= 3;
  return v * 6 + add * 2 + (p | w);
}

SL int nextstate(int s, int add) {
  int next = 0;
  for (int i = 0; i < 18; ++i) {
    if (bit_get(s, i) == 0) continue;
    for (int p = 0; p <= 1; ++p) {
      int n = trans(i, add, p);
      if (n != -1) next |= bit_set(next, n);
    }
  }
  return next;
}

SL void init() {
  int visited[512] = {0};
  queue<int> q;
  q.push(1);
  visited[get_id(1)] = 1;
  while (!q.empty()) {
    auto now = q.front();
    q.pop();
    const int currid = get_id(now);
    for (int i = 0; i <= 4; ++i) {
      const int nexts = nextstate(now, i);
      const int nextid = get_id(nexts);
      nfa[currid][i] = nextid;
      if (visited[nextid] == 0) {
        visited[nextid] = 1;
        q.push(nexts);
      }
    }
  }
}

int64 solve0(const int64 N, const int64 M, const int T) {
  const int T1 = T + 1;
  const int X = T * 3 + 2;
  const int cnt = nextId;
  auto result0 = power_mod<mod>(
      [&](auto& m, auto& v) {
        v[get_id(1)] = 1;
        for (int c0 = 0; c0 <= X; ++c0)
          for (int s0 = 0; s0 < cnt; ++s0)
            for (int i = 0; i <= 4 && i + c0 <= X; ++i) {
              const int nextid = nfa[s0][i];
              m((i + c0) * cnt + nextid, c0 * cnt + s0) += 1;
            }
      },
      nextId * (X + 1), N);
  auto calid = [=](int x, int y) { return x + y * T1; };
  auto result1 = power_mod(
      [&](auto& m, auto& v) {
        v[0] = 1;
        for (int a = 0; a < T1 * 2; ++a)
          for (int i = 0; i <= X; ++i) {
            int can = i / 3;
            if (a % T1 + can > T) continue;
            if (i % 3 == 0) {
              for (int j = 0; j < cnt; ++j)
                if (bit_get(state[j], 0)) {
                  m(calid(a % T1 + can, a / T1), a) =
                      add_mod((int64)m(calid(a % T1 + can, a / T1), a),
                              result0[i * cnt + j], mod);
                }
            } else if (i % 3 == 2) {
              if (a / T1) continue;
              for (int j = 0; j < cnt; ++j)
                if (bit_get(state[j], 1)) {
                  m(calid(a % T1 + can, 1), a) =
                      add_mod((int64)m(calid(a % T1 + can, 1), a),
                              result0[i * cnt + j], mod);
                }
            }
          }
      },
      T1 * 2, M, mod);
  int64 ans = result1[T1 * 2 - 1];
  return ans;
}

int64 dp[250][93][68];
int64 seq[250][62];
int64 solve1(const int64 N, const int64 M, const int T) {
  const int T1 = T + 1;
  const int X = T * 3 + 2;
  memset(dp, 0, sizeof dp);
  memset(seq, 0, sizeof seq);
  dp[0][0][get_id(1)] = 1;
  const int n = 240;
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j <= X; ++j)
      for (int k = 0; k < 68; ++k)
        if (dp[i - 1][j][k])
          for (int l = 0; l <= 4 && l + j <= X; ++l) {
            dp[i][l + j][nfa[k][l]] =
                add_mod(dp[i][l + j][nfa[k][l]], dp[i - 1][j][k], mod);
          }

  for (int i = 1; i <= n; ++i)
    for (int j = 0; j <= X; ++j)
      for (int k = 0; k < 68; ++k)
        if (j % 3 == 0) {
          if (bit_get(state[k], 0))
            seq[i][j / 3] = add_mod(seq[i][j / 3], dp[i][j][k], mod);
        } else if (j % 3 == 2) {
          if (bit_get(state[k], 1)) {
            seq[i][j / 3 + T1] = add_mod(seq[i][j / 3 + T1], dp[i][j][k], mod);
          }
        }

  vector<int64> result0;
  {
    for (int p = 0; p < T1 * 2; ++p) {
      NModPoly t(mod);
      for (int i = 0; i <= n; ++i) t.data.pb(seq[i][p]);
      {
        auto tmp = nth_element(t, N);
        assert(tmp != -1);
        result0.push_back(tmp);
      }
    }
  }
  auto calid = [=](int x, int y) { return x + y * T1; };
  auto result1 = power_mod(
      [&](auto& m, auto& v) {
        v[0] = 1;
        for (int a = 0; a < T1 * 2; ++a)
          for (int b = 0; b < T1 * 2; ++b) {
            if (a / T1 && b / T1) continue;
            if (a % T1 + b % T1 > T) continue;
            const int x = a % T1 + b % T1, y = a / T1 | b / T1;
            m(calid(x, y), a) =
                add_mod((int64)m(calid(x, y), a), result0[b], mod);
          }
      },
      T1 * 2, M, mod);
  int64 ans = result1[T1 * 2 - 1];
  return ans;
}

int main() {
  init();
  cout << solve1(4, 1, 1) << endl;
  cout << solve1(9, 1, 4) << endl;
  cout << solve1(9, 3, 4) << endl;
  cout << solve1(1000, 1000, 5) << endl;

  cout << solve0(4, 1, 1) << endl;
  cout << solve0(9, 1, 4) << endl;
  cout << solve0(9, 3, 4) << endl;
  cout << solve0(1000, 1000, 5) << endl;

  cout << solve1(1e8, 1e8, 30) << endl;
  return 0;
}