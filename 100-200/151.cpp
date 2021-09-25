#include "stdafx.h"
#include <stdio.h>
#include <math.h>

double probability[30][10][10][10][10];
int i,j,k,l,m;
double total;

int main()
{
	for(i=0;i<30;i++)
		for(j=0;j<10;j++)
			for(k=0;k<10;k++)
				for(l=0;l<10;l++)
					for(m=0;m<10;m++)
						probability[i][j][k][l][m]=0;

	probability[1][1][1][1][1]=1;
	for(i=1;i<=15;i++)
	{
		for(j=0;j<9;j++)
			for(k=0;k<9;k++)
				for(l=0;l<9;l++)
					for(m=0;m<9;m++)
					{
						total=(double)(k+l+m+j);
						if(m>0)
						{
							probability[i+1][j][k][l][m-1]+=(double)m/total*probability[i][j][k][l][m];
						}
					
						if(l>0)
						{
							probability[i+1][j][k][l-1][m+1]+=(double)l/total*probability[i][j][k][l][m];
						}
						if(k>0)
						{
							probability[i+1][j][k-1][l+1][m+1]+=(double)k/total*probability[i][j][k][l][m];
						}
						if(j>0)
						{
							probability[i+1][j-1][k+1][l+1][m+1]+=(double)j/total*probability[i][j][k][l][m];
							
						}
						//printf("%lf %lf\n",total,probability[i][j][k][l][m]);
					}
	}


	double expval=0;
	for(i=2;i<16;i++)
	{
		expval+=probability[i][1][0][0][0]+probability[i][0][1][0][0]+probability[i][0][0][1][0]+probability[i][0][0][0][1];
	}
printf("%lf\n",probability[16][0][0][0][0]);

printf("%1.10f\n",expval);


}