#include<stdio.h>

double a[52][52],sum;
int i,j,k,l,base;

void main(){
  for(i=3,base=1;i<=50;i++,base++){
    for(j=3,sum=0,k=base;k;j++,k--){
      sum+=k;
      for(l=i-4;l>=i-j-1&&l>2;l--){
	if(a[l][j]) a[i][j]+=a[l][j];
	else a[i][j]+=a[l][l];
	}
      a[i][j]+=sum;
      if(j<=i-1) a[i][j]+=a[i-1][j];
      else a[i][j]+=a[i-1][i-1];
      }
    }
  printf("%.0lf\n",a[50][50]-a[49][49]+1);
  }