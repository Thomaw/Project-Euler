#include<cstdio>
#include<vector>
#include<map>
#include<set>
#define N 1000000000

long long gcd ( long long a, long long b ) {
  long long t ;
  if (a<0) a=-a; if (b<0) b=-b;
  if (a<b) { t=a; a=b; b=t; }
  while ( b!=0 ) { t = a%b; a=b; b=t; }
  return a;
}

long long prime[1000000],nprimes=0;
inline void compute_primes() {
  prime[nprimes++]=2;
  for (long long i=3;i*i<=N;i+=2) {
    bool isprime = true ;
    for (int j=0;j<nprimes && prime[j]*prime[j]<=i;++j)
      if ( i%prime[j]==0 ) {isprime=false;break;}
    if (isprime) prime[nprimes++]=i;
  }
}

std::vector<long long> factors; //only small ones
std::map<long long, int> factorization;
typedef std::map<long long, int>::iterator f_iter;
inline void search_factors ( f_iter pos, long long curr, long long upperbound ) {
  if ( pos==factorization.end() ) {factors.push_back(curr);return;}
  f_iter next = pos; ++next;
  for (int i=0;i<=pos->second;++i) {
    search_factors(next,curr,upperbound);
    curr*=pos->first;
    if (curr>upperbound) break;
  }
}

inline void make_factorization ( long long value ) {
  factorization.clear();
  for ( int i=0;i<nprimes;++i) {
    int p = prime[i];
    if ( p*p>value ) break;
    while (value%p==0) {++factorization[p];value/=p;}
  }
  if (value!=1) ++factorization[value];
}

inline void compute_factors( long long value, long long upperbound ) {
  make_factorization(value);
  search_factors(factorization.begin(),1,upperbound);
}

long long num_factors ( long long value ) {
  long long ret = 1 ;
  make_factorization(value);
  for (f_iter f_i=factorization.begin();f_i!=factorization.end();++f_i) {
    ret *= 1+f_i->second;
  }
  return ret;
}

std::set<std::pair<long long,long long> > seen;
long long solutions ( long long k ) {
  long long count=0,a,b,d,g;
  compute_factors(k*k,k);
  for (int i=0;i<factors.size();++i) {
    d = factors[i];
    for (int j=0;j<2;++j,d=-d) {
      b = d+k; a=(k*k)/d+k;
      if (a*b!=k*(a+b)) continue;
      if (b<=0 || a<=0) continue;
      std::pair<int,int> entry ( a<b? std::make_pair(a,b): std::make_pair(b,a) ) ;
      if (seen.find(entry)!=seen.end()) continue;
      seen.insert(entry);
      count+=num_factors(gcd(a,b));
    }
  }
  return count;
}

int main() {
  compute_primes();
  long long total = 0 ;
  for ( long long x = 10; x<=N; x*=10 ) total += solutions(x);
  printf("%lld\n",total);
}