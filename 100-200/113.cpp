#include<stdio.h>

double down[15]={1,1,1,1,1,1,1,1,1,1};
int i,j;

void main(){
  for(i=1;i<=100;i++){
    for(j=1;j<10;j++) down[j]+=down[j-1];
    down[10]+=(down[9]+down[8]-10);
    }
  printf("%.0lf\n",down[10]);
  }