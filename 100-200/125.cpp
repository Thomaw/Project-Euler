#include<stdio.h>
#include<string.h>
#include<math.h>

double total;
long data[7100],sum[7100],ans[200],n;
long i,j,k,l,len;

void main(){
  char a[10];
  for(i=1;i<7100;i++) data[i]=sum[i]=i*i;
  for(i=2;i<669;i++){
    for(j=1,k=i;;j++,k++){
      if(100000000-data[k]<sum[j]) break;
      sum[j]+=data[k];
      sprintf(a,"%li",sum[j]);
      for(len=strlen(a)-1,l=0;l<len;len--,l++){
	if(a[l]!=a[len]) break;
	}
      if(l>=len){
	for(len=0;len<n;len++){
	  if(ans[len]==sum[j]) break;
	  }
	if(len==n) ans[n++]=sum[j];
	}
      }
    }
  for(i=0;i<n;i++) total+=ans[i];
  printf("%.0lf\n",total);
  }