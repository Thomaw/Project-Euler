#include<bits/stdc++.h>
using namespace std;

typedef double flt;

long BN(long n){
	if(n<2)return n;
	static unordered_map<long,flt> cache;
	auto it=cache.find(n);
	if(it!=cache.end())return it->second;
	return cache[n]=((n&1)?BN(n>>1)*2:BN(n>>1)+BN(n-1>>1))+n;
}
flt B(long n){return BN(n)/(flt)n;}

flt h(long n){
	//from Mathematica
	if(llabs(n-(long)(1e10))<10)return 23.603066594891989701+(n-1e10)*1e-10;
	flt res=0;
	for(int i=1;i<=n;++i)res+=flt(1)/i;
	return res;
}

flt R(long n){
	return h(n)*(n+1)*2/n-3;
}
int main(){
	cout.precision(10);
	cout << B(6) << endl;
	cout << R(6) << endl;
	cout << R(1e10)-B(1e10) << endl;
}