#include <stdio.h>

#define N 21

unsigned long long C[N][N];

unsigned long long get(int i, int j) {
  if (C[i][j] == 0) {
    C[i][j] = get(i-1, j) + get(i, j-1);
  }
  return C[i][j];
}

int main () {
  int i, j;
  for (i=0; i<N; ++i) {
    for (j=0; j<N; ++j) {
      C[i][j] = 0;
    }
  }
  for (i=0; i<N; ++i) {
    C[0][i] = 1;
    C[i][0] = 1;
  }

  for (i=0; i<N; ++i) {
    printf ("%2d: %llu\n", i, get(i, i));
  }
  return 0;
}
