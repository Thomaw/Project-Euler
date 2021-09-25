#include<stdio.h>
#include<string.h>
#include<math.h>

long p[1070],s[1070];
int n,count,a[10000]={1,1};

void sieve(){
  int i,j;
  for(i=4;i<10000;i+=2) a[i]=1;
  for(i=3;i<10000;i+=2){
    if(!a[i]){
      for(j=2*i;j<10000;j+=i) a[j]=1;
      if(i>1000){
	a[i]=-n-1;
	p[n++]=i;
	}
      }
    }
  }

void main(){
  int i,j,k,x,y;
  char stat[11];
  sieve();
  for(i=0,stat[10]=0;i<n;i++){
    memset(stat,'0',10);
    for(j=p[i];j;j/=10) stat[j%10]++;
    for(j=0;j<10;j++) s[i]+=(stat[j]*pow10(j));
    }
  for(i=0;i<n-2;i++){
    for(j=i+1;j<n-1;j++){
      k=2*p[j]-p[i];
      if(k>=p[n-1]) break;
      if(s[i]==s[j]&&a[k]<0&&s[i]==s[-a[k]-1]){
	if(++count==2){
	  x=p[i];
	  y=p[j];
	  printf("%i%i%i\n",x,y,k);
	  break;
	  }
	}
      }
    if(count==2) break;
    }
  }
