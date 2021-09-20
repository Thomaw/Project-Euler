#include <iostream>

using namespace std;

bool isabundant(int num)
{
    int sum=0;
    for(int i=1; i*2<=num; sum+=(num%i?0:i),i++);
    return sum > num;
}

int main()
{
    int sum = 0, t;
    for(int i=1; i<28123; i++)
    {
        t=0;
        for(int j=12; j*2<=i; j++)
        if(isabundant(j) && isabundant(i-j))
        {
            t=1;
            break;
        }
        if (t==0) sum += i;

    }
    cout<<sum<<endl;
}
