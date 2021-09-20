#include<iostream>

using namespace std;

int main()
{
    int maxprod = 0;
    int prod;
    char array[1001] = {"73...50"};
    for(int i = 0; i <= 995; i++)
    {
        prod = 1;
        for(int j = 0; j <= 4; j++)
            prod = prod * (array[i+j] - '0');
        if(prod > maxprod)
            maxprod = prod;
    }
cout << "The maximum product of five consecutive digits is " << maxprod << "\n";
system("PAUSE");
return 0;
}
