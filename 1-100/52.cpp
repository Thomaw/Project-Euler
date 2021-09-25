#include <set>
#include <iostream>
using namespace std;

typedef set<int> S;

S digits(int n) {
    S res;
    while(n) {
        res.insert(n%10);
        n/=10;
    }
    return res;
}

int main() {
    int x = 1;
    for(;;) {
        if(digits(2*x) == digits(3*x) && digits(3*x) == digits(4*x) &&
           digits(4*x) == digits(5*x) && digits(5*x) == digits(6*x)) {
            cout << x << endl;
            break;
        }
        x++;
    }
    return 0;
}
