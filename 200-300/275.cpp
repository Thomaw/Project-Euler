#include <iostream>
using namespace std;
const int N = 18;
int delta[4][2] = {{1,0},{-1,0},{0,-1},{0,1}};
int used[N+1][2*N+1];
int locs[N][2];
int weight = 0;
int minx=0, maxx=0;
int amount[2*N+1];
bool issquare[N+1][2*N+1];
void putsquare(int num, int a, int b, int type) {
    if (type==1) {
        issquare[a][b+N]=true;
        amount[b+N]++;
        weight += b;
        maxx>?=b;
        minx<?=b;
    } else {
        issquare[a][b+N]=false;
        amount[b+N]--;
        if (amount[b+N]==0) {
            if (b==maxx) maxx--;
            if (b==minx) minx++;
        }
        weight -= b;
    }
    used[a][b+N]+=type;
    if (type) {
        locs[num][0]=a;
        locs[num][1]=b;
    }
}
int ct = 0;
void solve(int upto) {
    if (upto==N) {
        if (weight==0) {
            bool issym = true;
            for (int i=0; i<N; i++) {
                if (!issquare[locs[i][0]][-locs[i][1]+N]) issym=false;
            }
            if (issym) ct += 2;
            else ct++;
        }
        return;
    }
    int tw = weight;    
    if (weight<0) {
        for (int i=upto; i<N; i++) {
            tw += maxx + (i-upto+1);
        }
        if (tw<0) return;
    } else if (weight>0) {
        for (int i=upto; i<N; i++) {
            tw += minx - (i-upto+1);
        }
        if (tw>0) return;
    }
    for (int i=0; i<upto; i++) {
        for (int j=0; j<4; j++) {
            int ta = locs[i][0]+delta[j][0];
            int tb = locs[i][1]+delta[j][1];
            if (ta<0) continue;
            if (!used[ta][tb+N]) {
                putsquare(upto,ta,tb,1);
                solve(upto+1);
                putsquare(upto,ta,tb,-1);
            }
            used[ta][tb+N]++;
        }
    }
    for (int i=0; i<upto; i++) {
        for (int j=0; j<4; j++) {
            int ta = locs[i][0]+delta[j][0];
            int tb = locs[i][1]+delta[j][1];
            if (ta<0) continue;
            used[ta][tb+N]--;
        }
    }
}
int main() {
    int start = clock();
    putsquare(0,0,0,1);
    solve(1);
    printf("%d\n",ct/2);
    printf("Time: %d\n",clock()-start);
}