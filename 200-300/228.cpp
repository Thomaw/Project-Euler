#include <stdio.h>

// return numbers of coprimes less than n
int coprimes(int n) {
  int p=2,count=1;
  while (p*p<=n || (p=n)>1) {
    if (n%p==0) {
      n/=p;
      count*=(p-1);
      while (n%p==0) {n/=p;count*=p;}
    }
    p++;
  }
  return count;
}

int main(int argc, char **args) {
  int from=1864,to=1909;
  //sscanf(args[1],"%d",&from);sscanf(args[2],"%d",&to);

  int b,s,denominators;
  s=(from-1+to-1)*(to-from+1)/2;  // all fractions 
  
  for (b=2;b<=to-from;b++) {
    denominators=to/b-(from-1)/b;     // denominators in range
    s-=(denominators-1)*coprimes(b);
  }

  printf("%d different fractions\n",s+1); // and 0
}
