#include<iostream>
using namespace std;

int sum = 0;

bool isprime(int x)
{
    for(int i = 2 ; i * i <= x ; i ++)
        if(x % i == 0)
            return false;
    return true;
}

bool cir(int mod)
{
    int x = 0 , ret = 1;
    while((10 * x + 1) % mod != 0)
    {
        x = (10 * x + 1) % mod;
        ret ++;
        if(ret > mod)
            return false;
    }
    while(ret % 2 == 0)
        ret /= 2;
    while(ret % 5 == 0)
        ret /= 5;
    return (ret == 1);
}

int main()
{
    for(int i = 2 ; i <= 100000 ; i++)
        if(isprime(i))
            if(cir(i) == false)
                sum += i;
    cout<<sum<<endl;
    return 0;
}