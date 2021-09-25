#include <iostream>
#include <iomanip>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 11;
vector< vector<int> > s;

void rec(vector<int> &v, int sum){
    if (sum==N) {
        s.push_back(v);
        return;
    }

    int a=N-sum;
    if (v.size()>0 && v.back()<a) {
        a=v.back();
    }
    for(int i=a;i>=1;i--){
        v.push_back(i);
        rec(v,sum+i);
        v.pop_back();
    }

}

int binom(int n, int k){
    int res = 1;
    for(int i=1;i<=k;i++){
        res*=n-i+1;
        res/=i;
    }
    return res;
}

int fact(int n){
    int res=1;
    for(int i=1;i<=n;i++){
        res*=i;
    }
    return res;
}

int getnr(vector<int> &v){
    int res = 1;
    int n=N;
    int sm=0;
    int denom=1;
    for(int i=0;i<v.size();i++){
        res*=binom(n,v[i])*fact(v[i]-1);
        n-=v[i];
        if (i>0 && v[i]!=v[i-1]){
            denom*=fact(sm);
            sm=1;
        } else {
            sm++;
        }

    }
    denom*=fact(sm);
    res/=denom;
    return res;
}

void getrep(const vector<int> &v, vector<int> &rep){
    if (rep.size()!=N) {
        rep.resize(N);
    }
    for(int i=0;i<N;i++) rep[i]=i;

    int j0=0;
    for(int i=0;i<v.size();i++){
        int j;
        int tmp=rep[j0];
        for(j=j0;j<j0+v[i]-1;j++){
            rep[j]=rep[j+1];
        }
        rep[j]=tmp;

        j0+=v[i];
    }
}

int maprep(vector<int> rep){
    vector<int> v;

    while (true) {
        int nr=0;
        int i;
        for(i=0;i<N && rep[i]<0;i++);
        if (i==N) break;
        while(rep[i]>=0){
            int j=rep[i];
            rep[i]=-1;
            i=j;
            nr++;
        }
        v.push_back(nr);
    }

    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());

    int res = find(s.begin(),s.end(),v)-s.begin();

if (res==s.size()) {
cout<<"ERROR!!!"<<endl;
}

    return res;
}

int main()
{
    vector<int> v;
    rec(v,0);
cout<<s.size()<<endl;

    vector<int> snr(s.size());
    int all=0;
    for(int i=0;i<s.size();i++){
        snr[i] = getnr(s[i]);
        all+=snr[i];

cout<<i<<": ";
for(int j=0;j<s[i].size();j++) cout<<s[i][j]<<" ";
cout<<": "<<snr[i]<<endl;
    }
cout<<all<<endl;

    vector< vector<int> > mtx(s.size(),vector<int>(s.size(),0)); //mtx[i][j]=k => from i to j there are k transitions


    for(int i0=0;i0<N-2;i0++){
        for(int i1=i0+1;i1<N-1;i1++){
            for(int i2=i1+1;i2<N;i2++){
                for(int i=0;i<s.size();i++){
                    //shuffle 1 out of 3!=6
                    {
                        vector<int> rep;
                        getrep(s[i],rep);
                        //123->123
                        int j=maprep(rep);
                        mtx[i][j]++;
                    }
                    //shuffle 2 out of 3!=6
                    {
                        vector<int> rep;
                        getrep(s[i],rep);
                        //123->213
                        swap(rep[i0],rep[i1]);
                        int j=maprep(rep);
                        mtx[i][j]++;
                    }
                    //shuffle 3 out of 3!=6
                    {
                        vector<int> rep;
                        getrep(s[i],rep);
                        //123->312
                        swap(rep[i0],rep[i2]);
                        int j=maprep(rep);
                        mtx[i][j]++;
                    }
                    //shuffle 4 out of 3!=6
                    {
                        vector<int> rep;
                        getrep(s[i],rep);
                        //123->132
                        swap(rep[i1],rep[i2]);
                        int j=maprep(rep);
                        mtx[i][j]++;
                    }
                    //shuffle 5 out of 3!=6
                    {
                        vector<int> rep;
                        getrep(s[i],rep);
                        //123->312
                        swap(rep[i0],rep[i2]);
                        swap(rep[i1],rep[i2]);
                        int j=maprep(rep);
                        mtx[i][j]++;
                    }
                    //shuffle 5 out of 3!=6
                    {
                        vector<int> rep;
                        getrep(s[i],rep);
                        //123->231
                        swap(rep[i0],rep[i1]);
                        swap(rep[i1],rep[i2]);
                        int j=maprep(rep);
                        mtx[i][j]++;
                    }
                }
            }
        }
    }

    //slightly change the matrix: from sorted state you go always back to the sorted state.
    {
        int nr=0;
        for(int i=0;i<s.size();i++){
            nr+=mtx[s.size()-1][i];
            mtx[s.size()-1][i]=0;
        }
        mtx[s.size()-1][s.size()-1]=nr;
    }

    //converting to sparse matrix
    vector< vector<int> > mtx2(s.size()); //mtx[i][j]=k => from i to j there are k transitions
    for(int i=0;i<s.size();i++){
        for(int j=0;j<s.size();j++){
            if (mtx[i][j]>0) {
                mtx2[i].push_back(j);
            }
        }
    }



for(int i=0;i<s.size();i++){
    for(int j=0;j<s.size();j++){
        cout<<setw(4)<<mtx[i][j];
    }
    cout<<endl;
}

    vector<long double> p0(s.size(),0);
    vector<long double> p1(s.size());
    for(int i=0;i<s.size();i++){
        p1[i]=(long double)snr[i]/all;
    }

    long double oneroute = 1.0L/(N*(N-1)*(N-2)); // -> 1/(binom(n,3)*3!)

    long double res = 0;
    for(int i=0;i<=2000000000;i++){

        res+=(p1[s.size()-1]-p0[s.size()-1])*i;
if (i%50000==0) cout<<i<<": "<<setprecision(20)<<setw(20)<<res<<" ("<<(p1[s.size()-1]-p0[s.size()-1])*i<<")"<<endl;
        p0=p1;
        for(int j=0;j<p1.size();j++) p1[j]=0;

        for(int k=0;k<s.size();k++){
            for(int j=0;j<mtx2[k].size();j++){
                p1[ mtx2[k][j] ]+=p0[k]*oneroute*mtx[k][ mtx2[k][j] ];
            }
        }

/*
        for(int j=0;j<s.size();j++){
            p1[j]=0;
            for(int k=0;k<s.size();k++){
                p1[j]+=p0[k]*oneroute*mtx[k][j];
            }
        }
*/
    }

    return 0;
}