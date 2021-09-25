#include <cassert>
#include <iostream>
#include <map>
typedef unsigned long long int ull;
size_t const N=1000;
size_t const B=9;
size_t const S=1<<B;
size_t bits[S]={};
std::map<size_t, size_t> cache;


size_t solve(size_t bits_sum, size_t n, size_t front_bits_set, size_t tail_size)
{
	if(n<2*front_bits_set)
	{
		bits_sum+=bits[S-1]+front_bits_set;
		if(n<bits_sum)
			bits_sum=bits[0]+front_bits_set;
		else bits_sum=0;
		return bits_sum;
	}

	size_t k=S;
	size_t bs0=bits_sum;
	while(k--)
	{
		bits_sum+=bits[k]+front_bits_set+tail_size-B;
		if(n<bits_sum)
		{
			bits_sum=0;
			break;
		}
	}

	size_t &c=cache[(front_bits_set<<20)|(tail_size<<10)|(S-k)];
	if(!c)
	{
		if(tail_size==B)
		{
			while(k--)
			{
				bits_sum+=bits[k]+front_bits_set;
				if(n<bits_sum)
					bits_sum=0;
			}
			c=1024+ bits_sum;
			return bits_sum;
		}
		else
		{
			bits_sum=solve(bs0, n, front_bits_set+1, tail_size-1);
			bits_sum=solve(bits_sum, n, front_bits_set+0, tail_size-1);
			c=1024+ bits_sum;
			return bits_sum;
		}
	}
	return c%1024;
}


int main()
{
	for(size_t i=0; i<S; ++i)
		for(size_t n=i; n; n/=2)
			if(n&1)
				++bits[i];

	ull r=558; // n=[1, 10);
	for(size_t n=10; n<=N; ++n)
	{
		cache.clear();
		ull w=solve(0, n, 0, n+1);
		r+=w*w*w;
		// std::cout << n << " " << w << " " << r << std::endl;
	}
	std::cout << "N=" << N << ", r=" << r << std::endl;
	return 0;
}


/* e3500 3.0G, i686, g++ 4.6.2

8) g++ -O6 -DNDEBUG --std=c++0x do391.cc
8) time ./a.out
N=1000, r=61029882288
./a.out  217.71s user 0.29s system 100% cpu 3:37.99 total
8)

*/