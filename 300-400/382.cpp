#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>
using namespace std;

int i,j,k,n;
long long int M[61][10][10],V[10],NV[10],MOD=1000000000LL,XX=999999999999999996LL;
bool Q[62];
double start;
int main(){
	start=clock();
	V[0]=2;V[8]=V[9]=1;
	M[0][0][0]=M[0][0][2]=M[0][0][7]=M[0][1][0]=M[0][2][1]=M[0][3][2]=M[0][4][3]=M[0][5][3]=M[0][6][5]=M[0][7][6]=M[0][5][7]=M[0][5][8]=M[0][9][9]=1;
	M[0][0][4]=M[0][5][4]=M[0][5][9]=-1;
	M[0][0][8]=7;M[0][8][8]=2;M[0][0][9]=-2;
	for(n=1;n<=60;n++){
		for(i=0;i<=9;i++){
			for(j=0;j<=9;j++){
				for(k=0;k<=9;k++){
					M[n][i][j]+=M[n-1][i][k]*M[n-1][k][j];
					while(M[n][i][j]<0)M[n][i][j]+=MOD;
					M[n][i][j]%=MOD;
				}
			}
		}
	}
	n=0;
	while(XX){
		if(XX%2)Q[n]=1;
		n++;
		XX/=2;
	}
	for(n=0;n<=59;n++){
		if(Q[n]){
			for(i=0;i<=9;i++){
				for(j=0;j<=9;j++){
					NV[i]+=M[n][i][j]*V[j];
					while(NV[i]<0)NV[i]+=MOD;
					NV[i]%=MOD;
				}
			}
			for(i=0;i<=9;i++){
				V[i]=NV[i];NV[i]=0;
			}
		}
	}
	cout<<"antwoord = "<<V[0]<<"\n"<<clock()-start;




return 0;}