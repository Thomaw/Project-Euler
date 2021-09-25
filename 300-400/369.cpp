#include<stdio.h>
#define N 52 
int b[]={0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
int binom[14][14]={0};

int choice[20],ci=0;

long long int x,total;

long long int f[N+1]={0};

char check() {  // is there a baduki with the ci+1 first choices
  int i=0,j=1,a=0,b=0,c=0,d=0;
  for(;i<=ci;i++,j*=2){
    if(choice[i]&1)a+=j;
    if(choice[i]&2)b+=j;
    if(choice[i]&4)c+=j;
    if(choice[i]&8)d+=j;
  }
  return 
    a&&b&&c&&d
    &&nb[a|b]>1&&nb[a|c]>1&&nb[a|d]>1&&nb[b|c]>1&&nb[b|d]>1&&nb[c|d]>1
    &&nb[a|b|c]>2&&nb[a|b|d]>2&&nb[a|c|d]>2&&nb[b|c|d]>2
    &&nb[a|b|c|d]>3;
}

void count(int ranks, int bits, int min, int rmin, long long int x) {
  int i;
  if(bits>N) return;
  if(!rmin) {
    f[bits]+=x;
    if(ranks<13)for(;min<=15;min++)count(ranks,bits,min,1,x);
  }
  else for(i=13-ranks;i>=rmin;i--)
    count(ranks+i,bits+b[min]*i,min+1,0,x*binom[13-ranks][i]);
}

void choose(int bits, int min) {
  int last,nlast,i,j;
  
  if(ci==13) return;
  
  if(min<15) choose(bits,min+1);
  
  choice[ci]=min;
  bits+=b[min];

  if(bits>N) return;

  if(ci>=3&&check()) {
    for(last=choice[i=ci];i>=0;i--) if(choice[i]!=last)break;
    
    x=1;last=choice[0];nlast=1;
    for(j=1;j<=i+1;j++) {
      if(choice[j]!=last||j==i+1){
        x*=binom[13-j+nlast][nlast];
        last=choice[j];nlast=0;
      }
      nlast++;
    }
    count(i+1,bits-(ci-i)*b[min],min,ci-i,x);
  }
  else {
    ci++;
    choose(bits,min);
    ci--;
  }
}

int main() {
  int n,i;
  binom[0][0]=1;
  for(n=1;n<14;n++){
    binom[n][0]=binom[n][n]=1;
    for(i=1;i<n;i++)binom[n][i]=binom[n-1][i-1]+binom[n-1][i];
  }

  ci=0;choose(0,1);
  
  for(n=0;n<=N;n++)
    printf("f(%d)=%lld total=%lld\n",n,f[n],total+=f[n]);
}