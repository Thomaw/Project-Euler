#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
#define ull unsigned long long
#define MAX 2000001
bool prime[MAX];
ull LP[2][MAX], f[2][MAX], ans;
vector<int> primes;
void init()
{
    ans = 1; // This accounts for f(1*1*1) = f(1) = 1
    for (ull i = 2; i < MAX; i++)
    {
        prime[i] = 1;
        f[0][i] = i+1;
        f[1][i] = i*i - i + 1;
    }
    for (int i = 2; i <= floor(sqrt(MAX)); i++) if (prime[i]) for (int j = i*i; j < MAX; j+=i) prime[j] = 0;
    for (int i = 2; i < MAX; i++) if (prime[i]) primes.push_back(i);
    for (int i = 2; i < MAX; i++)
    {
        if(!(i%100000)) cout << i << endl;
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < primes.size(); k++)
                if(primes[k]>floor(sqrt(f[j][i]))) break;
                else if (!(f[j][i]%primes[k]))
                {
                    LP[j][i] = (LP[j][i]>primes[k]?LP[j][i]:primes[k]);
                    while(!(f[j][i]%primes[k])) f[j][i]/=primes[k];
                }
            LP[j][i] = max(LP[j][i], f[j][i]);
        }
    }
}
void solve()
{
    for (int i = 2; i < MAX; i++) ans += max(LP[0][i], LP[1][i])-1;
    cout << ans << endl;
}
main()
{
    init();
    solve();
}