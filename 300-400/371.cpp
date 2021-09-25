#include <cstdio>

double M1[500],M0[500];

int main()
{
	int k=499;
	M1[k]=2;
	M0[k]=2+M1[k]/(999-k);
	for(k--;k>=0;k--)
	{
		M1[k]=(2*(499-k)*M1[k+1]+1000)/(999-k);
		M0[k]=(2*(499-k)*M0[k+1]+M1[k]+1000)/(999-k);
	}
	printf("%.8lf\n",M0[0]);
	return 0;
}