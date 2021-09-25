#include "../framework/number_theory.cpp"
#include <algorithm>

struct RAD
{
	int rad;
	int n;
};

bool operator<(const RAD& a, const RAD& b)
{
	if (a.rad > b.rad)
	{
		return 0;
	}
	else if (a.rad == b.rad)
	{
		return (a.n < b.n);
	}
	else
	{
		return 1;
	}
}

int main()
{
	const int MAX_N = 100000;
	int nr_of_primes;
	int* primes;
	RAD* rad_list = new RAD [MAX_N+1];
	primes = sieve(MAX_N+1, nr_of_primes);
	
	for (int i=0; i<=MAX_N; i++)
	{
		rad_list[i].rad = 1;
		rad_list[i].n = i;
	}
	for (int i=0; i<nr_of_primes; i++)
	{
		for (int j=primes[i]; j<MAX_N; j+=primes[i])
			rad_list[j].rad*=primes[i];
	}
	std::sort(rad_list, rad_list+MAX_N+1);
	printf("%d\n", rad_list[10000].n);
	return 0;
}