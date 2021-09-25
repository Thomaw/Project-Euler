#include<iostream>
#include<iomanip>
#define MAXN 4000000
using namespace std;

int n;
long long x[MAXN + 1];
long long s[1501];

long long double MomentOfInertia()
{
    long long double sigmaMD = 0 , sigmaM = 0;
    long long double ret = 0;
    for(int i = 1 ; i <= MAXN ; i++)
    {
        sigmaMD += x[i] * i;
        sigmaM += x[i];
    }
    long long double CM = sigmaMD / sigmaM;
    for(int i = 1 ; i <= MAXN ; i++)
        ret += (i - CM) * (i - CM) * x[i];
    return ret;
}

int which_empty()
{
    long long sigmaMD = 0 , sigmaM = 0;
    for(int i = 1 ; i <= MAXN ; i++)
    {
        sigmaMD += x[i] * i;
        sigmaM += x[i];
    }
    long long ret = (sigmaM * (sigmaM - 1) / 2 - sigmaMD) % sigmaM;
    ret += sigmaM;
    ret %= sigmaM;
    return ret;
}

int main()
{
    memset(x , 0 , sizeof(x));
    n = 1500;
    int t = 123456;
    for(int i = 1 ; i <= n ; i++)
    {
        if(t % 2 == 0)
            t = t / 2;
        else
            t = (t / 2) ^ 926252;
        x[i] = t % 2048 + 1;
        s[i] = x[i];
    }
    long long double I_ins = MomentOfInertia();
    int which = which_empty();
    memset(x , 0 , sizeof(x));
    int cur = 0;
    for(int i = 1 ; i <= n ; i++)
    {
        for(int j = 1 ; j <= s[i] ; j++)
            x[++cur] = 1;
    }
    x[which + 1] --;
    x[++cur] = 1;
    long long double I_fin = MomentOfInertia();
    cout << (I_fin - I_ins) / 2 << endl;
    system("pause");
    return 0;
}