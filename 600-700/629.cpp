#include<set>
#include<map>
#include<list>
#include<queue>
#include<stack>
#include<string>
#include<math.h>
#include<time.h>
#include<vector>
#include<bitset>
#include<memory>
#include<utility>
#include<fstream>
#include<stdio.h>
#include<sstream>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
using namespace std;
int sg[205];
bool vis[1005];
const int modo=1000000007;
int dp[205][205][205];
int n=200;
int dfs(int x,int y,int z)
{
    if (dp[x][y][z]!=-1) return dp[x][y][z];
    if (x==0)
    {
        if (z==0)
        {
            dp[x][y][z]=0;
        }
        else
        {
            dp[x][y][z]=1;
        }
        return dp[x][y][z];
    }
    if (y>x)
    {
        dp[x][y][z]=0;
        return dp[x][y][z];
    }
    int i;
    dp[x][y][z]=0;
    for (i=y;i<=x;i++)
    {
        dp[x][y][z]=(dp[x][y][z]+dfs(x-i,i,z^sg[i]))%modo;
    }
    return dp[x][y][z];
}
int main()
{
    //For k = 2 : ALL sg = 1(even) / 0(odd)
    //For k = 3 : 
    //For k >= 4 : ALL sg = n-1
    memset(dp,-1,sizeof(dp));
    sg[1]=0;
    int i;
    for (i=2;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));
        int j;
        for (j=1;j<=i;j++)
        {
            int k,l;
            for (k=j;j+k<=i;k++)
            {
                if (j+k==i) vis[sg[j]^sg[k]]=true;
                for (l=k;l+j+k<=i;l++)
                {
                    if (l+j+k==i) vis[sg[j]^sg[k]^sg[l]]=true;
                }
            }
        }
        for (j=0;;j++)
        {
            if (vis[j]) continue;
            break;
        }
        sg[i]=j;
    }
    memset(dp,-1,sizeof(dp));
    int val=dfs(n,1,0);
    for (i=1;i<=n;i++)
    {
        sg[i]=(i-1)%2;
    }
    memset(dp,-1,sizeof(dp));
    val=(val+dfs(n,1,0))%modo;
    for (i=1;i<=n;i++)
    {
        sg[i]=(i-1);
    }
    memset(dp,-1,sizeof(dp));
    val=(val+dfs(n,1,0)*(n-4+1ll))%modo;
    printf("%d\n",val);
    system("pause");
    return 0;
}