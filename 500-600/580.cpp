#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
const long long N=10000000000000000LL;
//const long long N=10000000LL;
const long long UP=100000LL;
bool sieve[UP+100];
long long prime[UP+100],top=0;
void init()
{
    sieve[1]=1;
    for (long long i=2;i<=sqrt(sqrt(N));i++)
        if (!sieve[i])
        {
            prime[top++]=i;
            for (long long j=1;j<=sqrt(sqrt(N))/i;j++)
                sieve[i*j]=1;
        }
}
vector<int> factorize;
bool comp2(const int &x,const int &y)
{
    return x>y;
}
void work()
{
    long long ans=0;
    for (long long i=1;i*i<=N;i+=2)
    {
        long long flag=0,count=1,n=i;
        factorize.clear();
        bool fast_break=false;
        for (int j=0;j<top && prime[j]<=n/prime[j];j++)
            if (n%prime[j]==0)
            {
                if (prime[j]%4==1)
                {
                    if (n%(prime[j]*prime[j])==0)
                    {
                        fast_break=true;
                        break;
                    }
                    n/=prime[j];
                    count=-count;
                    continue;
                }
                int power=0;
                for (;n%prime[j]==0;n/=prime[j],power++);
                factorize.push_back(power);
            }
        if (fast_break) continue;
        if (n>1)
        {
            if (n%4==1) count=-count;
            else factorize.push_back(1);
        }
        sort(factorize.begin(),factorize.end(),comp2);
        int omega=factorize.size();
        long long sign=((omega&1)?-1:1);
        if (omega>=2 && factorize[0]>=2 && factorize[1]>=2 || omega>=1 && factorize[0]>=3) continue;
        else if (omega>=1 && factorize[0]==2) flag=sign;
        else flag=-sign*(omega-1);
        ans=ans+((N/i/i-1)/4+1)*flag*count;
        //printf("i=%lld, %lld\n",i,((up-1)/4+1)*flag);
    }
    printf("ans=%lld\n",ans);
}
int main()
{
    init();
    printf("init finished\n");
    work();
    return 0;
}