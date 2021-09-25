#include <stdio.h>

int main()
{
  int cnt = 0;
  for(int a = 0; a <= 9; a++)
    for(int b = 0; b <= 9; b++)
      for(int c = 0; c <= 9; c++)
        for(int d = 0; d <= 9; d++) {
          int s = a+b+c+d;
          for(int e = 0; e <= 9; e++) {
            if(s - a - e < 0 || s - a - e > 18) continue;
            for(int f = 0; f <= 9; f++) {
              if(s - b - f < 0 || s - b - f > 18) continue;
              if(s - a - f < 0 || s - a - f > 18) continue;
              for(int g = 0; g <= 9; g++) {
                int h = s - e - f - g;
                if (h < 0 || h > 9) continue;
                if(s - c - g < 0 || s - c - g > 18) continue;
                if(s - d - h < 0 || s - d - h > 18) continue;
                if(s - d - g < 0 || s - d - g > 18) continue;
                for(int i = 0; i <= 9; i++) {
                  int j = 2 * a + b + c + e - g + i - s;
                  int k = 2 * a + b + c + e - f - 2*g + i - 2 * j;
                  int l = s - i - j - k;
                  int m = s - a - e - i;
                  int n = s - b - f - j;
                  int o = s - c - g - k;
                  int p = s - a - f - k;
                  if (h < 0 || h > 9) continue;
                  if (i < 0 || i > 9) continue;
                  if (l < 0 || l > 9) continue;
                  if (m < 0 || m > 9) continue;
                  if (n < 0 || n > 9) continue;
                  if (o < 0 || o > 9) continue;
                  if (p < 0 || p > 9) continue;
                  ++cnt;
                }
              }
            }
          }
        }
  printf("total count: %d\n", cnt);
  return 0;
}