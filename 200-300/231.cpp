#include <iostream>                 
#include <bitset>                   
#include <vector>                   
#include <cassert>                  

using namespace std;

template <int size>
vector<int> sieve() {
    vector<int> p;   
    bitset<size> comps(size);
    comps=0x3;               
    for (int i=2; i<size; i++)
        for (int j=i+i; j<size; j+=i)
            comps[j]=true;           
    for (int i=2; i<size; i++)
        if (!comps[i]) p.push_back(i);
    return p;
}

vector<int> primes=sieve<20000000>();

void factors(vector<int> & v1, vector<int> & v2, vector<int> & v3, int x, int n, int k) {
    int xx=x;
    for (vector<int>::iterator i=primes.begin(); i!=primes.end() && ((long long)(*i)*(*i))<=x; i++) {
        while (!(x%*i)) {
            x/=*i;
            v1[*i]++;
            if (xx<=k) v2[*i]++;
            if (xx<=n-k) v3[*i]++;
        }
    }
    if (x>1) {
        v1[x]++;
        if (xx<=k) v2[x]++;
        if (xx<=n-k) v3[x]++;
    }
}

long long sumt(int n, int k) {
    vector<int> p1(n+1,0);
    vector<int> p2(n+1,0);
    vector<int> p3(n+1,0);
    for (int i=1; i<=n; i++) {
        factors(p1,p2,p3,i,n,k);
        if (!(i%1000000)) cout << i << endl;
    }
    for (int i=0; i<=n; i++) {
        p1[i]-=p2[i]+p3[i];
    }
    long long sum=0;
    for (int i=2; i<=n; i++) {
        assert(p1[i]>=0);
        sum+=i*p1[i];
    }
    return sum;
}

int main() {
    cout << sumt(10,3) << endl;
    cout << sumt(20000000,15000000) << endl;
}