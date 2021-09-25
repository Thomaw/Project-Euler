#include<stdio.h>

int length,sum,count,a[205],data[205]={1};

int push(int pos){
  for(int i=0;i<pos;i++){
    data[pos]=data[pos-1]+data[i];
    if(!a[data[pos]]&&data[pos]<=200){
      a[data[pos]]=1;
      sum+=pos;
      if(++count==200) return 1;
      }
    if(pos!=length){
      if(push(pos+1)) return 1;
      }
    }
  return 0;
  }

void main(){
  for(length=count=1;!push(1);length++);
  printf("%i\n",sum);
  }