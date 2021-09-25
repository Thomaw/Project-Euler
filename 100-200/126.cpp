#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define NMAX 10000
int freq[NMAX+1];

int firstlayer(int x, int y, int z)
{
	return 2*(x*z+y*z+x*y);
}

void process(int x, int y, int z)
{
	int layers=0,r;
	while (true)
	{
		r=2*x*y;
		r+=(z+2*layers)*2*(x+y);
		r+=((layers-1)*layers)*4;
		r+=z*layers*4;
		if (r>2*NMAX) break;
		freq[r/2]++;
		layers++;
	}
}

int main(void)
{
	int x,y,z,i;
	for (i=0;i<=NMAX;i++) freq[i]=0;
	for (x=1;firstlayer(x,1,1)<=2*NMAX;x++)
	{
		for (y=1;firstlayer(x,y,1)<=2*NMAX&&y<=x;y++)
		{
			for (z=1;firstlayer(x,y,z)<=2*NMAX&&z<=y;z++)
			{
				process(x,y,z);
			}
		}
	}
	for (i=0;i<=NMAX;i++)
	{
		if (freq[i]==1000)
		{
			printf("%i\n",2*i);
			break;
		}
	}
	return 0;
}