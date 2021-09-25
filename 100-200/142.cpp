#include <cmath>

bool issquare(unsigned int N)
{
  unsigned int x = (unsigned int)sqrt((long double)N);
  return (N == x*x);
}

int main(int c, char **v)
{
  int N = 2000000;
  int smallest = N;
  for(int z = 1; z < N; z++)
  {
    int cnt0 = 1;
    int y = cnt0*cnt0-z;
    for(; y < N && (z+y) <= smallest; ++cnt0, y=cnt0*cnt0-z)
    {
      if ((y <= z) || !issquare(y-z))
        continue;
      int cnt = 1;
      int x = cnt*cnt-y;
      for(; x < N && (x+y+z) <= smallest; ++cnt, x=cnt*cnt-y)
      {
        if (x <= y)
          continue;
        if (issquare(x-y) && issquare(x+z) && issquare(x-z))
        {
          int small = x+y+z;
          if (small < smallest)
          {
            printf("%d %d %d = %d\n", x, y, z, x+y+z);
            N = smallest = small;
          }
        }
      }
    }
  }
  return 0;
}