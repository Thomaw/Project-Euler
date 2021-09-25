#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>

#define p 1000000007
//#define N 16
//#define N 1000
#define N 10000000

#define Nia 4000
typedef long long LL;
typedef struct{ LL a,b,c,d; } LL4;
typedef struct{ LL x,y; } LL2;

LL2 ia[Nia];
LL cnt[Nia],nia=0,limit;
LL *fak,*_fak;

LL max(LL a, LL b) {return (a<b)?b:a;}

int cmp(const void *aa, const void *bb) {
  LL2 *a = (LL2*) aa;
  LL2 *b = (LL2*) bb;

  if(a->x < b->x) return -1;
  if(a->x > b->x) return 1;
  
  if(a->y < b->y) return -1;
  if(a->y > b->y) return 1;

  return 0;
}

void add(LL x, LL y) {
  LL h,i;
  if(y<x){h=x;x=y;y=h;}
  for(i=1;i*i*y<=N;i++) {
    ia[nia++]=(LL2){i*i*x,i*i*y};
    assert(nia<Nia);
  } 
}

void gen(LL a, LL b, LL c) {
  if(c*c > limit) return;

  if(a*a<=N && b*b<=N) add(a*a,b*b);

  LL d,e,f,g;
  g=2*(a+b+c);   gen( d=g-a, e=g-b, f=g+c );
  g=2*(a*=2);    gen( d-a, e-g, f-g );
  g=2*(b*=2);    gen( d-g, e-b, f-g );
}

LL4 gcde(LL x, LL y) {
  LL a=1,b=0,c=0,d=1,z,e,f,g;
  while(y){
    z=x/y;
    e=a-z*c;a=c;c=e;
    f=b-z*d;b=d;d=f;
    g=x-z*y;x=y;y=g;
  }
  return (LL4){a,b,c,d};
}

LL val(LL m, LL n) {
  if(m<0 || n<0) return 0;
  return fak[m+n]*_fak[m]%p*_fak[n]%p;
}

int main() {
  LL i,j,_i,x,y,c;
  
  fak=(LL*)malloc((2*N+1)*sizeof(LL));
  _fak=(LL*)malloc((2*N+1)*sizeof(LL));
  
  limit=2*N; 
  gen(3,4,5); 

  qsort(ia,nia,sizeof(LL2),cmp);

  fak[0]=_fak[0]=1;
  for(i=1;i<=2*N;i++) {
    _i=gcde(i,p).a; if(_i<0)_i+=p;
    fak[i]=fak[i-1]*i%p;
    _fak[i]=_fak[i-1]*_i%p;
  }

  ia[nia++]=(LL2){N,N};
  for(i=0;i<nia;i++) cnt[i]=val(ia[i].x,ia[i].y);

  for(i=0;i<nia-1;i++) {
    x=ia[i].x;
    y=ia[i].y;
    c=cnt[i];

    for(j=i+1;j<nia;j++) {
      cnt[j] -=
        c*(val(ia[j].x-x,ia[j].y-y)+val(ia[j].x-y,ia[j].y-x))%p;
      if(cnt[j]<0)cnt[j]+=p;
    }
  }

  printf("%lld\n",cnt[nia-1]);
  return 0;
}