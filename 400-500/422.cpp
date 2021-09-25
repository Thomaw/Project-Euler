#include <iostream>

using namespace std;

int main()
{
    const __int64 M = 1000000007;
    const __int64 IM2 = 500000004, IM24 = 41666667;
    __int64 a0 = 15, b0 = 17, c0 = 8;
    __int64 a1 = -5, b1 = -13, c1 = 12;

    for ( __int64 i = 3; ; i++ ) {
        __int64 a = (a0*b1 - a1*b0) % M * IM2 % M;
        __int64 b = (b0*b1 - a0*a1) % M * IM2 % M;
        __int64 c = c0 * c1 % M * IM2 % M;
        if ( a < 0 ) a += M;
        if ( b < 0 ) b += M;
        a0 = a1, b0 = b1, c0 = c1;
        a1 = a, b1 = b, c1 = c;
        if ( i == 830545249 ) {
            cout << ((7*b-a)%M*IM24%M +  c*IM24%M + (7*a+b)%M*IM2%M + c*IM2%M) % M << endl;
            break;
        }
    }
    return 0;
}