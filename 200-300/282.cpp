#include <iostream>
#include <vector>
using namespace std;

#define lim 1475789056
#define lint __int64
#define gr 25000000

lint int rek(int A, int mod){
     if (A==1) return 2;
     if (mod==2) return 0;
     lint m=1, pom, suma;
     {
        vector <int> niz(gr,0);
        for (int i=1;i<=gr;i++) {
            m=(m*2)%mod;
            if (m<gr&&niz[m]) {pom=i-niz[m]; break;}
            if (m<gr) niz[m]=i;
        }
     }
     suma=rek(A-1,pom), m=1;
     for (int i=1;i<=suma;i++) m=(m*2)%mod;
     return m;
}

int main(){
    cout<<(rek(7,lim)+2*rek(10,lim)-9+1+3+7+61)%lim<<endl;;
    return 0;
}