#include <iostream>

int n=100000000;
int *factorials = new int[n+1];
int p=1008691207;

int main(){
    factorials[0]=1;
    long long f;
    for(int i=1; i<=n; i++){
        f = factorials[i-1];
        f*=i;
        factorials[i]=f%p;
    }
    long long sum=factorials[n]-1;
    for(int i=1; i<=n-1; i++){
        sum-=2*factorials[i];
        while(sum<0) sum+=p;
        sum%=p;
    }
    for(int i=0; i<=n-2; i++){
        f=factorials[i];
        f*=(n-i-1);
        sum+=f;
        sum%=p;
    }
    std::cout << sum << "\n";
}