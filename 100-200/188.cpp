#include <iostream>

__int64 powerMod(__int64 number, __int64 power, __int64 digits);
int hyperExpoEight(int base, int exp);

int main()
{
	std::cout << hyperExpoEight(1777,1855) << std::endl;
	return 0;
}

__int64 powerMod(__int64 number, __int64 power, __int64 mod)
{
	__int64 result = 1;
	while(power >0)
	{
		if((power&1)==1)
		{
			result = (result*number)%mod;
		}
		power >>=1;
		number = (number*number)%mod;
	}
	return result;
}

int hyperExpoEight(int base, int exp)
{
	//Recursive:
	if(exp==1) return base;
	return powerMod(base,hyperExpoEight(base,exp-1),100000000);
	
	//Iterative:
	//int myexp = base;
	//for(int i = 1; i < exp; i++)
	//{
	//	myexp = powerMod(base,myexp,100000000);
	//}
	//return myexp;
}