#include <iostream>
using namespace std;

#define POW5(a) ((a)*(a)*(a)*(a)*(a))

int main() {
	int sum = 0;
	for (int d1 = 0; d1 <= 9; d1++)
	for (int d2 = 0; d2 <= 9; d2++)
	for (int d3 = 0; d3 <= 9; d3++)
	for (int d4 = 0; d4 <= 9; d4++)
	for (int d5 = 0; d5 <= 9; d5++)
	for (int d6 = 0; d6 <= 9; d6++) {
		int num = d6*100000+d5*10000+d4*1000+d3*100+d2*10+d1;
		int powers = POW5(d6)+POW5(d5)+POW5(d4)+POW5(d3)+POW5(d2)+POW5(d1);
		if (num > 1 && num==powers) {
			cout << num << endl;
			sum += num;
		}
	}
	cout << "sum = " << sum << endl;
	
	return 0;
}
