#include<iostream>

using namespace std;
typedef unsigned long long int xint;

int main(){
	xint i, sum = 0, prod, tmp;
	xint const limit = 1000*1000*1000;
	for (i = 0; i < limit; i++) {
		prod = 1;
		tmp = 7;
		while (tmp <= limit) {
			prod *= (i/tmp)%7+1;
			tmp *= 7;
		}
		sum += (i%7+1)*prod;
	}
	cout << sum << endl;
	return 0;
}