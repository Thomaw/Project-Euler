#include <stdio.h>

#define N 10000000000000000LL

long long int answer;

#define PN 100
int prime_search[PN];
int prime_t[PN];
int primen=0;

void make_primetable();
void calc_c(int nth, int min, long long int n);

long long int local_a;
int main(int argc, char **argv) {
  make_primetable();

  int i, t, f;
  long long int base;

  t = 1;
  base = 2*3*5;
  f = 1;
  for (i=4; ; i++) {
    base *= prime_t[i-1];
    if (base > N)
      break;
    local_a = 0;
    calc_c(i, 0, 1);
    if (i!=4) {
      f *= i-1;
      f /= i-4;
    }
    if (t)
      answer += local_a * f;
    else
      answer -= local_a * f;
    t = 1-t;
  }

  printf ("answer: %lld\n", answer);

}


void calc_c(int nth, int min, long long int n) {
  int i;
  static long long int next_n;
  if (nth==0)
    local_a += N/n;
  else 
    for (i=min; i<primen-nth+1; i++) {
      next_n = n*prime_t[i];
      if (next_n >= N)
	break;
      calc_c(nth-1, i+1, next_n);
    }
}

void make_primetable() {
  int i, j;
  int SQRN = sqrt(PN);

  primen = 0;
  
  prime_t[0] = 2;
  primen++;
  prime_t[1] = 3;
  primen++;

  for (i=5; i<=SQRN; i+=2) { // sqrt(SQRN)
    if (i%3==0)
      continue;
    if (!prime_search[i/3]) {
      // prime
      prime_t[primen] = i;
      for (j=i; j<PN; j += (i+i)) {
	if (j%3==0)
	  continue;
        prime_search[j/3] = primen;
      }
      primen++;
    }
  }

  for (; i<=PN; i+=2) {
    if (i%3==0)
      continue;
    if (!prime_search[i/3]) {
      prime_search[i/3] = primen;
      prime_t[primen++] = i;
    }
  }

  printf("prime %d %d  PN: %d\n", primen, prime_t[primen-1], PN);
}