#include <stdio.h>


int main()  {
	
	int i,j,k,s;
        double A,B,maxi,maxi2,p[101][101],pow2[10];
	
	pow2[0]=1.0;
	for(i=1;i<10;i++)  pow2[i]=0.5*pow2[i-1];
	for(i=0;i<100;i++)  p[100][i]=0.0,p[i][100]=1.0;
	p[100][100]=1.0;
	for(i=99;i>=0;i--)  {
		for(j=99;j>=0;j--)  {
			maxi=0.0;
			for(k=1;j+(1<<(k-1))<=200;k++)  {
                           s=j+(1<<(k-1));
			   if(s>100)  s=100;
                           A=1.0-(1.0-pow2[k])*0.5;
			   B=(1.0-pow2[k])*0.5*p[i+1][j]+pow2[k]*(0.5*p[i][s]+0.5*p[i+1][s]);
			   maxi2=B/A;
			   if(maxi<maxi2)  maxi=maxi2;
		        }
			p[i][j]=maxi;
		}
	}
	printf("%.8lf\n",0.5*(p[0][0]+p[1][0]));
	return 0;
}