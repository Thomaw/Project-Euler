#include <stdio.h>

long long gcd(long long a, long long b)
{ return b ? gcd(b, a%b) : a; }

long long lcm(long long a, long long b)
{ return a * (b / gcd(a, b)); }

long long p(int s, long long n)
{
	long long l = 1;
	int i;
	for (i = 2; i <= s; i++)
		l = lcm(i, l);
	return (n - 2) / l - (n - 2) / lcm(l, s + 1);
}

int main()
{
	long long result = 0;
	for (int i = 1; i <= 31; i++) {
		result += p(i, 1LL << (2*i));
	}
	printf("%lld\n", result);
	return 0;
}