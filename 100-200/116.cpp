#include<stdio.h>
int unit,j,base;
double sum,save[55];
void main(){
  for(unit=2;unit<5;unit++){
    save[unit-1]=0;
    for(j=unit,base=1;j<51;j++,base++) save[j]=save[j-1]+base+save[j-unit];
    sum+=(save[50]-save[49]);
    }
  printf("%.0lf\n",sum);
  }