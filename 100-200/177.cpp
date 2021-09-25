#include <stdio.h>
#include <math.h>
int isint(double x);
double fabs(double x);

  long long int count;
double duparray[100][20];

double PIeight=3.14159265358979323846264338327950288419716939937510/180.0;
int main()
{
  double x,w,m;
  int  a,b,c,d;
  double maxxvalue;
  
  int iopt;
  int I,j;
  int N;
  count=0;
  double sine[200];
  double cosine[200];
  for(int i=1;i<=180;i++)
    {
      if(i<=90)
	{
	sine[i]=sin(PIeight*(double)i);
	cosine[i]=cos(PIeight*(double)i);
	}
      else
	{
	sine[i]=sine[180-i];
	cosine[i]=-cosine[180-i];
	}
    }
  
  for(int  alpha=1;alpha<=45;alpha++)
    {
       for(int beta=alpha;beta<180-alpha;beta++)
	{
	  
	  for(int gamma=alpha;gamma<=180-alpha-beta-alpha;gamma++)
	    {
	      w=sine[alpha+beta]/sine[alpha+beta+gamma];
	      int b=180-alpha-beta-gamma;
	      for(int delta=alpha;delta<=180-gamma-beta-alpha;delta++)
		{
		  x=sine[beta]/sine[beta+gamma+delta];
		  m=sqrt(w*w+x*x-2*w*x*cosine[delta]);
		  if(x*sine[delta]>m)
		    a=90;
		  else
		    a=(int)(round)(1.0/PIeight*asin(x*sine[delta]/m));
		  if(m*m+w*w-x*x<0)
		    a=180-a;		  
		  d=180-beta-gamma-delta;
		 
		  c=360-a-b-alpha-beta-gamma-delta-d;
		  
		  if(a>=alpha && c>=alpha && a+b+c+d+alpha+beta+gamma+delta==360)
		    {
		      if(fabs((sine[delta]*sine[c]/(sine[a]*sine[d]))-(sine[gamma]*sine[alpha]/(sine[beta]*sine[b])))<1e-11)
		      {
		      duparray[1][1]=(double)alpha;
		      duparray[1][2]=(double)beta;
		      duparray[1][3]=(double)gamma;
		      duparray[1][4]=(double)delta;
		      duparray[1][5]=(double)d;
		      duparray[1][6]=(double)c;
		      duparray[1][7]=(double)a;
		      duparray[1][8]=(double)b;
		      for(I=1;I<=3;I++)
			  for(j=1;j<=8;j++)
			    duparray[I+1][j]=duparray[1][(j+I*2-1)%8+1];
		      for(j=1;j<=8;j++)
			duparray[5][9-j]=duparray[1][j];
		      
		      for(I=1;I<=3;I++)
			  for(j=1;j<=8;j++)
			    duparray[I+5][j]=duparray[5][(j+I*2-1)%8+1];
		      N=8;
		      maxxvalue=1e22;
		      iopt=1;
		      for(I=1;I<=N;I++)
			{
			  duparray[I][9]=0;
			  for(j=1;j<=8;j++)
			    duparray[I][9]=duparray[I][9]*180+duparray[I][j];
			    
			  if(duparray[I][9]<maxxvalue-1e-7)
			    {
			    maxxvalue=duparray[I][9];
			      iopt=I;
			    }
			}
			  
			  
			  
			  if(iopt==1)
			    count++;
			}
		    }
		  
		  
		}
	    }
	}
    }

  printf("%lld\n",count);
  
}




double fabs(double x)
{
  if(x<0)
    return -x;
  else
    return x;
}
