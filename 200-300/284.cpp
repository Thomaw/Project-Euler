#include <stdio.h>
#include <math.h>

#define N 10000

long long int d[N+1][N+1];

long long int answer = 0;
void recur(int nth, int sum);

long long int a;
int an;
int ad[N+1];

int main(int argc, char **argv) {
  int i, j;
  int s;
  for (i=1; i<14; i++) { // 0 is excluded
    s = i*i;
    if (s%14==i) {
      d[0][0] = i;
      d[0][1] = s/14;
      answer += i;
      recur(1,i);
    }
  }

  printf ("ans %lld\n", answer);
  
  a = answer;
  an = 0;
  while (a) {
    ad[an++] = a%14;
    a /= 14;
  }
  for (i=an-1; i>=0; i--)
    printf ("%x", ad[i]);
  printf ("\n");
}
 
void recur(int nth, int sum) {
  int i, j;

  for (i=0; i<=N; i++)
    d[nth][i] = d[nth-1][i];

  for (i=0; i<14; i++) {
    if (nth*2 <=N)
      d[nth][nth*2] += i*i;
    if ((d[nth][nth]-i)%14==0) {
      d[nth][nth+1] += d[nth][nth]/14;
      d[nth][nth] = d[nth][nth]%14;
      if (i!=0) {
      answer += i;
      for (j=0; j<nth; j++)
	answer += d[nth][j];
      }
      if (nth < N-1)
	recur (nth+1, sum+i);
    }
    for (j=0; j<nth; j++) {
      if (nth+j > N)
	break;
      d[nth][nth+j] += d[nth-1][j]*2;
    }
    if (nth*2 <=N)
      d[nth][nth*2] -= i*i;
    
  }
}
