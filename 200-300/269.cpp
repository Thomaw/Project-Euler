#include <stdio.h>

#define NN 16

long long int answer;
long long int lanswer;

int limit[2][10];
int d[NN];
int factor;

void recur(int dn, int dif);
void calc_case1();
void calc_case2();

int main(int argc, char **argv) {
  int i;

  for (i=3; i<10; i++) {
    limit[0][i] = 9/(i-1);
    if (9%(i-1))
      limit[0][i]++;
    limit[1][i] = -limit[0][i];
  }

  for (factor=9; factor>2; factor--) {
    lanswer = 0;
    recur(NN-1, 0);
    answer += lanswer;
    printf ("%d: %16lld %16lld\n", factor, lanswer, answer);
  }

  calc_case2();
  calc_case1();
  // x=0
  answer += 1000000000000000LL;

  printf ("answer: %lld\n", answer);
}

void recur(int dn, int dif) {
  int i;
  int new_dif;

  if (dn<0) {
    if (!dif)
      if (double_check(factor))
	lanswer++;
    return;
  }
  
  dif = -factor*dif;
  for (d[dn]=0; d[dn]<10; d[dn]++) {
    new_dif = dif+d[dn];
    if (new_dif <= limit[1][factor])
      continue;
    if (new_dif >= limit[0][factor])
      break;
    recur(dn-1, new_dif);
  }

}


int double_check(int n) {
  int i, j;
  long long int s;

  if (d[0] == 0)
    return 0;

  for (i=1; i<n; i++) {
    s=d[NN-1];
    for (j=NN-2; j>=0; j--) {
      s *= -i;
      s += d[j];
    }
    if (!s)
      return 0;
  }
  return 1;
}

long long int s[NN/2][10*NN/2];
long long int t[10*NN/2];
void calc_case1() {
  int i, j, k;
  lanswer = 0;

  for (i=0; i<10; i++)
    s[0][i] = 1;

  for (i=1; i<NN/2; i++)
    for (j=0; j<10; j++)
      for (k=0; k<=i*9; k++)
	s[i][k+j] += s[i-1][k];

  for (j=1; j<10; j++)
    for (k=0; k<=(NN/2-1)*9; k++)
      t[k+j] += s[(NN/2-1)-1][k];

  for (i=1; i<10*NN/2; i++)
    lanswer += t[i]*s[NN/2-1][i];

  answer += lanswer;
  printf ("%d: %16lld %16lld\n", 1, lanswer, answer);
}

long long int table2[16][10][161];
void calc_case2() {
  int i, j, k, l;
  int index;

  lanswer = 0;

  table2[0][4][82] = 1; // 2->1 +3
  table2[0][5][84] = 1; // 4->2
  table2[0][6][86] = 1; // 6->3
  table2[0][7][88] = 1; // 8->4


  for (i=1; i<NN; i++) {
    for (j=0; j<10; j++) {
      for (k=0; k<10; k++) {
	if (!((j+k)%2))
	  continue;
	for (l=0; l<161; l++) {
	  index = 160-l+k;
	  if (index>160)
	    continue;
	  table2[i][(k-(j-3))/2+3][index] += table2[i-1][j][l];
	}
      }
    }

  }
  
  for (k=0; k<161; k++) {
    if (k==80)
      continue;
    lanswer += table2[NN-1][3][k];
  }
  answer += lanswer;
  printf ("%d: %16lld %16lld\n", 2, lanswer, answer);
}