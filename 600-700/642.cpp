#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
typedef unsigned int uint;
typedef unsigned long long ull;
ull const N=201820182018ull;
uint const P=450e3;
uint const B=5e4;
uint const mod=1e9;

std::vector<bool> is_p(P,1);
std::vector<uint> primes;

void gen_primes()
{
	for(uint p=2; p<P; ++p)
		if(is_p[p])
		{
			primes.push_back(p);
			for(ull n=ull(p)*p; n<P; n+=p)
				is_p[n]=0;
		}
	std::cout << P << " " << primes.size() << std::endl;
}

void kampjutah(ull &tr, uint ta, uint tm)
{
	ull r=0;
	ull const dp=1e9;
	ull np=dp;
	for(ull b=2+ta*B; b<N; b+=tm*B)
	{
		ull br=0;
		ull e=b+B;
		std::vector<ull> bs(B);
		for(uint i=0; i<B; ++i)
			bs[i]=b+i;
		for(uint p: primes)
		{
			ull pb=(b+p-1)/p*p;
			for(uint k=pb-b; k<B; k+=p)
				if(1<bs[k])
				{
					bs[k]/=p;
					while(bs[k]%p==0)
						bs[k]/=p;
					if(bs[k]==1 && b+k<=N)
						br+=p;
				}
		}
		for(uint i=0; i<B; ++i)
			if(1<bs[i] && b+i<=N)
				br+=bs[i];
		r=(r+br)%mod;

		if(np<e)
		{
			np+=dp;
			std::cout << ta << " " << double(e)/N << " [" << b << "," << e << ") " << br << " " << r << std::endl;
		}
	}
	tr=r;
}

int main()
{
	assert(N/P<P);
	assert(double(B)*N<1e18);
	gen_primes();

	uint T=6;
	std::vector<std::thread> threads(T);
	std::vector<ull> tr(T,0);
	for(uint i=0; i<T; ++i)
		threads[i]=std::thread(&kampjutah,std::ref(tr[i]),i,T);
	ull r=0;
	for(uint i=0; i<T; ++i)
	{
		threads[i].join();
		r+=tr[i];
	}
	std::cout << N << " " << r%mod << std::endl;
	return 0;
}