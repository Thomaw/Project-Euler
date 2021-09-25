#include<stdio.h>
#include<stdlib.h>

/*
#define N 50
#define M 1000
#define D 123
*/
/*
#define N 100000
#define M 1000
#define D 432
*/
//*
#define N 1000000
#define M 100000
#define D 65432
//*/
#define MOD 10000000000000061ll

typedef long long LL;

int main() {
  char *isprime;
  int *primes,*powers,nprimes;
  LL *freq,*freq_;

  LL i,j,k,k_,p,a,jmax,f,jlast,M2,D2;

  isprime = malloc((N+1)*sizeof(char));
  primes = malloc((N+1)*sizeof(int));
  powers = malloc((N+1)*sizeof(int));
  nprimes = 0;
  
  freq = malloc(M*sizeof(LL));
  freq_ = malloc(M*sizeof(LL));
  for(i=0;i<M;i++) freq[i]=freq_[i]=0;
  freq[1]=1;

  for(i=0;i<=N;i++) isprime[i]=1;
  isprime[0]=isprime[1]=0;
  for(i=2;i<=N;i++) {
    if(isprime[i]) {
      p=i;
      
      primes[nprimes]=p;
      for(j=p;j<=N;j*=p) powers[nprimes]+=N/j;
      nprimes++;
      
      for(j=p*p;j<=N;j+=p) isprime[j]=0;
    }
  }

  M2=M;
  D2=D;

  // init at p=2
  i=0; p=2; 
  for(j=1,a=p;j<=powers[i];j++) {
    freq[a]++;
    a*=p; if(a>=M)a%=M;
  }

  // reduce DP if p divides gcd(D,M)
  if(M2%p==0){
    int l=1;
    while(M2%(p*l)==0 && D2%(p*l)==0) l*=p;
    if(l>1) {
      int j1,j2;
      for(j1=0,j2=0;j2<M2;j1++,j2+=l) freq[j1]=freq[j2];
      D2/=l;M2/=l;
    }
  }

  for(i=1;i<nprimes;i++) {

    // for the sake of generality I'd like to move 
    // previous block (reduction of DP) to this place
    // but this means 4x increase of runtime !!! ???
    // is it a problem of GCC optimization?

    p=primes[i];

    // consider 5 
    if(M2%p==0 && D2%p!=0) continue;

    // prerun to possibly find p^x==1(mod M)
    jmax=jlast=powers[i];f=1;
    for(j=1,a=1;j<=powers[i];j++) {
      a*=p; if(a>=M2)a%=M2;
      if(a==1) {jmax=j-1;jlast=powers[i]%j;f=powers[i]/j+1;break;}
    }

    for(j=0;j<M2;j++) freq_[j]=0;
    for(j=0,a=1;j<=jmax;j++) {
      for(k=0;k<M2;k++) {
        k_=k*a%M2;
        freq_[k_] += freq[k]*(f-(j>jlast));
        if(freq_[k_]>=MOD) freq_[k_]%=MOD;
      }
      a*=p; if(a>=M2)a%=M2;
    }
    for(j=0;j<M2;j++) freq[j]=freq_[j];
  }

  printf("\n%lld\n",freq[D2]);
}