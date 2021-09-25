#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#define MODD 100000000
using namespace std;
#define ll long long
ll N;


ll POWTWO(ll x) {
    ll ts = 2;
    ll answer = 1;
    while(x) {
        if (x&1) {
            answer = (answer * ts)%MODD;
        }
        ts = (ts * ts)%MODD;
        x/=2;
    }
    return answer;
}


ll POW(ll b, ll x) {
    ll ts = b%MODD;
    ll answer = 1;
    while(x) {
        if (x&1) {
            answer = (answer * ts)%MODD;
        }
        ts = (ts * ts)%MODD;
        x/=2;
    }
    return answer;
}

ll gcd(ll a,ll b) {
    while(b!=0) {
        ll t = b;
        b=a%t;
        a=t;
    }
    return a;
}


ll f0(ll kmax) {
    return POWTWO(kmax)%MODD-1-kmax%MODD;
}

ll f1(ll kmax) {
    //return kmax * POWTWO[kmax] - 1 - (kmax * (kmax + 1))/2;
    ll answer = (kmax - 1)%MODD * POWTWO(kmax)%MODD + 1 %MODD;
    
    ll a = kmax;
    ll b = kmax+1;
    if(kmax&1)
        b/=2;
    else
        a/=2;
    a%=MODD;
    b%=MODD;
    answer = (answer - a%MODD*b%MODD)%MODD;
    return answer;
}

ll f2(ll kmax) {
    
    ll answer = POWTWO(kmax) %MODD * (kmax%MODD*kmax%MODD-2*kmax%MODD+3) - 3;
    
    ll a = kmax;
    ll b = kmax+1;
    ll c = 2*kmax+1;
    ll denom = 6;
    
    ll gcdval;
    gcdval = gcd(a,denom);
    a/=gcdval;
    denom/=gcdval;
    gcdval = gcd(b,denom);
    b/=gcdval;
    denom/=gcdval;
    gcdval = gcd(c,denom);
    c/=gcdval;
    
    a%=MODD;
    b%=MODD;
    c%=MODD;
    
    
    answer = (answer - a%MODD*b%MODD*c%MODD)%MODD;
    return answer;
}

ll sumone(ll x) {
    ll xm = x-1;
    if(x&1) {
        xm/=2;
    } else {
        x/=2;
    }
    x%=MODD;
    xm%=MODD;
    return x%MODD*xm%MODD;
}

ll sumone(ll lowx, ll highx) {
    if(lowx > highx)
        return 0;
    else
        return sumone(highx) - sumone(lowx-1);
}

ll sumtwo(ll x) {
    ll a = x;
    ll b = x+1;
    ll c= x-1;
    ll d= 3*x+2;
    ll denom = 24;
    ll gcdval;
    gcdval = gcd(a,denom);
    a/=gcdval;
    denom/=gcdval;
    gcdval = gcd(b,denom);
    b/=gcdval;
    denom/=gcdval;
    gcdval = gcd(c,denom);
    c/=gcdval;
    denom/=gcdval;
    gcdval = gcd(d,denom);
    d/=gcdval;
    denom/=gcdval;
    a%=MODD;
    b%=MODD;
    c%=MODD;
    d%=MODD;
    return a%MODD*b%MODD*c%MODD*d%MODD;
}


ll sumtwo(ll lowx, ll highx) {
    if(lowx > highx)
        return 0;
    else
        return sumtwo(highx) - sumtwo(lowx-1);
}


ll sumthree(ll x) {
    ll a = x;
    ll b = x+1;
    ll c = x-1;
    ll denom = 6;
    
    ll gcdval;
    gcdval = gcd(a,denom);
    a/=gcdval;
    denom/=gcdval;
    gcdval = gcd(b,denom);
    b/=gcdval;
    denom/=gcdval;
    gcdval = gcd(c,denom);
    c/=gcdval;
    a%=MODD;
    b%=MODD;
    c%=MODD;
    return a%MODD*b%MODD*c%MODD;
}

ll sumthree(ll lowx, ll highx) {
    if(lowx > highx)
        return 0;
    else
        return sumthree(highx) - sumthree(lowx-1);
}


ll summit(ll lowx, ll highx, ll k, ll tmax) {
    
    
    return ((N%MODD+1)*(N%MODD+1)%MODD*(f0(tmax)%MODD)%MODD*(sumone(lowx, highx)%MODD)%MODD + ((k%MODD) * (k%MODD) %MODD * (f2(tmax)%MODD))%MODD * sumtwo(lowx, highx)%MODD - ((3*k%MODD*(N%MODD+1)%MODD)*f1(tmax)%MODD)%MODD*sumthree(lowx, highx)%MODD)%MODD;
    
    
    //((N+1)%MODD*(N+1)%MODD*f0(tmax)%MODD*(dx-1)%MODD + k%MODD*k%MODD* dx%MODD * f2(tmax)%MODD*(dx*(dx-1))/2 - k*((N+1) * f1(tmax) * 3* dx*(dx-1))/2)
}


ll sumit(ll low, ll high) {
    
    ll max_prime = (ll)sqrt(high+0.1)+2;
    vector<bool> isprime(max_prime+1, true);
    //printf("%lld\n",max_prime);
    vector<vector<int> > allprimedivs(high - low + 1);
    //printf("here0\n");

    clock_t starttime=clock();

    for(long long i=2;i<=max_prime;i++) {
        if(isprime[i]) {
            long long low_d = low / i;
            long long high_d = high / i;
            for(long long k=low_d;k<=high_d+2;k++) {
                if (k*i>=low && k*i<=high) {
                    allprimedivs[k*i-low].push_back(i);
                }
            }
            for (long long j = i; j <= max_prime/i; ++j) {
                isprime[j*i]=false;
            }
        }
    }


    printf("here\n");
     
    vector<int> moebius(high-low+1, 0);
    for(long long i = low; i <= high; ++i) {
        moebius[i-low]=1;
        const vector<int>& divs = allprimedivs[i-low];
        long long k = i;
        for(int j=0;j<divs.size();j++) {
            int ct = 0;
            while(k%divs[j]==0) {
                k/=divs[j];
                ct++;
            }
            if(ct>=2)
                moebius[i-low]=0;
            else
                moebius[i-low]=-moebius[i-low];
        }
        if(k>1) {
            moebius[i-low]=-moebius[i-low];
        }
        
    }
    
    //printf("%E\n",(clock()-starttime)/(1.0*CLOCKS_PER_SEC)/((max_prime + high-low+1)));

    
    long long answer = 0;
    for(long long k=low;k<=high;k++) {
        if(moebius[k-low]==0)
            continue;
        
        
        long long curr_dx = 2;
        clock_t starttime=clock();

        ll steps = 0;
        while(curr_dx <= N) {
            steps++;
            long long tmax = N/(curr_dx*k);
            if(tmax==0)
                break;
            long long last_dx = max(curr_dx, N/(tmax*k));
            
            // curr_dx to last_dx
            answer = (answer + 4*moebius[k-low] * summit(curr_dx, last_dx, k, tmax))%MODD;
            curr_dx = last_dx + 1;
        }
        
       // printf("k=%lld, steps=%lld, time = %lf %E\n",k,steps,(clock()-starttime)/(1.0*CLOCKS_PER_SEC),(clock()-starttime)/(1.0*CLOCKS_PER_SEC)/steps);
    }
    
    while(answer < 0)
        answer=(answer+MODD)%MODD;
    return answer%MODD;
}

double compute_complexity(ll a, ll b, ll N) {
    return (b-a+0.0+sqrt(b))*0.37e-6 + 3.4*1e-6 * (sqrt(b)-sqrt(a) + 1) * sqrt(N);
}

bool possible(ll a, ll b, ll N, double maxcomplex) {
    double curr_complex =  compute_complexity(a, b, N);
    return curr_complex <= maxcomplex;
}

int main(int argc, char* argv[]) {
    
    N = 0;
    for(int i=0;argv[1][i]!='\0';i++)
        N=N*10+argv[1][i]-'0';

    
    
    
    
    

    
    ll LOW = 1;
    ll UP =  N;

    
    ll answer2=sumit(LOW, UP);

    cout << answer2%MODD << endl;

    ll a,b,c;
    a=N+1;
    b=N;
    if(N&1)
        a/=2;
    else
        b/=2;
    
    
    answer2 = (answer2  + (2*N+2)%MODD * (POWTWO(N+1)%MODD - 1 - (N+1) -  (a%MODD*b%MODD)%MODD) )%MODD;

    answer2 = (answer2 + 2*((POWTWO(N+1) - 1 - (N+1) - (a%MODD*b%MODD)%MODD)))%MODD;
    
    a = N-1;
    b=N;
    c=2*N-1;
    if(a%3==0) {
        a/=3;
    } else if(b%3==0) {
        b/=3;
    } else if(c%3==0) {
        c/=3;
    }
    
    answer2 += 8 * (POWTWO(N)-2) - 3 * N %MODD * (N-1)%MODD - 8 * (N-1)%MODD - a%MODD*b%MODD*c%MODD;
    
    
    
    answer2 += (N+1)%MODD*(N+1)%MODD;
    answer2 ++;
    
    answer2%=MODD;
    printf("B3=%lld %lld\n",answer2,POWTWO(N+1)%MODD);
    answer2 = POW(POWTWO(N+1)%MODD, N+1) - answer2;
    while(answer2<0)
        answer2=(answer2+MODD)%MODD;
    printf("Bfinal=%lld\n",answer2%MODD);

    return 0;
    
}
