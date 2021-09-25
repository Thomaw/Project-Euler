#include <iostream>
#include <vector>
#include "../tdn.hpp"
#include <queue>
typedef unsigned long long ULL;
using namespace std;

const ULL N=1e7;
vector <ULL> primes=Eratosthenes(N);
vector <int> aa[N+1];
bool fatto[N+1];

void collega(int i, int p){
	if(binary_search(primes.begin(), primes.end(), p)){
		aa[i].push_back( lower_bound(primes.begin(), primes.end(), p) -primes.begin() );
	}
}

int main(){
	for(int i=0;i<int(primes.size());i++){
		int p=primes[i];
		vector <int> dd=digits(p,10);
		dd.push_back(0);
		int pot=1;
		for(int k=0;k<int(dd.size());k++){
			p-=pot*dd[k];
			for(int j=0;j<=9;j++){
				if(j==dd[k])continue;
				p+=j*pot;
				collega(i,p);
				p-=j*pot;
			}
			p+=pot*dd[k];
			pot*=10;
		}
	}
	int mm=0;
	ULL res=2;
	priority_queue <int> coda;
	coda.push(0);
	fatto[0]=1;
	while(!coda.empty()){
		int x=-coda.top();
		coda.pop();
		mm=max(x,mm);
		for(int i=0;i<int(aa[x].size());i++){
			int a=aa[x][i];
			if(fatto[a])continue;
			fatto[a]=1;
			if(mm<a)res+=primes[a];
			coda.push(-a);
		}
	}
	ULL s=0;
	for(int i=0;i<int(primes.size());i++)s+=primes[i];
	cout << s-res << "\n";
}