#include <cstdio>
#include <iostream>
#include <vector>
#include "combinatorics.h"
size_t const D=6;
size_t const N=30;


size_t ds[32]={};
size_t dn[32][6]={};


size_t gc[32]={};
void gen(size_t a, size_t b, size_t c,
	size_t v=0, size_t pa=0, size_t pb=0, size_t pc=0,
	size_t sa=0, size_t sb=0, size_t sc=0,
	size_t wab=0, size_t wbc=0, size_t wca=0,
	size_t oa=0, size_t ob=0, size_t oc=0)
{
	if(sa<=sb && ob<oa || sa<=sc && oc<oa)
		return;
	if(wab+6*(D-sb)<=18 || wbc+6*(D-sc)<=18 || wca+6*(D-sa)<=18)
		return;
	if(pa<ds[a] || pb<ds[b] || pc<ds[c])
	{
		for(size_t i=1; i<=7; ++i)
		{
			bool ia=i&1;
			bool ib=i&2;
			bool ic=i&4;
			if((!ia || pa<ds[a]) && (!ib || pb<ds[b]) && (!ic || pc<ds[c]))
			{
				size_t dsa=ia*dn[a][pa];
				size_t dsb=ib*dn[b][pb];
				size_t dsc=ic*dn[c][pc];
				size_t oa2=oa;
				size_t ob2=ob;
				size_t oc2=oc;
				for(size_t j=0; j<dsa; ++j)
					oa2=oa2*32+v;
				for(size_t j=0; j<dsb; ++j)
					ob2=ob2*32+v;
				for(size_t j=0; j<dsc; ++j)
					oc2=oc2*32+v;
				gen(a, b, c, v+1,
					pa+ia, pb+ib, pc+ic,
					sa+dsa, sb+dsb, sc+dsc,
					wab+sa*dsb, wbc+sb*dsc, wca+sc*dsa,
					oa2, ob2, oc2);
			}
		}
	}
	else if(18<wab && 18<wbc && 18<wca)
		++gc[v];
}


int main()
{
	binomials_ull B;

	for(size_t i=0; i<32; ++i)
	{
		ds[i]=1;
		dn[i][0]=1;
		for(size_t b=0; b<5; ++b)
		{
			ds[i]+=(i>>b)&1;
			++dn[i][ds[i]-1];
		}
	}
	for(size_t a=0; a<32; ++a)
		for(size_t b=0; b<32; ++b)
			for(size_t c=0; c<32; ++c)
				gen(a, b, c);
	ull r=0;
	for(size_t i=0; i<32; ++i)
		if(gc[i])
		{
			ull d=gc[i]*B(N, i);
			r+=d;
			std::cout << i << " " << gc[i] << " " << d << "\n";
		}

	std::cout << "N=" << N << ", r=" << r << "\n";
	return 0;
}


/* e3500 3.0G, i686, g++ 4.6.2

8) g++ -O6 -std=c++0x do376.cc
8) time ./a.out
5 15 2137590
6 491 291543525
7 6028 12271802400
8 40974 239817748950
9 178508 2553940732200
10 535887 16100732953305
11 1152344 62949441391200
12 1808978 156464341174050
13 2082342 249380965568700
14 1741403 253239482513025
15 1030705 159880403451600
16 409596 59564545989300
17 98092 11747483206200
18 10705 925909973625
N=30, r=973059630185670
./a.out  6.48s user 0.00s system 99% cpu 6.483 total
8)
*/