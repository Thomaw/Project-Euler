#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

typedef unsigned long long uint64;

class SmallDigits
{
	vector<uint64> m_Array;
	uint64 m_Sum;
public:
	void gen(uint64 num, int n)
	{
		if (n == 0) return;

		if (num > 0)
		{
			// cout << s << endl;
			m_Array.push_back(num);

			gen(num * 10, n - 1);
		}

		gen(num * 10 + 1, n - 1);
		gen(num * 10 + 2, n - 1);
	}

	void compute()
	{
		cout << m_Array.size() << endl;

		sort(m_Array.begin(), m_Array.end());

		cout << "Sorted." << endl;

		uint minMultiple = 0;

		m_Sum = 0;

		for (uint i = 1; i <= 10000; i++)
		{
			uint j;
			for (j = minMultiple; m_Array[j] < i && j < m_Array.size(); j++)
			{
				minMultiple = j;
			}

			for (j = minMultiple; j < m_Array.size(); j++)
			{
				if (m_Array[j] % i == 0)
				{
					// cout << "Multiple for " << i << " is " << m_Array[j] << endl;

					m_Sum += m_Array[j] / i;
					break;
				}
			}

			if (j == m_Array.size())
			{
				cout << "Warning: Not enough multiples for " << i << endl;
			}
		}

		uint64 tmp(compute9999(0, 21));
		
		cout << "For 9999: " << tmp << endl;

		m_Sum += tmp / 9999;

		cout << "Ans = " << m_Sum << endl;
	}

	uint64 compute9999(uint64 num, int n)
	{
		if (n == 0) return 0;

		if (num > 0 && num % 9999ULL == 0)
		{
			return num;

			uint64 ret(compute9999(num * 10, n-1));
			if (ret > 0) return ret;
		}

		uint64 ret(compute9999(num * 10 + 1, n-1));
		if (ret > 0) return ret;
		ret = compute9999(num * 10 + 2, n-1);
		if (ret > 0) return ret;

		return 0;
	}
};

int main()
{
	SmallDigits sd;
	sd.gen(0, 17);
	sd.compute();
}