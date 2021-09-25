#include<stdio.h>
#include<time.h>

const int fibnum = 93;
long long fib[fibnum] = {0};

long long Sumf(long long n, long long mod);
long long SumF[fibnum] = {0};
long long Modulus = 282475249; //7^10

long long Sumfm(long long n, long long mod);
long long SumFM[fibnum] = {0};

long long Sumff(long long n, long long mod);
long long SumFF[fibnum] = {0};

int main()
{
	int i;
	long long answer = 0;
	
	double time=clock();

	fib[0] = 0;
	fib[1] = 1;
	for(i = 2; i < fibnum; i++)
		fib[i] = fib[i-1] + fib[i-2];

	SumF[0] = 0;
	SumF[1] = 1;
	SumF[2] = 1;
	SumF[3] = 2;

	for(i = 4; i < fibnum; i++)
		SumF[i] = (SumF[i-1] + SumF[i-2] + (fib[i-2]%Modulus)*(fib[i-2]%Modulus))%Modulus;

	SumFM[0] = 0;
	SumFM[1] = 1;
	SumFM[2] = 1;
	SumFM[3] = 3;

	for(i = 4; i < fibnum; i++)
		SumFM[i] = (SumFM[i-1] + SumFM[i-2] + (fib[i-1]%Modulus) * ((fib[i-2]%Modulus) * (fib[i-2]%Modulus) % Modulus + SumF[i-2]) + (fib[i-2]%Modulus)*(fib[i-2]%Modulus + 1) / 2 % Modulus * (fib[i-2]%Modulus))%Modulus;

	SumFF[0] = 0;
	SumFF[1] = 1;
	SumFF[2] = 1;
	SumFF[3] = 2;

	for(i = 4; i < fibnum; i++)
		SumFF[i] = (SumFF[i-1] + SumFF[i-2] + ((fib[i-2]%Modulus)*(fib[i-2]%Modulus)%Modulus)*(fib[i-2]%Modulus) + 2*(fib[i-2]%Modulus)*SumF[i-2]) % Modulus;
	
	long long TAR = 10000000000000000;//10^16
	answer = ((TAR%Modulus)*(TAR%Modulus+1)%Modulus)*(2*TAR%Modulus+1) % Modulus;
	if(answer % 2 != 0) answer += Modulus; 
	answer /= 2;
	if(answer % 3 == 2) answer += Modulus;
	if(answer % 3 == 1) answer += 2*Modulus;
	answer /= 3;
	answer -= ((TAR%Modulus)*(TAR%Modulus+1)/2)%Modulus;
	if(answer < 0) answer += Modulus;
	if(answer % 2 != 0) answer += Modulus;
	answer /= 2;
	answer *= 3;
	answer -= Sumfm(TAR-1, Modulus);
	long long cha = (Sumff(TAR-1, Modulus) + 3 * Sumf(TAR-1, Modulus)) % Modulus;
	if(cha % 2 != 0) cha += Modulus;
	cha /= 2;
	answer -= cha;
	if(answer < 0) answer += Modulus;
	if(answer < 0) answer += Modulus;
	

	printf("\n%lld\n", answer); 

	printf("in %lf ms\n", (double)(clock()-time)/CLOCKS_PER_SEC); 
	
	return 0;
}

long long Sumf(long long n, long long mod)
{
	if(n < 1) return 0;
	if(n == 1) return 1;
	if(n == 2) return 2;
	int i = 4;
	while(fib[i+1] <= n) i++;
	return (SumF[i] + ((n - fib[i])%mod) * (fib[i-1]%mod) + Sumf(n - fib[i], mod)) % mod;
}

long long Sumfm(long long n, long long mod)
{
	if(n < 1) return 0;
	if(n == 1) return 1;
	if(n == 2) return 3;
	int i = 4;
	while(fib[i+1] <= n) i++;
	long long ost = (n - fib[i]) % mod;
	return (SumFM[i] + ost * ((fib[i] % mod)*(fib[i-1] % mod) % mod) + (ost * (ost + 1) / 2 % mod) * (fib[i-1] % mod) + 
		Sumf(n - fib[i], mod) * (fib[i] % mod) + Sumfm(n - fib[i], mod)) % mod;
}

long long Sumff(long long n, long long mod)
{
	if(n < 1) return 0;
	if(n == 1) return 1;
	if(n == 2) return 2;
	int i = 4;
	while(fib[i+1] <= n) i++;
	long long ost = (n - fib[i]) % mod;
	return (SumFF[i] + (ost * (fib[i-1] % mod) % mod) * (fib[i-1] % mod) + 2*(fib[i-1]%mod)*Sumf(n - fib[i], mod) + Sumff(n - fib[i], mod)) % mod;
}