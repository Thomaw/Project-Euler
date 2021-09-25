#include<stdio.h>
#define int long long unsigned

int p10(int x){
  int i=1;
  while(x--)i*=10;
  return i;
}

int n2pos(int n){
  int lim=1,d=1,pos=1;
  while(1){
    if(n<=10*lim)return pos+d*(n-lim);
    pos+=9*lim*d;
    lim*=10;
    d++;
  }
}

typedef struct{
  int n,maxsteps,steps,mod,next;
} pattern;

int teste(int n, int x, int y,int count) {
  pattern p[x+y],*pp;
  int i,imin,a,b,c,d;
  
  a=p10(x+y-1);
  c=p10(x); 
  d=9*p10(y-1);
  for(i=0,b=1; i<y; i++,b*=10)
    p[i]=(pattern){a+n*b,d,0,b,(c-1)*b};

  d=p10(y);
  p[y]=(pattern){n*b,d,0,b,(c-1)*b};

  for(i=y+1,b=1;i<x+y;i++){
    b*=10;c/=10;
    p[i]=(pattern){(n%b)*c*d+(n/b),d,0,1,c-1};
  }

  d*=p10(x-1);
  for(i=0;i<x+y;i++)
    if(p[i].n<d) p[i].maxsteps=0; // leading 0 in pattern, drop

  while(1){
    // find smallest pattern
    imin=0;while(!p[imin].maxsteps)imin++;
    for(i=imin+1;i<x+y;i++){
      if(p[i].n==p[imin].n)fprintf(stderr,"collision\n");
      if(p[i].maxsteps)if(p[i].n<p[imin].n)imin=i;
    }

    pp=p+imin;
    if(++count==n)
      return n2pos(pp->n)+((imin<=y)?y-imin:imin);
   
    // next number in pattern 
    pp->n++;
    pp->maxsteps--;
    if(++(pp->steps) == pp->mod) {
      pp->steps = 0;
      pp->n += pp->next;
    }
  }
}

main() {
  int n=1,x=1,y,i,j,count,dcount,s=0,zeroes;
  for(i=0;i<13;i++) {
    n*=3;//n=7780;
    while(n>=p10(x))x++;
    
    for(j=1,x=0,zeroes=0; j<n; j*=10,x++) // count digits and zeroes
      if(n%(10*j)<j)zeroes++;
    
    count=x-zeroes;
    if(n==243)count++;
    
    for(y=1;count<n;count+=dcount,y++) // how many more digits
      dcount=(x+y-zeroes)*p10(y)-y*p10(y-1);
    
    s+=teste(n,x,y-1,count-dcount);
  }
  printf("%llu\n",s);
}