#include <stdio.h>

unsigned long long max=70+1;

unsigned long long odd_triplets(unsigned long long x) {
  unsigned long long ot=x%4>0,h=1;
  x/=2; while ((x/=2)>0) { if (x%2) ot=2*ot+h; h*=3; }
  return ot;
}

int main() {
  /*
    only the last statement of main() is essential for solution
    but the other draw beautiful ascii art    
  */ 
  unsigned long long f[max][max],g[max][max],n,k,s,i;
  char sum_gerade;

  for (n=0;n<max;n++) {f[n][0]=0;g[n][0]=1;}
  for (n=1;n<max;n++) {
    sum_gerade=(n%4==0)||(n%4==3);
    for (k=1;k<=n;k++) {
      if (k<=n/2) {
        s=0; for (i=k;i<=n;i++) s+=(i%2)?g[i-1][k-1]:f[i-1][k-1]; f[n][k]=s;
        s=0; for (i=k;i<=n;i++) s+=(i%2)?f[i-1][k-1]:g[i-1][k-1]; g[n][k]=s;
      }
      else {
        f[n][k]=sum_gerade?f[n][n-k]:g[n][n-k];
        g[n][k]=sum_gerade?g[n][n-k]:f[n][n-k];
      }
      //printf("%llu\t",f[n][k]);
      printf("%c",f[n][k]%2?'*':'.');
    }
    printf("\n");
  }

  printf("%llu\n",odd_triplets(1000000000000llu));
}

