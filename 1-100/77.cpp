public static void Main(string[] args)
{
	int i=1;
	while(part(++i,primes.Length-1) <= 5000);
	Console.WriteLine(i);
}
		
private static long part(long a, long b)
{
	if(a == 0)
		return 1;
	else if(a < 0 || b == 0)
		return 0;
	else return (part(a, b-1) +
	part(a-primes[b], b));
}