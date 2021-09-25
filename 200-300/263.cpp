#include <iostream>
#include <vector>
using namespace std;
vector<int> facts;
bool practical(int N) {
    facts.clear();
    int upto = 0;
    for (int i=1; i*i<=N; i++) {
        if (N%i==0) {
            if (i-upto>=2) return false;
            upto += i;
            if (upto>=N) return true;
            if (i<N/i) facts.push_back(N/i);
        }
    }
    for (int i=facts.size()-1; i>=0; i--) {
        int here = facts[i];
        if (here-upto>=2) return false;
        upto += here;
        if (upto>=N) return true;
    }
    return false;
}
bool isprime(int N) {
    if (N%2==0) return N==2;
    for (int i=3; i*i<=N; i+=2) {
        if (N%i==0) return false;
    }
    return true;
}
int main() {
    int ct = 0;
    for (int i=1;;i+=5) {
        if (isprime(i) && isprime(i+6) && isprime(i+12) && isprime(i+18)) {
            if (isprime(i+2) || isprime(i+4) || isprime(i+8) || isprime(i+10) || isprime(i+14) || isprime(i+16)) continue;
            if (practical(i+1) && practical(i+9) && practical(i+17) && practical(i+5) && practical(i+13)) {
                printf("%d\n",i+9);
            }
        }
    }
}