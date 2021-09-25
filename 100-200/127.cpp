
#include<iostream>
using namespace std;
#define M 100000
__int64 rad[M];

/*Euclidean GCD*/
int gcd (int x, int y)
{
	int t;
	if (x<y) {t=x;x=y;y=t;}
	while (y>0) {t=x%y; x=y; y=t;}
	return x;
}

/*... precomputation ...*/

int main(void)
{
	int c,j,total=0,lim;
	for (c=1;c<M;c++) if (rad[c]<c)
	{
		lim=c/rad[c];
		for (j=1;j<c/2;j++)
			if (gcd(c,j)==1)
				if (rad[c-j]*rad[j]<lim) total+=c;
	}
	printf("%i\n",total);
	return 0;
}