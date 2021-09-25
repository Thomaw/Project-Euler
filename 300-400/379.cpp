#include <iostream>
#include <cstdlib>
#include <cmath>
#include<time.h>
using namespace std;

int i,k,J,DEL[500],TEK[500],d,D,D1,x,x1,y,z,y2,r,PR[1000],M;				
long long int GR=1000000000000,BG,BG1,OG,OG1;
long long int TOTAAL;
double start;
bool Q;

int main()
{
start=clock();
PR[1]=2;						
PR[2]=3;
M=5;J=2;
while(M<=1100){				 
	k=2;
	while(PR[k]*PR[k]<=M){	 
		if(!(M%PR[k])){
			M+=2;
			k=2;
		}		
		else k++;				
	}													
	PR[++J]=M;
	M+=2;
}
TOTAAL=0;
for(x=2;x<=1000000;x++)TOTAAL+=(GR/(long long int)x);
TOTAAL*=2;
TOTAAL+=GR;
DEL[0]=1;TEK[0]=1;
for(x=707107;x<=999999;x++){
	x1=x;k=1;d=0,D=0;D1=D;
	while(PR[k]*PR[k]<=x1){
		if(!(x1%PR[k])){
			for(i=0;i<=D;i++){
				DEL[++D1]=DEL[i]*PR[k];
				TEK[D1]=-1*TEK[i];
			}
			D=D1;
			while(!(x1%PR[k]))x1/=PR[k];
		}
		k++;
	}
	if(x1>1){
		for(i=0;i<=D;i++){
			DEL[++D1]=DEL[i]*x1;
			TEK[D1]=-1*TEK[i];
		}
		D=D1;
	}
	BG1=BG=GR/(long long int)x;
	for(d=1;d<=D;d++)BG+=(long long int)TEK[d]*(BG1/(long long int)DEL[d]);
	OG1=OG=(long long int)x;
	for(d=1;d<=D;d++)OG+=(long long int)TEK[d]*(OG1/(long long int)DEL[d]);
	TOTAAL+=(BG-OG);
}
cout<<"Voorlopig totaal "<<TOTAAL<<"\n";
for(x=707106;x>=2;x--){
	x1=x;k=1;d=0,D=0;D1=D;
	while(PR[k]*PR[k]<=x1){
		if(!(x1%PR[k])){
			for(i=0;i<=D;i++){
				DEL[++D1]=DEL[i]*PR[k];
				TEK[D1]=-1*TEK[i];
			}
			D=D1;
			while(!(x1%PR[k]))x1/=PR[k];
		}
		k++;
	}
	if(x1>1){
		for(i=0;i<=D;i++){
			DEL[++D1]=DEL[i]*x1;
			TEK[D1]=-1*TEK[i];
		}
		D=D1;
	}
	Q=1;
	BG1=BG=GR/(long long int)x;
	for(d=1;d<=D;d++)BG+=(long long int)TEK[d]*(BG1/(long long int)DEL[d]);
	z=1;
	while(Q){
		z++;
		OG1=OG=GR/((long long int)x*(long long int)z);
		if(OG1>20000LL&&OG1>(long long int)x){
			for(d=1;d<=D;d++)OG+=(long long int)TEK[d]*(OG1/(long long int)DEL[d]);
			TOTAAL+=(BG-OG)*(long long int)(z-1);
			BG1=OG1;BG=OG;
		}
		else{
			if(x>=20000){
				Q=0;
				OG=OG1=(long long int)x;
				for(d=1;d<=D;d++)OG+=(long long int)TEK[d]*(OG1/(long long int)DEL[d]);
				TOTAAL+=(BG-OG)*(long long int)(z-1);
			}
			else{
				Q=0;
				OG1=OG=20000LL;
				for(d=1;d<=D;d++)OG+=(long long int)TEK[d]*(OG1/(long long int)DEL[d]);
				TOTAAL+=(BG-OG)*(long long int)(z-1);
				BG1=OG1;BG=OG;
				for(y=x+1;y<=(int)BG1;y++){
					y2=y;x1=x;r=y2%x1;
					while(r>1){
						y2=x1;x1=r;r=y2%x1;
					}
					if(r)TOTAAL+=GR/((long long int)x*(long long int)y);
				}
			}
		}
	}
	//if(!(x%2000))cout<<x<<" "<<TOTAAL<<"\n";
}
cout<<"Totaal is "<<TOTAAL<<"\n";
cout<<clock()-start;
return 0;}