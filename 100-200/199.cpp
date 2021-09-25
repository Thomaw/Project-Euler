#include <iostream>
#include <cmath>
using namespace std;

double initial=0.464101615;  // radius of initial three circles

double rec(double a, double b, double c, int depth){
    double next=a+b+c+2*sqrt(a*b+a*c+b*c);
    if (depth==10) return (1/next)*(1/next);
    return (1/next)*(1/next)+rec(a,b,next,depth+1)+rec(a,next,c,depth+1)+rec(next,b,c,depth+1);
}

int main(){
    cout<<1-(3*initial*initial+rec(1/initial,1/initial,1/initial,1)+3*rec(-1,1/initial,1/initial,1));
    getchar();
}
