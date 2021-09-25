#include <iostream>

int len(int n)
{
    int l=1;
    int t=n;
    while(n/=10)l++;
    return l;
}

int main()
{
    int prod = 1, i=1, pos=1, l=1;

    while(pos+l <= 100) 
    {
        pos+=l;
        l=len(++i);
    }
    int n = i;
    for(int p=0; p<l-100+pos-1;++p) n/=10;
    prod *= n%10;
    
    while(pos+l <= 1000) 
    {
        pos+=l;
        l=len(++i);
    }
    n = i;
    for(int p=0; p<l-1000+pos-1;++p) n/=10;
    prod *= n%10;
    
    while(pos+l <= 10000) 
    {
        pos+=l;
        l=len(++i);
    }
    n = i;
    for(int p=0; p<l-10000+pos-1;++p) n/=10;
    prod *= n%10;
    
    while(pos+l <= 100000) 
    {
        pos+=l;
        l=len(++i);
    }
    n = i;
    for(int p=0; p<l-100000+pos-1;++p) n/=10;
    prod *= n%10;
    
    while(pos+l <= 1000000) 
    {
        pos+=l;
        l=len(++i);
    }
    n = i;
    for(int p=0; p<l-1000000+pos-1;++p) n/=10;
    prod *= n%10;    
    
    std::cout << prod ;
}
