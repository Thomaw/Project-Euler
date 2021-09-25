#include<bits/stdc++.h>
using namespace std;
typedef long long u64;
const u64 u=100000,n=u*u,M=1e9;

bool sieve[u+1];
int p[u],c;
u64 res= (n+2)%(M*2)*((n-1)%(M*2))/2 % M;
int main(){
	for(u64 i=2;i<=u;++i){
		if(!sieve[i])p[c++]=i;
		for(int j=0;j<c && i*p[j]<=u; j++) {
			sieve[i * p[j]] = p[j];
			if(!(i%p[j])) break;
		}
	}
	int h=1,d;
	for(d=0;d<c && h*p[d]<=u;h*=p[d++]);
	vector<int> w;
	for(int i=2;i<=h+1;++i){
		for(int j=0;j<=d;++j)
			if(j==d)w.push_back(i);
			else if(i%p[j]==0) {
				u64 t=(n-i)/h;
				res = (res + (p[j]-i)*(t+1) ) %M;
				res = res - (t+1)*(t)/2 %M * h %M + M;
				break;
			}
	}
	#pragma omp parallel for reduction(+:res)
	for(size_t k=0;k<w.size();++k){
		u64 tmp=0;
		for(u64 i=w[k],_=n/p[d-1];i<=_;i+=h)
		for(int j=d;j<c && i*p[j]<=n;++j){
			tmp=(tmp+(1-i)*p[j])%M;
			if(!(i % p[j])) break;
		}
		res+=tmp;
		if(k%64==0)cerr << k+1 << "/" << w.size() << endl;
	}
	cout << (res %M +M)%M << endl;
}