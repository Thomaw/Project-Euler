#include<stdio.h>
#include<math.h>

long p[4800]={2,3};

void prime(){
  long a;
  int l=1,i,c;
  for(a=5;;a+=2){
    c=sqrt(a);
    for(i=1;p[i]<=c;i++){
      if(a%p[i]==0) c=0;
      }
    if(c){
      p[++l]=a;
      if(a>366) break;
      }
    }
  }

void main(){
  long i,j,l;
  int k,quadruplet=0,count=0;
  prime();
  for(i=210;quadruplet!=4;i++){
    j=sqrt(i);
    l=i;
    for(k=0,count=0;p[k]<=j;k++){
      if(l%p[k]==0){
	while(l%p[k]==0) l/=p[k];
	count++;
	}
      }
    if(l>1) count++;
    if(count==4) quadruplet++;
    else quadruplet=0;
    }
  printf("%li %li %li %li\n",i-4,i-3,i-2,i-1);
  }
