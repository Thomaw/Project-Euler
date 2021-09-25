#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;

double c[51][51];
double power2[51];
double possible[51][51];
double dp[51];

int main()
{
	memset(c , 0 , sizeof(c));
	c[0][0] = 1.0;
	for(int i = 1 ; i <= 50 ; i++)
	{
		c[i][0] = 1;
		for(int j = 1 ; j <= i ; j++)
			c[i][j] = c[i-1][j-1] + c[i-1][j];
	}
	power2[0] = 1;
	for(int i = 1 ; i <= 50 ; i++)
	{
		power2[i] = power2[i-1] * 2;
		for(int j = 0 ; j <= i ; j++)
			possible[i][j] = c[i][j] / power2[i];
	}
	
	dp[0] = 0;
	for(int i = 1 ; i <= 32 ; i++)
	{
		dp[i] = 1.0;
		for(int j = 1 ; j <= i ; j++)
			dp[i] += possible[i][j] * dp[i - j];
		dp[i] /= 1.0 - possible[i][0];
	}
	cout<<fixed<<setprecision(10)<<dp[32]<<endl;
	return 0;
}