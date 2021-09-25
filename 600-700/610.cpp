#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
using namespace std;

double TOTAAL=0.0,OK[1000],NK[1000],K;
int teller=0,i,j,J,J1,OW[1000],NW[1000],W;

int main(){
cout.precision(11);
OW[1]=0;OK[1]=1.0;J1=0;J=1;
while(teller<25){
    teller++;
    for(j=1;j<=J;j++){
        if(!(OW[j]%1000)){
            W=OW[j];K=OK[j]/50;TOTAAL+=(double)W*K;
            NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;NW[++J1]=W+10;NK[J1]=K*7;NW[++J1]=W+50;NK[J1]=K*7;NW[++J1]=W+100;NK[J1]=K*7;NW[++J1]=W+500;NK[J1]=K*7;NW[++J1]=W+1000;NK[J1]=K*7;
        }
        else{
            if(!(OW[j]%100)){
                switch (OW[j]%1000){
                case  100:
                    W=OW[j];K=OK[j]/50;TOTAAL+=(double)W*K;
                    NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;NW[++J1]=W+10;NK[J1]=K*7;NW[++J1]=W+50;NK[J1]=K*7;NW[++J1]=W+100;NK[J1]=K*7;NW[++J1]=W+300;NK[J1]=K*7;NW[++J1]=W+800;NK[J1]=K*7;
                    break;
                case 200:
                    W=OW[j];K=OK[j]/36;TOTAAL+=(double)W*K;
                    NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;NW[++J1]=W+10;NK[J1]=K*7;NW[++J1]=W+50;NK[J1]=K*7;NW[++J1]=W+100;NK[J1]=K*7;
                    break;
                case 300:
                    W=OW[j];K=OK[j]/29;TOTAAL+=(double)W*K;
                    NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;NW[++J1]=W+10;NK[J1]=K*7;NW[++J1]=W+50;NK[J1]=K*7;
                    break;
                case 400:
                    W=OW[j];K=OK[j]/29;TOTAAL+=(double)W*K;
                    NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;NW[++J1]=W+10;NK[J1]=K*7;NW[++J1]=W+50;NK[J1]=K*7;
                    break;
                case 500:
                    W=OW[j];K=OK[j]/36;TOTAAL+=(double)W*K;
                    NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;NW[++J1]=W+10;NK[J1]=K*7;NW[++J1]=W+50;NK[J1]=K*7;NW[++J1]=W+100;NK[J1]=K*7;
                    break;
                case 600:
                    W=OW[j];K=OK[j]/36;TOTAAL+=(double)W*K;
                    NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;NW[++J1]=W+10;NK[J1]=K*7;NW[++J1]=W+50;NK[J1]=K*7;NW[++J1]=W+100;NK[J1]=K*7;
                    break;
                case 700:
                    W=OW[j];K=OK[j]/36;TOTAAL+=(double)W*K;
                    NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;NW[++J1]=W+10;NK[J1]=K*7;NW[++J1]=W+50;NK[J1]=K*7;NW[++J1]=W+100;NK[J1]=K*7;
                    break;
                case 800:
                    W=OW[j];K=OK[j]/29;TOTAAL+=(double)W*K;
                    NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;NW[++J1]=W+10;NK[J1]=K*7;NW[++J1]=W+50;NK[J1]=K*7;
                    break;
                case 900:
                    W=OW[j];K=OK[j]/29;TOTAAL+=(double)W*K;
                    NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;NW[++J1]=W+10;NK[J1]=K*7;NW[++J1]=W+50;NK[J1]=K*7;
                    break;
                }
            }
            else{
                if(!(OW[j]%10)){
                    switch (OW[j]%100){
                    case  10:
                        W=OW[j];K=OK[j]/36;TOTAAL+=(double)W*K;
                        NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;NW[++J1]=W+10;NK[J1]=K*7;NW[++J1]=W+30;NK[J1]=K*7;NW[++J1]=W+80;NK[J1]=K*7;
                        break;
                    case 20:
                        W=OW[j];K=OK[j]/22;TOTAAL+=(double)W*K;
                        NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;NW[++J1]=W+10;NK[J1]=K*7;
                        break;
                    case 30:
                        W=OW[j];K=OK[j]/15;TOTAAL+=(double)W*K;
                        NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;
                        break;
                    case 40:
                        W=OW[j];K=OK[j]/15;TOTAAL+=(double)W*K;
                        NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;
                        break;
                    case 50:
                        W=OW[j];K=OK[j]/22;TOTAAL+=(double)W*K;
                        NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;NW[++J1]=W+10;NK[J1]=K*7;
                        break;
                    case 60:
                        W=OW[j];K=OK[j]/22;TOTAAL+=(double)W*K;
                        NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;NW[++J1]=W+10;NK[J1]=K*7;
                        break;
                    case 70:
                        W=OW[j];K=OK[j]/22;TOTAAL+=(double)W*K;
                        NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;NW[++J1]=W+10;NK[J1]=K*7;
                        break;
                    case 80:
                        W=OW[j];K=OK[j]/15;TOTAAL+=(double)W*K;
                        NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;
                        break;
                    case 90:
                        W=OW[j];K=OK[j]/15;TOTAAL+=(double)W*K;
                        NW[++J1]=W+1;NK[J1]=K*7;NW[++J1]=W+5;NK[J1]=K*7;
                        break;
                    }
                }
                else{
                    switch (OW[j]%10){
                    case  1:
                        W=OW[j];K=OK[j]/22;TOTAAL+=(double)W*K;TOTAAL+=(double)(W+3)*7.0*K;TOTAAL+=(double)(W+8)*7.0*K;
                        NW[++J1]=W+1;NK[J1]=K*7;
                        break;
                    case 2:
                        W=OW[j];K=OK[j]/8;TOTAAL+=(double)W*K;TOTAAL+=(double)(W+1)*7.0*K;
                        break;
                    case 5:
                        W=OW[j];K=OK[j]/8;TOTAAL+=(double)W*K;
                        NW[++J1]=W+1;NK[J1]=K*7;
                        break;
                    case 6:
                        W=OW[j];K=OK[j]/8;TOTAAL+=(double)W*K;
                        NW[++J1]=W+1;NK[J1]=K*7;
                        break;
                    case 7:
                        W=OW[j];K=OK[j]/8;TOTAAL+=(double)W*K;TOTAAL+=(double)(W+1)*7.0*K;
                        break;
                    }
                }
            }
        }
    }
    J=J1;J1=0;
    if(J>0){
        for(j=1;j<=J;j++){
            OW[j]=NW[j];OK[j]=NK[j];
            NW[j]=0.0;NK[j]=0.0;
        }
    }
}
cout<<"totaal is "<<TOTAAL<<"\n";

return 0;
}