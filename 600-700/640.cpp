#include<cstdio>
#include<cstring>

double min(double a, double b, double c)
{
  if(a>b) a = b;
  if(a<c) return a;
  return c;
}
const int roll = 6;
double DP[1<<(2*roll)], tDP[1<<(2*roll)];
int main()
{
  for(int i=0; i<(1<<(2*roll)); ++i) DP[i] = 1e9;
  DP[0] = 0;
  while(true)
  {
    tDP[0] = 0;
    for(int i=1; i<(1<<(2*roll)); ++i)
    {
      double exp = 0;
      for(int x=1; x<=roll; ++x)
        for(int y=1; y<=roll; ++y)
          exp += min(DP[i^(1<<(x-1))], DP[i^(1<<(y-1))], DP[i^(1<<(x+y-1))]);
      tDP[i] = exp/(roll*roll)+1;
    }
    memcpy(DP, tDP, sizeof DP);
    printf("%.12f\n", DP[(1<<(2*roll))-1]);
  }
}