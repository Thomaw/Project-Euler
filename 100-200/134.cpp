int times[10];
long long findans(int p1, int p2)
{
	long long a, b, power;

	for(int i = 0; i < 10; i++)
		times[ (p2 * i) % 10 ] = i;
	
	a = 0;
	b = p1;
	power = 1;
	while( b )
	{
		a += p2 * times[ ((b % 10) - (a % 10) + 10) % 10 ];
		a /= 10;
		b /= 10;
		power *= 10;
	}
	return a * power + p1;
}