#include <iostream>
#include <set>

using namespace std;

int const L=12000;

int best[20*L]; // You don't need this much, but I didn't want to think how much you need

int product; // Using global variables is ugly but convenient

void process(int sum, int num){
  if(best[product-sum+num]>product)
    best[product-sum+num]=product;
}

void generate(int n, int k, int s, int num){
  for(;k*k<=n;++k){
    if(!(n%k)){
      int quotient=n/k;
      process(s+k+quotient,num+2);
      if(k*k<=quotient)
        generate(quotient,k,s+k,num+1);
    }
  }
}

int main(){
  for(int i=0;i<20*L;++i)
    best[i]=999999999;
  for(product=4;product<=2*L;++product)
    generate(product,2,0,0);
  set<int> s;
  for(int i=2;i<=L;++i)
    s.insert(best[i]);
  int sum=0;
  for(set<int>::const_iterator it=s.begin();it!=end();++it)
    sum+=*it;
  cout << sum << endl;
}