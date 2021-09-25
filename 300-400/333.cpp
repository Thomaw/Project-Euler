#include<stdio.h>
#include<math.h>
#include<time.h>

#define M 1000000
#define log3M 12

char var[M][log3M+1] = {{0}};

char isprime(int n); //for n == 1 or 5 mod 6

int main()
{
	int i, j;
	long long answer = 0;
	double time=clock();
		
	for(i = 0; i <= log3M; i++) var[1][i] = 1;
	for(i = 2; i < M; ++i)
	{
		if(i%2 == 0) 	
		{
			int i2 = i/2;
			for(j = 0; j <= log3M; j++)
				var[i][j] = var[i2][j];
		}
		else if(i%3 == 0) 
		{
			int i3 = i/3;
			for(j = 0; j < log3M; j++)
				var[i][j+1] = var[i3][j];
		}
		else
		{
			char* vari = var[i];
			int deg = 1;
			for(j = 3; j <= i; j*=3, ++deg)
				vari[deg] = var[i-j][deg-1];
			for(j = 2; j <= log3M && vari[j] < 2; ++j)
				vari[j] += vari[j-1];
			for(; j <= log3M; ++j)
				vari[j] = 2; //for avoid of overflow
		}
	}

	answer = 2+3;
	for(i = 5; i < M; i+=6)
		if(var[i][log3M] == 1)
			if(isprime(i) == 1)
				answer += i;

	for(i = 7; i < M; i+=6)
		if(var[i][log3M] == 1)
			if(isprime(i) == 1)
				answer += i;

	printf("%lld\n", answer);

	printf("in %lf ms\n", (double)(clock()-time)/CLOCKS_PER_SEC);
	
	return 0;
}

char isprime(int n)
{
	int i, ii; //ii = i*i
	for(i = 5, ii = 25; ii <= n; i+=6, ii += 12*i-36)
		if(n % i == 0) return 0;
	for(i = 7, ii = 49; ii <= n; i+=6, ii += 12*i-36)
		if(n % i == 0) return 0;
	return 1;
}