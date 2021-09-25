#include <iostream>
typedef unsigned __int64 u64;
#define M 410338673 // 17^7
#define L 152370032 // Mod[10^Mod[10^18, 193100552], 193100552]
// the same code used to calculate period == 193100552
void main() {
  u64 f=0,e=0;
  for(u64 n=2;n<=L;n++) {
    e=(e+1+(n&1))*2%M;      // number of edge points
    f=(f*4+e)%M;              // 4 mirrors of previous iteration + edge points
  }
  std::cout<<f; 
}