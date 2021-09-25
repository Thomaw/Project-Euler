#include <stdio.h>
#include <math.h>

#define N 10000000000000000LL
#define N8 100000000
#define PN 190
#define LN 21

long long int answer = 0;
int primen=0;
int prime_search [PN];
int prime_t[PN];
double p_log[PN];
double p_log_lim[PN];
double target_d;
double log_max = 0.0;

typedef struct _Pset {
  long long int n;
  double logs;
} Pset;
int psetn = 0;
Pset pset[1<<(LN+1)];

void make_primetable();
void recur(int nth, long long int n, double logs);
void recur0(int nth, long long int n, double logs);
int comp_pset(Pset *a, Pset *b);
long long int prod(long long int n1, long long int n2);

int main(int argc, char **argv) {
  int i;
  double tmp;

  make_primetable();

  target_d = 0.0;
  for (i=0; i<primen; i++) {
    p_log[i] = log(prime_t[i]);
    target_d += p_log[i];
  }
  target_d /= 2;

  recur0(0, 1, 0.0);
  qsort(pset, psetn, sizeof(Pset), comp_pset);

  recur(primen-1, 1, 0.0);


  printf ("Answer: %lld\n", answer);
}

int comp_pset(Pset *a, Pset *b) {
  if (a->logs == b->logs)
    return 0;
  else if (a->logs < b->logs)
    return -1;
  else
    return 1;
}

void recur0(int nth, long long int n, double logs) {
  double new_logs;
  if (nth == LN) {
    pset[psetn].n = n;
    pset[psetn].logs = logs;
    psetn++;
    return;
  }

  recur0(nth+1, n, logs);
  new_logs = logs + p_log[nth];
  recur0(nth+1, (n*prime_t[nth])%N, new_logs);
}

int base;
int add;
int index2;
double target_log;

void recur(int nth, long long int n, double logs) {
  double new_logs;
  if (nth == LN-1) {
    base = 0;
    add = psetn>>1;
    target_log = target_d - logs;
    while (add) {
      index2 = base + add;
      if (pset[index2].logs < target_log)
	base = index2;
      add >>= 1;
    }
    if (pset[index2].logs > target_log)
      index2 = base;
    

    target_log = logs + pset[index2].logs;
    if (target_log > log_max) {
      answer = prod(n, pset[index2].n);
      log_max = logs+pset[index2].logs;
    }
    return;
  }

  recur(nth-1, n, logs);
  new_logs = logs + p_log[nth];
  if (new_logs > target_d)
    return;
  recur(nth-1, (n*prime_t[nth])%N, new_logs);
}

void make_primetable() {
  int i, j;
  
  int SQRN = sqrt(PN);

  primen = 0;
  for (i=2; i<=SQRN; i++) { // sqrt(SQRN)
    if (!prime_search[i]) {
      // prime
      prime_t[primen++] = i;
      for (j=i+i; j<PN; j += i)
        prime_search[j] = 1;
    }
  }

  for (; i<PN; i++)
    if (!prime_search[i])
      prime_t[primen++] = i;


  printf("prime %d %d\n", primen, prime_t[primen-1]);
}

long long int prod(long long int n1, long long int n2) {
  long long int n11, n12, n21, n22;
  long long int n;
  n12 = n1 % N8;
  n11 = n1 / N8;
  n22 = n2 % N8;
  n21 = n2 / N8;
  n = n12*n22+((n11*n22)%N8)*N8+((n12*n21)%N8)*N8;
  return (n%N);
}