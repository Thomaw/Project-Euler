
#include<stdio.h>

char num[10000],polygon[10],exist[105];
int eight[40],sum;

struct node{
  int back[10][5];
  }number[105];

void generate_polygonal(){
  int index,i,j,k;

//generating members of 3-7 gonal
  for(index=3;index<8;index++){
    for(i=1;;i++){
      switch(index){
	case 3: j=i*(i+1)/2;break;
	case 4: j=i*i;break;
	case 5: j=i*(3*i-1)/2;break;
	case 6: j=i*(2*i-1);break;
	case 7: j=i*(5*i-3)/2;break;
	}
      if(j>9999) break;
      if(j>999&&j%100>9){
	for(k=0;number[j/100].back[index][k];k++);
	number[j/100].back[index][k]=j%100;
	exist[j/100]++;
	}
      }
    }

//generating the members of octagonal
  for(i=1,k=0;;i++){
    j=i*(3*i-2);
    if(j>9999) break;
    if(j>999&&j%100>9) eight[k++]=j;
    }
  }

int solve(int front, int pos){
  int i,j,k;
  for(i=3;i<8;i++){
    if(!polygon[i]){
      for(j=0;number[front].back[i][j];j++){
	k=number[front].back[i][j];
	if(exist[k]){
	  if(pos==6){
	    if(k==eight[35]){
	      sum+=front*100+k;
	      return 1;
	      }
	    return 0;
	    }
	  polygon[i]=1;
	  num[front*100+k]=1;
	  if(solve(k,pos+1)){
	    sum+=front*100+k;
	    return 1;
	    }
	  num[front*100+k]=0;
	  polygon[i]=0;
	  }
	}
      }
    }
  return 0;
  }

void main(){
  generate_polygonal();
  for(int i=0;eight[i];i++){
    if(exist[eight[i]%100]){
      num[eight[i]]=1;
      eight[35]=eight[i]/100;
      if(solve(eight[i]%100,2)) break;
      num[eight[i]]=0;
      }
    }
  printf("%i\n",sum+eight[i]);
  }
/* 1281 (P8,21), 8128 (P6,64), 2882 (P5,44), 8256 (P3,128), 5625 (P4,75), 2512 (P7,32)*/
