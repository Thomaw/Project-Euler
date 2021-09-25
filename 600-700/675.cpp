#include <iostream>
#include "lib/field.cpp"
#include "lib/primes.cpp"
using namespace std;
constexpr long long N = 10000000;
constexpr long long M = 1000000087;
using F =Field<M>;

F S(const map<long long, long long> &fs){
	F a = 1;
	for(auto& [p,e]: fs) a*=1+2*e;
	return a;
}

int main(){
	sieve(N);

	F a = 0;
	F s = 1;
	map<long long, long long> factors;
	for(long long n = 2; n <= N; ++n){
		for(auto [p,e]: factor(n)){
			auto o = factors[p];
			auto n = o + e;
			factors[p] = n;
			s /= 1+2*o;
			s *= 1+2*n;
		}
		a += s;
	}
	cout << a << endl;
}
