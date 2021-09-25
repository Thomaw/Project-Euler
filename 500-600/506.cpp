#include <iostream>
#include <vector>

using namespace std;

uint64_t gcd(uint64_t a,uint64_t b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}

uint64_t expmod(uint64_t base,uint64_t exp,uint64_t mod)
{
    if(exp==0) return 1;
    if(exp==1) return base;
    uint64_t x=expmod(base,exp/2,mod);
    x=x*x%mod;
    if(exp%2==1) x=x*base%mod;
    return x;
}

const uint64_t MASK=123454321;
const uint64_t DEN=expmod(999999ULL*999999ULL%MASK,40*270*41*271-1,MASK);
const uint64_t LIM=100000000000000ULL;
// The inverse of 999,999^2 mod 123454321, which is equal to 41^2*271^2, by Euler's theorem

int main()
{
    vector<uint64_t> pattern;
    vector<pair<uint64_t,uint64_t> > v;
    uint64_t i,j,a,total,temp,repeat,currv;
    for(i=1;i<=4;i++) pattern.push_back(i);
    pattern.push_back(3);
    pattern.push_back(2);
    v.push_back(make_pair(0,0)); // v0=0
    v.push_back(make_pair(0,1)); // v1=1
    v.push_back(make_pair(1,1)); // v2=2
    v.push_back(make_pair(2,1)); // v3=3
    v.push_back(make_pair(3,1)); // v4=4
    v.push_back(make_pair(4,2)); // v5=32
    v.push_back(make_pair(0,3)); // v6=123
    v.push_back(make_pair(3,2)); // v7=43
    v.push_back(make_pair(5,4)); // v8=2123
    v.push_back(make_pair(3,3)); // v9=432
    v.push_back(make_pair(0,4)); // v10=1234
    v.push_back(make_pair(4,5)); // v11=32123
    v.push_back(make_pair(3,5)); // v12=43212
    v.push_back(make_pair(2,5)); // v13=34321
    v.push_back(make_pair(1,5)); // v14=23432
    total=0;
    for(i=0;i<=14;i++)
    {
        a=(LIM-i)/15;
        temp=(122454322*(a%MASK)+122454321+expmod(1000000,a+1,MASK))%MASK*DEN%MASK;
        repeat=0;
        for(j=0;j<=5;j++) repeat=repeat*10+pattern[(v[i].first+j)%6];
        temp=temp*repeat%MASK*expmod(10,v[i].second,MASK)%MASK;
        currv=0;
        for(j=0;j<v[i].second;j++) currv=currv*10+pattern[(v[i].first+j)%6];
       // cout << currv << endl;
        temp=(temp+(a+1)*currv)%MASK;
        total=(total+temp)%MASK;
    }
    cout << total << endl;
    return 0;
}