#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
FILE *in = fopen("sudoku.txt", "r"), *out = fopen("sudoku.out", "w");

int n,data[9][9];
int partt(int i, int j)
{
	if (i<3)
	{
		if (j<3) return 0;
		else if (j<6) return 1;
		else return 2;
	}
	else if (i<6)
	{
		if (j<3) return 3;
		else if (j<6) return 4;
		else return 5;
	}
	else
	{
		if (j<3) return 6;
		else if (j<6) return 7;
		else return 8;
	}
}
bool col[9][10],row[9][10],sq[9][10];
int nz;
void inita (void)
{
	int t,i,j;nz=0;
	for (i=0;i<9;i++)
	{
		for (j=1;j<=9;j++)
		{
			col[i][j]=false;
			row[i][j]=false;
			sq[i][j]=false;
		}
	}
	for (i=0;i<9;i++)
	{
		for (j=0;j<9;j++)
		{
			if (data[i][j]==0) nz++;
			else
			{
				t=partt(i,j);
				col[j][data[i][j]]=true;
				row[i][data[i][j]]=true;
				sq[t][data[i][j]]=true;
			}
		}
	}
}
bool dfs (int depth)
{
	if (depth==0) return true;
	bool curr[20];
	int i,j,t,k,c,best=10,besti=0,bestj=0;
	for (i=0;i<9;i++)
	{
		for (j=0;j<9;j++)
		{
			if (data[i][j]==0)
			{
				t=partt(i,j);c=9;
				for (k=1;k<=9;k++) curr[k]=false;
				for (k=1;k<=9;k++) if (col[j][k]) curr[k]=true;
				for (k=1;k<=9;k++) if (row[i][k]) curr[k]=true;
				for (k=1;k<=9;k++) if (sq[t][k]) curr[k]=true;
				for (k=1;k<=9;k++) if (curr[k]) c--;
				if (c==0) return false;
				if (c<best) {best=c; besti=i; bestj=j;}
			}
		}
	}
	t=partt(besti,bestj);
	for (k=1;k<=9;k++) curr[k]=false;
	for (k=1;k<=9;k++) if (col[bestj][k]) curr[k]=true;
	for (k=1;k<=9;k++) if (row[besti][k]) curr[k]=true;
	for (k=1;k<=9;k++) if (sq[t][k]) curr[k]=true;
	for (i=1;i<=9;i++)
	{
		if (!curr[i])
		{
			data[besti][bestj]=i;
			col[bestj][i]=true;
			row[besti][i]=true;
			sq[t][i]=true;
			if (dfs(depth-1)) return true;
			col[bestj][i]=false;
			row[besti][i]=false;
			sq[t][i]=false;
			data[besti][bestj]=0;
		}
	}
	return false;
}
int main(void)
{
	int i,j,k,ret=0,s; char c;
	fscanf(in,"%i\n",&n);
	for (k=0;k<n;k++)
	{
		printf("Doing puzzle #%i\n",k+1);
		fscanf(in,"%c%c%c",&c,&c,&c);
		for (i=0;i<9;i++)
		{
			for (j=0;j<9;j++)
			{
				fscanf(in,"%c",&c);
				data[i][j]=c-'0';
			}
			fscanf(in,"%c",&c);
		}
		inita();
		dfs(nz);
		for (i=0;i<9;i++)
		{
			for (j=0;j<9;j++)
			{
				fprintf(out,"%i",data[i][j]);
			} fprintf(out,"\n");
		}
		s=data[0][0]*100+data[0][1]*10+data[0][2];
		ret+=s;
		fprintf(out,"Answer code = %i\n",s);
		fprintf(out,"\n");
	}
	fprintf(out,"Desired sum = %i\n",ret);
	fclose(in); fclose(out); return 0;
}