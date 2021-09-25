#include <stdio.h>
#define p 61LL
#define power 10LL
#define q 10000000LL
long long T[q+10];
long long pp[30];
long long ans;
long long c,n,m;
int main(){
/*Calculate powers of p*/
pp[0]=1;
for(c=1;c<25;c++) pp[c]=p*pp[c-1];
/*Calculate T[n]*/
T[0]=290797;
for(c=1;c<=q+5;c++){
  T[c]=(T[c-1]*T[c-1])%50515093;
  T[c-1]%=p;
}

/*Calculate answer by adding up the relevant things
  and ignoring the terms that will be modded out*/
for(n=1;n<=q;n++)
for(m=n;(m<n+power)&&(m<=q);m++){
  ans+=T[m]*pp[m-n];
  ans%=pp[power];
}

printf("%lld\n",ans);
return 0;
}