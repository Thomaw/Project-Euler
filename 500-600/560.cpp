#include "library/trivial.h"
#include "library/convolution.h"
#include "library/int-mod.h"
#include "library/util.h"

const int MOD = 1000000007;
typedef int_mod<MOD> im;

const int N = 1E7;
const int L = 20;

int rev[N];

struct st {
	vector<im> v;
	st() : v(1<<L, 0) {}
	void dft() {
		REP(i,0,L) {
			REP(f,0,1<<L) {
				if ((f&(1<<i)) == 0) {
					im a = v[f], b = v[f+(1<<i)];
					v[f] = a+b;
					v[f+(1<<i)] = a-b;
				}
			}
		}
	}
};

st pow(st a, ull n) {
	a.dft();
	REP(f,0,1<<L)
		a.v[f] = fastpow(a.v[f], n);
	a.dft();
	REP(f,0,1<<L)
		a.v[f] *= fastpow(fastpow(im(2), L), MOD-2);
	return a;
}

int main() {
	precompute(N);
	REP(i,0,(int)vprimes.size())
		rev[vprimes[i]] = i+1;
	rev[2] = 0;
	st a;
	REP(n,2,N)
		a.v[rev[dvd[n]]]++;
	a.v[1]++;
	printf("%lld\n", pow(a, N).v[0].v);
	return 0;
}