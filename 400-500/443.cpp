#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

#define primeLim 40000000
#define target 1000000000000000LL

int main()
{
	vector<bool> sieve(primeLim);
	vector<int> prime;
	for(int i = 3; i < primeLim; i += 2) sieve[i] = 1;
	for(int i = 3; i < primeLim; i += 2)
		if(sieve[i])
		{
			for(int j = 3*i; j < primeLim; j += 2*i) sieve[j] = 0;
			prime.push_back(i);
		}
	cout << prime.size() << " primes generated." << endl;

	long long int a = 9;
	long long int g = 27;

	while(1)
	{
		long long int diff = g - a - 1;
		long long int factor = 0;
		for(vector<int>::iterator i = prime.begin(); i != prime.end() && *i**i <= diff; i++)
			if(diff % *i == 0)
			{
				factor = *i;
				break;
			}
		if(factor == 0) factor = diff;
		if(a + factor - (a % factor) > target) break;
		a += factor - ( a % factor );
		g += 2*factor - 1 - ( a % factor );
	}
	g += target - a;
	cout << target << " : " << g << endl;
	return 0;
}