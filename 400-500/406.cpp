#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
typedef long double real;
typedef unsigned long long ull;
const ull N = 1000000000000ull;
const real eps =1e-12; 
real A,B;
real solve(ull n,ull a,ull b){
	if(a>b)swap(a,b);
	A=sqrt(a);B=sqrt(b);
	if(a==b)for(int i=0;i<=50;++i)
		if(n<(1ull<<i+1))
			return i*A;
	for(real bound = 10;;bound*=10){
		vector<real> C;
		vector<ull> F;
		for(int i=0;i*B<bound;++i)
			for(int j=0;;++j){
				real t=j*A+i*B;
				if(t>bound)break;
				C.push_back(t);
			}
		sort(C.begin(),C.end());
		F.resize(C.size(),0);
		F[0]=1;
		for(int i=1;i<C.size();++i){
			real &y=C[i];
			F[i]=1+F[upper_bound(C.begin(),C.end(),y-A+eps)-C.begin()-1];
			if(y+eps>B)
				F[i]+=F[upper_bound(C.begin(),C.end(),y-B+eps)-C.begin()-1];
			if(F[i]>=n)return C[i];
		}
	}
}
int main(){
	cout.precision(14);
	cout << solve(5,4,9) << endl;
	cout << solve(500,2,3) << endl;
	cout << solve(20000,25,49) << endl;
	cout << solve(2000000,5,7)<< endl;
	real res =0;
	ull a=1,b=0;
	for(int i=1;i<=30;++i){
		real t= solve(N,i,a+=b);
		res+=t;
		cout << i << ": " << i <<"," << a << ": "<<t << endl;
		swap(a,b);
	}
	cout << res << endl;
}