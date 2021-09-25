#include <iostream>
using namespace std;

int ways[1000];
#define k 50
#define L 1000000
int main(void)
{
	int i,j,r=0;
	for (i=0;;i++)
	{
		if (i==0) ways[i]=1;
		else if (i<=k) ways[i]=0;
		else
		{
			ways[i]=0;
			for (j=0;j<i-k;j++)
				ways[i]+=ways[j]*(i-k-j);
		}
		r+=ways[i];
		if (r>L) break;
	}
	printf("%i\n",i-1);
	return 0;
}