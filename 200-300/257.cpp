#include <stdio.h>
#include <math.h>

/*
1. a=b=c
2. (b-a)(c-a)=2a^2
3. (2b-a)(2c-a)=3a^2

find co-prime triplests (a,b,c)

2*3*5*7*11*13*17*19
9699690  ==> at most 8 prime elements
 */


#define N 100000000LL
//#define N 50000000LL // 67163758
//#define N 1000000LL
//#define N 3000

#define PN (N/3)
#define P_N6 1071205 // # of prime <= N/6

int primen=0;

typedef struct _Prim {
  int n;
  struct _Prim *next;
} Prim;
Prim *plink[PN+1];
Prim pslink[P_N6];

long long int prime2f[8];
int prime2n;

long long int count = 0;

long long int a;
long long int a22, a33;
long long int limit2, limit3;
long long int limit2h, limit3h;

void check_2(int nth, long long int small);
void check_2n(long long int small);
void check_3(int nth, long long int small);
void check_3even();
void check_3n(long long int small);
void decompose2();

int main(int argc, char **argv) {
  int i;

  for (a=2; a<=N/3; a++) {
    decompose2();

    // *2
    if (a%2) {
      prime2f[prime2n] = 2;
      prime2n++;
    } else
      prime2f[0] *= 2;

    a22 = 2 * a * a;
    limit2 = N - 3 * a;
    limit2h = a * sqrt(2);

    check_2(0, 1);

    if (a%2) {
      prime2n--;
    } else
      prime2f[0] /= 2;

    // *3
    if (a%4 == 2)
      continue;

    if (a%3) {
      prime2f[prime2n] = 3;
      prime2n++;
    } else {
      if (a%2)
	prime2f[0] *= 3;
      else
	prime2f[1] *= 3;
    }
    a33 = 3 * a * a;
    limit3 = 2 * N - 4 * a;
    limit3h = a * sqrt(3);

    if (a%2)
      check_3(0, 1);
    else
      check_3even();    
  }

  // N/3 , 4
  printf ("answer: %lld\n", count+N/3);
}

void check_2(int nth, long long int small) {
  int i;
  long long int sn;

  if (nth == prime2n)
    check_2n(small);
  else {
    check_2(nth+1, small);
    sn = small * prime2f[nth];
    if (sn <= limit2h)
      check_2(nth+1, sn);
  }
}

void check_2n(long long int small) {
  long long int large;

  if (small <= a)
    return;
  large = a22/small;
  if (large - small >= a)
    return;
  // small+large = b+c-2a <= N-3*a
  if (small+large > limit2)
    return;

  count+= N / (small + large + 3*a);
}


void check_3(int nth, long long int small) {
  int i;
  long long int sn;

  if (nth == prime2n)
    check_3n(small);
  else {
    sn = small;
    check_3(nth+1, small);
    sn = small * prime2f[nth];
    if (sn <= limit3h)
      check_3(nth+1, sn);
  }
}
void check_3even() {
  int i;
  long long int sn;

  check_3(1, 2);
  sn = prime2f[0]/2;
  if (sn <= limit3h)
    check_3(1, sn);
}

void check_3n(long long int small) {
  long long int large;

  if (small <= a)
    return;
  large = a33/small;
  if (large - small >= a*2)
    return;
  // small+large = 2(b+c)-2a <= 2*N-4*a
  if (small+large > limit3)
    return;

  count += N/ (a+ ((small+a)>>1) + ((large+a)>>1));
}

// decompose a^2 to p^n
void decompose2() {
  int p;
  int a_div = a;
  Prim *link, *link_bak;

  // prime 2,3 should be head of the prime-link list
  prime2n = 0;
  if (!(a_div%2)) {
    prime2f[0] = 2*2;
    a_div /= 2;
    while (!(a_div%2)) {
      prime2f[0] *= 2*2;
      a_div /= 2;
    }
    prime2n++;
  }
  if (!(a_div%3)) {
    prime2f[prime2n] = 3*3;
    a_div /= 3;
    while (!(a_div%3)) {
      prime2f[prime2n] *= 3*3;
      a_div /= 3;
    }
    prime2n++;
  }

  link = plink[a];
  while(link) {
    p = link->n;
    prime2f[prime2n] = p;
    prime2f[prime2n] *= p;
    a_div /= p;
    while (!(a_div%p)) {
      prime2f[prime2n] *= p;
      prime2f[prime2n] *= p;
      a_div /= p;
    }
    prime2n++;

    /* link change */
    link_bak = link->next;
    if (a+p <= PN) {
      link->next = plink[a+p];
      plink[a+p] = link;
    }
    link = link_bak;
  }

  if (a_div != 1) { // register new prime and link from p*2
    if (a <= PN/2) {
      pslink[primen].n = a;
      pslink[primen].next = plink[a<<1];
      plink[a<<1] = &pslink[primen];
      primen++;
    }
  }
}