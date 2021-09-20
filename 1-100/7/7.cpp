#include "iostream"

int main(int argc, char** argv)
{
	unsigned int prime_nb = 2;
	unsigned long i = 5;
	unsigned int k;
	bool found;
	for(;;)
	{
		found = true;
		for(k = 2; k < i; ++k)
			if(!(i % k))
				found = false;
		if(found)
			++prime_nb;
		if(prime_nb >= 10001)
			break;
		i += 2; // all even numbers are not prime
	}
	std::cout << i;
	return 0;
}
