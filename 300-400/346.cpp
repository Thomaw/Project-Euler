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
#define MAXX 1000
set<ll> isstrong;
int main()
{
    for(ll b=2;b<=1000000;b++)
    {
        ll N=1;
        
        for(int s=1;;s++)
        {
            if(N>=MAXX)
                break;
            if(s>2)
                isstrong.insert(N);
            N=N*b+1;
        }
        
    }
    printf("%d\n",(int)isstrong.size());
    ll answer=0;
    for(set<ll>::iterator it=isstrong.begin();it!=isstrong.end();++it)
        answer+=(*it);
    printf("%lld\n",answer+1);
    
}