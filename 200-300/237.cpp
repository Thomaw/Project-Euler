#include <stdio.h>
#include <string.h>
/*
eight possible transitions
0: 0-> 3<-
1: 0-> 1<-
2: 2-> 3<-
3: 1-> 2<-
4: 0-> 1<- 2-> 3<-
5: 0-> 3<- 2-> 1<-
6: 2-> 1<- 0-> 3<-
7: end

ways from transition x to transition y, that pass through all squares between
*/
long long int ways[7][8]={
  {0,1,1,1,1,0,0,1},
  {1,0,0,0,0,1,0,0},
  {1,0,0,0,0,0,1,0},
  {1,0,0,0,0,0,0,0},
  {0,1,1,0,1,0,0,1},
  {1,0,0,0,0,1,0,0},
  {1,0,0,0,0,0,1,0},
};

long long int x10[7][8];

int y; // global goal for recursive count()
long long int count(int level,int t0) {
  if (level==0) return ways[t0][y];

  long long int sum=0;

  for (int t1=0;t1<7;t1++)
    if (ways[t0][t1])
      sum+=ways[t0][t1]*count(level-1,t1);
  
  return sum%100000000;
}

int main() {

  for (int power=1;power<=12;power++) {
    for (int x=0;x<7;x++) for (y=0;y<8;y++)
      x10[x][y]=count(4,x);  // *5
    memcpy(ways,x10,sizeof(long long int)*72);

    for (int x=0;x<7;x++) for (y=0;y<8;y++)
      x10[x][y]=count(1,x);  // *2
    memcpy(ways,x10,sizeof(long long int)*72);
  }

  printf("%d->%d %lld\n",0,7,ways[0][7]);
}