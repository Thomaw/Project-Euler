#include <iostream>
using namespace std;
#define N 100
#define M 500
#define L (N*M)

double c[L][N+N+1];
void main() {
  for(int i=0; i<L; i++) {
    int x1=i%N; 
    int y1=i/N; 
    int x2,y2,r=4;
    if(x1==0 || x1==N-1)r--;
    if(y1==0 || y1==M-1)r--;
    c[i][N]=r;

    x2=(i-1)%N; 
    y2=(i-1)/N; 
    if(x1==x2 && abs(y1-y2)==1) c[i][N-1]=-1;
    if(y1==y2 && abs(x1-x2)==1) c[i][N-1]=-1;
    x2=(i+1)%N; 
    y2=(i+1)/N; 
    if(x1==x2 && abs(y1-y2)==1) c[i][N+1]=-1;
    if(y1==y2 && abs(x1-x2)==1) c[i][N+1]=-1;
    c[i][0]=c[i][N+N]=-1;
  }

  double s=1;
  int ss=0;

  for(int k=0; k<L-1; k++){
    double d1=c[k][N];
    s*=d1;
    if(s>10){s/=10;ss++;}
    for(int y=k+1, p=N-1;y<L && y<=k+N; y++,p--) {
      double dd=-c[y][p]/d1;
      for(int z1=p+1, z2=N+1; z2<=N+N; z1++,z2++) c[y][z1]+=dd*c[k][z2];
    }
  }
  cout.precision(5);
  cout << s << "e" << ss << endl;
}