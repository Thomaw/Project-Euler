#include <iostream>
using namespace std;
int limit = 1000000;
int pc = 0;
int main() {
    long long ct = 0, tmp;
    for (long long i=3; i<limit; i+=2) {
        for (long long j=3; j*j<=i; j+=2) {
            if (i%j==0) goto nope;
        }
        ct += 2; // |m-n|=1 case
        if (i*i<15) continue;
        tmp = (i*i-15)/2;
        ct += 2*((tmp/4-tmp%3+3)/3);
        nope:;
    }
    printf("%I64d\n",ct);
}