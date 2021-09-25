#include <pe_base>
#include <pe_util>

const int MAGIC = 59049;  // 3^10
int64 dp1[MAGIC];
int64 dp2[MAGIC];
int64 sum[MAGIC];
int main()
{
  for (int i = 0; i < MAGIC; ++i)
  {
    int64 base = 1;
    int dig[20];
    int top = 0;
    int s = 0;
    int div = 1;
    for (int j = 0; j < 10; ++j, base *= 3)
    {
      int now = i / base % 3;
      s += now * j;
      div *= now == 2 ? 2 : 1;
      top += now;
      dig[j] = now;
    }
    if (top != 10) continue;

    sum[i] = s;
    dp1[i] = dp2[i] = 3628800 / div;
    
    if (dig[0] > 0)
    {
      dp2[i] -= 362880 / div * (dig[0] == 2 ? 2 : 1);
    }
  }
  int64 ans = 0;
  for (int i = 0; i < MAGIC; ++i)
  {
    int base = 1;
    int dig[20];
    int top = 0;
    int s = 0;
    int div = 1;
    int id = 0;
    for (int j = 0; j < 10; ++j, base *= 3)
    {
      int now = i / base % 3;
      s += now * j;
      div *= now == 2 ? 2 : 1;
      id += base * (2-now);
      top += now;
      dig[j] = now;
    }
    if (top != 10) continue;
    
    if ((sum[id]-sum[i])%11==0)
    ans += dp1[i] * dp2[id];
  }
  dbg(ans);
  return 0;
}