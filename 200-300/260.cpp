#include <stdio.h>

#define N 1000

char w[N+1][N+1][N+1];
long long int answer = 0;

int min(int a, int b) { return ((a>b)?b:a);}
int max(int a, int b) { return ((a>b)?a:b);}

int main(int argc, char **argv) {
  int i, j, k, l;
  int lim;

  int s;

  w[0][0][0] = 1;
  for (i=1; i<=N; i++) {
    w[0][0][i] = -1;
    w[0][i][i] = -1;
    w[i][i][i] = -1;
  }
  for (i=0; i<=N; i++)
    for (j=i; j<=N; j++)
      for (k=j; k<=N; k++) {
	if (w[i][j][k] != 0)
	  continue;
	// check phase

	// 1 pile remove
	for (l=0; l<i; l++)
	  if (w[l][j][k] == 1)
	    goto Label_k_end;
	for (l=0; l<i; l++)
	  if (w[l][i][k] == 1)
	    goto Label_k_end;
	for (; l<j; l++)
	  if (w[i][l][k] == 1)
	    goto Label_k_end;
	for (l=0; l<i; l++)
	  if (w[l][i][j] == 1)
	    goto Label_k_end;
	for (; l<j; l++)
	  if (w[i][l][j] == 1)
	    goto Label_k_end;
	for (; l<k; l++)
	  if (w[i][j][l] == 1)
	    goto Label_k_end;


	// 2 piles remove
	for (l=1; l<=i; l++)
	  if (w[i-l][j-l][k] == 1)
	    goto Label_k_end;
	lim = min(i, k-j);
	for (l=1; l<=lim; l++)
	  if (w[i-l][j][k-l] == 1)
	    goto Label_k_end;
	for (; l<=i; l++)
	  if (w[i-l][k-l][j] == 1)
	    goto Label_k_end;
	lim = min(j, j-i);
	for (l=1; l<=lim; l++)
	  if (w[i][j-l][k-l] == 1)
	    goto Label_k_end;
	lim = min(j, k-i);
	for (; l<=lim; l++)
	  if (w[j-l][i][k-l] == 1)
	    goto Label_k_end;
	for (; l<=j; l++)
	  if (w[j-l][k-l][i] == 1)
	    goto Label_k_end;

	// 3 piles remove
	for (l=1; l<=i; l++)
	  if (w[i-l][j-l][k-l] == 1)
	    goto Label_k_end;

	// lose case
	// optimization phase

	// 1 pile add
	for (l=k+1; l<=N; l++)
	  w[i][j][l] = -1;
	for (l=j+1; l<=k; l++)
	  w[i][l][k] = -1;
	for (; l<=N; l++)
	  w[i][k][l] = -1;
	for (l=i+1; l<=j; l++)
	  w[l][j][k] = -1;
	for (; l<=k; l++)
	  w[j][l][k] = -1;
	for (; l<=N; l++)
	  w[j][k][l] = -1;

	// 2 piles add
	for (l=1; l<=N-k; l++)
	  w[i][j+l][k+l] = -1;
	lim = min (N-k, j-i);
	for (l=1; l<=lim; l++)
	  w[i+l][j][k+l] = -1;
	for (; l<=N-k; l++)
	  w[j][i+l][k+l] = -1;
	lim = min (N-j, k-j);
	for (l=1; l<=lim; l++)
	  w[i+l][j+l][k] = -1;
	lim = min (N-j, k-i);
	for (; l<=lim; l++)
	  w[i+l][k][j+l] = -1;
	for (; l<=N-j; l++)
	  w[k][i+l][j+l] = -1;

	// 3 piles add
	for (l=1; l<=N-k; l++)
	  w[i+l][j+l][k+l] = -1;
	
	answer += i+j+k;
	w[i][j][k] = 1;
	continue;

      Label_k_end: // win
	w[i][j][k] = -1;
      }

  printf ("answer: %lld\n", answer);
}