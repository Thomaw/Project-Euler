#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;

int n[5][2]={{1312,1888},{5248,640},{2624,3776},{5760,3776},{3936,5664}};

int gcd(int a,int b)
{
  if (a==0 || b==0) return a+b;
  if (a>b) {return gcd(b,a%b);} else return gcd(a,b%a); 
}

int main ()
{
  int s1a,s1b,pm,qm,dm,k,a2,a3,a4,a5,siga=0,sigb=0,spoila,spoilb;
  int f[5][2];
  bool go_on;
  int pmax=1,qmax=1;

  for (k=0;k<=5;k++) {siga+=n[k][0];sigb+=n[k][1];};
  for (s1b=36;s1b<=n[0][1];s1b++)
    {
      for (s1a=36;s1a<(qmax*s1b*n[0][0])/(n[0][1]*pmax);s1a++)
      	{
	  pm=s1b*n[0][0];
	  qm=s1a*n[0][1];
	  dm=gcd(pm,qm);
	  pm/=dm;
	  qm/=dm;
	  go_on=true;
	  for (k=1;k<=4;k++)
	    {
	      dm=gcd(pm*n[k][1],qm*n[k][0]);
	      f[k][0]=pm*n[k][1]/dm;
	      f[k][1]=qm*n[k][0]/dm;
	    };
	  for (a2=0;go_on && a2<=min(n[2][0]/f[1][1],n[2][1]/f[1][0]);a2++)
	    {
	      for (a3=0;go_on && a3<=min(n[3][0]/f[2][1],n[3][1]/f[2][0]);a3++)
		{
		  for (a4=0;go_on && a4<=min(n[4][0]/f[3][1],n[4][1]/f[3][0]);a4++)
		    {
		      for (a5=0;go_on && a5<=min(n[5][0]/f[4][1],n[5][1]/f[4][0]);a5++)
			{
			  spoila=s1a+a2*f[1][1]+a3*f[2][1]+a4*f[3][1]+a5*f[4][1];
			  spoilb=s1b+a2*f[1][0]+a3*f[2][0]+a4*f[3][0]+a5*f[4][0];
			  if (spoila*qm*sigb==spoilb*pm*siga)
			    {
			      cout <<pm << "/"<< qm << endl;
			      pmax=pm;qmax=qm;
			      go_on=false;
			    }
			};	  
		      
		    };	  
		  
		};	  
	      
	    };	  
	};
    };
  cout << "Max=" << pmax << "/" << qmax << endl;
  return 0;
}