#include <iostream>
using namespace std;
long long get(long long a, long long b, long long m) {
    long long ret = 1;
    while (b) {
        if (b%2==1) ret = (ret*a)%m;
        a = (a*a)%m;
        b/=2;
    }
    return ret;
}
long long getphi(int pow2, int pow3, int pow13, int *phipow2, int *phipow3, int *phipow13){
    *phipow2 = (pow2==0?0:pow2-1) + (pow3==0?0:1) + (pow13==0?0:2);
    *phipow3 = (pow3==0?0:pow3-1) + (pow13==0?0:1);
    *phipow13 = (pow13==0?0:pow13-1);
    long long actualpow = 1;
    for (int i=0; i<*phipow2; i++) actualpow = (actualpow*2);
    for (int i=0; i<*phipow3; i++) actualpow = (actualpow*3);
    for (int i=0; i<*phipow13; i++) actualpow = (actualpow*13);        
    return actualpow;
}
long long calc(long long N, int depth, int pow2, int pow3, int pow13) {
    if (depth==0) return N;
    long long tot = 1;
    for (int i=0; i<pow2; i++) tot*=2;
    for (int i=0; i<pow3; i++) tot*=3;
    for (int i=0; i<pow13; i++) tot*=13;        
    // calculate C(C(.. [depth times] (N) mod 2^pow2 * 3^pow3 * 13^pow13
    /*
    first step: calculate (3^(m-2)-3)/2 mod phi(pow)
    ie          calculate (3^(m-3)-1) mod 2/3*phi(pow)        
    first step part 1: calculate m-3 mod phi(2/3*phi(pow))
    */
    int phipow2, phipow3, phipow13;
    long long phi = getphi(pow2,pow3,pow13,&phipow2,&phipow3,&phipow13);
    phipow2++;
    phi*=2;
    assert(phipow3);
    phipow3--;
    phi/=3;
    
    int ppow2, ppow3, ppow13;
    long long pp = getphi(phipow2,phipow3,phipow13,&ppow2,&ppow3,&ppow13);
    
    long long m = calc(N,depth-1,ppow2,ppow3,ppow13);
    m = (m+pp-3)%pp;
    long long n = get(3,m,phi);
    n = (n+phi-1)%phi;
    assert(n%2==0);
    n = n*3/2;    
    /*
    now we want 3^n mod tot
    */
    long long part1 = get(3,n,tot);
    /*
    now multiply the power by 2 and add three, mod phi to get the other power
    */
    n = (n*2+3)%phi;
    /*
    2^n mod tot
    */
    long long part2 = get(2,n,tot);
    long long ret = (part1*part2)%tot;
    return ret;
}
int main() {
    printf("%I64d\n",calc(10000,3,0,0,8));
}