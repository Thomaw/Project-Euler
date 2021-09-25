
#include <stdio.h>
#include <math.h>

#define N 1000

int main()
{
	/*
		3/N(5N-4) 4/N(5N-4) ... 4/N(5N-4) 3/N(5N-4)
		4/N(5N-4) 5/N(5N-4) ... 5/N(5N-4) 4/N(5N-4)
		...
		4/N(5N-4) 5/N(5N-4) ... 5/N(5N-4) 4/N(5N-4)
		3/N(5N-4) 4/N(5N-4) ... 4/N(5N-4) 3/N(5N-4)
	*/
	int numer = 6;
	int i;
	for (i = 2; i < N; i++) {
		if (i * i < N)
			numer += 4;
		else if (i * i == N)
			numer += 3;
		else if ((i * i) % N == 0 || (i * i) % N == 1)
			numer += 4;
		else
			numer += 5;
	}
	double sum = (double)numer / (N * (5 * N - 4));
	/*
		2/4N(N-1) 3/4N(N-1) ... 3/4N(N-1) 2/4N(N-1)
		3/4N(N-1) 4/4N(N-1) ... 4/4N(N-1) 3/4N(N-1)
		...
		3/4N(N-1) 4/4N(N-1) ... 4/4N(N-1) 3/4N(N-1)
		2/4N(N-1) 3/4N(N-1) ... 3/4N(N-1) 2/4N(N-1)
	*/
	numer = 4;
	for (i = 2; i < N; i++) {
		if (i * i < N)
			numer += 3;
		else if (i * i == N)
			numer += 2;
		else if ((i * i) % N == 0 || (i * i) % N == 1)
			numer += 3;
		else
			numer += 4;
	}
	sum = (sum + (double)numer / (4 * N * (N - 1))) / 2;
	printf("%.12lf\n", sum);
	return 0;
}