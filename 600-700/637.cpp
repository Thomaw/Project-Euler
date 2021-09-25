#define N 10000000

int i, j, f[2][N+1], b[2] = {3, 10};

void dfs1(int n, int s, int q) {
  int d;
  if (s == 0) f[i][n] = 1;
  else for (; n + q*s <= N; q *= b[i])
      for (d = 1; d <= s; d++) dfs1(n + q*d, s - d, q*b[i]);
}

int dfs2(int n, int s) {
  int m;
  if (n == 0) return f[i][s] == 1;
  else for (m = b[i]; m <= b[i]*n; m *= b[i])
      if (dfs2(n/m, s + n%m)) return 1;
  return 0;
}

int main() {
  for (i = 0; i < 2; i++)
    for (j = 1; j < b[i]; j++) {
      dfs1(0, j, 1);
      f[i][j] = 0;
    }

  for (i = 0; i < 2; i++)
    for (j = b[i]; j <= N; j++)
      if (!f[i][j]) f[i][j] = 2 + !dfs2(j, 0);

  long long g = 0;
  for (j = 1; j <= N; j++)
    if (f[0][j] == f[1][j]) g += j;
  printf("%lld\n", g);
  return 0;
}