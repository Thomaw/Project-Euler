long long getsum(long long len, long long power) {
    if (power==0) return len;
    else if (power==1) return (len*len+len)/2;
    else if (power==2) return (2*len*len*len+3*len*len+len)/6;
}
long long getdiff(long long A, long long B, long long power) {
    return getsum(B,power)-getsum(A,power);
}
long long numtris(long long P) {
    long long K = P/3;
    long long part1 = (getsum(K,2) + getsum(K,1))/2;
    long long a = 1 - 3*3;
    long long b = 1 - (3*(1-P) - P*3);
    long long c = 0 - (-P)*(-P+1);
    long long lim = (P-1)/2;
    long long part2 = (a*getdiff(K,lim,2) + b*getdiff(K,lim,1) + c*getdiff(K,lim,0))/2;
    long long part3 = getsum(P/4,1);
    long long part4 = -3*getdiff(P/4,P/3,1) + (P+1)*getdiff(P/4,P/3,0);
    long long total = part1 + part2 + part3 + part4;
    total/=2;
    return total;
}