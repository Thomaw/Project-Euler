#include <cassert>
#include <iostream>
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;
uint const M=87654321;
uint const offs[6]={86,118,150,182,216,252};

ull mul_mod(ull a, ull b, ull m)
{
	assert(0<m && a<m && b<m && m<(1ull<<63));
	long double x=a;
	ull c(x*b/m);
	ll r=ll(a*b-c*m)%ll(m);
	return r<0?r+m:r;
}

ull pow_mod(ull a, ull e, ull m)
{
	ull r=1;
	while(e)
	{
		if(e&1)
			r=mul_mod(r,a,m);
		if(e/=2)
			a=mul_mod(a,a,m);
	}
	return r;
}

ll euclidean(ll &x, ll &y, ull a, ull b)
{
	if(b==0)
	{
		x=1;
		y=0;
		return a;
	}
	ll d=euclidean(x,y,b,a%b);
	ll t=x;
	x=y;
	y=t-(a/b)*y;
	return d;
} 

ull inv_mod(ull a, ull m)
{
	ll x,y;
	ll g=euclidean(x,y,a,m);
	assert(g==1);
	if(g==1)
	{
		if(x<0)
			x+=m;
		return ull(x);
	}
	return 0;
}

main()
{
	uint const P=7299372;
	ull const L=1e18;
	ull Y=P/6;
	ull K=ull(Y)*M;
	ull z=inv_mod(200,M);
	ull mi=inv_mod(Y%M,M);
	ull yi=inv_mod(M%Y,Y);
	ull r=0;
	for(uint d=0; d<6; ++d)
	{
		for(ull y=0,e2=1<<(6+d+1); y<Y; ++y)
		{
			ull b=(e2+M-offs[d])%M;
			ull m=b*z%M;
			ull k=(mul_mod(m*Y,mi,K)+mul_mod(y*M,yi,K))%K;
			ull n=6*(k+1)+d;
			if(n<=L)
				r+=(L-n)/(6*K)+1;
			e2=e2*64%M;
		}
	}
	std::cout << double(L) << "=" << L << " " << r << std::endl;
}

/*
8) g++ -O6 wat.cc
8) time ./a.out
1e+18=1000000000000000000 11408450515
./a.out  0.92s user 0.00s system 99% cpu 0.919 total
8)
*/