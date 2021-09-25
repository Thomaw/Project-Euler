#include <map>
#include <string>
#include <vector>
#include <math.h>
#include <set>
#include <algorithm>
#include <list>
#include <iostream>
using namespace std;
#define ll long long
int N;
bool isprime[10000010];
bool there[10000010];
vector <int> primes;
int main()
{
    scanf("%d",&N);
    
    for(int i=2;i<=N;i++)
        isprime[i]=true;
    for(int i=2;i<=N;i++)
    {
        if(isprime[i])
            primes.push_back(i);
        for(int j=i;j<=N/i;j++)
            isprime[i*j]=false;
    }
   

    map<int,int> powers;
    for(int i=0;i<primes.size();i++)
    {
        ll V=primes[i];
        for(int j=0;;j++)
        {
            if(V>=N)
                break;
            powers[V]=i;
            V*=primes[i];
        }
                
    }

    
    
    map<pair<int,int>, int> maxmap;
    for(int i=2;i<=N;i++)
    {
        for(map<int,int>::iterator it=powers.begin();it!=powers.end();++it)
        {
            int val=(*it).first;
            int p1=(*it).second;
            if((ll)val*(ll)val>i)
                break;
            if(i%val!=0)
                continue;
            if(powers.find(i/val)==powers.end())
                continue;
            int p2=powers[i/val];
            if(p1==p2)
                continue;
            printf("%d %d %d\n",i,primes[p1],primes[p2]);
            maxmap[make_pair(min(p1,p2),max(p1,p2))]=i;
        }
    }
    ll answer=0;
    for(map<pair<int,int>,int>::iterator it=maxmap.begin();it!=maxmap.end();++it)
    {
        answer+=(*it).second;
    }
    printf("%lld\n",answer);
    
    
    
            
    
    
    
    
    
}