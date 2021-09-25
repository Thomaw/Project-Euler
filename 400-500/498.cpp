#include <iostream>
#include <vector>

using namespace std;

const int64_t P=999999937LL;
vector<int64_t> fact;

int64_t expmod(int64_t base,int64_t exp,int64_t mod)
{
    if(exp==1) return base;
    int64_t x=expmod(base,exp/2,mod);
    x=x*x%mod;
    if(exp%2==1) x=x*base%mod;
    return x;
}

int main()
{
    int64_t sum1,sum2,sum3,i,curr,total;
    fact.push_back(1);
    for(i=1;i<=10000;i++) fact.push_back(i*fact.back()%P);
    curr=1;
    for(i=630000;i>620000;i--) curr=curr*i%P;
    curr=curr*expmod(fact[10000],P-2,P);  // Multiply by the inverse of 10,000!
    sum1=P-curr;
    for(i=10001;i<63000;i++)
    {
        curr=curr*expmod(i-10000,P-2,P)%P*(630001-i)%P;
        if(i%2==1) sum1=(sum1+curr)%P;
        else sum1=(sum1+P-curr)%P;  //The +P is to prevent negative numbers.
    }
    sum2=sum1;
    for(i=63000;i<=630000;i++)
    {
        curr=curr*expmod(i-10000,P-2,P)%P*(630001-i)%P;
        if(i%2==1) sum2=(sum2+curr)%P;
        else sum2=(sum2+P-curr)%P;
    }
    sum3=0;
    for(i=0;i<1000;i+=2) sum3=(sum3+fact[10000]*expmod(fact[i]*fact[10000-i]%P,P-2,P))%P;
    for(i=1;i<=999;i+=2) sum3=(sum3+P-fact[10000]*expmod(fact[i]*fact[10000-i]%P,P-2,P))%P;
    total=(sum2*sum3%P+sum1*fact[10000]%P*expmod(fact[1000]*fact[9000]%P,P-2,P))%P;
    cout << total << endl;

    return 0;
}