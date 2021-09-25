typedef long long num;
#include <iostream>
int main(){
    int n = 10000000L; // 10^7
    num p[11];
    for(int i=0;i<11;i++) p[i]=i;
    num m[11]={0, 592830158L, 954427201L, 703125087L, 944791783L, 88541678L, 708091605L, 781901138L, 958891487L, 853515730L, 331853734L};
    num MOD = 1000000123L;
    num total = -2*218750027L;
    num termN = 218750027L*2;
    for(int u=1;u<=n;u++){
        for(int i=1;i<=10;i++){
            p[i] = (p[i]*p[i]) % MOD;
            total += p[i]*m[i] % MOD;
        }
        total %= MOD;
        termN *= 2;
        termN %= MOD;
    }
    std::cout << (total + termN) % MOD << "\n";
}
