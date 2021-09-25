#include <stdio.h>

/*
ans cand: 2
ans cand: 24
ans cand: 4680
ans cand: 26208
ans cand: 17428320
ans cand: 4320
ans cand: 8910720
ans cand: 91963648
ans cand: 197064960
ans cand: 20427264
ans cand: 88898072401645056
ans cand: 8583644160
ans cand: 57629644800
ans cand: 206166804480
ans cand: 17116004505600
ans cand: 75462255348480000
ans cand: 57575890944
ans cand: 10200236032
ans cand: 21857648640
ans cand: 1416963251404800
ans cand: 15338300494970880
ans cand: 301183421949935616
result: 482316491800641154

*/

#define N 1000000000000000000LL
#define SQRN 1000000000LL

int prime_t[100000];
int prime_f[100000];
int prime_search[SQRN/10];
int primen;

int myprime_t[200];
int myprime_f[200];
int myprime_i[200];
int myprimen;

#define ANSWERN 100000
long long int answer[ANSWERN];
int answern = 0;
long long int sum = 0;

int target2;
int sum2;
long long int deno;
long long int pow2_deno = 1;

void make_primetable();
long long int mypow_sum(int b, int n);
void prime_deno();
int answer_check(long long int ans);

int main(int argc, char **argv) {
  int i;
  int j, k;
  int s;
  int max;
  
  long long int pow2_add = 1;
  int primemax;

  long long int target;
  make_primetable();

  int s2count;


  // main routine: check 2^n
  for (i=1;; i++) {
    pow2_deno *= 2;
    pow2_add = pow2_add * 2+1;
    if (pow2_deno > N /5)
      break;
    //printf ("%d %lld %lld %lld\n", i, pow2_deno, pow2_add, pow2_add*pow2_deno);

    for (j=0; j<primen; j++)
      prime_f[j] = 0;
    target = pow2_add;
    for (j=0; j<primen; j++) {
      while (!(target % prime_t[j])) {
	prime_f[j]++;
	target /= prime_t[j];
      }
      if (target == 1)
	break;
    }
    myprimen = 0;
    //printf ("%lld = ", pow2_add);
    if (target != 1) {
      //printf (" %lld^%d", target, 1);
      myprime_t[myprimen] = target;
      myprime_f[myprimen++] = 1;

      target = target+1;
      s2count = 0;
      while (!(target % 2)) {
	s2count++;
	target /= 2;
      }
      //printf ("(%d) ", s2count);
    }
    primemax = j;

    s2count = 0;
    for (j=0; j<=primemax; j++) {
      if (prime_f[j]) {
	//printf (" %d^%d(", prime_t[j], prime_f[j]);
	myprime_t[myprimen] = prime_t[j];
	myprime_f[myprimen] = prime_f[j];
	myprimen++;
	for (k=1; k<=prime_f[j]; k++) {
	  target = mypow_sum(prime_t[j], k);
	  s2count = 0;
	  while (!(target % 2)) {
	    s2count++;
	    target /= 2;
	  }
	  //printf ("%d ", s2count);
	}
	//printf (")");
      }

    }

    //printf("\n");

    target2 = i-1;
    sum2 = 0;
    deno = pow2_deno;
    prime_deno();

  }

  printf ("result: %lld\n",sum);
}


void make_primetable()
{
  int i, j;
  int SQRM = sqrt(SQRN);
  int SQRMSQRM = sqrt(SQRM);

  for (i=2; i<SQRMSQRM; i++) {
    if (!prime_search[i]) {
      // prime
      
      prime_t[primen++] = i;
      for (j=i+i; j<=SQRM; j += i)
	prime_search[j] = 1;

      //      printf ("%d %d\n", primen, i);
    }
  }
  for (; i<=SQRM; i++)
    if (!prime_search[i])
      prime_t[primen++] = i;

  printf ("prime: %d %d\n", primen, prime_t[primen-1]);
}

// b^n
long long int mypow(int b, int n) {
  int i;
  long long int answer = 1;

  for (i=0; i<n; i++)
    answer *= b;

  return answer;
}
// 1+b+b^2+..+b^n = (b^(n+1)-1)/(b-1)
long long int mypow_sum(int b, int n) {
  int i;
  long long int answer = 1;

  for (i=0; i<n+1; i++)
    answer *= b;

  return ((answer-1)/(b-1));
}

// make denominator for each prime
void prime_deno() {
  int i, j, k;
  long long int target;

  int myprimen_l;
  int myprimef_l;
  int mymyprimen;
  int mymyprime_t[100];
  int mymyprime_f[100];
  int sqrt_t;


  long long int deno_l;
  if (sum2 > target2)
    return;
  if (sum2 == target2)
    answer_check(deno);


  myprimen_l = myprimen;
  deno_l = deno;

  for (i=0; i<myprimen_l; i++) {
    if (myprime_i[i])
      continue;

    myprimef_l = myprime_f[i];

    // this +3 is not accurate....
    // this is required to find number like 4320
    // 4320 = 2^5 * 5 * 3^3
    // 1+...+2^5 = 63 =       3^2     * 7
    // 1+...+5^1 =  6 = 2   * 3
    // 1+...+3^3 = 40 = 2^3 *     * 5
    // element of 5 and element of 3 reduce each other.
    // then if we search only from 3^1 to 3^2 because 63 cannot divide by 3^3
    // you cannot find this answer.
    for (myprime_i[i]=1; myprime_i[i]<=myprimef_l+3; myprime_i[i]++) {
      if (N/deno < myprime_t[i])
	break;
      deno *= myprime_t[i];
      if (deno > N)
	break;

      // numerator
      target = mypow_sum(myprime_t[i], myprime_i[i]);


      // prime decompostion
      mymyprimen = 0;
      sqrt_t = sqrt(target);
      for (j=0; j< primen; j++) {
	
	if (sqrt_t < prime_t[j])
	  break;
	if (!(target % prime_t[j])) {
	  target /= prime_t[j];
	  mymyprime_t[mymyprimen] = prime_t[j];
	  mymyprime_f[mymyprimen++] = 1;
	  while (!(target % prime_t[j])) {
	    mymyprime_f[mymyprimen-1]++;
	    target /= prime_t[j];
	  }
	  sqrt_t = sqrt(target);
	}
      }
      if (target != 1) {
	mymyprime_t[mymyprimen] = target;
	mymyprime_f[mymyprimen++] = 1;
      }
	

      for (j=0; j<mymyprimen; j++) {
	if (mymyprime_t[j] == 2) {
	  sum2 += mymyprime_f[j];
	  continue;
	}
	for (k=0; k<myprimen; k++) {
	  if (mymyprime_t[j] == myprime_t[k]) {
	    myprime_f[k] += mymyprime_f[j];
	    break;
	  }
	}
	if (k==myprimen) {// new prime
	  myprime_t[myprimen] = mymyprime_t[j];
	  myprime_f[myprimen++] = mymyprime_f[j];
	}

      }

//      if (sum<=2)
//	printf ("sum2: %d\n", sum2);

      // main routine
      prime_deno();

      // change myprime_t
      for (j=0; j<mymyprimen; j++) {
	if (mymyprime_t[j] == 2) {
	  sum2 -= mymyprime_f[j];
	  continue;
	} 
	for (k=0; k<myprimen; k++) {
	  if (mymyprime_t[j] == myprime_t[k]) {
	    myprime_f[k] -= mymyprime_f[j];
	    break;
	  }
	}
      }

      myprimen = myprimen_l;
	    

    }

    deno = deno_l;
    myprime_i[i] = 0;
  }

}

// check if answer is already registered
int answer_check(long long int ans) {
  int i;
  
  for (i=0; i<answern; i++) 
    if (answer[i] == ans)
      return -1;
  // check valid answer
  for (i=0; i<myprimen; i++)
    if (myprime_i[i] > myprime_f[i])
      return -1;


  answer[answern++] = ans;
  sum += ans;

  printf ("ans cand: %lld\n", ans);

  if (answern >= ANSWERN)
    printf ("overflow\n");

  return 1;
}