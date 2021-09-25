#include <iostream>

long long r(int * t, int n);
int main()
{
    const int N = 10000000;
    int * t = new int [N+1];
    long long s = 290797;
    for(int i=0; i<N+1; i++){
        t[i] = s%64 + 1;
        s = s*s%50515093;
    }
    std::cout << r(t,N) << "\n";
    delete [] t;
    return 0;
}
long long r(int * t, int n){
    if(n==0) return t[0]*t[0];
    int c = 0, tt;
    for(int i=0; i<n; i+=2){
        tt = t[i];
        t[i+1] < t[i]+c ? t[i] = t[i+1] : t[i] = t[i]+c;
        t[i+1] = t[i+1] + t[i+2] - t[i];
        c = c + tt - t[i];
    }
    t[n] += c;
    int j = 0;
    long long ssq = 0;
    while(j<n && t[j]<t[j+1]){
        ssq += t[j]*t[j];
        j+=2;
    }
    if(j==n) return ssq + t[n]*t[n];
    int surpl, m, k;
    while(j<n){
        surpl = t[j] - t[j+1];
        k = j;
        while(surpl>0 && j<n-2){
            j+=2;
            surpl += t[j]-t[j+1];
        }
        if(j==n-2) j+=2;
        m = j-k;
        int * tsub = new int [m+1];
        for(int i=0; i<m+1; i++) tsub[i] = t[k+i];
        ssq += r(tsub,m);
        delete [] tsub;
        j+=2;
    }
    return ssq;
}