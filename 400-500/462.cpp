#include<iostream>
#include<gmpxx.h>

using namespace std;

int main(void)
{
    const mpz_class N=1000000000000000000;
    //const mpz_class N=20;
    mpz_class count=0;
    mpz_class total=1;
    mpz_class hooklengths=1;
    for(mpz_class x=1;x <= N;x*=2) {
        for(mpz_class y=1;x*y<=N;y*=3) {
            mpz_class hook=1;
            for(mpz_class xx=x*2;xx*y<=N;xx*=2) {
                hook++;
            }
            for(mpz_class yy=y*3;x*yy<=N;yy*=3) {
                hook++;
            }
            hooklengths*=hook;
            count++;
            total*=count;
        }
    }
    cout << total/hooklengths << endl;
    return 0;
}