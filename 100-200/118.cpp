#include <iostream>

#define uint unsigned int 

using namespace std;

const uint length = 9;
uint digits[length] = {1,2,3,4,5,6,7,8,9};
uint counter = 0;

bool prime(uint n)
{
	if(n > 2 && n % 2 == 1)
	{
		for(uint i = 3; i * i <= n; i += 2)
			if(n % i == 0)
				return false;
		return true;
	}
	else if(n == 2)
		return true;

	return false;
}

uint fac(uint n)
{
	return (n ? n * fac(n - 1) : 1);
}

void permutation_generator()
{
	uint j = length - 2;
	while(digits[j] > digits[j + 1])
		j--;

	uint k = length - 1;
	while(digits[j] > digits[k])
		k--;

	swap(digits[j], digits[k]);

	uint r = length - 1;
	uint s = j + 1;
	while(r > s)
	{
		swap(digits[r], digits[s]);
		r--;
		s++;
	}
}

/* low is included and high is excluded */
uint convert(uint low, uint high)
{
	uint nr = 0;
	for(uint i = low; i < high; i++)
	{
		nr *= 10;
		nr += digits[i];
	}
	return nr;
}

void count(uint i, uint max, uint last)
{
	for(uint j = min(i + max, length); j > i; j--)
	{
		uint nr = convert(i,j);
		if(prime(nr) && (j - i < max || nr > last))
		{
			if(j == length)
				counter++;
			else
				count(j, j - i, nr);
		}
	}
}

int main(int argc, char** argv)
{	
	uint max = fac(length);
	count(0, length, 0);
	for(uint i = 1; i < max; i++)
	{	
		permutation_generator();
		count(0, length, 0);
	}

	cout << counter << endl;
}