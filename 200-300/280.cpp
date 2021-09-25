#include <iostream>
using namespace std;
double prob[5][5][2];
double exp[5], endprob[5];
int adj[5][5];
int delta[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
void solve(int x, int y, int state) {
    for (int i=0; i<5; i++)
    for (int j=0; j<5; j++) {
        prob[i][j][0]=(i==x && j==y)?1:0;
    }
    for (int i=0; i<5; i++) exp[i]=endprob[i]=0;
    
    int t = 0;
    
    for (int N=1; N<=2000; N++)
    {
        t = 1-t;
        for (int i=0; i<5; i++)
        for (int j=0; j<5; j++) prob[i][j][t]=0;

        for (int i=0; i<5; i++)
        for (int j=0; j<5; j++) {
            if (j==0 && state&(1<<i)) {}
            else {
                for (int k=0; k<4; k++) {
                    int ti = i+delta[k][0];
                    int tj = j+delta[k][1];
                    if (ti<0 || tj<0 || ti>=5 || tj>=5) continue;
                    prob[ti][tj][t] += prob[i][j][1-t]*1./adj[i][j];
                }
            }
        }
        for (int i=0; i<5; i++) {
            exp[i] += N*prob[i][0][t];
            endprob[i] += prob[i][0][t];
        }

    }
    for (int i=0; i<5; i++) 
    if (state&(1<<i)) {
        exp[i] /= endprob[i];

    }      

}
double memo[5][5][32][32];
double getfinalans(int x, int y, int state1, int state2) {
    if (memo[x][y][state1][state2]>-0.5) return memo[x][y][state1][state2];
    memo[x][y][state1][state2]=0;
    if (state1==0 && state2==0) return 0;

    int ty, state;
    if (y==0) {
        ty=4; state=state2;
    } else {
        ty=y; state=state1;
    }
    
    solve(x,ty,state);
    
    double tmp[5][2];
    for (int i=0; i<5; i++) {tmp[i][0]=exp[i]; tmp[i][1]=endprob[i];}
    double ret = 0;
    double here = 0;
    for (int i=0; i<5; i++) {
        if (state&(1<<i)) {
            ret += tmp[i][1] * (tmp[i][0] + getfinalans(i,0,state&~(1<<i),state1+state2-state));
            here += tmp[i][1];
        }
    }

    return memo[x][y][state1][state2]=ret;
}
int main() {
    memset(memo,-1,5*5*32*32*sizeof(double));
    for (int i=0; i<5; i++)
    for (int j=0; j<5; j++) {
        if (i>0) adj[i][j]++;
        if (i<4) adj[i][j]++;
        if (j>0) adj[i][j]++;
        if (j<4) adj[i][j]++;        
    }
    
    printf("%f\n",getfinalans(2,2,(1<<5)-1,(1<<5)-1));

    system("PAUSE");        
}