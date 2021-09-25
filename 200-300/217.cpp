#include <iostream>
#include <ctime>
using namespace std;
typedef unsigned long long ui;

// up to 10^n
const int n=1000;
const int MOD=14348907;

// x[i][k] is number of i digit numbers with digitsum = k.
// s[i][k] is sum of i digit numbers with digitsum = k.
// L is without leading zeroes, R is with leading zeroes.
ui xL[2][(n/2)*9+1], xR[2][(n/2)*9+1];
ui sL[2][(n/2)*9+1], sR[2][(n/2)*9+1];
ui P10[n+1];

int main() {
  double dt=clock();
  ui S=50040;
  ui X=108;
  
  // precomputing 10^k
  P10[0]=1;
  for(short i=1;i<=n;i++) P10[i]=(10*P10[i-1]) % MOD; 
    
  // initialising dp 
  for(int i=0;i<10;i++) {
     xL[1][i]=xR[1][i]=1;
     sL[1][i]=sR[1][i]=i;
  }
  xL[1][0]=0;
  
  // dp
  for(int i=2;i<=n/2;i++) {
     short i0=i%2, i1=(i+1)%2;
     
     for(int k=0;k<=i*9;k++) {
        xL[i0][k]=xR[i0][k]=0;
        sL[i0][k]=sR[i0][k]=0;
     }
     
     for(short j=0;j<=9;j++) {
        for(int k=0;k<=(i-1)*9;k++) {
           if(j>0) xL[i0][k+j]+=xR[i1][k];
                   xR[i0][k+j]+=xR[i1][k];
           
           if(k>0) sL[i0][k+j]+=10*sL[i1][k]+j*xL[i1][k];
                   sR[i0][k+j]+=10*sR[i1][k]+j*xR[i1][k];
        }
     }
     
     for(int k=0;k<=i*9;k++) {
        xL[i0][k]%=MOD; xR[i0][k]%=MOD;
        sL[i0][k]%=MOD; sR[i0][k]%=MOD;
     }
     
     for(int j=1;j<=i*9;j++) {       
        S+=sR[i0][j]*xL[i0][j];
        S+=sL[i0][j]*((xR[i0][j]*P10[i])%MOD);
        X+=xL[i0][j]*xR[i0][j];
        
        X%=MOD; S%=MOD;
     }
     
     if(i!=n/2 || (n/2)*2!=n) {
       for(int j=1;j<=i*9;j++) {
          S+=sR[i0][j]*xL[i0][j]*10;
          S+=sL[i0][j]*((xR[i0][j]*P10[i+2])%MOD);
          S+=xL[i0][j]*((xR[i0][j]*45*P10[i])%MOD);
          X+=xL[i0][j]*xR[i0][j]*10;
          
          X%=MOD; S%=MOD;
       }
     }
  }
    
  cout<<n<<" -> "<<S<<" in "<<(clock()-dt)/1000<<" seconds"<<endl;
  system("Pause");
  return 0;
}
