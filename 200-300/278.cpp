#include <stdio.h>

#define N 5000
long long int answer = 0;

int prime_search[N];
int prime_t[N];
int primen=0;

void make_primetable();

int main(int argc, char **argv) {
  int i, j, k;
  long long int s,t;
  make_primetable();

  for (i=0; i<primen-2; i++)
    for (j=i+1; j<primen-1; j++)
      for (k=j+1; k<primen; k++) {
	s = ((long long int)prime_t[k]*prime_t[j]-prime_t[k]-prime_t[j])*(long long int)prime_t[i];
	t = prime_t[k]*prime_t[j];
	answer += s+t*(prime_t[i]-1);
      }

  printf ("answer: %lld\n", answer);
}

void make_primetable() {
   ... snipped ...
}