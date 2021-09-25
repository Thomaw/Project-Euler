#include<iostream>
using namespace std;

__int64 ways[100];
int mn(int a, int b) {if (a<b) return a; return b;}
int main (void)
{
	ways[0]=1; ways[1]=0;
	__int64 result=1; int i,j;
	for (i=2;i<=50;i++)
	{
		for (j=0;j<=i-2;j++)
		{
			ways[i]+=ways[j]*mn(3,i-j-1);
		}
		result+=ways[i];
	}
	return 0;
}