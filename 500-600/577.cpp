#include <stdio.h>
#include <time.h>

#define MAX_N 12345

unsigned long answer, t[MAX_N - 1];
int i, n, s;

int main() {
  clock_t start= clock();
  for (n= 1; n <= MAX_N - 2; n++) {
    answer+= t[n]= t[n - 1] + n;
  }
  for (s= 2; s <= MAX_N; s++) {
    i= 1;
    for (n= s * 3; n <= MAX_N; n++) {
      answer+= t[i] * s;
      i++;
    }
  }
  double time_count = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf("\ne577: %lu\n\n", answer);
  printf("Elapsed time %f seconds\n", time_count);
  return 0;
}