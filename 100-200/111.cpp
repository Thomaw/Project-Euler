#include <algorithm>
#include <iostream>
#include <math.h>
#include <malloc.h>
#include <NTL/ZZ.h>

inline bool incstates (int *states,int fields,int avoid){
    states[--fields]++;
	if(states[fields]==avoid)states[fields]++;
	while (fields&&states[fields]>9){
		states[fields]=0;
		states[--fields]++;
		if(states[fields]==avoid)states[fields]++;
	}
	return (states[0] > 9)?(states[0]=0,false):true;
}

int main()
{
	ZZ totalsum = ZZ::zero();
	ZZ zzOne = to_ZZ(1);
	ZZ mul;
	ZZ num;
	ZZ min = to_ZZ(1000000000);
	int a[] = {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1};
    int states[] = {0,0,0,0,0,0,0,0};
	int nxt;
	for (int i = 0;i < 10;i++){
		bool found = false;
		for(int rep=1;rep<4&&!found;replaced++){
			do{
				do{
					nxt = 0;
					num = ZZ::zero();
					mul = min * 10;
					for(int k = rep;k<rep+10;k++)num+=((mul/=10)*((a[k])?states[nxt++]:i));
					if(ProbPrime(num) && num>min)found = (totalsum+=num,true);
				}while(incstates(states,rep,i));
			}while (std::next_permutation(a+rep,a+10+rep));
		}
	}
	cout << totalsum << "\n";
	return free(a);
}