#include<iostream>

using namespace std;

  int steine[12]={3,6,3*8,6*8,3*64,6*64,9,72,9*2,72*2,9*4,72*4};

  int t[512][512]={0};

  int symm[512]={0};
  int sc[512]={0};

  int m0;

  int fill(int m, int last) {  // space at 0's
    t[symm[m^511]][m0]++;
    int i;
    for(i=last+1;i<12;i++)
      if((m&steine[i])==0){
        int mm=m|steine[i];
        fill(mm,i);
      }
  }

  int turn(int x) {
    int m=0;
    if(x&1) m|=4;
    if(x&2) m|=32;
    if(x&4) m|=256;
    if(x&8) m|=2;
    if(x&16) m|=16;
    if(x&32) m|=128;
    if(x&64) m|=1;
    if(x&128) m|=8;
    if(x&256) m|=64;
    return m;
  }
  int mirror(int x) {
    int m=0;
    if(x&1) m|=4;
    if(x&2) m|=2;
    if(x&4) m|=1;
    if(x&8) m|=32;
    if(x&16) m|=16;
    if(x&32) m|=8;
    if(x&64) m|=256;
    if(x&128) m|=128;
    if(x&256) m|=64;
    return m;
 }

int main() {
  for(int i=0;i<512;i++) if(!symm[i]) {
    int j=i;symm[i]=i;sc[i]++;
    j=turn(j);symm[j]=i;sc[j]++;
    j=turn(j);symm[j]=i;sc[j]++;
    j=turn(j);symm[j]=i;sc[j]++;
    j=mirror(i);symm[j]=i;sc[j]++;
    j=turn(j);symm[j]=i;sc[j]++;
    j=turn(j);symm[j]=i;sc[j]++;
    j=turn(j);symm[j]=i;sc[j]++;
  }

  for(m0=0;m0<512;m0++) // holes at 1's
    if(m0==symm[m0]) 
      fill(m0,-1);

  cout<<"A=[";
  for(int i=0;i<512;i++)if(i==symm[i]){
    if(i>0)cout<<";";
    for(int j=0;j<512;j++)if(j==symm[j]){
      if(j>0)cout<<",";
      cout<<t[i][j];
    }
  }
  cout<<"];b0=vectorv(length(A));b0[1]=1;(Mod(A,100000007)^10^10000*b0)[1]\n";    

}