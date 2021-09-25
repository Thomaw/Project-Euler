#include<iostream>
#include<iomanip>
using namespace std;

int n;
double p_not[10001] , p_have[10001];
double f[10001];
double g[10001];

double F(int i , int j)
{
    return 1 + f[i - j] + p_have[j] * g[j];
}

double G(int i , int j)
{
    double prob = p_have[j] / p_have[i];
    return 1 + prob * (g[j] + f[i - j]) + (1.0 - prob) * g[i - j];
}

double solve(int _n , double _p)
{
    n = _n;
    p_not[0] = 1;
    p_not[1] = 1.0 - _p;
    for(int i = 2 ; i <= n ; i++)
        p_not[i] = p_not[i-1] * p_not[1];
    for(int i = 0 ; i <= n ; i++)
        p_have[i] = 1.0 - p_not[i];
    f[0] = 0;
    f[1] = 1;
    g[1] = 0;
    g[0] = 0;
    for(int i = 2 ; i <= n ; i++)
    {
        f[i] = 1e10 , g[i] = 1e10;
        
        for(int j = 1 ; j < i ; j++)
            g[i] = min(g[i] , G(i , j));
        for(int j = 1 ; j <= i ; j++)
            f[i] = min(f[i] , F(i , j));
    }
    return f[n];
}

int main()
{
    cout << fixed << setprecision(6);
    double ans = 0;
    for(int p = 1 ; p <= 50 ; p ++)
        ans += solve(10000 , 0.01 * p);
    cout << ans << endl;
    system("pause");
    return 0;
}