#include <stdio.h>
#include <math.h>
#include <map>
using namespace std;
#define ll long long
#define MODD 1000000000000000000ll
int grundy[10002];
ll dp[11002][11002];
ll numways(int x, int reqd)
{

    if(reqd==-1)
        return 1;
    if(x==1)
        return 0;
    if(x==2)
        return (reqd==0);
   if(dp[x][reqd]!=-1)
        return dp[x][reqd];
    ll retval=(numways(x-1,(reqd^(grundy[x-2]+1))-1)+numways(x-2,(reqd^(grundy[x-1]+1))-1))%MODD;
    return dp[x][reqd]=retval;
}


int main()
{
    grundy[1]=0;
    grundy[2]=1;
    for(int i=3;i<=10000;i++)
        grundy[i]=((grundy[i-1]+1)^(grundy[i-2]+1));
    for(int i=0;i<=11000;i++)
        for(int j=0;j<=11000;j++)
            dp[i][j]=-1;
    printf("%lld\n",numways(10000,0));
}