#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;
typedef struct Solution {
    long long a,b,c,d,e,f;
    double p;
    Solution(long long aa, long long bb, long long cc, long long dd, long long ee, long long ff, double pp) {
        a=aa;b=bb;c=cc;d=dd;e=ee;f=ff;p=pp;
        if (a<c || a==c && b<d) {
            long long t = a; a = c; c = t;
            t = b; b = d; d = t;
        }
        if (a<e || a==e && b<f) {
            long long t = a; a = e; e = t;
            t = b; b = f; f = t;
        }
        if (c<e || c==e && d<f) {
            long long t = c; c = e; e = t;
            t = d; d = f; f = t;
        }
    }
    bool operator<(const Solution& s) const {
        if (a!=s.a) return a<s.a;
        if (b!=s.b) return b<s.b;
        if (c!=s.c) return c<s.c;
        if (d!=s.d) return d<s.d;
        if (e!=s.e) return e<s.e;
        if (f!=s.f) return f<s.f;                                
        return false;
    }
};
set<Solution> sols;
long long maxrad = 40000;
double maxperim = 100000;
double finalans = 0;
void tryit(long long a, long long b, long long c, long long d, long long e, long long f) {
    if (a==c && b==d || a==e && b==f || c==e && d==f) return;
    double perim = sqrt((a-c)*(a-c)+(b-d)*(b-d)) + sqrt((a-e)*(a-e)+(b-f)*(b-f)) + sqrt((c-e)*(c-e)+(d-f)*(d-f));
    if (perim<=maxperim+1e-9) {
        Solution s(a,b,c,d,e,f,perim);
        int before = sols.size();
        sols.insert(s);
        if (sols.size()!=before) {
            finalans += perim;           
        }
    }
}
int main() {
    for (long long a=0; a<=maxrad; a++) {
        long long bmax = (long long)sqrt(maxrad*maxrad-a*a);
        for (long long b=-bmax; b<=bmax; b++) {
            long long K = a*a + b*b;
            long long X = 2*(5-a);
            long long Y = -2*b;
            long long Z = (5-a)*(5-a)+b*b;
            if (X==0) {
                if (Y==0) {
                    if (Z!=0) continue;
                    long long upto = (long long)sqrt(K);
                    for (long long c=-upto; c<=upto; c++) {
                        long long d2 = K-c*c;
                        long long d = (long long)sqrt(d2);
                        if (d*d==d2) {
                            tryit(a,b,c,d,5-a-c,-b-d);
                        }
                    }
                    continue;
                }
                if (Z%Y) continue;
                long long d = Z/Y;
                long long c2 = K-d*d;
                if (c2<0) continue;
                long long c = (long long)sqrt(c2);
                if (c*c!=c2) continue;
                long long e = 5-a-c;
                long long f = -b-d;
                tryit(a,b,c,d,e,f);
            } else {
                long long AA = X*X+Y*Y;
                long long BB = -2*Y*Z;
                long long CC = Z*Z-K*X*X;
                long long disc = Z*(4*K-Z);
                if (disc<0) continue;
                long long sqdisc = (long long)sqrt(disc);
                if (sqdisc*sqdisc!=disc) continue;
                sqdisc = 2*X*sqdisc;
                long long d1num = -BB + sqdisc;
                long long d2num = -BB - sqdisc;
                if (d1num%(2*AA)==0) {
                    long long d = d1num/(2*AA);
                    long long c1num = (Z-Y*d);
                    if (c1num%X==0) {
                        long long c = c1num/X;
                        long long e = 5-a-c;
                        long long f = -b-d;
                        tryit(a,b,c,d,e,f);
                    }
                } 
                if (d2num%(2*AA)==0) {
                    long long d = d2num/(2*AA);                    
                    long long c2num = (Z-Y*d);
                    if (c2num%X==0) {
                        long long c = c2num/X;
                        long long e = 5-a-c;
                        long long f = -b-d;
                        tryit(a,b,c,d,e,f);
                    }
                } 
                
            }
        }
    }
    printf("%f\n",finalans);
    system("PAUSE");
}