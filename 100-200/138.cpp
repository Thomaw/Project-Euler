#include <iostream>
#include <duration/Duration.h> //cduration from codeproject

using namespace std;

int main()
{
	CDuration d;
	d.Start();
	long long m = 4;
	long long sum = 0;
	int found = 0;
	while(found < 12)
	{
		long long low = 1;
		long long high = m-1;
		long long ms = m*m;

		while(low < high)
		{
			//binary search the 1 or -1
			long long mid = (low+high)/2;
			long long  bmh = ms - mid*mid - ((m*mid)<<2);
			if(bmh > 1)
				low = mid+1;
			else
				high = mid;
		}

		if(std::abs(ms-low*low - ((m*low)<<2))==1)
		{
			sum += (m*m + low*low);
			++found;
		}

		++m;
	}

	d.Stop();

	cout << sum << endl;
	cout << "Time: " << (d.GetDuration()/1000.) << endl;

	return 0;
}