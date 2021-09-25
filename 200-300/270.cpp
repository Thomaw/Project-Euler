#include <stdio.h>

#define N 30
#define LIMIT 100000000

long long int answer;

long long int tri[N][N];
long long int dia[N][N];
long long int dib[N][N];
long long int dic[N][N];

int find_tri();
int find_d1();
int find_d2();
int find_d3();

int main(int argc, char **argv) {
  int i, j;

  find_tri();
  find_d3();
  find_d1();
  find_d2();

  answer = dib[N-2][N-2];
  for (i=0; i<N-1; i++) {
    answer += tri[N-1][i]*dia[N-2][N-1-i-1];
    answer %= LIMIT;
  }
  answer += tri[N-1][N-1]*tri[N-2][N-1];
  answer %= LIMIT;
  for (i=0; i<N-1; i++) {
    answer += tri[N-2][i]*dia[N-1][N-1-i-1];
    answer %= LIMIT;
  }

  printf ("answer: %lld\n", answer);
}

int find_tri() {
  int i, j, k;
 
  for (i=0; i<N; i++) {
    tri[0][i] = 1;
    tri[i][0] = 1;
  }
  for (i=1; i<N; i++)
    for (j=i; j<N; j++) {
      for (k=0;k<=i; k++) {
	tri[i][j] += tri[k][j-1];
	tri[i][j] %= LIMIT;
      }
      tri[j][i] = tri[i][j];
    }
}

int find_d1() {
  int i, j, k;
 
  for (i=0; i<N-1; i++)
    for (j=i; j<N; j++) {
      if (i==0) {
	dia[i][j] = dic[N-2][j];
	for (k=0; k<=j; k++)
	  dia[i][j] += tri[N-1][k];
      } else {
	dia[i][j] = tri[i-1][N-1];
	for (k=0; k<N-1; k++) {
	  dia[i][j] += tri[i-1][N-2-k]*dic[k][j];
	  dia[i][j] %= LIMIT;
	}
	for (k=0; k<=j; k++)
	  dia[i][j] += dia[i-1][k];
      }
 
      dia[i][j] %= LIMIT;
      dia[j][i] = dia[i][j];
    }
}

int find_d2() {
  int i, j, k;

  for (i=0; i<N-1; i++)
    for (j=i; j<N-1; j++) {
      if (i==0)
	dib[i][j] = dia[j][N-1];
      else
	dib[i][j] = dib[i-1][j];

      dib[i][j] %= LIMIT;
      if (j==0)
	dib[i][j] += dia[i][N-1];
      else
	dib[i][j] += dib[i][j-1];
      dib[i][j] %= LIMIT;

      for (k=0; k<N-1; k++) {
	dib[i][j] += tri[i][k]* dia[j][N-2-k];
	dib[i][j] %= LIMIT;
	dib[i][j] += tri[j][k]* dia[i][N-2-k];
	dib[i][j] %= LIMIT;
      }
      dib[i][j] += tri[i][N-1]*tri[j][N-1];

      dib[i][j] %= LIMIT;
      dib[j][i] = dib[i][j];
    }
}

int find_d3() {
  int i, j, k;

  for (i=0; i<N-1; i++)
    for (j=0; j<N; j++) {
      if (i==0)
	dic[i][j] = 1;
      else
	dic[i][j] = dic[i-1][j];
      for (k=0; k<=j; k++) {
	dic[i][j] += tri[i][k];
	dic[i][j] %= LIMIT;
      }
    }
}