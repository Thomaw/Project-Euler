#include<stdio.h>
typedef long long unsigned llu;

llu countY(int n, llu a); 
llu countX(int n, llu a) {
  llu ret;
  if(a<=0) ret=0;
  else if(a>=(1llu<<(n+1))) ret=0;
  else if(a==(1llu<<n)) ret=a;
  else if(a<(1llu<<n)) ret=countX(n-1,a)+countY(n-1,a);
  else {
    a-=(1llu<<n);
    ret=countX(n-1,a)+countY(n-1,(1llu<<n)-a);
  }
  return ret;
}

llu countY(int n, llu a) {
  llu ret;
  if(a<=(1llu<<n)) ret=0;
  else if(a>(1llu<<(n+1))) ret=0;
  else if(a==(1llu<<(n+1))) ret=a/2;
  else {
    a-=(1llu<<n);
    ret=countX(n-1,a)+2*countY(n-1,a)+countX(n-1,(1llu<<n)-a);
  }
  return ret;
}

llu posY(int n, llu a, llu b);
llu posX(int n, llu a, llu b) {
  llu c,ret;
  if(a==(1llu<<n)) {
    if(b==a) ret=(1llu<<(2*n));
    else if(b<=a/2) ret=posY(n-1,a,b);
    else ret=posY(n-1,a,b-a/2)+(1llu<<(2*n-1));
  }
  else if(a<(1llu<<n)) {
    c=countX(n-1,a);
    if(b<=c) ret=posX(n-1,a,b);
    else ret=posY(n-1,a,b-c);
  }
  else {
    a-=(1llu<<n);
    c=countX(n-1,a);
    if(b<=c) ret=posX(n-1,a,b)+(1llu<<(2*n-1));
    else ret=posY(n-1,(1llu<<n)-a,b-c)+(1llu<<(2*n-1));
  }
  return ret;
}

llu posY(int n, llu a, llu b) {
  llu c,ret;
  a-=(1llu<<n);
  if(a==(1llu<<n)) {
    if(b==a) ret=(1llu<<(2*n+1));
    else if(b<=a/2) ret=posY(n-1,a,b)+(1llu<<(2*n));
    else ret=posY(n-1,a,b-a/2)+(3llu<<(2*n-1));
  }
  else {
    c=countX(n-1,a);
    if(b<=c) ret=posX(n-1,a,b)+(1llu<<(2*n));
    else {
      b-=c;
      c=countY(n-1,a);
      if(b<=c) ret=posY(n-1,a,b)+(1llu<<(2*n));
      else {
        b-=c;
        c=countX(n-1,(1llu<<n)-a);
        if(b<=c) ret=posX(n-1,(1llu<<n)-a,b)+(3llu<<(2*n-1));
        else ret=posY(n-1,a,b-c)+(3llu<<(2*n-1));
      }
    }
  }
  return ret;
}

llu g(llu a,llu b) {
  llu j=0,j2=1;
  while(j2<a) {j++;j2*=2;}
  return posX(j,a,b)-1;
}

int main() {
  printf("%lld\n",g(3,3)); 
  printf("%lld\n",g(4,2));
  printf("%lld\n",g(54321,12345));

  llu a=1,b=1,c,j2,sum=0,i;
  for(i=2;i<=45;i++) {
    c=a+b; b=a; a=c;
    sum+=g(a,b);
    printf("i=%lld a=%lld b=%lld sum=%lld\n",i,a,b,sum);fflush(stdout);
  }
}